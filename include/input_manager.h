#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <raylib.h>
#include <stdio.h>
#define MAX_BINDINGS_LINE_LENGTH 10

struct InputManager {
	KeyboardKey* keyboard_bindings;
	unsigned int keyboard_bindings_count;
	char* keyboard_bindings_path;
	GamepadButton* gamepad_bindings;
	unsigned int gamepad_bindings_count;
	char* gamepad_bindings_path;
};

void	inputManagerInitialize(char* default_keyboard_bindings, char* default_gamepad_bindings);
void	inputManagerUninitialize();
void	nullTerminateLine(char* line);
unsigned int	parseSize(FILE* file);
void	parseKeyboardBindings(char* bindings_path, KeyboardKey** keyboard_bindings, unsigned int* keyboard_bindings_count);
unsigned char	isDown(unsigned int id);
unsigned char	isPressed(unsigned int id);
unsigned char	isReleased(unsigned int id);
void	saveKeyboardBindings(char* path, KeyboardKey* bindings, unsigned int bindings_size);
void	setAndSaveKeyboardBinding(unsigned int id, KeyboardKey key);
void	setKeyboardBinding(unsigned int id, KeyboardKey key);
struct InputManager*	_getInputManager();

#endif
