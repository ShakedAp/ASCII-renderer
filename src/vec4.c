#include "vec4.h"
#include <math.h>

void addVec4(const vec4 left, const vec4 right, vec4 *output)
{
    output->x = left.x + right.x;
    output->y = left.y + right.y;
    output->z = left.z + right.z;
    output->w = left.w + right.w;
}

void subVec4(const vec4 left, const vec4 right, vec4 *output)
{
    output->x = left.x - right.x;
    output->y = left.y - right.y;
    output->z = left.z - right.z;
    output->w = left.w - right.w;
}


float dotVec4(const vec4 left, const vec4 right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

float lengthVec4(const vec4 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

void scaleVec4(vec4 *vec, const float scale)
{
    vec->x *= scale;
    vec->y *= scale;
    vec->z *= scale;
    vec->w *= scale;
}

void normalizeVec4(vec4 *vec)
{
   float len = lengthVec4(*vec);

    vec->x /= len;
    vec->y /= len;
    vec->z /= len;
    vec->w /= len;
}

float distVec4(const vec4 left, vec4 right)
{
    float x = left.x - right.x;
    float y = left.y - right.y;
    float z = left.z - right.z;
    float w = left.w - right.w;

    return sqrt(x * x + y * y + z * z + w * w);
}