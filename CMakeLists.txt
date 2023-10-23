cmake_minimum_required(VERSION 3.26)
project(chip_8_emulator C)

set(CMAKE_C_STANDARD 11)

add_executable(chip_8_emulator main.c
        src/components/memory.c
        src/components/memory.h
        src/utils/utils.c
        src/utils/utils.h
        src/utils/setup.c
        src/utils/setup.h)
