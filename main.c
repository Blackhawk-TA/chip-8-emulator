#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/utils/setup.h"
#include "src/utils/utils.h"
#include "src/sdl/sdl_wrapper.h"
#include "src/components/stack.h"
#include "src/components/memory.h"

int main(int argc, char **argv) { // TODO: Add parameter for instructions per second
	// Get cli parameter for ROM path
	if (argc != 2) {
		printf("Error: Invalid amount of parameters\n");
		exit(EXIT_FAILURE);
	}
	char *rom_path = get_path_from_parameter(argv);

	// Seed random number
	srand(time(NULL));

	// Init emulator components
	init_memory();
	init_stack();

	// Setup emulator memory
	load_font();
	load_rom_file(rom_path);

	// Setup SDL rendering. Should be run as last because it runs a loop and blocks all following commands.
	init_sdl();

	return 0;
}
