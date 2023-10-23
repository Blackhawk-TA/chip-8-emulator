//
// Created by daniel on 23.10.23.
//

#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* get_path_from_parameter(char **argv) {
	char *param_value = NULL;

	// Get char array of parameter name
	char *param_name = strtok(argv[1], "=");
	if (param_name == NULL) {
		perror("Error: Invalid parameter separation\n");
		exit(EXIT_FAILURE);
	} else if (strcmp(param_name, "--rom") != 0) {
		perror("Error: Invalid parameter name\n");
		exit(EXIT_FAILURE);
	}

	// Get char array of parameter value
	param_value = strtok(NULL, "\0");
	if (param_value == NULL) {
		perror("Error: Invalid parameter value\n");
		exit(EXIT_FAILURE);
	}

	return param_value;
}
