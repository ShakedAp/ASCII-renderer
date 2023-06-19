#ifndef __VEC2_H
#define __VEC2_H

typedef struct
{
    float x, y;
}vec2;

void addVec2(const vec2 left, const vec2 right, vec2 *output);
void subVec2(const vec2 left, const vec2 right, vec2 *output);

float dotVec2(const vec2 left, const vec2 right);
float lengthVec2(const vec2 vec);
void scaleVec2(vec2 *vec, const float scale);

float angleVec2(const vec2 left, const vec2 right);
void normalizeVec2(vec2 *vec);
float distVec2(const vec2 left, vec2 right);

#endif
