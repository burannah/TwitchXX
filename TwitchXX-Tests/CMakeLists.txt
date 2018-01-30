find_package(Boost 1.55 COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package (Threads)
find_package(GTest REQUIRED)
#file(GLOB SOURCES *.cpp)
set (CMAKE_CXX_STANDARD 14)


add_executable(TwitchXX-Tests Clip.t.cpp TwitchXX-Tests.cpp Entitlement.t.cpp Game.t.cpp)
target_link_libraries(TwitchXX-Tests TwitchXX ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${LIB_CPPREST} ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} -lcpprest)
install(TARGETS TwitchXX-Tests DESTINATION bin)
