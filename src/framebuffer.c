#include "framebuffer.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

const char *LightAscii = ".,:;ox%#@";
const long int LightAsciiLen = 9;


framebuffer *createFramebuffer(const int width, const int height)
{   
    framebuffer *fb = (framebuffer *) malloc(sizeof(framebuffer));
    if (!fb)
    {
        fprintf(stderr, "Couldn't allocate framebuffer.\n");
        return NULL;
    }
    
    colorbuffer *cb = (colorbuffer *) malloc(sizeof(colorbuffer) * width * height);
    if (!cb)
    {
        fprintf(stderr, "Couldn't allocate colorbuffer.\n");
        free(fb);
        return NULL;
    }

    depthbuffer *db = (depthbuffer *) malloc(sizeof(depthbuffer) * width * height);
    if (!db)
    {
        fprintf(stderr, "Couldn't allocate depthbuffer.\n");
        free(fb);
        free(cb);
        return NULL;
    }

    fb->width = width;
    fb->height = height;
    fb->colorBuffer = cb;
    fb->depthBuffer = db;
    clearFramebuffer(0, fb);

    return fb;
}

void freeFramebuffer(framebuffer *fb)
{
    free(fb->colorBuffer);
    free(fb->depthBuffer);
    free(fb);
}


void clearFramebuffer(const int clearcolor, framebuffer *fb)
{
    memset(fb->colorBuffer, clearcolor, sizeof(colorbuffer) * fb->width * fb->height);
    memset(fb->depthBuffer, MAX_DEPTH_VALUE, sizeof(depthbuffer) * fb->width * fb->height);
}

void setPixelLightFramebuffer(const int x, const int y, float lightLevel, depthbuffer depth, framebuffer *fb)
{
    int index = (y * fb->width) + x;
    if(index > fb->height * fb->width || index < 0) return;


    if(depth <= fb->depthBuffer[index])
    {

        fb->colorBuffer[index] = LightAscii[(int) (LightAsciiLen * lightLevel)];
        fb->depthBuffer[index] = depth;
    }
}

void setPixelFramebuffer(const int x, const int y, colorbuffer pixelcolor, depthbuffer depth, framebuffer *fb)
{
    int index = (y * fb->width) + x;
    if(index > fb->height * fb->width || index < 0) return;


    if(depth <= fb->depthBuffer[index])
    {
        fb->colorBuffer[index] = pixelcolor;
        fb->depthBuffer[index] = depth;
    }
}

colorbuffer getPixelFramebuffer(const int x, const int y, const framebuffer *fb)
{
    int index = (y * fb->width) + x;
    return fb->colorBuffer[index];
}

void setStrFramebuffer(const int x, const int y, const char *str, framebuffer *fb)
{
    int posx = x, posy = y;
    for (int i = 0, n=strlen(str); i<n; i++, posx++)
    {
        if (posx > fb->width)
        {
            posy++;
            posx = 0;
        }
        setPixelFramebuffer(posx, posy, str[i], 0, fb);
    }
}

void printFramebuffer(const framebuffer *fb)
{
    for (int i=0, w=fb->width; i<w; i++)
    {
        for (int j=0, h=fb->height; j<h; j++)
        {
            int index = (j * w) + i;
            
            if(!fb->colorBuffer[index]) continue;

            mvaddch(j, i, fb->colorBuffer[index]);
        }
    }
}

// draw
bool isPointInTriangle(const float ptx, const float pty, const vec2 v1, const vec2 v2, const vec2 v3)
{
    float wv1 = ((v2.y - v3.y) * (ptx - v3.x) +
            (v3.x - v2.x) * (pty - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) +
         (v3.x - v2.x) * (v1.y - v3.y));

    float wv2 = ((v3.y - v1.y) * (ptx - v3.x) +
            (v1.x - v3.x) * (pty - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) +
         (v3.x - v2.x) * (v1.y - v3.y));

    float wv3 = 1.0f - wv1 - wv2;

    int one = (wv1 < -0.001);
    int two = (wv2 < -0.001);
    int three = (wv3 < -0.001);

    //is the point in the triangle
    return ((one == two) && (two == three));
}


void drawFilledTriangle(const vec4 V1, const vec4 V2, const vec4 V3, float lightLevel, framebuffer *fb)
{
    // Transforming the coordinates to be from -1 to 1 
    int h_width = fb->width / 2, h_height = fb->height / 2;
    vec2 v1 = (vec2) {V1.x * h_width + h_width, -V1.y * h_height + h_height};
    vec2 v2 = (vec2) {V2.x * h_width + h_width, -V2.y * h_height + h_height};
    vec2 v3 = (vec2) {V3.x * h_width + h_width, -V3.y * h_height + h_height};
    

    // Set the border of the triangle box
    int minx = MAX(0, MIN(v1.x, MIN(v2.x, v3.x)));
    int miny = MAX(0, MIN(v1.y, MIN(v2.y, v3.y)));

    int maxx = MIN(fb->width, MAX(v1.x, MAX(v2.x, v3.x)) + 1);
    int maxy = MIN(fb->height, MAX(v1.y, MAX(v2.y, v3.y)) + 1);

    // Render the triangle
    for(int i = miny; i < maxy; i++)
    {
        for(int j = minx; j < maxx; j++)
        {
            if (isPointInTriangle(j, i, v1, v2, v3))
                setPixelLightFramebuffer(j, i, lightLevel, (V1.w + V2.w + V3.w)/3.0f, fb);
        }
    }

}


void drawEmptyTriangle(const vec4 V1, const vec4 V2, const vec4 V3, const char color, framebuffer *fb)
{
    // Transforming the coordinates to be from -1 to 1 
    int h_width = fb->width / 2, h_height = fb->height / 2;
    vec2 v1 = (vec2) {V1.x * h_width + h_width, -V1.y * h_height + h_height};
    vec2 v2 = (vec2) {V2.x * h_width + h_width, -V2.y * h_height + h_height};
    vec2 v3 = (vec2) {V3.x * h_width + h_width, -V3.y * h_height + h_height};
    drawLine(v1, v2, color, fb);
    drawLine(v1, v3, color, fb);
    drawLine(v2, v3, color, fb);
}


void drawLine(const vec2 v1, const vec2 v2, const char color, framebuffer *fb)
{
    vec2 result, current;
    subVec2(v2, v1, &result);
    float len = lengthVec2(result);
    normalizeVec2(&result);

    for (int i = 0; i < len; i++)
    {
        current = result;
        scaleVec2(&current, i);
        addVec2(v1, current, &current);
        setPixelFramebuffer(round(current.x), round(current.y), color, 0, fb);
    }

}