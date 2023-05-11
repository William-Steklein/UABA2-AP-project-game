cmake_minimum_required(VERSION 3.22)
project(AP_Game)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

set(PATH_TO_SFML ${ANDROID_NDK}/sources/third_party/sfml)
set(SFML_DIR ${PATH_TO_SFML}/lib/${ANDROID_ABI}/cmake/SFML)

#find_package(SFML 3 COMPONENTS Graphics Audio Network REQUIRED)
find_package(SFML 2 COMPONENTS graphics audio network REQUIRED)
# or 2 for 2.6.x

add_library(openal SHARED IMPORTED)
set_target_properties(openal PROPERTIES IMPORTED_LOCATION_RELEASE ${PATH_TO_SFML}/extlibs/lib/${ANDROID_ABI}/libopenal.so)
set_target_properties(openal PROPERTIES IMPORTED_LOCATION_DEBUG ${PATH_TO_SFML}/extlibs/lib/${ANDROID_ABI}/libopenal.so)

set(PATH_TO_SOURCES ./)
add_library(example SHARED
        ${PATH_TO_SOURCES}/src/main.cpp
        )

target_compile_features(example PUBLIC cxx_std_20)

add_subdirectory(${PATH_TO_SOURCES}/external/)
add_subdirectory(${PATH_TO_SOURCES}/src)

target_link_libraries(example
        log
        android
        sfml-system
        sfml-graphics
        sfml-audio
        sfml-activity
        sfml-network -Wl,--whole-archive
        sfml-main -Wl,--no-whole-archive
        openal
        EGL
        GLESv1_CM

        renderer_lib
        )
# SFML::Graphics, etc. -> sfml-graphics for 2.6.x

