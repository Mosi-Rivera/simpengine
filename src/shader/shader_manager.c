#include "../../include/shader_manager.h"
#include <raylib.h>

static struct ShaderManager shader_manager = {0};

void	shaderManagerInitialize(struct ShaderData* shaders, unsigned int size) {
	shader_manager.shaders = shaders;
	shader_manager.size = size;
}

void	shaderManagerUninitialize() {
	struct ShaderData* shaders = shader_manager.shaders;
	struct ShaderData* shader;
	unsigned int i = 0;
	unsigned int l = shader_manager.size;

	while (i < l) {
		shader = &shaders[i++];
		UnloadShader(shader->shader);
	}
}

struct ShaderData*	getShader(unsigned int shader) {
	return &shader_manager.shaders[shader];
}
