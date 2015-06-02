add_library(bot robot.cpp)
add_dependencies(bot world network)
target_link_libraries(bot network)
target_compile_features(bot PUBLIC cxx_range_for)
