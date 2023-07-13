#include "player.hpp"

player::player(game_context &game_context_ref) : _game_context_ref(game_context_ref) {
  player_logger = std::make_unique<logger_decorator>("player", "player.log");
  Camera _camera = {0};
  _camera.position = (Vector3){48.0f, 48.0f, -48.0f};
  _camera.target = (Vector3){-28.0f, 48.0f, -28.0f};
  _camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  _camera.fovy = 80.0f;
  _camera.projection = CAMERA_PERSPECTIVE;

  this->camera = _camera;
  DisableCursor();
}

Vector3 player::get_position() const { return this->camera.position; }

player::~player() {}

void player::update_game_input() {
  float player_speed = 0.5f;
  float zoom = GetMouseWheelMove() * 0.5f;
  Vector3 movement = {0.0f, 0.0f, 0.0f};
  Vector3 rotation = {0.0f, 0.0f, 0.0f};

  if (IsKeyPressed(KEY_F5)) {
    auto date = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&date), "%Y-%m-%d_%H-%M-%S");
    std::string filename = ss.str();
    player_logger->info("Taking screenshot: {}", filename);
    TakeScreenshot(("screenshot_" + filename + ".png").c_str());
  }

  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    movement.x = player_speed;
  }
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    movement.x = -player_speed;
  }
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    movement.y = player_speed;
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    movement.y = -player_speed;
  }
  if (IsKeyDown(KEY_SPACE)) {
    movement.z = player_speed;
  }
  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    movement.z = -player_speed;
  }

  rotation.x = GetMouseDelta().x * 0.05f;
  rotation.y = GetMouseDelta().y * 0.05f;

  UpdateCameraPro(&camera, movement, rotation, zoom);

  // Update player chunk position in game context
  _game_context_ref.player_pos = std::move(camera.position);
}

void player::update_game_logic() {}

void player::update_opengl_logic() {}

void player::update_draw2d() {}

void player::update_draw3d() {}