file(GLOB SOURCES *.cpp)

add_library(TwitchXX ${SOURCES})
target_link_libraries(TwitchXX libcpprest)