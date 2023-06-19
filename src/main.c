#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include<sys/time.h>

#include "objectLoader.h"
#include "framebuffer.h"
#include "rasterizer.h"
#include "camera.h"
#include "mat44.h"
#include "vec4.h"
#include "defs.h"


long long timeInMilliseconds() {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

void renderfunc(framebuffer *fb);
void *getInput(void *s);

bool running = 1;
triangle *objectTrigs;
int objectTrigLen;
WINDOW *inputWin;
float angle = 0.0f, inc = 0.001f;
int dispFrames;

int main(int argc, char *argv[])
{
    char *meshPath = "meshes/cube.obj";

    if(argc > 2)
    {
        printf("Sorry, too much arguments. \n");
        return 1;
    }
    if (argc == 2)
        meshPath = argv[1];
    
    objectTrigs = loadFromObject(meshPath, &objectTrigLen);
    if (objectTrigLen == 0 || objectTrigs == NULL)
    {
        printf("Sorry, couldn't load the object located at: %s \n", meshPath);
        return 2;
    }

    initscr();
    raw();
    noecho();
    curs_set(0);

    inputWin = newwin(10, 10, 0, 0);
    keypad(inputWin, true);

    running = initRasterizer(WW, WH); 

    setRenderFuncRasterizer(&renderfunc);

    unsigned long threadID;
    pthread_create(&threadID, NULL, getInput, NULL);

    long long lastTime, currentTime = timeInMilliseconds();
    int dt = 0, frames = 0;
    while(running)
    {
        // Counting the frames per second
        lastTime = currentTime;
        currentTime = timeInMilliseconds();
        dt += currentTime - lastTime;
        frames++;
        if (dt >= 1000)
        {
            dt = 0;
            dispFrames = frames;
            frames = 0;
        }

        presentRasterizer();
        refresh();
        erase();
    }

    closeRasterizer();
    free(objectTrigs);

    endwin();
    return 0;
}

void transformVertex(const vec4 vertex, const mat44 VPMatrix, vec4 *output){
    transMat44(VPMatrix, vertex, output);

    output->x /= output->w;
    output->y /= output->w;
    output->z /= output->w;
}
int toatalClipped = 0;
void renderfunc(framebuffer *fb)
{

    clearRenderRasterizer(); // Clear render buffer

    angle += inc; 
    if (angle >= 2*PI)
        angle -= 2*PI;
    mat44 transformMat, viewMat, projMat;

    // Setting up matrices
    calcViewMatrixCamera(&viewMat);
    calcProjectionCamera(70.0f, (WW / 2.f) / WH, .1f, 1000.0f, &projMat);

    setIdentityMat44(&transformMat);
    translateMat44(&transformMat, (vec3) {0, 0.1, -3});
    rotateMat44(&transformMat, (vec3) {0, 0, 1}, angle);
    rotateMat44(&transformMat, (vec3) {0, 1, 0}, angle);
    rotateMat44(&transformMat, (vec3) {1, 0, 0}, angle);
    

    for (int i=0; i<objectTrigLen; i++)
    {
        vec4 v1 = {objectTrigs[i].vert1.x, objectTrigs[i].vert1.y, objectTrigs[i].vert1.z, 1.0f};
        vec4 v2 = {objectTrigs[i].vert2.x, objectTrigs[i].vert2.y, objectTrigs[i].vert2.z, 1.0f};
        vec4 v3 = {objectTrigs[i].vert3.x, objectTrigs[i].vert3.y, objectTrigs[i].vert3.z, 1.0f};

        // World
        transMat44(transformMat, v1, &v1);
        transMat44(transformMat, v2, &v2);
        transMat44(transformMat, v3, &v3);

        // Clip
        triangle triViewed = {{v1.x, v1.y, v1.z},
                              {v2.x, v2.y, v2.z},
                              {v3.x, v3.y, v3.z}};

        int nClippedTriangles = 0;
        triangle clipped[2];
        nClippedTriangles = triangleClipPlane((vec3) { 0.0f, 0.0f, 0.1f }, (vec3) { 0.0f, 0.0f, 1.0f }, 
                                                        triViewed, &clipped[0], &clipped[1]);

        
        toatalClipped += nClippedTriangles;
        // We may end up with multiple triangles form the clip, so project as required
        // for (int n = 0; n < nClippedTriangles; n++)
        // {
        //     v1 = (vec4) {clipped[n].vert1.x, clipped[n].vert1.y, clipped[n].vert1.z, 1.0f};
        //     v2 = (vec4) {clipped[n].vert2.x, clipped[n].vert2.y, clipped[n].vert2.z, 1.0f};
        //     v3 = (vec4) {clipped[n].vert3.x, clipped[n].vert3.y, clipped[n].vert3.z, 1.0f};

            vec3 normal, line1, line2, toCamera;
            subVec3((vec3) {v1.x, v1.y, v1.z}, (vec3) {v2.x, v2.y, v2.z}, &line1);
            subVec3((vec3) {v1.x, v1.y, v1.z}, (vec3) {v3.x, v3.y, v3.z}, &line2);
            
            crossVec3(line1, line2, &normal);
            normalizeVec3(&normal);

            subVec3((vec3) {v1.x, v1.y, v1.z}, positionCamera, &toCamera);

            if (dotVec3(normal, toCamera) < 0.0f)
            {
                vec3 lightDirection = {0.0f, 0.0f, 1.0f}; 
                normalizeVec3(&lightDirection);
                float lightLevel = MAX(0.0f, dotVec3(normal, lightDirection));
                
                // View
                transMat44(viewMat, v1, &v1);
                transMat44(viewMat, v2, &v2);
                transMat44(viewMat, v3, &v3);
                
                // Projected
                transformVertex(v1, projMat, &v1);
                transformVertex(v2, projMat, &v2);
                transformVertex(v3, projMat, &v3);
                drawFilledTriangle(v1, v2, v3, lightLevel, fb);
                // drawEmptyTriangle(v1, v2, v3, '0', fb); ++lightLevel;
            }

        // }
    }

    // Create cursor
    setPixelFramebuffer(WW/2, WH/2, '+', 0, fb);
    // Display text to the screen;
    char buffer[WW];

    sprintf(buffer, "frames: %i, angle_inc=%.5f, angle=%.5f, cam_pos: %.3fx %.3fy %.3fz, cam_rot: %.3fpitch %.3fyaw, Clipped: %i", dispFrames, inc, angle, positionCamera.x, positionCamera.y, positionCamera.z, rotationCamera.x, rotationCamera.y, toatalClipped);

    setStrFramebuffer(0, 0, buffer, fb);
}

void *getInput(void *s)
{   
    int c;
    vec3 movement;
    while(running)
    {
        c = wgetch(inputWin);
        if (c == 3) // ctrl c
        {
            running = false;
            continue;
        }

        movement = (vec3) {0.0f, 0.0f, 0.0f};
        float mvunit = 0.05, rotunit = 0.05;

        switch (c)
        {
        case 'w':
            movement.z = -mvunit;
            break;
        case 's':
            movement.z = mvunit;
            break;
        case 'd':
            movement.x = mvunit;
            break;
        case 'a':
            movement.x = -mvunit;
            break;
        
        case KEY_DOWN:
            rotationCamera.x += rotunit;
        break;
        case KEY_UP:
            rotationCamera.x -= rotunit;
        break;
        case KEY_LEFT:
            rotationCamera.y -= rotunit;
        break;
        case KEY_RIGHT:
            rotationCamera.y += rotunit;
        break;

        case 'q':
            inc /= 10.0f;
            if (inc < 0.00001f)
                inc = 0.00001f;
            break;
        case 'e':
            inc *= 10.0f;
            if (inc > 1.0f)
                inc = 1.0f;
            break;
        }
        yrotateVec3(&movement, rotationCamera.y);
        xrotateVec3(&movement, rotationCamera.x);
        addVec3(positionCamera, movement, &positionCamera);        
    }

    return NULL;
}