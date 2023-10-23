//
// Created by daniel on 23.10.23.
//

#include "setup.h"
#include "../components/memory.h"
#include <stdio.h>
#include <stdlib.h>

void load_rom_file(char* path) {
	FILE *file = fopen(path, "rb");
	if (file == NULL) {
		printf("Error: Cannot open file");
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	rewind(file);

	u_int8_t *buffer = (u_int8_t*) malloc(file_size);
	size_t bytes_read = fread(buffer, 1, file_size, file);
	if (bytes_read != file_size) {
		printf("Error: Unable to memory_read file");
		exit(EXIT_FAILURE);
	}
	fclose(file);

	const u_int16_t rom_start_addr = 0x200;
	for (int i = 0; i < file_size; i++) {
		memory_write(rom_start_addr + i, buffer[i]);
	}

	free(buffer);
}

void load_font() {
	const u_int16_t font_start_addr = 0x50;
	const u_int16_t font_char_count = 80;
	const u_int16_t font[80] = {
			0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
			0x20, 0x60, 0x20, 0x20, 0x70, // 1
			0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
			0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
			0x90, 0x90, 0xF0, 0x10, 0x10, // 4
			0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
			0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
			0xF0, 0x10, 0x20, 0x40, 0x40, // 7
			0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
			0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
			0xF0, 0x90, 0xF0, 0x90, 0x90, // A
			0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
			0xF0, 0x80, 0x80, 0x80, 0xF0, // C
			0xE0, 0x90, 0x90, 0x90, 0xE0, // D
			0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
			0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	// Font is stored in address range: 0x050 - 0x09F
	for (u_int16_t i = 0; i < font_char_count; i++) {
		memory_write(font_start_addr + i, font[i]);
	}
}