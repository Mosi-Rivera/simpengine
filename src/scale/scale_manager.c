#include <raylib.h>
#include "../../include/config.h"
#include "../../include/math_utils.h"

static int virtual_width = DEFAULT_VIRTUAL_WIDTH;
static int virtual_height = DEFAULT_VIRTUAL_HEIGHT;
static float offset_x = 0;
static float offset_y = 0;
static float scale = 1;
static RenderTexture2D scale_texture;

void	drawScaleTexture(void) {
	DrawTexturePro(
		scale_texture.texture, 
		(Rectangle){
			0.0f, 0.0f, (float)scale_texture.texture.width, (float)-scale_texture.texture.height
		},
		(Rectangle){ 
			offset_x,
			offset_y,
			scale * virtual_width,
			scale * virtual_height
		},
		(Vector2){ 0, 0 },
		0.0f,
		WHITE
	);
}

void	resizeForce(void) {
	float screenWidth = GetScreenWidth();
	float screenHeight = GetScreenHeight();

	scale = min_float((float)screenWidth / virtual_width, (float)screenHeight / virtual_height);
	offset_x = (float)(screenWidth - ((float)virtual_width * scale)) / 2;
	offset_y = (float)(screenHeight - ((float)virtual_height * scale)) / 2;
}

void	handleResize(RenderTexture2D* scale_texture) {
	if (IsWindowResized()) {
		resizeForce();
	}
}

Vector2	getOffset(void) {
	return (Vector2){offset_x, offset_y};
}

float	getScale(void) {
	return scale;
}

int getVirtualWidth() {
	return virtual_width;
}

int getVirtualHeight() {
	return virtual_height;
}

void	beginScaledMode(void) {
	BeginTextureMode(scale_texture);
}

void	endScaledMode(void) {
	EndTextureMode();
}

void	scaleInitialize(void) {
	scale_texture = LoadRenderTexture(virtual_width, virtual_height);
	SetTextureFilter(scale_texture.texture, TEXTURE_FILTER_TRILINEAR);
	resizeForce();
}

void	scaleUninitialize(void) {
	UnloadRenderTexture(scale_texture);
}
