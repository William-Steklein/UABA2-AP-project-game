cmake_minimum_required(VERSION 3.22)
project(game_engine)

set(CMAKE_CXX_STANDARD 14)

set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
endif ()

#if (WIN32)
#    if (CMAKE_BUILD_TYPE MATCHES "Release")
#        # -mwindows removes the console window
#        set(CMAKE_CXX_FLAGS "-pthread -mwindows")
#    endif ()
#endif ()

add_subdirectory(src)

# data
file(COPY "./data" DESTINATION "${CMAKE_BINARY_DIR}")