#include <raylib.h>
#include "../include/config.h"
#include "../include/scene_manager.h"
#include "../include/scenes.h"
#include "../include/shader_manager.h"
#include "../include/shaders.h"
#include "../include/scale.h"
#include "../include/simple_engine.h"

int main(void) {
	const unsigned int screen_width = DEFAULT_WINDOW_WIDTH;
	const unsigned int screen_height = DEFAULT_WINDOW_HEIGHT;

	InitWindow(screen_width, screen_height, "My Special Game Engine");
	SetTargetFPS(60);

	struct SimpleEngineConfig simple_engine_config = {
		(struct ShaderData[]){
			(struct ShaderData){
				LoadShader(0, "src/shader/shaders/fade/fade.frag"),
				shaderDrawFade
			}
		},
		1,
		(struct Scene[]){
			*loadingSceneInitialize(&(struct Scene){0})
		},
		1,
		0,
		1,
		"assets/bindings/keyboard.csv",
		0
	};
	simpleEngineInitialize(&simple_engine_config);

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();

		handleResize();

		sceneUpdate(dt);

		BeginDrawing();
		{
			ClearBackground(BLACK);
			beginScaledMode();
			{
				ClearBackground(BLACK);
				sceneDraw();
			}
			endScaledMode();
			drawScaleTexture();
		}
		EndDrawing();
	}

	simpleEngineUninitialize();
	CloseWindow();
	return 0;
}
