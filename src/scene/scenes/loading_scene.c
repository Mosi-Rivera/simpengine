#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../include/scene_manager.h"
#include "../../../include/shader_manager.h"
#include "../../../include/shaders.h"
#include "../../../include/scale.h"
#include "../../../include/camera.h"
#include "../../../include/animation.h"
#include "../../../include/input_manager.h"
#define TRANSITION_IN_DURATION 1.5f
#define TRANSITION_OUT_DURATION 1.5f

struct LoadingData {
	Camera2D camera;
};

static unsigned int frames_count = 5;

static float frames[5] = {
	100, 150, 200, 250, 300
};

static struct Animation pauseAnimation = {0};

static struct Animation simpleAnimation = {0};

static struct Animation repeatAnimation = {0};

static struct Animation reverseAnimation = {0};

static struct Animation reverseRepeatAnimation = {0};

static struct Animation yoyoAnimation = {0};

void	loadingDestroy(struct Scene* scene) {
	if (scene->data) {
		free(scene->data);
		scene->data = 0;
	}
}

void loadingSceneUpdate(void* data, float dt) {
	struct LoadingData* loading_data = data;
	loading_data->camera.target.x += dt * 20;
	animationUpdate(&pauseAnimation, dt);
	animationUpdate(&simpleAnimation, dt);
	animationUpdate(&repeatAnimation, dt);
	animationUpdate(&reverseAnimation, dt);
	animationUpdate(&reverseRepeatAnimation, dt);
	animationUpdate(&yoyoAnimation, dt);
};

void loadingSceneDraw(void* data) {
	struct LoadingData* loading_data = data;

	BeginMode2D(loading_data->camera);
	DrawText("Hello world.", getVirtualWidth() / 2 - 10, 200, 20, LIGHTGRAY);
	EndMode2D();
	// if (isDown(0)) {
	// 	DrawText("Left", getVirtualWidth() / 2, 20, 20, LIGHTGRAY);
	// }
	// if (isDown(1)) {
	// 	DrawText("right", getVirtualWidth() / 2, 60, 20, LIGHTGRAY);
	// }
	// if (isDown(2)) {
	// 	DrawText("up", getVirtualWidth() / 2, 100, 20, LIGHTGRAY);
	// }
	// if (isDown(3)) {
	// 	DrawText("down", getVirtualWidth() / 2, 140, 20, LIGHTGRAY);
	// }
	DrawRectangle(0, 0, frames[pauseAnimation.current_frame], 25, RED);
	DrawRectangle(0, 30, frames[simpleAnimation.current_frame], 25, RED);
	DrawRectangle(0, 60, frames[repeatAnimation.current_frame], 25, RED);
	DrawRectangle(0, 90, frames[reverseAnimation.current_frame], 25, RED);
	DrawRectangle(0, 120, frames[reverseRepeatAnimation.current_frame], 25, RED);
	DrawRectangle(0, 150, frames[yoyoAnimation.current_frame], 25, RED);
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

	animationInitialize(&pauseAnimation, ANIMATION_PAUSE, frames_count, 2);
	animationInitialize(&simpleAnimation, ANIMATION_SIMPLE, frames_count, 2);
	animationInitialize(&repeatAnimation, ANIMATION_REPEAT, frames_count, 2);
	animationInitialize(&reverseAnimation, ANIMATION_REVERSE, frames_count, 2);
	animationInitialize(&reverseRepeatAnimation, ANIMATION_REVERSE_REPEAT, frames_count, 2);
	animationInitialize(&yoyoAnimation, ANIMATION_YOYO, frames_count, 2);
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
