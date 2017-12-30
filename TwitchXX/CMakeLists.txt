file(GLOB SOURCES *.cpp)

set (CMAKE_CXX_STANDARD 14)

add_library(TwitchXX STATIC ${SOURCES} TwitchUser.cpp)
target_link_libraries(TwitchXX ${LIB_CPPREST})

install(TARGETS TwitchXX DESTINATION lib)
install(FILES TwitchXX.h Property.h TwitchGame.h TwitchDef.h TwitchStream.h TwitchChannel.h TwitchFeaturedStream.h
              TwitchPost.h TwitchUser.h TwitchFollower.h TwitchIngest.h TwitchTeam.h TwitchVideo.h AuthToken.h Logger.h
        DESTINATION include/TwitchXX)


