cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    brawl_masters
    VERSION 1.0.0
    DESCRIPTION "The world of cubes!"
    HOMEPAGE_URL "https://github.com/bensuperpc"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare options ----
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)


##
#add_library(
#    brawl_masters_lib OBJECT
#    source/lib.cpp
#)

#target_include_directories(
#    brawl_masters_lib ${warning_guard}
#    PUBLIC
#    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
#)

# ---- Dependencies ----

add_subdirectory(source/lib) # brawl_masters_lib
add_subdirectory(source/intro) # benlib_intro

include(cmake/lib/openmp.cmake)
include(cmake/lib/raylib.cmake)
#include(cmake/lib/fast_noise2.cmake)
include(cmake/lib/spdlog.cmake)
include(cmake/lib/json.cmake)
include(cmake/utile/ccache.cmake)

# ---- Declare executable ----

add_executable(brawl_masters_exe source/main.cpp source/Game.cpp)
add_executable(brawl_masters::exe ALIAS brawl_masters_exe)

set_property(TARGET brawl_masters_exe PROPERTY OUTPUT_NAME brawl_masters)

target_compile_features(brawl_masters_exe PRIVATE cxx_std_20)

target_link_libraries(brawl_masters_exe PRIVATE brawl_masters_lib benlib_intro)
target_link_libraries(brawl_masters_exe PRIVATE raylib)
target_link_libraries(brawl_masters_exe PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(brawl_masters_exe PRIVATE nlohmann_json::nlohmann_json)

set_target_properties(brawl_masters_exe
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Download assets
#file(DOWNLOAD
#  https://github.com/raysan5/raylib/blob/master/examples/textures/resources/wabbit_alpha.png?raw=true
#  ${CMAKE_BINARY_DIR}/asset/wabbit_alpha.png)

#file(DOWNLOAD
#https://raw.githubusercontent.com/ChrisDill/raylib-instancing/master/resources/shaders/bunnymark_instanced.fs
#  ${CMAKE_BINARY_DIR}/asset/bunnymark_instanced.fs)

#file(DOWNLOAD
#  https://raw.githubusercontent.com/ChrisDill/raylib-instancing/master/resources/shaders/bunnymark_instanced.vs
#  ${CMAKE_BINARY_DIR}/asset/bunnymark_instanced.vs)

file(COPY ${CMAKE_SOURCE_DIR}/asset DESTINATION ${CMAKE_BINARY_DIR})

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT brawl_masters_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of brawl_masters"
  )
endif()

include(cmake/dev-mode.cmake)
