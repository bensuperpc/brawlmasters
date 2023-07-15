#ifndef BRAWL_MASTERS_GAME_ELEMENT_HANDLER_CLASS_HPP
#define BRAWL_MASTERS_GAME_ELEMENT_HANDLER_CLASS_HPP

#include "game_base.hpp"

#include <chrono>
#include <string>

class game_element_handler : public game_base {
public:
  virtual ~game_element_handler() = default;
  game_element_handler() = default;

  // Update game input (Like Keyboard, Mouse, etc)
  virtual void update_game_input() = 0;
  std::chrono::steady_clock::time_point last_update_game_input;
  std::chrono::milliseconds update_game_input_cooldown = std::chrono::milliseconds(2);

  // Update game logic (Like physics, etc)
  virtual void update_game_logic() = 0;
  std::chrono::steady_clock::time_point last_update_game_logic;
  std::chrono::milliseconds update_game_logic_cooldown = std::chrono::milliseconds(30);

  // Update opengl logic (Like Models, Textures, etc)
  virtual void update_opengl_logic() = 0;
  std::chrono::steady_clock::time_point last_update_opengl_logic;
  std::chrono::milliseconds update_opengl_logic_cooldown = std::chrono::milliseconds(4);

  // Won't need to be scheduled, always called
  // Update draw 3d (Like Models, Textures, etc)
  virtual void update_draw3d() = 0;
  // Update draw 2d (Like Text, etc)
  virtual void update_draw2d() = 0;

  // Update draw interface (Like Text, etc)
  virtual void update_draw_interface() = 0;

  std::string name = "";
};

#endif // BRAWL_MASTERS_GAME_CLASS_HPP