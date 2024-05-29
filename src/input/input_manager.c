#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../include/input_manager.h"

static struct InputManager input_manager = {0};

struct InputManager*	_getInputManager() {
	return &input_manager;
}

void	setKeyboardBinding(unsigned int id, KeyboardKey key) {
	if (id >= input_manager.keyboard_bindings_count || !input_manager.keyboard_bindings_path) {
		return;
	}
	input_manager.keyboard_bindings[id] = key;
}

void setAndSaveKeyboardBinding(unsigned int id, KeyboardKey key) {
	setKeyboardBinding(id, key);
	saveKeyboardBindings(
		input_manager.keyboard_bindings_path,
		input_manager.keyboard_bindings,
		input_manager.keyboard_bindings_count
	);
}

void	parseGamepadBindings(char* bindings_path, GamepadButton** gamepad_buttons, unsigned int* gamepad_bingings_count) {

}

void	inputManagerInitialize(char* default_keyboard_bindings, char* default_gamepad_bindings) {
	input_manager.keyboard_bindings = 0;
	input_manager.keyboard_bindings_count = 0;
	input_manager.gamepad_bindings = 0;
	input_manager.gamepad_bindings_count = 0;

	if (default_keyboard_bindings) {
		parseKeyboardBindings(default_keyboard_bindings, &input_manager.keyboard_bindings, &input_manager.keyboard_bindings_count);
		input_manager.keyboard_bindings_path = default_keyboard_bindings;
	}
	if (default_gamepad_bindings) {
		parseGamepadBindings(default_gamepad_bindings, &input_manager.gamepad_bindings, &input_manager.gamepad_bindings_count);
	}
}

void	inputManagerUninitialize() {
	if (input_manager.keyboard_bindings) {
		free(input_manager.keyboard_bindings);
	}
	if (input_manager.gamepad_bindings) {
		free(input_manager.gamepad_bindings);
	}
}

unsigned char	checkKeyboardAndGamepadInput(unsigned int id, bool(*getKeyboardInput)(int key), bool(*getGamepadInput)(int gamepad, int key)) {
	unsigned char is_down = 0;

	if (id < input_manager.keyboard_bindings_count) {
		is_down = getKeyboardInput(input_manager.keyboard_bindings[id]);
	} else if (id < input_manager.gamepad_bindings_count) {
		is_down = is_down || getGamepadInput(0, input_manager.gamepad_bindings[id]);
	}
	return is_down;
}

unsigned char	isDown(unsigned int id) {
	return checkKeyboardAndGamepadInput(id, IsKeyDown, IsGamepadButtonDown);
}

unsigned char	isPressed(unsigned int id) {
	return checkKeyboardAndGamepadInput(id, IsKeyPressed, IsGamepadButtonPressed);
}

unsigned char	isReleased(unsigned int id) {
	return checkKeyboardAndGamepadInput(id, IsKeyReleased, IsGamepadButtonReleased);
}
