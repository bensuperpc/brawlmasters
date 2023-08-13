#ifndef BRAWL_MASTERS_PLAYER_HPP
#define BRAWL_MASTERS_PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib_interface.hpp"

// World of blocks
#include "GameContext.hpp"
#include "gameElementHandler.hpp"

// spdlog
#include "logger/logger_facade.hpp"

class Player : public gameElementHandler {
public:
  Player(GameContext &game_context_ref);

  ~Player();

  void updateGameInput() override;
  void updateGameLogic() override;

  void updateOpenglLogic() override;
  void updateDraw2d() override;
  void updateDraw3d() override;

  void updateDrawInterface() override;

  Camera2D camera;

private:
  GameContext &_game_ctx;

  // logger
  std::unique_ptr<logger_decorator> player_logger;

  std::unique_ptr<Texture2D> texPlayer;
};

#endif // BRAWL_MASTERS_HPP