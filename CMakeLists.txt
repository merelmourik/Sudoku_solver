cmake_minimum_required(VERSION 3.17)
project(sudoku)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE__FLAGS} -g -Wall -Werror -Wextra")

add_executable(
        sudoku_solver
        sudoku.c
        solving.c
        preparing.c
        validating.c)

#set_target_properties(sudoku PROPERTIES LINKER_LANGUAGE C C_STANDARD 99)