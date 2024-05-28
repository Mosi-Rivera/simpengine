#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/input_manager.h"

void	nullTerminateLine(char* line) {
	unsigned int i = 0;
	while (*line != '\n' && i++ < MAX_BINDINGS_LINE_LENGTH - 1 && *line++);
	*line = '\0';
}

unsigned int	parseSize(FILE* file) {
	char line[MAX_BINDINGS_LINE_LENGTH];
	if (!fgets(line, sizeof(line), file)) {
		perror("Error reading bindings size.");
		exit(1);
	}

	nullTerminateLine(line);
	return (unsigned int)atoi(line);
}
