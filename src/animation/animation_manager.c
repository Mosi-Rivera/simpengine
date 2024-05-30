#include "../../include/animation.h"
#include <raylib.h>
#include <stdio.h>

void*	getActive(struct AnimationManager* animation_manager) {
	return animation_manager->animations[animation_manager->current_animation];
}

void	animationManagerSetActive(struct AnimationManager* animation_manager, unsigned int index) {
	if (index >= animation_manager->animations_count) {
		return;
	}

	animation_manager->current_animation = index;
}

void	animationManagerUpdate(struct AnimationManager* animation_manager, float dt) {
	struct Animation* animation = getActive(animation_manager);

	animationUpdate(animation, dt);
}

unsigned int	animationManagerGetFrame(struct AnimationManager* animation_manager) {
	struct Animation* animation = getActive(animation_manager);

	return animation->frames[animation->current_frame_index];
}

void	animationManagerInitialize(struct AnimationManager* animation_manager, void** animations, unsigned int animations_count) {
	animation_manager->animations = animations;
	animation_manager->animations_count = animations_count;
	animation_manager->current_animation = 0;
}
