file(GLOB_RECURSE renderer_lib_sources ./*.cpp)
add_library(renderer_lib STATIC ${renderer_lib_sources})
target_include_directories(renderer_lib PUBLIC "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(renderer_lib PUBLIC
        game_lib

        sfml-graphics
        sfml-audio
        )