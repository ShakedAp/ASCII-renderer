#include "rasterizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void *renderThread(void *s);

int width, height;
bool renderStart = false, renderFinished = false, programRunning;

framebuffer *renderBuffer = NULL;
framebuffer *presentBuffer = NULL;
void (*renderFunc) (framebuffer *) = NULL;

bool initRasterizer(const int w, const int h) 
{
    width = w, height = h;
    programRunning = true;

    renderBuffer = createFramebuffer(w, h);
    presentBuffer = createFramebuffer(w, h);
    if (!renderBuffer || !presentBuffer) return false;

    // Start render thread
    unsigned long threadID;
    pthread_create(&threadID, NULL, renderThread, NULL);
    return true;
}

void closeRasterizer()
{
    programRunning = false;
    freeFramebuffer(renderBuffer);
    freeFramebuffer(presentBuffer);
}

void clearRenderRasterizer()
{
    if (renderBuffer == NULL) return;

    clearFramebuffer(0, renderBuffer);
}

void setRenderFuncRasterizer(void (*f) (framebuffer *))
{
    renderFunc = f;
}

void *renderThread(void *s)
{
    while(programRunning)
    {
        if(renderStart)
        {
            renderStart = false;
            renderFinished = false;

            if(renderFunc != NULL)
            {
                renderFunc(renderBuffer);
            }
            renderFinished = true;
        }
    }
    return NULL;
}

void presentRasterizer()
{
    if (renderBuffer == NULL || presentBuffer == NULL) return;

    renderStart = true;
    printFramebuffer(presentBuffer);
    while(!renderFinished);

    // Swap the buffers
    framebuffer *ptr = renderBuffer;
    renderBuffer = presentBuffer;
    presentBuffer = ptr;
}
