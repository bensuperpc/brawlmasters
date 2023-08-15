#ifndef BRAWL_MASTERS_GAME_ELEMENT_HANDLER_CLASS_HPP
#define BRAWL_MASTERS_GAME_ELEMENT_HANDLER_CLASS_HPP

#include "GameBase.hpp"

#include <chrono>
#include <string>
#include <mutex>

class gameElementHandler : public GameBase {
public:
  virtual ~gameElementHandler() = default;
  gameElementHandler() = default;

  // Update Game input (Like Keyboard, Mouse, etc)
  virtual void updateGameInput() = 0;
  std::chrono::steady_clock::time_point last_update_game_input;
  std::chrono::milliseconds update_game_input_cooldown = std::chrono::milliseconds(4);

  // Update Game logic (Like physics, etc)
  virtual void updateGameLogic() = 0;
  std::chrono::steady_clock::time_point last_update_game_logic;
  std::chrono::milliseconds update_game_logic_cooldown = std::chrono::milliseconds(30);

  // Update opengl logic (Like Models, Textures, etc)
  virtual void updateOpenglLogic() = 0;
  std::chrono::steady_clock::time_point last_update_opengl_logic;
  std::chrono::milliseconds update_opengl_logic_cooldown = std::chrono::milliseconds(4);

  // Won't need to be scheduled, always called
  // Update draw 3d (Like Models, Textures, etc)
  virtual void updateDraw3d() = 0;
  // Update draw 2d (Like Text, etc)
  virtual void updateDraw2d() = 0;

  // Update draw interface (Like Text, etc)
  virtual void updateDrawInterface() = 0;

  std::mutex _mutex;

  std::string name = "";
};

#endif // BRAWL_MASTERS_GAME_CLASS_HPP