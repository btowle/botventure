FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(Ruby)
INCLUDE_DIRECTORIES(${RUBY_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/src/network/messages)

SET_SOURCE_FILES_PROPERTIES(botventure.i PROPERTIES CPLUSPLUS ON SWIG_FLAGS "-DGOOGLE_PROTOBUF_VERSION=3000000")
SET(CMAKE_SWIG_FLAGS "-autorename")
SWIG_ADD_MODULE(botventure ruby botventure.i ../src/bot/robot.cpp ../src/world/position.cpp ../src/world/mob.cpp ../src/world/map2d.cpp ../src/network/gameconnection.cpp ../src/network/gameserver.cpp)
SET_TARGET_PROPERTIES(botventure PROPERTIES PREFIX "" OUTPUT_NAME "botventure" LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/ruby")
SWIG_LINK_LIBRARIES(botventure ${RUBY_LIBRARY} PocoNet protobuf bot messages network world)
add_dependencies(botventure bot messages network world)
