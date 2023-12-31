#include "Player.hpp"

Player::Player(GameContext &game_context_ref) : _game_ctx(game_context_ref) {
  player_logger = std::make_unique<logger_decorator>("Player", "Player.log");

  Camera2D _camera = {{0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f, 1.0f};

  _playerPosition = {_game_ctx.screen_width/2.0f, _game_ctx.screen_height/2.0f};
  _camera.target = (Vector2){  20.0f, 20.0f };
  _camera.offset = _playerPosition;

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
  float zoom = GetMouseWheelMove() * 0.05f;

  if (IsKeyDown(KEY_UP)) {
    _playerPosition.y -= player_speed;
  }
  if (IsKeyDown(KEY_DOWN)) {
    _playerPosition.y += player_speed;
  }
  if (IsKeyDown(KEY_LEFT)) {
    _playerPosition.x -= player_speed;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    _playerPosition.x += player_speed;
  }

  camera.zoom += zoom;
  if (camera.zoom > 3.0f)
    camera.zoom = 3.0f;
  else if (camera.zoom < 0.1f)
    camera.zoom = 0.1f;

  _game_ctx.player_position = _playerPosition;
  camera.target = _playerPosition;
}

void Player::updateGameLogic() {
}

void Player::updateOpenglLogic() {}

void Player::updateDraw2d() {
  DrawRectangleRec({_playerPosition.x, _playerPosition.y, 10, 10}, RED);
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
