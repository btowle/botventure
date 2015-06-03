#Sample bot that runs to the goal of default.map
class Player
def do_turn(bot)
  #Print the turn number
  puts bot.get_map.get_width
  puts "Turn: #{bot.get_turn}"

  #Quit if we've run for longer than 25 turns
  if bot.get_turn > 25 then
    puts "I'm tired, goodnight. zzzz"
    exit
  end

  #Get information about the world
  map = bot.get_map
  enemies = bot.get_enemies
  player = bot.get_player

  #Print the map
  puts map.to_string(enemies, player)

  @direction ||= Botventure::DOWN
  @left_moves ||= 0

  #Move
  if !bot.move @direction then
    #Go left if we hit the bottom wall
    if @direction == Botventure::DOWN then
      puts "going left"
      @direction = Botventure::LEFT
    end
  else
    #Go up once we've gone left 5 times
    if @direction == Botventure::LEFT then
      @left_moves += 1
    end
    if @left_moves == 5 then
      @direction = Botventure::UP
    end
  end
end
end
