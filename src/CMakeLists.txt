include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/src/network/messages)

add_subdirectory(world)
add_subdirectory(network)
add_subdirectory(bot)

set(SERVER_INCLUDES server.cpp)
set(CLIENT_INCLUDES client.cpp)
set(EXTERNAL_LIBRARIES PocoNet PocoFoundation protobuf)
set(LIBRARIES world messages gameconnection network bot)

add_executable(botventure-client ${CLIENT_INCLUDES})
add_dependencies(botventure-client ${LIBRARIES})
target_link_libraries(botventure-client ${LIBRARIES} ${EXTERNAL_LIBRARIES})
add_executable(botventure-server ${SERVER_INCLUDES})
add_dependencies(botventure-server ${LIBRARIES})
target_link_libraries(botventure-server ${LIBRARIES} ${EXTERNAL_LIBRARIES})
