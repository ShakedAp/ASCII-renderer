#include "vec2.h"
#include <math.h>

void addVec2(const vec2 left, const vec2 right, vec2 *output)
{
    output->x = left.x + right.x;
    output->y = left.y + right.y;
}

void subVec2(const vec2 left, const vec2 right, vec2 *output)
{
    output->x = left.x - right.x;
    output->y = left.y - right.y;
}


float dotVec2(const vec2 left, const vec2 right)
{
    return left.x * right.x + left.y * right.y;
}

float lengthVec2(const vec2 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

void scaleVec2(vec2 *vec, const float scale)
{
    vec->x *= scale;
    vec->y *= scale;
}


float angleVec2(const vec2 left, const vec2 right)
{
    float dot = dotVec2(left, right);
    return acos(dot/(lengthVec2(left) * lengthVec2(right)));
}

void normalizeVec2(vec2 *vec)
{
   float len = lengthVec2(*vec);

    vec->x /= len;
    vec->y /= len;
}

float distVec2(const vec2 left, vec2 right)
{
    float x = left.x - right.x;
    float y = left.y - right.y;

    return sqrt(x * x + y * y);
}
