cmake_minimum_required(VERSION 3.6)
project(TwitchSpy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Use custom Find-.cmake path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Boost 1.55 COMPONENTS system regex date_time)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
set(CPP_REST_FOUND False)
set(CPP_REST_FIND_REQUIRED True)
find_package(cpprestsdk REQUIRED) # populates CPP_REST_INCLUDE_DIR and CPP_REST_LIBRARY

set(LIB_CPPREST optimized ${CPP_REST_LIBRARY} debug ${CPP_REST_LIBRARY_DEBUG})

set(OpenSSL_libeay_LIBRARY ${OPENSSL_LIBRARIES})
set(OpenSSL_ssleay_LIBRARY ${OPENSSL_LIBRARIES})

option(BUILD_TESTS "Build tests." ON)

include(ExternalProject)

ExternalProject_add(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
		CMAKE_ARGS -DBUILD_SHARED_LIBS=ON
        UPDATE_DISCONNECTED 1
        INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

set(gtest_source_dir ${source_dir})
set(gtest_binary_dir ${binary_dir})

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)


if(MSVC)
	add_library(libgtestd IMPORTED STATIC GLOBAL)
	add_dependencies(libgtestd gtest)

	set_target_properties(libgtest PROPERTIES
			"IMPORTED_LOCATION" "${gtest_binary_dir}/googlemock/gtest/Release/gtest.lib"
			"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LINS_INIT}"
			)

	set_target_properties(libgtestd PROPERTIES
			"IMPORTED_LOCATION" "${gtest_binary_dir}/googlemock/gtest/Debug/gtest.lib"
			"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LINS_INIT}"
			)
	set(LIB_GTEST optimized libgtest debug libgtestd) 

else()
	set_target_properties(libgtest PROPERTIES
			"IMPORTED_LOCATION" "${gtest_binary_dir}/googlemock/gtest/libgtest.a"
			"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LINS_INIT}"
			)
	set(LIB_GTEST libgtest)

endif()

#add_library(libgmock IMPORTED STATIC GLOBAL)
#add_dependencies(libgmock gtest)

#set_target_properties(libgmock PROPERTIES
#        "IMPORTED_LOCATION" "${gtest_binary_dir}/googlemock/libgmock.a"
#        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

include_directories(${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} "${CPP_REST_INCLUDE_DIR}/..")
link_directories(${Boost_LIBRARY_DIRS})
		
include_directories("${gtest_source_dir}/googletest/include"
                    "${gtest_source_dir}/googlemock/include"
                    "${PROJECT_SOURCE_DIR}/TwitchXX"
                    "${PROJECT_SOURCE_DIR}/TwitchXX-Tests")


if(MSVC)                        # Microsoft uses magic to handle this
    SET(LINK FLAGS "")
else()
    SET(LINK_FLAGS "-lboost_system -lssl -lcrypto")
endif()


SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}" )


add_subdirectory(TwitchXX)

if(BUILD_TESTS)
    message("Building tests!")
    add_subdirectory(TwitchXX-Tests)
endif()

