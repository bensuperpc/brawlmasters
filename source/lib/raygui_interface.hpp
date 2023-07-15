#ifndef BRAWL_MASTERS_RAYGUI_INTERFACE_HPP
#define BRAWL_MASTERS_RAYGUI_INTERFACE_HPP

#ifdef __GNUC__
#pragma GCC system_header
#endif

#ifdef __clang__
#pragma clang system_header
#endif

#if defined(__cplusplus)
extern "C" {
#define RAYGUI_IMPLEMENTATION
#include "src/raygui.h"
#undef RAYGUI_IMPLEMENTATION
}
#endif

#endif // BRAWL_MASTERS_RAYGUI_INTERFACE_HPP