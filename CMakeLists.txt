cmake_minimum_required(VERSION 3.22)
project(game_engine)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)

# data
file(COPY "./data" DESTINATION "${CMAKE_BINARY_DIR}")