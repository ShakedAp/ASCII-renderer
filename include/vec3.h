#ifndef __VEC3_H
#define __VEC3_H

#include "defs.h"

typedef struct
{
    float x, y, z;
}vec3;

typedef struct
{
    vec3 vert1, vert2, vert3;
} triangle;

void addVec3(const vec3 left, const vec3 right, vec3 *output);
void subVec3(const vec3 left, const vec3 right, vec3 *output);
void crossVec3(const vec3 left, const vec3 right, vec3 *output);

float dotVec3(const vec3 left, const vec3 right);
float lengthVec3(const vec3 vec);
void scaleVec3(vec3 *vec, const float scale);

float angleVec3(const vec3 left, const vec3 right);
void normalizeVec3(vec3 *vec);
float distVec3(const vec3 left, vec3 right);

void xrotateVec3(vec3 *vec, float angle);
void yrotateVec3(vec3 *vec, float angle);
void zrotateVec3(vec3 *vec, float angle);

void planeIntersectVec3(vec3 planePoint, vec3 planeNormal, vec3 lineStart, vec3 lineEnd, vec3 *output);
int triangleClipPlane(vec3 planePoint, vec3 planeNormal, triangle inTri, triangle *outTri1, triangle *outTri2);
#endif