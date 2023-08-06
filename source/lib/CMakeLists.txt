##############################################################
#   ____                                                     #
#  | __ )  ___ _ __  ___ _   _ _ __   ___ _ __ _ __   ___    #
#  |  _ \ / _ \ '_ \/ __| | | | '_ \ / _ \ '__| '_ \ / __|   #
#  | |_) |  __/ | | \__ \ |_| | |_) |  __/ |  | |_) | (__    #
#  |____/ \___|_| |_|___/\__,_| .__/ \___|_|  | .__/ \___|   #
#                             |_|             |_|            #
##############################################################
#                                                            #
#  BenLib, 2021                                              #
#  Created: 16, March, 2021                                  #
#  Modified: 17, March, 2021                                 #
#  file: CMakeLists.txt                                      #
#  CMake                                                     #
#  Source:                                                   #
#  OS: ALL                                                   #
#  CPU: ALL                                                  #
#                                                            #
##############################################################

cmake_minimum_required(VERSION 3.14)
project(
    brawl_masters_lib
    VERSION 0.1.0
    DESCRIPTION "world of blocks lib"
    HOMEPAGE_URL "https://github.com/bensuperpc"
    LANGUAGES C CXX
)

include(../../cmake/lib/raylib.cmake)
include(../../cmake/lib/openmp.cmake)
include(../../cmake/lib/json.cmake)
include(../../cmake/utile/ccache.cmake)

add_subdirectory(logger)
add_subdirectory(math)

set(SOURCES
    player.cpp
    world.cpp
    game_context.cpp
    game_base.cpp
)

set(HEADERS
    player.hpp
    world.hpp
    game_context.hpp
    raylib_interface.hpp
    raylib_interface.hpp
)

#add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME} ${SOURCES})
#target_precompile_headers(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/generator.hpp>)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_C OpenMP::OpenMP_CXX)
target_link_libraries(${PROJECT_NAME} PUBLIC logger::logger benlib_math::benlib_math)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

set_target_properties(brawl_masters_lib
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


target_include_directories(
    brawl_masters_lib INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)


