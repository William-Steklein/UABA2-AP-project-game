file(GLOB_RECURSE engine_lib_files *.cpp)
add_library(engine_lib STATIC ${engine_lib_files})
target_include_directories(engine_lib PUBLIC "${PROJECT_SOURCE_DIR}/src/engine")