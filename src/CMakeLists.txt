add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(renderer)

add_executable(${PROJECT_NAME} ./main.cpp)
target_link_libraries(${PROJECT_NAME} renderer_lib)