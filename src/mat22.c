#include "mat22.h"
#include <mat22.h>

void addMat22(const mat22 left, const mat22 right, mat22 *output)
{
    output->m00 = left.m00 + right.m00;
    output->m01 = left.m01 + right.m01;
    output->m10 = left.m10 + right.m10;
    output->m11 = left.m11 + right.m11;
}

void subMat22(const mat22 left, const mat22 right, mat22 *output)
{
    output->m00 = left.m00 - right.m00;
    output->m01 = left.m01 - right.m01;
    output->m10 = left.m10 - right.m10;
    output->m11 = left.m11 - right.m11;
}

void mulMat22(const mat22 left, const mat22 right, mat22 *output)
{
    float m00 = left.m00 * right.m00 + left.m10 * right.m01;
    float m01 = left.m01 * right.m00 + left.m11 * right.m01;
    float m10 = left.m00 * right.m10 + left.m10 * right.m11;
    float m11 = left.m01 * right.m10 + left.m11 * right.m11;

    output->m00 = m00;
    output->m01 = m01;
    output->m10 = m10;
    output->m11 = m11;
}

void transMat22(const mat22 left, const vec2 right, vec2 *output)
{
    float x = left.m00 * right.x + left.m10 * right.y;
    float y = left.m01 * right.x + left.m11 * right.y;

    output->x = x;
    output->y = y;
}


float detMat22(const mat22 mat)
{
    return mat.m00 * mat.m11 - mat.m01 * mat.m10;
}

void setIdentityMat22(mat22 *mat)
{
    mat->m00 = 1;
    mat->m11 = 1;
    mat->m01 = 0;
    mat->m10 = 0;
}

void setZeroMat22(mat22 *mat)
{
    mat->m00 = 0;
    mat->m11 = 0;
    mat->m01 = 0;
    mat->m10 = 0;
}

void transposeMat22(mat22 *mat)
{
    float temp = mat->m01;
    mat->m01 = mat->m10;
    mat->m10 = temp;
}

void invertMat22(mat22 *mat)
{
    float det = detMat22(*mat);

    if (det != 0) {
        float determinant_inv = 1.0f / det;
        float t00 =  mat->m11*determinant_inv;
        float t01 = -mat->m01*determinant_inv;
        float t11 =  mat->m00*determinant_inv;
        float t10 = -mat->m10*determinant_inv;

        mat->m00 = t00;
        mat->m01 = t01;
        mat->m10 = t10;
        mat->m11 = t11;
    }

}

void negateMat22(mat22 *mat)
{
    mat->m00 = -mat->m00;
    mat->m01 = -mat->m01;
    mat->m10 = -mat->m10;
    mat->m11 = -mat->m11;
}
