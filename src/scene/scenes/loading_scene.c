#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../include/scene_manager.h"
#include "../../../include/shader_manager.h"
#include "../../../include/shaders.h"
#include "../../../include/scale.h"
#include "../../../include/camera.h"
#include "../../../include/input_manager.h"
#define TRANSITION_IN_DURATION 1.5f
#define TRANSITION_OUT_DURATION 1.5f

struct LoadingData {
	Camera2D camera;
};

void	loadingDestroy(struct Scene* scene) {
	if (scene->data) {
		free(scene->data);
		scene->data = 0;
	}
}

void loadingSceneUpdate(void* data, float dt) {
	struct LoadingData* loading_data = data;
	loading_data->camera.target.x += dt * 20;
};

void loadingSceneDraw(void* data) {
	struct LoadingData* loading_data = data;

	BeginMode2D(loading_data->camera);
	DrawText("Hello world.", getVirtualWidth() / 2 - 10, 200, 20, LIGHTGRAY);
	EndMode2D();
	if (isDown(0)) {
		DrawText("Left", getVirtualWidth() / 2, 20, 20, LIGHTGRAY);
	}
	if (isDown(1)) {
		DrawText("right", getVirtualWidth() / 2, 60, 20, LIGHTGRAY);
	}
	if (isDown(2)) {
		DrawText("up", getVirtualWidth() / 2, 100, 20, LIGHTGRAY);
	}
	if (isDown(3)) {
		DrawText("down", getVirtualWidth() / 2, 140, 20, LIGHTGRAY);
	}
}

void loadingSceneEnter(void* data) {
	struct LoadingData* loading_data = data;

	float halfVirtualWidth = (float)getVirtualWidth() / 2;
	float halfVirtualHeight = (float)getVirtualHeight() / 2;

	cameraInitialize(
		&loading_data->camera,
		(Vector2){halfVirtualWidth, halfVirtualHeight},
		(Vector2){halfVirtualWidth, halfVirtualHeight}
	);
	printf("\nenter Loading\n");
}

void loadingSceneExit(void* data) {}

void loadingSceneTransitionIn(void* data, float progress) {
	struct ShaderData* shader_data = getShader(0);

	float percentage = progress / TRANSITION_IN_DURATION;
	shader_data->init(&shader_data->shader, &(struct FadeData){percentage});
	BeginShaderMode(shader_data->shader);
	DrawRectangle(0, 0, getVirtualWidth(), getVirtualHeight(), Fade(WHITE, 0));
	EndShaderMode();
}

void loadingSceneTransitionOut(void* data, float progress) {
	struct ShaderData* shader_data = getShader(0);

	float percentage = 1 - progress / TRANSITION_IN_DURATION;
	shader_data->init(&shader_data->shader, &(struct FadeData){percentage});
	BeginShaderMode(shader_data->shader);
	DrawRectangle(0, 0, getVirtualWidth(), getVirtualHeight(), Fade(WHITE, 0));
	EndShaderMode();
}

struct Scene*	loadingSceneInitialize(struct Scene* scene) {
	scene->update = loadingSceneUpdate;
	scene->draw = loadingSceneDraw;
	scene->enter = loadingSceneEnter;
	scene->exit = loadingSceneExit;
	scene->transition_in = loadingSceneTransitionIn;
	scene->transition_out = loadingSceneTransitionOut;
	scene->destroy = loadingDestroy;
	scene->transition_in_duration = TRANSITION_IN_DURATION;
	scene->transition_out_duration = TRANSITION_OUT_DURATION;
	scene->data = calloc(1, sizeof(struct LoadingData));
	if (scene->data == 0) {
		exit(1);
	}
	return scene;
}
