#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <raylib.h>
#include <stdio.h>
#define MAX_BINDINGS_LINE_LENGTH 10

struct InputManager {
	KeyboardKey* keyboard_bindings;
	unsigned int keyboard_bindings_count;
	GamepadButton* gamepad_bindings;
	unsigned int gamepad_bindings_count;
};

void	inputManagerInitialize(void* default_keyboard_bindings, void* default_gamepad_bindings);
void	inputManagerUninitialize();
void	nullTerminateLine(char* line);
unsigned int	parseSize(FILE* file);
void	parseKeyboardBindings(char* bindings_path, KeyboardKey** keyboard_bindings, unsigned int* keyboard_bindings_count);
unsigned char	isDown(unsigned int id);
unsigned char	isPressed(unsigned int id);
unsigned char	isReleased(unsigned int id);

#endif
