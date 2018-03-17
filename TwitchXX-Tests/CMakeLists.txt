find_package(Boost 1.55 COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package (Threads)
find_package(GTest REQUIRED)
#file(GLOB SOURCES *.cpp)
set (CMAKE_CXX_STANDARD 17)


add_executable(TwitchXX-Tests Clip.t.cpp TwitchXX-Tests.cpp Entitlement.t.cpp Game.t.cpp AppAccessToken.t.cpp UserAccessToken.t.cpp Stream.t.cpp TestConstants.h StreamMetadata.t.cpp User.t.cpp UserFollows.t.cpp Vide.t.cpp)
target_link_libraries(TwitchXX-Tests TwitchXX ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${LIB_CPPREST} ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} -lcpprest)
install(TARGETS TwitchXX-Tests DESTINATION bin)
