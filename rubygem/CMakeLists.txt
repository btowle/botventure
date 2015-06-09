configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/botventure.gemspec.in"
  "${CMAKE_CURRENT_BINARY_DIR}/botventure.gemspec"
)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Rakefile.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Rakefile"
)
set(ROLLDIR ${PROJECT_SOURCE_DIR}/src/roll)
set(BOTDIR ${PROJECT_SOURCE_DIR}/src/bot)
set(NETDIR ${PROJECT_SOURCE_DIR}/src/network)
set(WORLDDIR ${PROJECT_SOURCE_DIR}/src/world)
set(MESSAGEDIR ${CMAKE_BINARY_DIR}/src/network/messages)
set(BOTVENTURE_DIR ${CMAKE_CURRENT_BINARY_DIR}/ext/botventure)
#Copy bin/botventure
file(COPY ${PROJECT_SOURCE_DIR}/src/game/ruby/botventure DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
#Copy data
file(COPY ${PROJECT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#Copy data/bots
file(COPY ${PROJECT_SOURCE_DIR}/src/game/ruby/bots DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

#Glob all sources needed
file(GLOB ROLLSOURCES ${ROLLDIR}/*.hpp ${ROLLDIR}/*.cpp)
file(GLOB BOTSOURCES ${BOTDIR}/*.hpp ${BOTDIR}/*.cpp)
file(GLOB NETSOURCES ${NETDIR}/*.hpp ${NETDIR}/*.cpp)
file(GLOB WORLDSOURCES ${WORLDDIR}/*.hpp ${WORLDDIR}/*.cpp)
file(GLOB MESSAGESOURCES ${MESSAGEDIR}/*.h ${MESSAGEDIR}/*.cc)
#can't glob messages because they don't exist before the build
set(MESSAGESOURCES
      ${MESSAGEDIR}/action.pb.h ${MESSAGEDIR}/action.pb.cc
      ${MESSAGEDIR}/botstatus.pb.h ${MESSAGEDIR}/botstatus.pb.cc
      ${MESSAGEDIR}/enemy.pb.h ${MESSAGEDIR}/enemy.pb.cc
      ${MESSAGEDIR}/game.pb.h ${MESSAGEDIR}/game.pb.cc
      ${MESSAGEDIR}/handshake.pb.h ${MESSAGEDIR}/handshake.pb.cc
      ${MESSAGEDIR}/header.pb.h ${MESSAGEDIR}/header.pb.cc
      ${MESSAGEDIR}/map.pb.h ${MESSAGEDIR}/map.pb.cc
      ${MESSAGEDIR}/sensor.pb.h ${MESSAGEDIR}/sensor.pb.cc)

#Copy this directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})

#Remove .in files we've copied
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/botventure.gemspec.in)
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/Rakefile.in)

add_custom_target(rubygem ALL)

add_custom_command(TARGET rubygem
  COMMAND ${CMAKE_COMMAND} -E
    copy ${CMAKE_BINARY_DIR}/swig/botventureRUBY_wrap.cxx ${BOTVENTURE_DIR}/botventure.cpp)

foreach(S IN LISTS MESSAGESOURCES BOTSOURCES NETSOURCES WORLDSOURCES ROLLSOURCES)
add_custom_command(TARGET rubygem
  COMMAND ${CMAKE_COMMAND} -E
    copy ${S} ${BOTVENTURE_DIR})
endforeach(S)

add_dependencies(rubygem botventure messages)
