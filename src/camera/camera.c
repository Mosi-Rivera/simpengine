#include <raylib.h>

void	cameraInitialize(Camera2D* camera, Vector2 offset, Vector2 target) {
	*camera = (Camera2D){0};
	camera->target = target;
	camera->offset = offset;
	camera->rotation = 0;
	camera->zoom = 1;
}
