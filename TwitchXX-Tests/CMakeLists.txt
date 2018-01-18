find_package(Boost 1.55 COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package (Threads)
find_package(GTest REQUIRED)
file(GLOB SOURCES *.cpp)
set (CMAKE_CXX_STANDARD 14)


#TODO: For Windows only
foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
   if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
   endif(${flag_var} MATCHES "/MD")
endforeach(flag_var)

add_executable(TwitchXX-Tests ${SOURCES} ClipTest.cpp)
target_link_libraries(TwitchXX-Tests TwitchXX ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${LIB_CPPREST} ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} -lcpprest)
install(TARGETS TwitchXX-Tests DESTINATION bin)
