#ifndef BRAWL_MASTERS_GAME_HPP
#define BRAWL_MASTERS_GAME_HPP

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <numeric>
#include <omp.h>
#include <queue>
#include <random>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

//  Raylib
#include "raylib_interface.hpp"

// Cube lib

extern "C" {
#include "benlib_intro.h"
#include "raylib_cpp_intro.h"
#include "raylib_intro.h"
}

#include "Player.hpp"
#include "world.hpp"

#include "GameContext.hpp"
#include "gameElementHandler.hpp"
#include "nlohmann/json.hpp"

class Game {
public:
  Game(nlohmann::json &_config_json);
  ~Game();
  void run();
  void init();

  void render_thread_func();
  void auxillary_thread_game_logic(std::vector<std::shared_ptr<gameElementHandler>> &);

private:
  std::shared_ptr<Player> player1;
  std::shared_ptr<GameContext> game_context1;
  std::shared_ptr<world> world1;

  std::vector<std::shared_ptr<gameElementHandler>> game_classes;

  nlohmann::json &config_json;
  std::future<void> auxillary_thread;

  bool game_running = true;
};

#endif // GAME_HPP
