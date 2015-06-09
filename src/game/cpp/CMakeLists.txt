set(SERVER_INCLUDES server.cpp)
set(CLIENT_INCLUDES client.cpp)
set(EXTERNAL_LIBRARIES PocoFoundation PocoNet protobuf)
set(LIBRARIES world network messages bot roll)

add_executable(botventure-client ${CLIENT_INCLUDES})
add_dependencies(botventure-client ${LIBRARIES})
target_link_libraries(botventure-client ${LIBRARIES} ${EXTERNAL_LIBRARIES})

add_executable(botventure-server ${SERVER_INCLUDES})
add_dependencies(botventure-server ${LIBRARIES})
target_link_libraries(botventure-server ${LIBRARIES} ${EXTERNAL_LIBRARIES} ${LIBRARIES})
