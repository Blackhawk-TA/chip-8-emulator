#include <stdio.h>
#include <stdlib.h>
#include "src/utils/setup.h"
#include "src/utils/utils.h"
#include "src/utils/sdl_wrapper.h"

int main(int argc, char **argv) {
	// Get cli parameter for ROM path
	if (argc != 2) {
		perror("Error: Invalid amount of parameters\n");
		exit(EXIT_FAILURE);
	}
	char *rom_path = get_path_from_parameter(argv);

	// Setup SDL
	init_sdl();

	// Setup emulator memory
	load_font();
	load_rom_file(rom_path);

	return 0;
}
