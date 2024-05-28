#ifndef SCALE_H
#define SCALE_H

void	scaleInitialize();
void	scaleUninitialize();
void	drawScaleTexture();
void	resizeForce();
void	handleResize();
void	beginScaledMode();
void	endScaledMode(void);
int	getVirtualWidth();
int	getVirtualHeight();

#endif
