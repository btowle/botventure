add_subdirectory(messages)
add_library(gameconnection gameconnection.cpp)
target_link_libraries(gameconnection map2d)
