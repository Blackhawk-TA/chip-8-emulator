cmake_minimum_required(VERSION 3.26)
project(chip_8_emulator C)

set(CMAKE_C_STANDARD 11)

add_executable(chip_8_emulator main.c
        src/components/memory.c
        src/components/memory.h
        src/utils/utils.c
        src/utils/utils.h
        src/utils/setup.c
        src/utils/setup.h
        src/sdl/sdl_wrapper.c
        src/sdl/sdl_wrapper.h
        src/components/display.c
        src/components/display.h
        src/components/stack.c
        src/components/stack.h
        src/components/timer.c
        src/components/timer.h
        src/sdl/renderer.c
        src/sdl/renderer.h
        src/components/keypad.c
        src/components/keypad.h
        src/components/cpu.c
        src/components/cpu.h)

find_package(SDL2 REQUIRED)
target_link_libraries(chip_8_emulator PRIVATE SDL2::SDL2)
