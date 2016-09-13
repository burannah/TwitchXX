find_package(Boost 1.55 COMPONENTS system)
find_package(OpenSSL REQUIRED)
file(GLOB SOURCES *.cpp)

add_executable(TwitchXX-Tests ${SOURCES})
target_link_libraries(TwitchXX-Tests TwitchXX libgtest libgmock ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
install(TARGETS TwitchXX-Tests DESTINATION bin)
