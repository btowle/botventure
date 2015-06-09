add_library(world STATIC map2d.cpp mob.cpp worldmanager.cpp position.cpp)
add_dependencies(world messages roll)
SET_TARGET_PROPERTIES(world PROPERTIES COMPILE_FLAGS "-fPIC")
