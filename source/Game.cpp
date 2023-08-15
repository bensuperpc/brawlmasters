#include "Game.hpp"
#include "raylib_interface.hpp"

Game::Game(nlohmann::json &_config_json) : config_json(_config_json) {}

Game::~Game() {}

void Game::init() {}

void Game::run() {
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

  game_context1 = std::make_shared<GameContext>(game_classes, config_json);
  game_classes.push_back(game_context1);

  auxillary_thread = std::async(std::launch::async, &Game::auxillary_thread_game_logic, this, std::ref(game_classes));

  InitWindow(game_context1->screen_width, game_context1->screen_height, "World of blocks");
  // game_context1->load_texture();

  world1 = std::make_shared<world>(*game_context1.get());
  game_classes.push_back(world1);

  // Play intro animation
  SetTargetFPS(60);
  // AudioDevice audiodevice;

  // async intro animation
  play_intro_raylib(game_context1->screen_width, game_context1->screen_height);
  play_intro_raylib_cpp(game_context1->screen_width, game_context1->screen_height);
  play_intro_benlib(game_context1->screen_width, game_context1->screen_height);

  SetTargetFPS(game_context1->target_fps);

  // Player init after window is created
  player1 = std::make_shared<Player>(*game_context1.get());
  game_classes.push_back(player1);

  while (game_running) {
    game_running = !WindowShouldClose();
    // !IsWindowFocused()
    if (IsWindowMinimized()) {
      continue;
    }

    for (auto &item : game_classes) {
      if (!item->is_active) {
        continue;
      }

      if (std::chrono::steady_clock::now() - item->last_update_opengl_logic < item->update_opengl_logic_cooldown) {
        continue;
      }
      item->updateOpenglLogic();
      item->last_update_opengl_logic = std::chrono::steady_clock::now();
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    /*
    BeginMode3D(player1->camera);
    for (auto &item : game_classes) {
      if (!item->is_active) {
        continue;
      }

      item->updateDraw3d();
    }
    EndMode3D();
    */

    BeginMode2D(player1->camera);
    for (auto &item : game_classes) {
      if (!item->is_active) {
        continue;
      }

      item->updateDraw2d();
    }
    EndMode2D();

    for (auto &item : game_classes) {
      if (!item->is_active) {
        continue;
      }

      item->updateDrawInterface();
    }

    EndDrawing();
    game_context1->frame_count++;
  }

  if (auxillary_thread.wait_for(std::chrono::milliseconds(1500)) == std::future_status::timeout) {
    std::cout << "auxillary_thread.wait_for(std::chrono::milliseconds(1500)) == std::future_status::timeout" << std::endl;
    auxillary_thread.wait();
  }

  game_classes.clear();

  player1.reset();
  world1.reset();
  game_context1.reset();

  CloseWindow();
}

// Update Game logic and input
void Game::auxillary_thread_game_logic(std::vector<std::shared_ptr<gameElementHandler>> &game_handled_classes) {
  while (game_running) {
    auto start_time = std::chrono::high_resolution_clock::now();
    for (auto &item : game_handled_classes) {
      // Skip inactive items
      if (!item->is_active) {
        continue;
      }

      // Update input
      if (std::chrono::steady_clock::now() - item->last_update_game_input < item->update_game_input_cooldown) {
        continue;
      }
      item->updateGameInput();
      item->last_update_game_input = std::chrono::steady_clock::now();

      // Update Game logic
      if (std::chrono::steady_clock::now() - item->last_update_game_logic < item->update_game_logic_cooldown) {
        continue;
      }
      item->updateGameLogic();
      item->last_update_game_logic = std::chrono::steady_clock::now();
    }

    /*
    // Ensure that the Game runs at the target fps
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    auto sleep_time = std::chrono::milliseconds(1000 / game_context1->target_fps) - duration;

    if (sleep_time > std::chrono::milliseconds(2)) {
      std::this_thread::sleep_for(sleep_time);
    }
    */
  }

  std::cout << "auxillary_thread_game_logic() exiting" << std::endl;
}