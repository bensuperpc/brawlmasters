#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "raylib.h"

auto main() -> int {

  const int screenWidth = 1920;
  const int screenHeight = 1080;

  const int blockPixelHeight = 10;
  const int blockPixelWidth = 10;

  const int startTextureX = 0;
  const int startTextureY = 0;

  const int blockX = screenWidth / blockPixelWidth;
  const int blockY = screenHeight / blockPixelHeight;

  const uint32_t targetFPS = 120;

  const uint32_t ImageUpdatePerSecond = 30;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "2D Perlin Noise by Bensuperpc");

  SetTargetFPS(targetFPS);

  Image gridImage = GenImageColor(screenWidth, screenHeight, RAYWHITE);

  Color *pixels = LoadImageColors(gridImage);

  Texture gridTexture = LoadTextureFromImage(gridImage);

  std::vector<uint32_t> blocks(blockX * blockY, 0);

  std::for_each(blocks.begin(), blocks.end(), [](uint32_t &n) { n = GetRandomValue(0, 100); });

  blocks[0] = 0;
  blocks[blockX * blockY - 1] = 0;

  uint64_t framesCounter = 0;

  Camera2D camera = {0};
  camera.target = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  bool displayGrid = false;

  while (!WindowShouldClose()) {
    framesCounter++;

    if (IsKeyPressed(KEY_S)) {
      const std::string filename = "screenshot_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".png";
      Image screenshot = {pixels, screenWidth, screenHeight, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
      ExportImage(screenshot, filename.c_str());
      pixels = LoadImageColors(screenshot);
    }

    if (IsKeyPressed(KEY_R)) {
      std::for_each(blocks.begin(), blocks.end(), [](uint32_t &n) { n = GetRandomValue(0, 100); });

      // Remove start and end
      blocks[0] = 0;
      blocks[blockX * blockY - 1] = 0;
    }

    if (IsKeyPressed(KEY_G)) {
      displayGrid = !displayGrid;
    }

    if (IsKeyDown(KEY_RIGHT)) {
      camera.target.x += 10.0f;
    }
    if (IsKeyDown(KEY_LEFT)) {
      camera.target.x -= 10.0f;
    }
    if (IsKeyDown(KEY_UP)) {
      camera.target.y -= 10.0f;
    }
    if (IsKeyDown(KEY_DOWN)) {
      camera.target.y += 10.0f;
    }

    if (IsKeyDown(KEY_A)) {
      camera.rotation--;
    }
    if (IsKeyDown(KEY_S)) {
      camera.rotation++;
    }

    if (camera.rotation > 40)
      camera.rotation = 40;
    else if (camera.rotation < -40)
      camera.rotation = -40;

    camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

    if (camera.zoom > 3.0f)
      camera.zoom = 3.0f;
    else if (camera.zoom < 0.1f)
      camera.zoom = 0.1f;

    if (IsKeyPressed(KEY_R)) {
      camera.zoom = 1.0f;
      camera.rotation = 0.0f;
    }

    if (framesCounter % (targetFPS / ImageUpdatePerSecond) == 0) {
      for (uint64_t x = 0; x < screenWidth; x++) {
        for (uint64_t y = 0; y < screenHeight; y++) {
          // Draw Rectangle with blockPixelHeight and blockPixelWidth size for each block

          auto blocksIndex = (y / blockPixelHeight) * blockX + (x / blockPixelWidth);
          auto pixelIndex = y * screenWidth + x;
          if (blocks[blocksIndex] >= 65) {
            pixels[pixelIndex] = (Color){0, 0, 0, 255};
          } else {
            pixels[pixelIndex] = (Color){255, 255, 255, 255};
          }
          // Draw grid
          if (!displayGrid) {
            continue;
          }

          if (x % blockPixelWidth == 0 || y % blockPixelHeight == 0) {
            pixels[pixelIndex] = Fade(BLACK, 0.1f);
          }
        }
      }

      // Update texture
      UpdateTexture(gridTexture, pixels);
    }

    ClearBackground(RAYWHITE);
    BeginDrawing();

    BeginMode2D(camera);
    DrawTexture(gridTexture, startTextureX, startTextureY, WHITE);
    EndMode2D();

    // display FPS
    DrawRectangle(screenWidth - 90, 10, 80, 20, Fade(SKYBLUE, 0.95f));
    DrawText(TextFormat("FPS: %02d", GetFPS()), screenWidth - 80, 15, 15, DARKGRAY);

    // DrawRectangle(0, 0, 275, 200, Fade(SKYBLUE, 0.95f));
    // DrawRectangleLines(0, 0, 275, 200, BLUE);
    EndDrawing();
  }

  UnloadImageColors(pixels);
  UnloadTexture(gridTexture);
  CloseWindow();

  return 0;
}
