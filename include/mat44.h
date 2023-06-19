#ifndef __MAT44_H
#define __MAT44_H
#include "vec4.h"
#include "vec3.h"

typedef struct
{
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
}mat44;

void addMat44(const mat44 left, const mat44 right, mat44 *output);
void subMat44(const mat44 left, const mat44 right, mat44 *output);
void mulMat44(const mat44 left, const mat44 right, mat44 *output);
void transMat44(const mat44 left, const vec4 right, vec4 *output);

float detMat44(const mat44 mat);

void setIdentityMat44(mat44 *mat);
void setZeroMat44(mat44 *mat);
void transposeMat44(mat44 *mat);
void invertMat44(mat44 *mat);
void negateMat44(mat44 *mat);

void scaleMat44(mat44 *mat, const vec3 scale);
void rotateMat44(mat44 *mat, const vec3 eulerAxis, const float angle);
void translateMat44(mat44 *mat, const vec3 vec);

#endif