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

file(GLOB_RECURSE SOURCES *.cpp *.h)

add_library(TwitchXX STATIC ${SOURCES})
target_link_libraries(TwitchXX ${LIB_CPPREST})

install(TARGETS TwitchXX DESTINATION lib)
install(FILES Clip.h Api.h Entitlement.h Game.h Logger.h Request.h RequestOnce.h RequestWait.h Stream.h
              StreamMetadata.h StreamsOptions.h StreamType.h TwitchDef.h TwitchException.h User.h
              UserFollows.h UserType.h Utility.h Video.h VideoOptions.h PeriodType.h VideoSortType.h
              VideoType.h ClipOptions.h BitsLeaderboardEntry.h BitsLeaderboardOptions.h Direction.h
        DESTINATION include/TwitchXX)
install(FILES v5/Action.h v5/Channel.h v5/User.h v5/UserFollows.h v5/Subscription.h v5/Team.h
        DESTINATION include/TwitchXX/v5)

install(FILES Auth/AuthToken.h Auth/AppAccessToken.h Auth/UserAccessToken.h DESTINATION include/TwitchXX/Auth)


