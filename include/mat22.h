#ifndef __MAT22_H
#define __MAT22_H
#include "vec2.h"

typedef struct
{
    float m00, m01;
    float m10, m11;
}mat22;

void addMat22(const mat22 left, const mat22 right, mat22 *output);
void subMat22(const mat22 left, const mat22 right, mat22 *output);
void mulMat22(const mat22 left, const mat22 right, mat22 *output);
void transMat22(const mat22 left, const vec2 right, vec2 *output);

float detMat22(const mat22 mat);

void setIdentityMat22(mat22 *mat);
void setZeroMat22(mat22 *mat);
void transposeMat22(mat22 *mat);
void invertMat22(mat22 *mat);
void negateMat22(mat22 *mat);

#endif