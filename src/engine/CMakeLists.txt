file(GLOB_RECURSE engine_lib_sources ./*.cpp)
add_library(engine_lib STATIC ${engine_lib_sources})
target_include_directories(engine_lib PUBLIC "${PROJECT_SOURCE_DIR}/src")