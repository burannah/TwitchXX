cmake_minimum_required(VERSION 3.0)
project(TwitchSpy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Threads REQUIRED)

include(ExternalProject)

ExternalProject_add(
        gtest
        URL https://github.com/google/googletest/archive/master.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LINS_INIT}"
        )

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include"
                    "${PROJECT_SOURCE_DIR}/TwitchXX"
                    "${PROJECT_SOURCE_DIR}/TwitchXX-Tests")
#Add Casablanka
ExternalProject_add(
        cpprestsdk
        URL https://github.com/Microsoft/cpprestsdk/archive/master.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/cpprestsdk
        #SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/cpprestsdk/Release/
        #SOURCE_SUBDIR /Release
        INSTALL_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/cpprestsdk/Release/CMakeLists.txt
)

ExternalProject_Get_Property(cpprestsdk source_dir binary_dir)

add_library(libcpprestsdk IMPORTED STATIC GLOBAL)
add_dependencies(libcpprestsdk cpprestsdk)

set_target_properties(libcpprestsdk PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/cpprestsdk/libcpprestsdk.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )

include_directories("${source_dir}/Release/include")


add_subdirectory(bin/cpprestsdk/src/cpprestsdk/Release)
add_subdirectory(TwitchXX)
add_subdirectory(TwitchXX-Tests)
