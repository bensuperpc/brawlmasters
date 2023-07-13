#ifndef WORLD_OF_CUBE_GAME_BASE_HPP
#define WORLD_OF_CUBE_GAME_BASE_HPP

class game_base {
public:
  virtual ~game_base() = default;
  game_base() = default;
  
  bool is_active = true;
  bool is_visible = true;
};

#endif // WORLD_OF_CUBE_GAME_BASE_HPP