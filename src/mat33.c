#include "mat33.h"
#include <math.h>

void addMat33(const mat33 left, const mat33 right, mat33 *output)
{
    output->m00 = left.m00 + right.m00;
    output->m01 = left.m01 + right.m01;
    output->m02 = left.m02 + right.m02;

    output->m10 = left.m10 + right.m10;
    output->m11 = left.m11 + right.m11;
    output->m12 = left.m12 + right.m12;

    output->m20 = left.m20 + right.m20;
    output->m21 = left.m21 + right.m21;
    output->m22 = left.m22 + right.m22;
}

void subMat33(const mat33 left, const mat33 right, mat33 *output)
{
    output->m00 = left.m00 - right.m00;
    output->m01 = left.m01 - right.m01;
    output->m02 = left.m02 - right.m02;

    output->m10 = left.m10 - right.m10;
    output->m11 = left.m11 - right.m11;
    output->m12 = left.m12 - right.m12;

    output->m20 = left.m20 - right.m20;
    output->m21 = left.m21 - right.m21;
    output->m22 = left.m22 - right.m22;
}

void mulMat33(const mat33 left, const mat33 right, mat33 *output)
{
    float m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02;
    float m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02;
    float m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02;
    float m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12;
    float m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12;
    float m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12;
    float m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22;
    float m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22;
    float m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22;

    output->m00 = m00;
    output->m01 = m01;
    output->m02 = m02;
    output->m10 = m10;
    output->m11 = m11;
    output->m12 = m12;
    output->m20 = m20;
    output->m21 = m21;
    output->m22 = m22;
}

void transMat33(const mat33 left, const vec3 right, vec3 *output)
{
    float x = left.m00 * right.x + left.m10 * right.y + left.m20 * right.z;
    float y = left.m01 * right.x + left.m11 * right.y + left.m21 * right.z;
    float z = left.m02 * right.x + left.m12 * right.y + left.m22 * right.z;

    output->x = x;
    output->y = y;
    output->z = z;
}


float detMat33(const mat33 mat)
{
    return mat.m00 * (mat.m11 * mat.m22 - mat.m12 * mat.m21)
            + mat.m01 * (mat.m12 * mat.m20 - mat.m10 * mat.m22)
            + mat.m02 * (mat.m10 * mat.m21 - mat.m11 * mat.m20);
}

void setIdentityMat33(mat33 *mat)
{
    mat->m00 = 1;
    mat->m01 = 0;
    mat->m02 = 0;

    mat->m10 = 0;
    mat->m11 = 1;
    mat->m12 = 0;

    mat->m20 = 0;
    mat->m21 = 0;
    mat->m22 = 1;
}

void setZeroMat33(mat33 *mat)
{
    mat->m00 = 0;
    mat->m01 = 0;
    mat->m02 = 0;

    mat->m10 = 0;
    mat->m11 = 0;
    mat->m12 = 0;

    mat->m20 = 0;
    mat->m21 = 0;
    mat->m22 = 0;
}

void transposeMat33(mat33 *mat)
{
    float m00 = mat->m00;
    float m01 = mat->m10;
    float m02 = mat->m20;
    float m10 = mat->m01;
    float m11 = mat->m11;
    float m12 = mat->m21;
    float m20 = mat->m02;
    float m21 = mat->m12;
    float m22 = mat->m22;

    mat->m00 = m00;
    mat->m01 = m01;
    mat->m02 = m02;
    mat->m10 = m10;
    mat->m11 = m11;
    mat->m12 = m12;
    mat->m20 = m20;
    mat->m21 = m21;
    mat->m22 = m22;
}

void invertMat33(mat33 *mat)
{
    float det = detMat33(*mat);

    if (det != 0) {
        float determinant_inv = 1.0f / det;

        float t00 = mat->m11 * mat->m22 - mat->m12* mat->m21;
        float t01 = - mat->m10 * mat->m22 + mat->m12 * mat->m20;
        float t02 = mat->m10 * mat->m21 - mat->m11 * mat->m20;
        float t10 = - mat->m01 * mat->m22 + mat->m02 * mat->m21;
        float t11 = mat->m00 * mat->m22 - mat->m02 * mat->m20;
        float t12 = - mat->m00 * mat->m21 + mat->m01 * mat->m20;
        float t20 = mat->m01 * mat->m12 - mat->m02 * mat->m11;
        float t21 = -mat->m00 * mat->m12 + mat->m02 * mat->m10;
        float t22 = mat->m00 * mat->m11 - mat->m01 * mat->m10;

        mat->m00 = t00*determinant_inv;
        mat->m11 = t11*determinant_inv;
        mat->m22 = t22*determinant_inv;
        mat->m01 = t10*determinant_inv;
        mat->m10 = t01*determinant_inv;
        mat->m20 = t02*determinant_inv;
        mat->m02 = t20*determinant_inv;
        mat->m12 = t21*determinant_inv;
        mat->m21 = t12*determinant_inv;
    }
}

void negateMat33(mat33 *mat)
{
    mat->m00 = -mat->m00;
    mat->m01 = -mat->m02;
    mat->m02 = -mat->m01;
    mat->m10 = -mat->m10;
    mat->m11 = -mat->m12;
    mat->m12 = -mat->m11;
    mat->m20 = -mat->m20;
    mat->m21 = -mat->m22;
    mat->m22 = -mat->m21;
}
