#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>
enum animation_types {
	ANIMATION_PAUSE,
	ANIMATION_SIMPLE,
	ANIMATION_REPEAT,
	ANIMATION_REVERSE,
	ANIMATION_REVERSE_REPEAT,
	ANIMATION_YOYO,
	ANIMATION_COUNT
};

struct Quad {
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h;
};

struct Animation {
	enum animation_types type;
	unsigned int current_frame_index;
	unsigned int frame_count;
	unsigned int* frames;
	float time_to_next_frame;
	float timer;
	void(*update)(void* ptr_animation, float dt);
	char direction;
};

struct AnimationManager {
	void** animations;
	unsigned int animations_count;
	unsigned int current_animation;
};

void	animationInitialize(struct Animation* animation, enum animation_types type, unsigned int* frames, unsigned int frame_count, unsigned int fps);
void	animationUpdate(void* ptr_animation, float dt);
unsigned int	animationGetCurrentFrame(void* ptr_animation);
void	animationManagerInitialize(struct AnimationManager* animation_manager, void** animations, unsigned int animations_count);
unsigned int	animationManagerGetFrame(struct AnimationManager* animation_manager);
void	animationManagerUpdate(struct AnimationManager* animation_manager, float dt);
void	animationManagerSetActive(struct AnimationManager* animation_manager, unsigned int index);

#endif
