#ifndef BRAWL_MASTERS_PLAYER_HPP
#define BRAWL_MASTERS_PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib_interface.hpp"

// World of blocks
#include "game_element_handler.hpp"
#include "game_context.hpp"

// spdlog
#include "logger/logger_facade.hpp"

class player : public game_element_handler {
public:
  player(game_context &game_context_ref);

  ~player();

  void update_game_input() override;
  void update_game_logic() override;

  void update_opengl_logic() override;
  void update_draw2d() override;
  void update_draw3d() override;

  Vector3 get_position() const;

  Camera camera;

private:
  game_context &_game_context_ref;

  // logger
  std::unique_ptr<logger_decorator> player_logger;
};

#endif // BRAWL_MASTERS_HPP