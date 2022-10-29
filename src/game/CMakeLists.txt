file(GLOB_RECURSE game_lib_files *.cpp)
add_library(game_lib STATIC ${game_lib_files})
target_include_directories(game_lib PUBLIC "${PROJECT_SOURCE_DIR}/src/game")

target_link_libraries(game_lib engine_lib)