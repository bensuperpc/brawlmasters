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
#include "raylib.h"

// Cube lib

extern "C" {
#include "benlib_intro.h"
#include "raylib_cpp_intro.h"
#include "raylib_intro.h"
}

#include "player.hpp"
#include "world.hpp"

#include "game_element_handler.hpp"
#include "game_context.hpp"
#include "nlohmann/json.hpp"

class game {
public:
  game(nlohmann::json &_config_json);
  ~game();
  void run();
  void init();

  void render_thread_func();
  void auxillary_thread_game_logic(std::vector<std::shared_ptr<game_element_handler>>&);

private:
  std::shared_ptr<player> player1;
  std::shared_ptr<game_context> game_context1;
  std::shared_ptr<world> world1;

  std::vector<std::shared_ptr<game_element_handler>> game_classes;

  nlohmann::json &config_json;
  std::future<void> auxillary_thread;

  bool game_running = true;
};

#endif // GAME_HPP
