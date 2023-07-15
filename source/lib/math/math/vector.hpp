#ifndef BRAWL_MASTERS_VECTOR_HPP
#define BRAWL_MASTERS_VECTOR_HPP

#include <cstdint>

namespace benlib {

struct Vector3i {
  int x;
  int y;
  int z;
};

struct Vector2i {
  int x;
  int y;
};

struct Vector3f {
  float x;
  float y;
  float z;
};

struct Vector2f {
  float x;
  float y;
};

} // namespace benlib

#endif // BRAWL_MASTERS_VECTOR_HPP