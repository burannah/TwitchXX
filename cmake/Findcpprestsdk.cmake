IF(UNIX)
    FIND_PATH(CPP_REST_INCLUDE_DIR http_client.h
      "$ENV{LIB_DIR}/include"
      "$ENV{LIB_DIR}/include/cpprest"
            "/usr/local/include/cpprest"
      "${CMAKE_SOURCE_DIR}/include"
      "${CMAKE_SOURCE_DIR}/include/cpprest"
      #mingw
      c:/msys/local/include
      NO_DEFAULT_PATH
      )

    SET(CMAKE_FIND_LIBRARY_PREFIXES "" "lib")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a" ".lib")
    FIND_LIBRARY(CPP_REST_LIBRARY NAMES cpprest PATHS
      $ENV{LIB}
      "/usr/lib"
      "$ENV{LIB_DIR}/lib"
      "${CMAKE_SOURCE_DIR}/lib"
            "/usr/local/lib"
      #mingw
      c:/msys/local/lib
      NO_DEFAULT_PATH
      )

    SET(CPP_REST_LIBRARY_DEBUG True)
ELSE()
    SET(CPP_REST_DIR "$ENV{CPP_REST_DIR}")
    set(CPP_REST_HEADERS_DIR "${CPP_REST_DIR}\\include\\cpprest")
    FIND_PATH(CPP_REST_INCLUDE_DIR http_client.h
        "${CPP_REST_HEADERS_DIR}"
	)

    set(CPP_REST_LIBS_DIR "${CPP_REST_DIR}/lib")
    FILE(GLOB CPP_REST_LIBRARY NAMES
        "${CPP_REST_LIBS_DIR}/cpprest*.lib"
	#"${CPP_REST_LIBS_DIR}/libcpprest*.lib"
        #"${CPP_REST_LIBS_DIR}/cpprest*.dll"
        )

    #set(CPP_REST_LIBS_DIR "${CPP_REST_DIR}/Binaries/Win32/Debug")
    #FILE(GLOB CPP_REST_LIBRARY_DEBUG NAMES
    #    "${CPP_REST_LIBS_DIR}/cpprest*.lib"
	#"${CPP_REST_LIBS_DIR}/libcpprest*.lib"
        #"${CPP_REST_LIBS_DIR}/cpprest*.dll"
    #    )
ENDIF()


#IF (CPP_REST_INCLUDE_DIR AND CPP_REST_LIBRARY AND CPP_REST_LIBRARY_DEBUG)
IF (CPP_REST_INCLUDE_DIR AND CPP_REST_LIBRARY)
    SET(CPP_REST_FOUND TRUE)
#ELSE(CPP_REST_INCLUDE_DIR AND CPP_REST_LIBRARY AND CPP_REST_LIBRARY_DEBUG)
ELSE(CPP_REST_INCLUDE_DIR AND CPP_REST_LIBRARY)
	IF(NOT CPP_REST_INCLUDE_DIR)
		MESSAGE("Unable to find CPPRESTSDK include dir ${CPP_REST_HEADERS_DIR}")
	ENDIF()
	IF(NOT CPP_REST_LIBRARY)
		MESSAGE("Unable to find CPPRESTSDK library file")
	ENDIF()
	#IF(NOT CPP_REST_LIBRARY_DEBUG)
	#	MESSAGE("Unable to find CPPRESTSDK debug library file")
	#ENDIF()
#ENDIF (CPP_REST_INCLUDE_DIR AND CPP_REST_LIBRARY AND CPP_REST_LIBRARY_DEBUG)
ENDIF (CPP_REST_INCLUDE_DIR AND CPP_REST_LIBRARY)

IF (CPP_REST_FOUND)

   IF (NOT CPP_REST_FIND_QUIETLY)
       MESSAGE(STATUS "Found C++ REST: ${CPP_REST_LIBRARY}")
   ENDIF (NOT CPP_REST_FIND_QUIETLY)

ELSE (CPP_REST_FOUND)
    IF (CPP_REST_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find C++ REST")
    ENDIF (CPP_REST_FIND_REQUIRED)
ENDIF (CPP_REST_FOUND)