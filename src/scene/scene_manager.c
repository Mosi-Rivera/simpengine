#include "../../include/scene_manager.h"
#include <stdio.h>

static struct SceneManager scene_manager = {0};

struct SceneManager* _getSceneManager() {
	return &scene_manager;
}

struct Scene*	getScene(unsigned int scene) {
	return &scene_manager.scenes[scene];
}

void setTransition(enum TransitionStates state, float transition_duration) {
	scene_manager.transition = (struct SceneTransition){state, transition_duration};
}

void	sceneExit() {
	struct Scene* current_scene = scene_manager.current_scene;
	if (current_scene) {
		current_scene->exit(current_scene->data);
	}
}

void	sceneEnter() {
	struct Scene* current_scene = scene_manager.current_scene;
	if (current_scene) {
		current_scene->enter(current_scene->data);
	}
}

void setScene(unsigned int scene) {
	if (scene_manager.current_scene == 0) {
		scene_manager.current_scene = getScene(scene);
		sceneEnter();
		setTransition(TransitionIn, getScene(scene)->transition_in_duration);
	} else {
		scene_manager.next_scene = getScene(scene);
		if (scene_manager.transition.state == TransitionNone) {
			setTransition(TransitionOut, getScene(scene)->transition_out_duration);
		}
	}
}

void	sceneManagerInitialize(struct Scene* scenes, unsigned int scenes_count, unsigned int default_scene) {

	scene_manager.current_scene = 0;
	scene_manager.next_scene = 0;
	scene_manager.scenes_count = scenes_count;
	scene_manager.scenes = scenes;

	setScene(default_scene);
}

void sceneManagerUninitialize() {
	struct Scene* scenes = scene_manager.scenes;
	struct Scene* scene;
	unsigned int i = 0;
	unsigned int l = scene_manager.scenes_count;

	while (i < l) {
		scene = &scenes[i++];
		scene->destroy(scene);
	}
}

void transitionOutUpdate(float dt) {
	scene_manager.transition.progress -= dt;
	if (scene_manager.transition.progress <= 0) {
		sceneExit();
		scene_manager.current_scene = scene_manager.next_scene;
		scene_manager.next_scene = 0;
		sceneEnter();
		setTransition(TransitionIn, scene_manager.current_scene->transition_in_duration);
	}
}

void transitionInUpdate(float dt) {
	scene_manager.transition.progress -= dt;
	if (scene_manager.transition.progress <= 0) {
		if (scene_manager.next_scene != 0) {
			setTransition(TransitionOut, scene_manager.current_scene->transition_out_duration);
		} else {
			setTransition(TransitionNone, 0);
		}
	}
}

void transitionUpdate(float dt) {
	struct SceneTransition* transition = &scene_manager.transition;

	if (transition->state == TransitionOut) {
		transitionOutUpdate(dt);
	} else if (transition->state == TransitionIn) {
		transitionInUpdate(dt);
	}
}

void drawSceneTransition(struct Scene *scene) {
	struct SceneTransition transition = scene_manager.transition;

	if (transition.state == TransitionIn) {
		scene->transition_in(scene->data, transition.progress);
	} else if (transition.state == TransitionOut) {
		scene->transition_out(scene->data, transition.progress);
	}
}

void sceneDraw() {
	struct Scene* current_scene = scene_manager.current_scene;

	current_scene->draw(current_scene->data);
	drawSceneTransition(current_scene);
}

void sceneUpdate(float dt) {
	struct Scene* current_scene = scene_manager.current_scene;

	current_scene->update(current_scene->data, dt);
	transitionUpdate(dt);
}
