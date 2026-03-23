cmake_minimum_required(VERSION 3.15)
project(proyectosRaylibCpp)

set(CMAKE_CXX_STANDARD 17)

# Apunta al raylib que ya tienes descargado
add_subdirectory(raylib)

# Agrega cada juego
add_subdirectory(snake)
add_subdirectory(pong)