#ifndef __FRAMEBUFFER_H
#define __FRAMEBUFFER_H
#include <stdint.h>
#include "vec4.h"
#include "vec2.h"

#define MAX_DEPTH_VALUE 0xFF

typedef char colorbuffer;
typedef uint8_t depthbuffer;

typedef struct
{
    int width, height;
    colorbuffer *colorBuffer;
    depthbuffer *depthBuffer;
}framebuffer;

framebuffer *createFramebuffer(const int width, const int height);
void freeFramebuffer(framebuffer *fb);
void clearFramebuffer(const int clearcolor, framebuffer *fb);
void setPixelFramebuffer(const int x, const int y, colorbuffer pixelcolor, 
                        depthbuffer depth, framebuffer *fb);
void setPixelLightFramebuffer(const int x, const int y, float lightLevel,
                        depthbuffer depth, framebuffer *fb);
void setStrFramebuffer(const int x, const int y, const char *str, framebuffer *fb);
colorbuffer getPixelFramebuffer(const int x, const int y, const framebuffer *fb);
void printFramebuffer(const framebuffer *fb);

void drawFilledTriangle(const vec4 v1, const vec4 v2, const vec4 v3, float lightLevel, framebuffer *fb);
void drawEmptyTriangle(const vec4 v1, const vec4 v2, const vec4 v3, const char color, framebuffer *fb);
void drawLine(const vec2 v1, const vec2 v2, const char color, framebuffer *fb);
#endif