#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

enum TransitionStates {
	TransitionNone,
	TransitionIn,
	TransitionOut
};

struct Scene {
	void (*update)(void*, float);
	void (*draw)(void*);
	void (*enter)(void*);
	void (*exit)(void*);
	void (*transition_in)(void*, float);
	void (*transition_out)(void*, float);
	void (*destroy)(struct Scene* scene);
	float transition_in_duration;
	float transition_out_duration;
	void* data;
};

struct SceneTransition {
	enum TransitionStates state;
	float progress;
};

struct SceneManager {
	struct Scene* current_scene;
	struct Scene* next_scene;
	unsigned int scenes_count;
	struct SceneTransition transition;
	struct Scene* scenes;
};

void	sceneManagerInitialize(struct Scene* scenes, unsigned int scenes_count, unsigned int default_scene);
void sceneManagerUninitialize();
struct SceneManager* _getSceneManager();
void setScene(unsigned int scene);
void sceneUpdate(float dt);
void sceneDraw();

#endif
