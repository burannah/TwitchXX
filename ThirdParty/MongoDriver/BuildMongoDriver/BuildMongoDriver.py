import os, sys,subprocess

#compiler_type = "Visual Studio 14 Win64"
compiler_type = "Visual Studio 14 2015"
compiler_name = "C:/Program Files (x86)/MSBuild/14.0/Bin/MSBuild.exe"

if sys.platform.startswith('win'):
    shell = True
else:
    shell = False


def is_exe(fpath):
    return os.path.isfile(fpath) and os.access(fpath, os.X_OK)

def which(program):
    if not program.endswith('.exe') and shell:
        program = program + '.exe'
    fpath, fname = os.path.split(program)
    if fpath:
        if is_exe(program):
            return program
    else:
        for path in os.environ['PATH'].split(os.pathsep):
            path = path.strip('"')
            exe_file = os.path.join(path,program)
            if is_exe(exe_file):
                return exe_file
    return None

if __name__ == "__main__":
    cmake_exe = which('cmake')
    if not cmake_exe:
        print("Unable to find cmake!")
        exit(1)
    build_exe = which(compiler_name)
    if not build_exe:
        print("Unable to find build program " + compiler_name)
        exit(1)
    mongo_dir = os.path.abspath(os.path.join(os.getcwd(),os.pardir))
    if not mongo_dir.endswith("MongoDriver"):
        print("Must be runned from ThirdParty/MongoDriver dir!")
        exit(1);
    #Check build dir exist
    build_dir = os.path.join(mongo_dir,'mongo-driver-build')
    if not (os.path.exists(build_dir) and os.path.isdir(build_dir)):
        os.makedirs(build_dir)
        print("{0} has been created".format(build_dir))
    else:
        print("{0} already exsist".format(build_dir))
    #Build Mongo C Driver
    #Build libbson
    mongo_c_driver_dir = os.path.join(mongo_dir,'mongo-c-driver')
    libbson_dir = os.path.join(mongo_c_driver_dir,'src','libbson')
    command_line = [cmake_exe,'-G',compiler_type,"-DCMAKE_BUILD_TYPE=Release",'-DCMAKE_INSTALL_PREFIX='+build_dir]
    os.chdir(libbson_dir)
    ret_code = subprocess.check_call(command_line,stderr=subprocess.STDOUT, shell=shell)
    command_line = [build_exe,'ALL_BUILD.vcxproj']
    ret_code = subprocess.check_call(command_line,stderr=subprocess.STDOUT, shell=shell)
    command_line = [build_exe,'INSTALL.vcxproj']
    ret_code = subprocess.check_call(command_line,stderr=subprocess.STDOUT, shell=shell)
    #Build c driver
    os.chdir(mongo_c_driver_dir)
    command_line = [cmake_exe,'-G',compiler_type,"-DCMAKE_BUILD_TYPE=Release","-DCMAKE_INSTALL_PREFIX="+build_dir,"-DBSON_ROOT_DIR="+build_dir]
    ret_code = subprocess.check_call(command_line,stderr=subprocess.STDOUT, shell=shell)
    command_line = [build_exe,'ALL_BUILD.vcxproj']
    ret_code = subprocess.check_call(command_line,stderr=subprocess.STDOUT, shell=shell)
    command_line = [build_exe,'INSTALL.vcxproj']
    ret_code = subprocess.check_call(command_line,stderr=subprocess.STDOUT, shell=shell)
    #Build c++ driver
    mongo_cxx_driver_dir = os.path.join(mongo_dir,'mongo-cxx-driver')
    os.chdir(mongo_cxx_driver_dir)
    command_line = [cmake_exe,'-G',compiler_type,"-DCMAKE_BUILD_TYPE=Release","-DCMAKE_INSTALL_PREFIX="+build_dir,"-DLIBBSON_DIR="+build_dir,"-DLIBMONGOC_DIR="+build_dir]
    ret_code = subprocess.check_call(command_line,stderr=subprocess.STDOUT, shell=shell)
    command_line = [build_exe,'ALL_BUILD.vcxproj']
    ret_code = subprocess.check_call(command_line,stderr=subprocess.STDOUT, shell=shell)
    command_line = [build_exe,'INSTALL.vcxproj']
    ret_code = subprocess.check_call(command_line,stderr=subprocess.STDOUT, shell=shell)
