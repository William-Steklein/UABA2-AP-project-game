cmake_minimum_required(VERSION 3.22)
project(game_engine)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)

add_executable(${PROJECT_NAME} ./apps/app.cpp)
target_link_libraries(${PROJECT_NAME} renderer_lib)

# data
file(COPY "./data" DESTINATION "${CMAKE_BINARY_DIR}")