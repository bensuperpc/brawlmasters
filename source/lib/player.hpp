#ifndef BRAWL_MASTERS_PLAYER_HPP
#define BRAWL_MASTERS_PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib_interface.hpp"

// World of blocks
#include "game_context.hpp"
#include "game_element_handler.hpp"

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

  void update_draw_interface() override;

  Camera2D camera;

private:
  game_context &_game_ctx;

  // logger
  std::unique_ptr<logger_decorator> player_logger;

  std::unique_ptr<Texture2D> texPlayer;
};

#endif // BRAWL_MASTERS_HPP