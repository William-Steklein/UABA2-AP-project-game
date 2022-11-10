file(GLOB_RECURSE game_lib_sources ./*.cpp)
add_library(game_lib STATIC ${game_lib_sources})
target_include_directories(game_lib PUBLIC "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(game_lib engine_lib)