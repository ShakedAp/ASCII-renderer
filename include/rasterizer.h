#ifndef __RASTERIZER_H
#define __RASTERIZER_H

#include <stdbool.h>
#include "framebuffer.h"
#include "vec2.h"
#include "defs.h"

bool initRasterizer(const int w, const int h);
void closeRasterizer();
void clearRenderRasterizer();
void setRenderFuncRasterizer(void (*f) (framebuffer *));
void presentRasterizer();
#endif