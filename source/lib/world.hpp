#ifndef BRAWL_MASTERS_WORLD_HPP
#define BRAWL_MASTERS_WORLD_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// World of blocks
#include "game_context.hpp"
#include "game_element_handler.hpp"

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

class world : public game_element_handler {
public:
  world(game_context &game_context_ref);

  ~world();

  void update_game_input() override;
  void update_game_logic() override;

  void update_opengl_logic() override;
  void update_draw2d() override;
  void update_draw3d() override;
  void update_draw_interface() override;

private:
  game_context &_game_ctx;

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