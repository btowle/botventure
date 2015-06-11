# Building
## Build Dependencies (Without Vagrant)
* Google's Protocol Buffers >= 2.5.0: https://github.com/google/protobuf
* POCO C++ Libraries >= 1.3.6: http://pocoproject.org/
* CMake >= 2.8.12: http://www.cmake.org/
* SWIG >= 2.0.11: http://www.swig.org/
* C++11 compatible compiler
* Ruby 2.2.2

## Local Gem Installation with Vagrant
* locally install poco and protobuf
  * `brew install poco protobuf` on OSX
  * `sudo apt-get install libpoco-dev libprotobuf-dev` in Ubuntu
* `vagrant up`
* `gem install build/rubygem/pkg/botventure\*.gem`

## Playing
* In a directory you want to play in: `botventure --init`
* edit player.rb
* `botventure`

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
`::Up`
`::Right`
`::Down`
`::Left`

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
