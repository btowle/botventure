# Building
## Build Dependencies
Google's Protocol Buffers >= 2.5.0: https://github.com/google/protobuf

POCO C++ Libraries >= 1.3.6: http://pocoproject.org/

CMake >= 2.8.12: http://www.cmake.org/

SWIG >= 2.0.11: http://www.swig.org/

C++11 compatible compiler

Ruby 2.2.2

# Playing
## Ruby:
### Setup:
#### With Vagrant:
`host$ vagrant up`

`host$ vagrant ssh`

`vagrant$ botventure --init`

`Add code to player.rb`

`vagrant$ botventure`

### Bot Methods:
`#turn`

`#map`

`#enemies`

`#player`

`#move!(direction)`

### Mob Methods:
`#is_walkable?(terrain)`

`#health`

`#health=`

`#position`

`#position=`


### Map Methods:
`#to_string(enemies, player)`

`#to_s`

`#width`

`#height`

`#nodes`

`#node(index)`

`#node(x, y)`

`#node(position)`

`#is_in_bounds?(position)`


### Position Methods:
`#==`

`#+`

`#-`

`#x`

`#x=`

`#y`

`#y=`

`#to_s`


### Botventure Constants:
### Directions:
`Botventure::NODIRECTION`

`Botventure::UP`

`Botventure::RIGHT`

`Botventure::DOWN`

`Botventure::LEFT`


### Terrain:
`Botventure::UNKNOWN`

`Botventure::GROUND`

`Botventure::WALL`

`Botventure::GOAL`
