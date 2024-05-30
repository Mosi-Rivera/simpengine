#include "../../include/animation.h"
#include "../../include/math_utils.h"

void	updateSimple(void* ptr_animation, float dt) {
	struct Animation* animation = ptr_animation;

	animation->timer += dt;
	if (animation->timer >= animation->time_to_next_frame) {
		animation->timer = 0;
		animation->current_frame = min_uint(animation->current_frame + 1, animation->frame_count - 1);
	}
}

void	updateRepeat(void* ptr_animation, float dt) {
	struct Animation* animation = ptr_animation;

	animation->timer += dt;
	if (animation->timer >= animation->time_to_next_frame) {
		animation->timer = 0;
		animation->current_frame = (animation->current_frame + 1) % animation->frame_count;
	}
}

void	updateReverse(void* ptr_animation, float dt) {
	struct Animation* animation = ptr_animation;

	animation->timer += dt;
	if (animation->timer >= animation->time_to_next_frame) {
		animation->timer = 0;
		if (animation->current_frame != 0) {
			animation->current_frame--;
		}
	}
}

void	updateReverseRepeat(void* ptr_animation, float dt) {
	struct Animation* animation = ptr_animation;

	animation->timer += dt;
	if (animation->timer >= animation->time_to_next_frame) {
		animation->timer = 0;
		if (animation->current_frame == 0) {
			animation->current_frame = animation->frame_count - 1;
		} else {
			animation->current_frame--;
		}
	}
}

void	updateYoyo(void* ptr_animation, float dt) {
	struct Animation* animation = ptr_animation;

	animation->timer += dt;
	if (animation->timer >= animation->time_to_next_frame) {
		animation->timer = 0;
		if (animation->current_frame == (animation->direction < 0 ? 0 : animation->frame_count - 1)) {
			animation->direction = animation->direction < 0 ? 1 : -1;
		}
		animation->current_frame = animation->current_frame + (animation->direction < 0 ? -1 : 1);
	}
}

void	animationInitialize(struct Animation* animation, enum animation_types type, unsigned int frame_count, unsigned int fps) {
	animation->current_frame = 0;
	animation->frame_count = frame_count;
	animation->time_to_next_frame = 1.f / fps;
	animation->type = type;
	switch (type) {
		case ANIMATION_PAUSE: animation->update = 0; break;
		case ANIMATION_SIMPLE: animation->update = updateSimple; break;
		case ANIMATION_REPEAT: animation->update = updateRepeat; break;
		case ANIMATION_REVERSE: {
			animation->current_frame = frame_count - 1;
			animation->update = updateReverse;
			break;
		}
		case ANIMATION_REVERSE_REPEAT: {
			animation->current_frame = frame_count - 1;
			animation->update = updateReverseRepeat;
			break;
		}
		case ANIMATION_YOYO: animation->update = updateYoyo; break;
		default: break;
	}
}

void	animationUpdate(void* ptr_animation, float dt) {
	struct Animation* animation = ptr_animation;

	if (animation->type == ANIMATION_PAUSE) {
		return;
	}

	animation->update(animation, dt);
}
