add_library(world map2d.cpp mob.cpp worldmanager.cpp position.cpp)
add_dependencies(world messages)
target_compile_features(world PUBLIC cxx_range_for)
SET_TARGET_PROPERTIES(world PROPERTIES COMPILE_FLAGS "-fPIC")
