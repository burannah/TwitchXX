#file(GLOB SOURCES *.cpp)

set (CMAKE_CXX_STANDARD 14)
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

add_library(TwitchXX STATIC TwitchDef.h MakeRequest.h MakeRequest.cpp Clip.cpp Clip.h Utility.h Utility.cpp JsonWrapper.h Entitlement.cpp Entitlement.h TwitchException.h Game.cpp Game.h Auth/AuthToken.h Auth/AppAccessToken.cpp Auth/AppAccessToken.h Auth/UserAccessToken.cpp Auth/UserAccessToken.h Stream.cpp Stream.h StreamMetadata.cpp StreamMetadata.h StreamsOptions.h StreamsOptions.cpp StreamType.h StreamType.cpp User.cpp User.h UserType.cpp UserType.h BroadcasterType.cpp BroadcasterType.h UserFollows.cpp UserFollows.h Api.cpp Api.h Video.cpp Video.h VideoOptions.cpp VideoOptions.h VideoPeriodType.cpp VideoPeriodType.h VideoSortType.cpp VideoSortType.h VideoType.cpp VideoType.h)
target_link_libraries(TwitchXX ${LIB_CPPREST})

install(TARGETS TwitchXX DESTINATION lib)
install(FILES Clip.h
        DESTINATION include/TwitchXX)


