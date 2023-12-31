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
#  Modified: 11, July, 2023                                  #
#  file: CMakeLists.txt                                      #
#  CMake                                                     #
#  Source:                                                   #
#  OS: ALL                                                   #
#  CPU: ALL                                                  #
#                                                            #
##############################################################


cmake_minimum_required(VERSION 3.14)

project(
    benlib_math
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES NONE
)

#add_library(${PROJECT_NAME} INTERFACE ${HEADERS} ${SOURCES})
#target_precompile_headers(${PROJECT_NAME} INTERFACE ${HEADERS})

set(HEADERS
    math/vector.hpp
    math/math.hpp
)

# ---- Declare library ----

add_library(benlib_math_benlib_math INTERFACE ${HEADERS})
add_library(benlib_math::benlib_math ALIAS benlib_math_benlib_math)

set_property(
    TARGET benlib_math_benlib_math PROPERTY
    EXPORT_NAME benlib_math
)

target_include_directories(
    benlib_math_benlib_math ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
)

target_compile_features(benlib_math_benlib_math INTERFACE cxx_std_20)
