#include "Player.hpp"

Player::Player(GameContext &game_context_ref) : _game_ctx(game_context_ref) {
  player_logger = std::make_unique<logger_decorator>("Player", "Player.log");

  Camera2D _camera = {{0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f, 1.0f};

  _camera.target = {0.0f, 0.0f};
  _camera.offset = {0.0f, 0.0f};

  _camera.target = (Vector2){  20.0f, 20.0f };
  _camera.offset = (Vector2){ _game_ctx.screen_width/2.0f, _game_ctx.screen_height/2.0f };

  _camera.rotation = 0.0f;
  _camera.zoom = 1.0f;

  this->camera = _camera;
  // DisableCursor();

  // Image img = GenImageChecked(256, 256, 32, 32, GREEN, RED);
  Image img = GenImageColor(16, 16, WHITE);
  // Texture2D textureGrid = LoadTextureFromImage(img);
  texPlayer = std::make_unique<Texture2D>(LoadTextureFromImage(img));
  UnloadImage(img);
  // SetTextureFilter(textureGrid, TEXTURE_FILTER_ANISOTROPIC_16X);
  // SetTextureWrap(textureGrid, TEXTURE_WRAP_CLAMP);
}

Player::~Player() {
  player_logger->info("Player destructor called");
  UnloadTexture(*texPlayer);
}

void Player::updateGameInput() {
  // TODO: Move to GameContext
  _game_ctx.mouse_position_in_world = GetScreenToWorld2D(_game_ctx.mouse_position, camera);

  const float player_speed = 0.75f;
  float zoom = GetMouseWheelMove() * 0.5f;
  
  if (IsKeyDown(KEY_UP)) {
    camera.target.y -= player_speed;
  }
  if (IsKeyDown(KEY_DOWN)) {
    camera.target.y += player_speed;
  }
  if (IsKeyDown(KEY_LEFT)) {
    camera.target.x -= player_speed;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    camera.target.x += player_speed;
  }
  
  _game_ctx.player_position = camera.target;
}

void Player::updateGameLogic() {}

void Player::updateOpenglLogic() {}

void Player::updateDraw2d() {
  DrawRectangleRec({camera.target.x, camera.target.y, 10, 10}, RED);
}

void Player::updateDraw3d() {}

void Player::updateDrawInterface() {
  // DrawTexture(*texPlayer, camera.target.x, camera.target.y, BLUE);
  //  Draw crosshair in the middle of the screen
  DrawLine(_game_ctx.screen_middle.x - 10, _game_ctx.screen_middle.y, _game_ctx.screen_middle.x + 10, _game_ctx.screen_middle.y,
           SKYBLUE);
  DrawLine(_game_ctx.screen_middle.x, _game_ctx.screen_middle.y - 10, _game_ctx.screen_middle.x, _game_ctx.screen_middle.y + 10,
           SKYBLUE);
  DrawCircleV(_game_ctx.mouse_position, 10, GREEN);
}
