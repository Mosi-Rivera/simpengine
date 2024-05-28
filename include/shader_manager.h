#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H
#include <raylib.h>

struct ShaderData {
	Shader shader;
	void(*init)(Shader* shader, void* data);
};

struct ShaderManager {
	unsigned int size;
	struct ShaderData* shaders;
};

void	shaderManagerInitialize(struct ShaderData* shaders, unsigned int size);
void	shaderManagerUninitialize();
struct ShaderData*	getShader(unsigned int shader);

#endif
