//
// Created by daniel on 23.10.23.
//

#include "utils.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* get_path_from_parameter(char **argv) {
	char *param_value = NULL;

	// Get char array of parameter name
	char *param_name = strtok(argv[1], "=");
	if (param_name == NULL) {
		printf("Error: Invalid parameter separation\n");
		exit(EXIT_FAILURE);
	} else if (strcmp(param_name, "--rom") != 0) {
		printf("Error: Invalid parameter name\n");
		exit(EXIT_FAILURE);
	}

	// Get char array of parameter value
	param_value = strtok(NULL, "\0");
	if (param_value == NULL) {
		printf("Error: Invalid parameter value\n");
		exit(EXIT_FAILURE);
	}

	return param_value;
}

u_int64_t get_time_ns() {
	struct timespec ts;

	if (clock_gettime(CLOCK_REALTIME, &ts) != 0) {
		perror("Error: Unable to get clock time");
		exit(EXIT_FAILURE);
	}
	return ts.tv_sec * 1000000000 + ts.tv_nsec;
}
