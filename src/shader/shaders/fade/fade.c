#include <raylib.h>
#include "../../../../include/shaders.h"
#define UNIFORM_NAME_TIME "time"

void	shaderDrawFade(Shader* shader, void* data) {
	int timeLocation = GetShaderLocation(*shader, UNIFORM_NAME_TIME);
	SetShaderValue(*shader, timeLocation, &((struct FadeData*)data)->percentage, SHADER_UNIFORM_FLOAT);
}
