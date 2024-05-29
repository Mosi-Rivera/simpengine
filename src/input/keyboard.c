#include <ctype.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/input_manager.h"

void	parseKeyboardBindingsLine(char* line, unsigned int* id, KeyboardKey* key) {
	unsigned int i = 0;
	*id = 0;
	*key = 0;
	while (i < MAX_BINDINGS_LINE_LENGTH && *line != '\n' && *line != 0 && *line != ',') {
		if (isdigit(*line)) {
			*id = *id * 10 + (*line - '0');
		}
		line++;
		i++;
	}
	
	while (i < MAX_BINDINGS_LINE_LENGTH && *line != '\n' && *line != 0 && *line != '\n') {
		if (isdigit(*line)) {
			*key = *key * 10 + (*line - '0');
		}
		line++;
		i++;
	}
}

KeyboardKey*	newKeyboardBindings(unsigned int size) {
	KeyboardKey* key_bindings = (KeyboardKey*)calloc(size, sizeof(KeyboardKey));

	if (key_bindings == 0) {
		perror("Error allocating memory for key bindings.");
		exit(1);
	}

	for (unsigned int i = 0; i < size; i++) {
		key_bindings[i] = 0;
	}
	return key_bindings;
}

void	saveKeyboardBindings(char* path, KeyboardKey* bindings, unsigned int bindings_size) {
	if (!path) {
		return;
	}
	FILE* file = fopen(path, "w");
	if (file == 0) {
		perror("Error trying to open bindings file for write.");
		exit(1);
	}

	file = freopen(path, "a", file);
	if (file == 0) {
		perror("Error while trying to reopen file");
		exit(1);
	}

	fprintf(file, "%d\nid, key", bindings_size);
	for (unsigned int i = 0; i < bindings_size; i++) {
		fprintf(file, "\n%d, %d", i, bindings[i]);
	}
	fclose(file);
}

void	parseKeyboardBindings(char* bindings_path, KeyboardKey** keyboard_bindings, unsigned int* keyboard_bindings_count) {
	FILE* file = fopen(bindings_path, "r");
	char line[MAX_BINDINGS_LINE_LENGTH];
	unsigned int count = 0;
	unsigned int size;
	unsigned int id;
	KeyboardKey key;

	if (file == 0) {
		perror("Error opening keyboard bindings file.");
		exit(1);
	}

	size = parseSize(file);
	*keyboard_bindings_count = size;
	*keyboard_bindings = newKeyboardBindings(size);

	if (fgets(line, sizeof(line), file) == NULL) {
		perror("Error skipping header.");
		exit(1);
	}

	while (fgets(line, sizeof(line), file) != NULL && count < size) {
		parseKeyboardBindingsLine(line, &id, &key);
		if (id >= size) {
			perror("Error: Invalid binding id. Corrupted file.");
		}
		// if ((*keyboard_bindings)[id] == 0) {
		// 	count++;
		// }
		(*keyboard_bindings)[id] = key;
	}
	fclose(file);
}
