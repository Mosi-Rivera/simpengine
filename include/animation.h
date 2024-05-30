#ifndef ANIMATION_H
#define ANIMATION_H

enum animation_types {
	ANIMATION_PAUSE,
	ANIMATION_SIMPLE,
	ANIMATION_REPEAT,
	ANIMATION_REVERSE,
	ANIMATION_REVERSE_REPEAT,
	ANIMATION_YOYO,
	ANIMATION_COUNT
};

struct Animation {
	enum animation_types type;
	unsigned int current_frame;
	unsigned int frame_count;
	float time_to_next_frame;
	float timer;
	void(*update)(void* ptr_animation, float dt);
	char direction;
};

void	animationInitialize(struct Animation* animation, enum animation_types type, unsigned int frame_count, unsigned int fps);
void	animationUpdate(void* ptr_animation, float dt);

#endif
