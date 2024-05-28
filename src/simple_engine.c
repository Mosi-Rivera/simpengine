#include "../include/simple_engine.h"
#include "../include/input_manager.h"
#include <raylib.h>

void	simpleEngineInitialize(struct SimpleEngineConfig* config) {
	inputManagerInitialize(config->keyboard_bindings_path, config->gamepad_bindings_path);
	scaleInitialize();
	shaderManagerInitialize(config->shaders, config->shaders_count);
	sceneManagerInitialize(config->scenes, config->scenes_count, config->default_scene);

	if (config->hide_cursor) {
		HideCursor();
	}
}

void simpleEngineUninitialize() {
	sceneManagerUninitialize();
	shaderManagerUninitialize();
	scaleUninitialize();
	inputManagerUninitialize();
}
