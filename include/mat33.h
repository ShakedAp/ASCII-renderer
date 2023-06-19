#ifndef __MAT33_H
#define __MAT33_H
#include "vec3.h"

typedef struct
{
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
}mat33;

void addMat33(const mat33 left, const mat33 right, mat33 *output);
void subMat33(const mat33 left, const mat33 right, mat33 *output);
void mulMat33(const mat33 left, const mat33 right, mat33 *output);
void transMat33(const mat33 left, const vec3 right, vec3 *output);

float detMat33(const mat33 mat);

void setIdentityMat33(mat33 *mat);
void setZeroMat33(mat33 *mat);
void transposeMat33(mat33 *mat);
void invertMat33(mat33 *mat);
void negateMat33(mat33 *mat);

#endif