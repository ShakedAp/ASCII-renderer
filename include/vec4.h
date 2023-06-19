#ifndef __VEC4_H
#define __VEC4_H

typedef struct
{
    float x, y, z, w;
}vec4;

void addVec4(const vec4 left, const vec4 right, vec4 *output);
void subVec4(const vec4 left, const vec4 right, vec4 *output);

float dotVec4(const vec4 left, const vec4 right);
float lengthVec4(const vec4 vec);
void scaleVec4(vec4 *vec, const float scale);

void normalizeVec4(vec4 *vec);
float distVec4(const vec4 left, vec4 right);

void printVec4(const vec4 vec);

#endif