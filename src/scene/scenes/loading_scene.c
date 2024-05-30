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

static unsigned int* animation_frames = 0;

static struct AnimationManager animation_manager = {0};

static struct Animation pauseAnimation = {0};

static struct Animation simpleAnimation = {0};

static struct Animation repeatAnimation = {0};

static struct Animation reverseAnimation = {0};

static struct Animation reverseRepeatAnimation = {0};

static struct Animation yoyoAnimation = {0};

static void* animations[] = {
	(void*)&simpleAnimation,
	(void*)&repeatAnimation,
	(void*)&reverseAnimation,
	(void*)&yoyoAnimation,
	(void*)&reverseRepeatAnimation,
	(void*)&pauseAnimation
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
	if (isPressed(0)) {
		animationManagerSetActive(&animation_manager, 0);
	}
	if (isPressed(1)) {
		animationManagerSetActive(&animation_manager, 1);
	}
	if (isPressed(2)) {
		animationManagerSetActive(&animation_manager, 2);
	}
	if (isPressed(3)) {
		animationManagerSetActive(&animation_manager, 3);
	}
	animationManagerUpdate(&animation_manager, dt);
};

void loadingSceneDraw(void* data) {
	struct LoadingData* loading_data = data;

	BeginMode2D(loading_data->camera);
	DrawText("Hello world.", getVirtualWidth() / 2 - 10, 200, 20, LIGHTGRAY);
	EndMode2D();
	DrawRectangle(0, 100, frames[animationManagerGetFrame(&animation_manager)], 20, RED);
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
	animation_frames = (unsigned int*)calloc(5, sizeof(unsigned int));
	if (animation_frames == 0) {
		exit(1);
	}

	for (unsigned int i = 0; i < 5; i++) {
		animation_frames[i] = i;
	}

	animationInitialize(&pauseAnimation, ANIMATION_PAUSE, animation_frames, frames_count, 2);
	animationInitialize(&simpleAnimation, ANIMATION_SIMPLE, animation_frames, frames_count, 2);
	animationInitialize(&repeatAnimation, ANIMATION_REPEAT, animation_frames, frames_count, 2);
	animationInitialize(&reverseAnimation, ANIMATION_REVERSE, animation_frames, frames_count, 2);
	animationInitialize(&reverseRepeatAnimation, ANIMATION_REVERSE_REPEAT, animation_frames, frames_count, 2);
	animationInitialize(&yoyoAnimation, ANIMATION_YOYO, animation_frames, frames_count, 2);

	animationManagerInitialize(
		&animation_manager,
		animations,
		5
	);
	printf("\nenter Loading\n");
}

void loadingSceneExit(void* data) {
	free(animation_frames);
}

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
