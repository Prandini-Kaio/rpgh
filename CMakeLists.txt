cmake_minimum_required(VERSION 3.23)
project(rpg2 C)

set(CMAKE_C_STANDARD 99)

add_executable(rpg2 main.c src/mesa.c headers/mesa.h src/section.c headers/section.h)
