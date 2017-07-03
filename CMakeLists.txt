cmake_minimum_required(VERSION 3.6)
project(TwitchSpy)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Use custom Find-.cmake path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Boost 1.55 COMPONENTS system regex date_time)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
set(CPP_REST_FOUND False)
set(CPP_REST_FIND_REQUIRED True)
find_package(cpprestsdk REQUIRED) # populates CPP_REST_INCLUDE_DIR and CPP_REST_LIBRARY

set(OpenSSL_libeay_LIBRARY ${OPENSSL_LIBRARIES})
set(OpenSSL_ssleay_LIBRARY ${OPENSSL_LIBRARIES})

option(BUILD_TESTS "Build tests." ON)

include(ExternalProject)

if(MSVC)
	#set(LIB_CPPREST optimized ${CPP_REST_LIBRARY} debug ${CPP_REST_LIBRARY_DEBUG})
	set(LIB_CPPREST ${CPP_REST_LIBRARY})
else()
	set(LIB_CPPREST ${CPP_REST_LIBRARY})
endif()

include_directories(${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} "${CPP_REST_INCLUDE_DIR}/..")
link_directories(${Boost_LIBRARY_DIRS})
		
include_directories("${PROJECT_SOURCE_DIR}/TwitchXX"
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

