cmake_minimum_required(VERSION 3.5)
project(TwitchXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost 1.55 COMPONENTS system regex date_time)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
set(CPP_REST_FOUND False)
set(CPP_REST_FIND_REQUIRED True)

set(OpenSSL_libeay_LIBRARY ${OPENSSL_LIBRARIES})
set(OpenSSL_ssleay_LIBRARY ${OPENSSL_LIBRARIES})

option(BUILD_TESTS "Build tests." ON)

add_definitions(-D_TURN_OFF_PLATFORM_STRING)
include_directories(${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} "${CPP_REST_INCLUDE_DIR}/..")

add_subdirectory(TwitchXX)

if(BUILD_TESTS)
    message("Building tests!")
    macro(install)
    endmacro()
    add_subdirectory(TwitchXX-Tests)
    macro(install)
        _install(${ARGN})
    endmacro()
endif()

