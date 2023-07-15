#ifndef BRAWL_MASTERS_RAYLIB_INTERFACE_HPP
#define BRAWL_MASTERS_RAYLIB_INTERFACE_HPP

#ifdef __GNUC__
#pragma GCC system_header
#endif

#ifdef __clang__
#pragma clang system_header
#endif

#define MAX_BATCH_ELEMENTS 16384
#define RL_DEFAULT_BATCH_BUFFER_ELEMENTS 8192

#if defined(__cplusplus)
extern "C" {

// Raylib
#include "raylib.h"
#include "raymath.h"

// Raylib rlgl
#include "rlgl.h"
}
#endif

#endif // BRAWL_MASTERS_RAYLIB_INTERFACE_HPP