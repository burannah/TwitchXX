#file(GLOB SOURCES *.cpp)

set (CMAKE_CXX_STANDARD 17)
option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    #add_definitions(-D_DEBUG)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

set(SOURCES
        Api.cpp
        Api.h
        BitsLeaderboardEntry.cpp
        BitsLeaderboardEntry.h
        BitsLeaderboardOptions.cpp
        BitsLeaderboardOptions.h
        BroadcasterType.cpp
        BroadcasterType.h
        Clip.cpp
        Clip.h
        ClipOptions.cpp
        ClipOptions.h
        CMakeLists.txt
        Direction.cpp
        Direction.h
        Doxyfile
        Entitlement.cpp
        Entitlement.h
        Game.cpp
        Game.h
        JsonWrapper.h
        Log.cpp
        Log.h
        Logger.cpp
        Logger.h
        MakeRequest_Impl.cpp
        MakeRequest_Impl.h
        PeriodType.cpp
        PeriodType.h
        Request.cpp
        Request.h
        RequestOnce.cpp
        RequestOnce.h
        RequestParams.cpp
        RequestParams.h
        RequestWait.cpp
        RequestWait.h
        Stream.cpp
        Stream.h
        StreamMetadata.cpp
        StreamMetadata.h
        StreamsOptions.cpp
        StreamsOptions.h
        StreamType.cpp
        StreamType.h
        TwitchDef.h
        TwitchException.h
        User.cpp
        User.h
        UserFollows.cpp
        UserFollows.h
        UserType.cpp
        UserType.h
        Utility.cpp
        Utility.h
        UtilsInternal.cpp
        UtilsInternal.h
        Video.cpp
        Video.h
        VideoOptions.cpp
        VideoOptions.h
        VideoSortType.cpp
        VideoSortType.h
        VideoType.cpp
        VideoType.h
        v5/Action.cpp
        v5/Action.h
        v5/Channel.cpp
        v5/Channel.h
        v5/Commercial.cpp
        v5/Commercial.h
        v5/Create.h
        v5/Subscription.cpp
        v5/Subscription.h
        v5/Team.cpp
        v5/Team.h
        v5/User.cpp
        v5/User.h
        v5/UserFollows.cpp
        v5/UserFollows.h
        v5/Video.cpp
        v5/Video.h
        Auth/AppAccessToken.cpp
        Auth/AppAccessToken.h
        Auth/AuthToken.h
        Auth/UserAccessToken.cpp
        Auth/UserAccessToken.h)

add_library(TwitchXX STATIC ${SOURCES})
target_link_libraries(TwitchXX ${LIB_CPPREST})

target_include_directories(TwitchXX PUBLIC
        .
        v5
        Auth
        )

install(TARGETS TwitchXX DESTINATION lib)
install(FILES Clip.h Api.h Entitlement.h Game.h Logger.h Request.h RequestOnce.h RequestWait.h Stream.h
              StreamMetadata.h StreamsOptions.h StreamType.h TwitchDef.h TwitchException.h User.h
              UserFollows.h UserType.h Utility.h Video.h VideoOptions.h PeriodType.h VideoSortType.h
              VideoType.h ClipOptions.h BitsLeaderboardEntry.h BitsLeaderboardOptions.h Direction.h
        DESTINATION include/TwitchXX)
install(FILES v5/Action.h v5/Channel.h v5/User.h v5/UserFollows.h v5/Subscription.h v5/Team.h v5/Video.h v5/Commercial.h
        DESTINATION include/TwitchXX/v5)

install(FILES Auth/AuthToken.h Auth/AppAccessToken.h Auth/UserAccessToken.h DESTINATION include/TwitchXX/Auth)


