add_library(bot STATIC robot.cpp)
add_dependencies(bot world network)
target_link_libraries(bot network)
