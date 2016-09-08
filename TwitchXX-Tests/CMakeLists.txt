file(GLOB SOURCES *.cpp)

add_executable(TwitchXX-Tests ${SOURCES})
target_link_libraries(TwitchXX-Tests TwitchXX libgtest libgmock)
install(TARGETS TwitchXX-Tests DESTINATION bin)
