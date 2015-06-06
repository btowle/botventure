#Sample bot that runs to the goal of default.map
class Player
def do_turn(bot)
  @bot = bot

  #Quit if we've run for longer than 25 turns
  if bot.turn > 25 then
    puts "I'm tired, goodnight. zzzz"
    exit
  end

  get_world_info

  decide_direction

  bot.move! @direction
end

def get_world_info
  @map = @bot.map
  @enemies = @bot.enemies
  @player = @bot.player
end

def decide_direction
  @direction ||= Botventure::DOWN
  @left_moves ||= 0

  node_below = @map.node(@player.position + Botventure::Position.new(0,-1))

  #Move left if there is a wall below us
  if node_below == Botventure::WALL then
    @direction = Botventure::LEFT
  end

  #Move up if we have moved left enough times
  if @direction == Botventure::LEFT && @left_moves == 5 then
    @direction = Botventure::UP
  end

  #Count the number of times we've moved left
  if @direction == Botventure::LEFT then
    @left_moves = @left_moves + 1
  end
end
end
