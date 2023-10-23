cmake_minimum_required(VERSION 3.26)
project(chip_8_emulator C)

set(CMAKE_C_STANDARD 11)

add_executable(chip_8_emulator main.c
        src/memory.c
        src/memory.h
        src/utils.c
        src/utils.h)
