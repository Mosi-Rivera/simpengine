#ifndef SIMPLE_ENGINE_H
#define SIMPLE_ENGINE_H
#include "./config.h"
#include "./scene_manager.h"
#include "./scenes.h"
#include "./shader_manager.h"
#include "./shaders.h"
#include "./scale.h"

struct SimpleEngineConfig {
	struct ShaderData* shaders;
	unsigned int shaders_count;
	struct Scene* scenes;
	unsigned int scenes_count;
	unsigned int default_scene;
	unsigned char hide_cursor;
	char* keyboard_bindings_path;
	char* gamepad_bindings_path;
};

void	simpleEngineInitialize(struct SimpleEngineConfig* config);
void	simpleEngineUninitialize();
#endif
