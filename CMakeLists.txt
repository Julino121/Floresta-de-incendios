cmake_minimum_required(VERSION 3.10)
project(Incendios C)

set(CMAKE_C_STANDARD 11)

add_executable(Incendios main.c funcoes.c)

target_link_libraries(Incendios pthread)
