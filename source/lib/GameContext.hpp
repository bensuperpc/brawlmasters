#ifndef BRAWL_MASTERS_GAME_CONTEXT_HPP
#define BRAWL_MASTERS_GAME_CONTEXT_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib_interface.hpp"

// World of blocks
#include "gameElementHandler.hpp"
#include "math/vector.hpp"

#include "GameContext.hpp"
#include "gameElementHandler.hpp"

#include "nlohmann/json.hpp"

class GameContext : public gameElementHandler {
public:
  GameContext(std::vector<std::shared_ptr<gameElementHandler>> &game_classes, nlohmann::json &_config_json);

  ~GameContext();

  void updateGameInput() override;
  void updateGameLogic() override;

  void updateOpenglLogic() override;
  void updateDraw2d() override;
  void updateDraw3d() override;
  void updateDrawInterface() override;

  void load_texture();
  void unload_texture();

  // Game settings and window
  int screen_width = 1920;
  int screen_height = 1080;
  int target_fps = 240;

  uint64_t frame_count = 0;

  // Game variables
  Vector2 mouse_position = {0, 0};
  Vector2 mouse_position_in_world = {0, 0};
  Vector2 screen_middle = {0, 0};

  Vector2 player_position = {0, 0};

  benlib::Vector3i block_info_pos = {0, 0, 0};
  size_t block_info_index = 0;

  nlohmann::json &config_json;

  std::vector<std::shared_ptr<gameElementHandler>> &game_classes;

  // Debug menu
  bool *display_debug_menu = nullptr;
};

#endif // BRAWL_MASTERS_HPP