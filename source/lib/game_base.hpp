#ifndef BRAWL_MASTERS_GAME_BASE_HPP
#define BRAWL_MASTERS_GAME_BASE_HPP

class game_base {
public:
  virtual ~game_base();
  explicit game_base();

  bool is_active = true;
  bool is_visible = true;
};

#endif // BRAWL_MASTERS_GAME_BASE_HPP