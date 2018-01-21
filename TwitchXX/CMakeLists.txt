#file(GLOB SOURCES *.cpp)

set (CMAKE_CXX_STANDARD 14)

add_library(TwitchXX STATIC MakeRequest.h MakeRequest.cpp Clip.cpp Clip.h Utility.h Utility.cpp JsonWrapper.h)
target_link_libraries(TwitchXX ${LIB_CPPREST})

install(TARGETS TwitchXX DESTINATION lib)
install(FILES Clip.h
        DESTINATION include/TwitchXX)


