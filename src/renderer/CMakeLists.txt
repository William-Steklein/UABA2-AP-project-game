file(GLOB_RECURSE renderer_lib_sources ./*.cpp)
add_library(renderer_lib STATIC ${renderer_lib_sources})
target_include_directories(renderer_lib PUBLIC "${PROJECT_SOURCE_DIR}/src")

# SFML
find_package(SFML COMPONENTS graphics audio REQUIRED)

target_link_libraries(renderer_lib PUBLIC game_lib sfml-graphics sfml-audio)
#target_link_libraries(renderer_lib PUBLIC game_lib sfml-graphics sfml-audio nlohmann_json::nlohmann_json)

