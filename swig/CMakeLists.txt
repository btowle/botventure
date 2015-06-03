FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(Ruby)
INCLUDE_DIRECTORIES(${RUBY_INCLUDE_DIRS})

SET_SOURCE_FILES_PROPERTIES(botventure.i PROPERTIES CPLUSPLUS ON)
SET(CMAKE_SWIG_FLAGS "-autorename")
SWIG_ADD_MODULE(botventure ruby botventure.i ../src/bot/robot.cpp ../src/world/map2d.cpp ../src/world/mob.cpp ../src/network/gameserver.cpp ../src/network/gameconnection.cpp)
SET_TARGET_PROPERTIES(botventure PROPERTIES PREFIX "" OUTPUT_NAME "botventure")
SWIG_LINK_LIBRARIES(botventure ${RUBY_LIBRARY} PocoNet protobuf messages network world)
add_dependencies(botventure bot messages network world)
target_compile_features(botventure PUBLIC cxx_range_for)
