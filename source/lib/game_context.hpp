#ifndef BRAWL_MASTERS_GAME_CONTEXT_HPP
#define BRAWL_MASTERS_GAME_CONTEXT_HPP

#include <iostream>
#include <string>
#include <vector>

#include <omp.h>

// Raylib
#include "raylib_interface.hpp"

// World of blocks
#include "game_element_handler.hpp"
#include "math/vector.hpp"

#include "game_context.hpp"
#include "game_element_handler.hpp"

#include "nlohmann/json.hpp"

class game_context : public game_element_handler {
public:
  game_context(std::vector<std::shared_ptr<game_element_handler>> &game_classes, nlohmann::json &_config_json);

  ~game_context();

  void update_game_input() override;
  void update_game_logic() override;

  void update_opengl_logic() override;
  void update_draw2d() override;
  void update_draw3d() override;
  void update_draw_interface() override;

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
  Texture2D _texture;

  nlohmann::json &config_json;

  std::vector<std::shared_ptr<game_element_handler>> &game_classes;

  // Debug menu
  bool *display_debug_menu = nullptr;
};

#endif // BRAWL_MASTERS_HPP