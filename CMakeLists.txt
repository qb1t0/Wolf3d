cmake_minimum_required(VERSION 3.9)
project(wolf3d_ C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES w3d.c w3d_events.c w3d_draw.c includes/w3d.h w3d_game.c wolf_other.c)

include_directories(include libft ${OpenGL_INCLUDE_DIR})
find_package(OpenGL REQUIRED)
add_executable(wolf3d_ ${SOURCE_FILES} w3d_game.c wolf_other.c)

target_link_libraries(wolf3d_ -lpthread -lmlx "-framework OpenGL" "-framework AppKit" ${CMAKE_SOURCE_DIR}/libft/libft.a)