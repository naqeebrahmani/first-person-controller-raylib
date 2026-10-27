cmake_minimum_required(VERSION 3.23)

project(FPS_CAM)

add_executable(main)

target_sources(main
PRIVATE main.cpp)

include_directories(C:/Libraries/raylib/raylib/build/raylib/include)

add_library(raylib STATIC IMPORTED)

set_property(TARGET raylib PROPERTY IMPORTED_LOCATION "C:/Libraries/raylib/raylib/build/raylib/libraylib.a")

target_link_libraries(main 
PRIVATE raylib winmm opengl32 gdi32)