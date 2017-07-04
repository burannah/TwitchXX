file(GLOB SOURCES *.cpp)


#TODO: For Windows only
foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
   if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
   endif(${flag_var} MATCHES "/MD")
endforeach(flag_var)

set (CMAKE_CXX_STANDARD 14)

add_library(TwitchXX STATIC ${SOURCES})
target_link_libraries(TwitchXX ${LIB_CPPREST})

