cmake_minimum_required(VERSION 3.0)
project(TwitchSpy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Threads REQUIRED)

option(BUILD_TESTS "Build tests." ON)

include(ExternalProject)

ExternalProject_add(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        UPDATE_DISCONNECTED 1
        INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

set(gtest_source_dir ${source_dir})
set(gtest_binary_dir ${binary_dir})

ExternalProject_add(
        cpprest
        GIT_REPOSITORY https://github.com/Microsoft/cpprestsdk.git
        GIT_TAG master
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/cpprest
        SOURCE_SUBDIR Release
        CMAKE_ARGS -DBUILD_TESTS=OFF -DBUILD_SAMPLES=OFF
        INSTALL_COMMAND ""
)

ExternalProject_Get_Property(cpprest source_dir binary_dir)
set(cpprestsdk_source_dir ${source_dir})
set(cpprestsdk_binary_dir ${binary_dir})


add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${gtest_binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LINS_INIT}"
        )

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${gtest_binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

add_library(libcpprest IMPORTED SHARED GLOBAL)
add_dependencies(libcpprest cpprest)

set_target_properties(libcpprest PROPERTIES
        "IMPORTED_LOCATION" "${cpprestsdk_binary_dir}/Binaries/libcpprest.so"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LINS_INIT}"
        )


include_directories("${gtesource_dir}/googletest/include"
                    "${gtest_source_dir}/googlemock/include"
                    "${cpprestsdk_source_dir}/Release/include"
                    "${PROJECT_SOURCE_DIR}/TwitchXX"
                    "${PROJECT_SOURCE_DIR}/TwitchXX-Tests")

add_subdirectory(TwitchXX)

if(BUILD_TESTS)
    message("Building tests!")
    add_subdirectory(TwitchXX-Tests)
endif()

