#ifndef BRAWL_MASTERS_WORLD_HPP
#define BRAWL_MASTERS_WORLD_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// World of blocks
#include "GameContext.hpp"
#include "gameElementHandler.hpp"

// spdlog
#include "logger/logger_facade.hpp"

#include <stdlib.h>

#define MAX_BUNNIES 500000 // 50K bunnies limit

// Raylib
#include "raylib_interface.hpp"

typedef struct Bunny {
  Vector2 position;
  Vector2 speed;
  Color color;
} Bunny;

class world : public gameElementHandler {
public:
  world(GameContext &game_context_ref);

  ~world();

  void updateGameInput() override;
  void updateGameLogic() override;

  void updateOpenglLogic() override;
  void updateDraw2d() override;
  void updateDraw3d() override;
  void updateDrawInterface() override;

private:
  GameContext &_game_ctx;

  // logger
  std::unique_ptr<logger_decorator> world_logger;

  std::mutex _world_mutex;

  Texture2D texBunny;
  Shader shader;

  Bunny *bunnies;
  int bunniesCount = 0;

  rlRenderBatch batch;
  int bufferLength = 0;
  int buffer = 0;
  bool drawInstanced = false;
};

#endif // BRAWL_MASTERS_HPP