#include "world.hpp"

world::world(game_context &game_context_ref) : _game_ctx(game_context_ref) {
  texBunny = LoadTexture("../asset/wabbit_alpha.png");
  shader = LoadShader("../asset/bunnymark_instanced.vs", "../asset/bunnymark_instanced.fs");
  bunnies = (Bunny *)RL_CALLOC(MAX_BUNNIES, sizeof(Bunny));
  bunniesCount = 0;

  // Configure instanced buffer
  // -------------------------
  batch = rlLoadRenderBatch(1, 1);
  // batch.instances = bunniesCount;
  batch.instances = bunniesCount;

  rlEnableVertexArray(batch.vertexBuffer[0].vaoId);
  bufferLength = MAX_BUNNIES;
  buffer = rlLoadVertexBuffer(bunnies, bufferLength * sizeof(Bunny), true);

  // Shader attribute locations
  int positionAttrib = rlGetLocationAttrib(shader.id, "bunnyPosition");
  int colorAttrib = rlGetLocationAttrib(shader.id, "bunnyColor");

  // instanced bunny positions(2 x float = 2 x GL_FLOAT)
  rlEnableVertexAttribute(positionAttrib);
  rlSetVertexAttribute(positionAttrib, 2, RL_FLOAT, false, sizeof(Bunny), (void *)0);
  rlSetVertexAttributeDivisor(positionAttrib, 1);

  // instanced bunny colors(4 x unsigned char = 4 x GL_UNSIGNED_BYTE)
  rlEnableVertexAttribute(colorAttrib);
  rlSetVertexAttribute(colorAttrib, 4, RL_UNSIGNED_BYTE, true, sizeof(Bunny), (void *)offsetof(Bunny, color));
  rlSetVertexAttributeDivisor(colorAttrib, 1);

  rlDisableVertexArray();
}

world::~world() {
  RL_FREE(bunnies);

  rlUnloadVertexBuffer(buffer);
  rlUnloadRenderBatch(batch);
  UnloadTexture(texBunny);
  UnloadShader(shader);
}

void world::update_game_input() {
  if (IsKeyPressed(KEY_I)) {
    this->drawInstanced = !this->drawInstanced;
  }

  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    // Create more bunnies
    for (int i = 0; i < 10000; i++) {
      if (bunniesCount < MAX_BUNNIES) {

        // Add bunny only if is inside the screen limits
        if (_game_ctx.mouse_position_in_world.x < 15.0f || _game_ctx.mouse_position_in_world.x > _game_ctx.screen_width - 15.0f
            || _game_ctx.mouse_position_in_world.y < 15.0f || _game_ctx.mouse_position_in_world.y > _game_ctx.screen_height - 15.0f) {
          continue;
        }
        bunnies[bunniesCount].position = _game_ctx.mouse_position_in_world;
        bunnies[bunniesCount].speed.x = (float)GetRandomValue(-350, 350) / 60.0f;
        bunnies[bunniesCount].speed.y = (float)GetRandomValue(-350, 350) / 60.0f;
        bunnies[bunniesCount].color = (Color){GetRandomValue(50, 240), GetRandomValue(80, 240), GetRandomValue(100, 240), 255};
        bunniesCount++;
        batch.instances = bunniesCount;
      }
    }
  }
}

void world::update_game_logic() {
  std::lock_guard<std::mutex> lock(_world_mutex);
  // #pragma omp parallel for schedule(auto)
  for (int i = 0; i < bunniesCount; i++) {
    bunnies[i].position.x += bunnies[i].speed.x;
    bunnies[i].position.y += bunnies[i].speed.y;

    if (((bunnies[i].position.x + texBunny.width / 2) > GetScreenWidth()) || ((bunnies[i].position.x + texBunny.width / 2) < 0))
      bunnies[i].speed.x *= -1;
    if (((bunnies[i].position.y + texBunny.height / 2) > GetScreenHeight()) || ((bunnies[i].position.y + texBunny.height / 2 - 40) < 0))
      bunnies[i].speed.y *= -1;
  }
}

void world::update_opengl_logic() {}

void world::update_draw2d() {
  std::lock_guard<std::mutex> lock(_world_mutex);
  // Re-upload bunnies array every frame to apply movement
  int length = std::min(bunniesCount, bufferLength);
  rlUpdateVertexBuffer(buffer, bunnies, length * sizeof(Bunny), 0);

  if (drawInstanced) {
    BeginShaderMode(shader);

    rlSetRenderBatchActive(&batch);
    DrawTexture(texBunny, 0, 0, WHITE);
    rlDrawRenderBatchActive();
    rlSetRenderBatchActive(NULL);

    EndShaderMode();
  } else {
    for (int i = 0; i < bunniesCount; i++) {
      DrawTexture(texBunny, bunnies[i].position.x, bunnies[i].position.y, bunnies[i].color);
    }
  }
}

void world::update_draw3d() {}

void world::update_draw_interface() {
  DrawRectangle(0, 0, GetScreenWidth(), 40, BLACK);
  DrawText(TextFormat("bunnies: %i", bunniesCount), 120, 10, 20, GREEN);

  if (!drawInstanced) {
    DrawText(TextFormat("batched draw calls: %i", 1 + bunniesCount / RL_DEFAULT_BATCH_BUFFER_ELEMENTS), 300, 10, 20, MAROON);
  }
  DrawText(TextFormat("instanced: %i", drawInstanced), 550, 10, 20, MAROON);

  DrawFPS(10, 10);
}
