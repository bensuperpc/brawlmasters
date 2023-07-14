#ifndef WORLD_OF_CUBE_WORLD_HPP
#define WORLD_OF_CUBE_WORLD_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>



// World of blocks
#include "game_element_handler.hpp"
#include "game_context.hpp"

// spdlog
#include "logger/logger_facade.hpp"

#include <stdlib.h>


#define MAX_BUNNIES        500000    // 50K bunnies limit
#define MAX_BATCH_ELEMENTS  16384
#define RL_DEFAULT_BATCH_BUFFER_ELEMENTS    8192

#include "rlgl.h"
// Raylib
#include "raylib.h"

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

private:
  game_context &_game_context_ref;

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

#endif // WORLD_OF_CUBE_WORLD_HPP