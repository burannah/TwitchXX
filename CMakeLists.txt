project(TwitchSpy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Boost 1.55 COMPONENTS system regex date_time)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

set(OpenSSL_libeay_LIBRARY ${OPENSSL_LIBRARIES})
set(OpenSSL_ssleay_LIBRARY ${OPENSSL_LIBRARIES})

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


add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

if(${WIN32})
	set_target_properties(libgtest PROPERTIES
			"IMPORTED_LOCATION" "${gtest_binary_dir}/googlemock/gtest/Release/gtest.lib"
			"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LINS_INIT}"
			)
else()
	set_target_properties(libgtest PROPERTIES
			"IMPORTED_LOCATION" "${gtest_binary_dir}/googlemock/gtest/libgtest.a"
			"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LINS_INIT}"
			)

endif()

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${gtest_binary_dir}/googlemock/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

include_directories(${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} cpprestsdk/Release/include)
link_directories(${Boost_LIBRARY_DIRS})		
set(BUILD_TESTS OFF)
set(BUILD_SAMPLES OFF)
add_subdirectory(cpprestsdk/Release)
set(BUILD_TESTS ON)
		
include_directories("${gtesource_dir}/googletest/include"
		    "${gtest_source_dir}/googletest/include"
                    "${gtest_source_dir}/googlemock/include"
                    "${cpprestsdk_source_dir}/Release/include"
                    "${PROJECT_SOURCE_DIR}/TwitchXX"
                    "${PROJECT_SOURCE_DIR}/TwitchXX-Tests")

add_subdirectory(TwitchXX)

if(BUILD_TESTS)
    message("Building tests!")
    add_subdirectory(TwitchXX-Tests)
endif()

