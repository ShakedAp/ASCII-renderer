#include "mat44.h"
#include <math.h>

// Use macro to avoid function call
#define DET33(t00, t01, t02, t10, t11, t12, t20, t21, t22) (((t00) * ((t11) * (t22) - (t12) * (t21))) + ((t01) * ((t12) * (t20) - (t10) * (t22))) + ((t02) * ((t10) * (t21) - (t11) * (t20))))

void addMat44(const mat44 left, const mat44 right, mat44 *output)
{
    output->m00 = left.m00 + right.m00;
    output->m01 = left.m01 + right.m01;
    output->m02 = left.m02 + right.m02;
    output->m03 = left.m03 + right.m03;

    output->m10 = left.m10 + right.m10;
    output->m11 = left.m11 + right.m11;
    output->m12 = left.m12 + right.m12;
    output->m13 = left.m13 + right.m13;

    output->m20 = left.m20 + right.m20;
    output->m21 = left.m21 + right.m21;
    output->m22 = left.m22 + right.m22;
    output->m23 = left.m23 + right.m23;

    output->m30 = left.m30 + right.m30;
    output->m31 = left.m31 + right.m31;
    output->m32 = left.m32 + right.m32;
    output->m33 = left.m33 + right.m33;
}

void subMat44(const mat44 left, const mat44 right, mat44 *output)
{
    output->m00 = left.m00 - right.m00;
    output->m01 = left.m01 - right.m01;
    output->m02 = left.m02 - right.m02;
    output->m03 = left.m03 - right.m03;

    output->m10 = left.m10 - right.m10;
    output->m11 = left.m11 - right.m11;
    output->m12 = left.m12 - right.m12;
    output->m13 = left.m13 - right.m13;

    output->m20 = left.m20 - right.m20;
    output->m21 = left.m21 - right.m21;
    output->m22 = left.m22 - right.m22;
    output->m23 = left.m23 - right.m23;

    output->m30 = left.m30 - right.m30;
    output->m31 = left.m31 - right.m31;
    output->m32 = left.m32 - right.m32;
    output->m33 = left.m33 - right.m33;
}

void mulMat44(const mat44 left, const mat44 right, mat44 *output)
{
    float m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02 + left.m30 * right.m03;
    float m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02 + left.m31 * right.m03;
    float m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02 + left.m32 * right.m03;
    float m03 = left.m03 * right.m00 + left.m13 * right.m01 + left.m23 * right.m02 + left.m33 * right.m03;
    float m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12 + left.m30 * right.m13;
    float m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12 + left.m31 * right.m13;
    float m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12 + left.m32 * right.m13;
    float m13 = left.m03 * right.m10 + left.m13 * right.m11 + left.m23 * right.m12 + left.m33 * right.m13;
    float m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22 + left.m30 * right.m23;
    float m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22 + left.m31 * right.m23;
    float m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22 + left.m32 * right.m23;
    float m23 = left.m03 * right.m20 + left.m13 * right.m21 + left.m23 * right.m22 + left.m33 * right.m23;
    float m30 = left.m00 * right.m30 + left.m10 * right.m31 + left.m20 * right.m32 + left.m30 * right.m33;
    float m31 = left.m01 * right.m30 + left.m11 * right.m31 + left.m21 * right.m32 + left.m31 * right.m33;
    float m32 = left.m02 * right.m30 + left.m12 * right.m31 + left.m22 * right.m32 + left.m32 * right.m33;
    float m33 = left.m03 * right.m30 + left.m13 * right.m31 + left.m23 * right.m32 + left.m33 * right.m33;

    output->m00 = m00;
    output->m01 = m01;
    output->m02 = m02;
    output->m03 = m03;
    output->m10 = m10;
    output->m11 = m11;
    output->m12 = m12;
    output->m13 = m13;
    output->m20 = m20;
    output->m21 = m21;
    output->m22 = m22;
    output->m23 = m23;
    output->m30 = m30;
    output->m31 = m31;
    output->m32 = m32;
    output->m33 = m33;
}

void transMat44(const mat44 left, const vec4 right, vec4 *output)
{
    float x = left.m00 * right.x + left.m10 * right.y + left.m20 * right.z + left.m30 * right.w;
    float y = left.m01 * right.x + left.m11 * right.y + left.m21 * right.z + left.m31 * right.w;
    float z = left.m02 * right.x + left.m12 * right.y + left.m22 * right.z + left.m32 * right.w;
    float w = left.m03 * right.x + left.m13 * right.y + left.m23 * right.z + left.m33 * right.w;

    output->x = x;
    output->y = y;
    output->z = z;
    output->w = w;
}

float detMat44(const mat44 mat)
{
    float f = mat.m00 * ((mat.m11 * mat.m22 * mat.m33 + mat.m12 * mat.m23 * mat.m31 + mat.m13 * mat.m21 * mat.m32)
            - mat.m13 * mat.m22 * mat.m31
            - mat.m11 * mat.m23 * mat.m32
            - mat.m12 * mat.m21 * mat.m33);
    f -= mat.m01 * ((mat.m10 * mat.m22 * mat.m33 + mat.m12 * mat.m23 * mat.m30 + mat.m13 * mat.m20 * mat.m32)
            - mat.m13 * mat.m22 * mat.m30
            - mat.m10 * mat.m23 * mat.m32
            - mat.m12 * mat.m20 * mat.m33);
    f += mat.m02 * ((mat.m10 * mat.m21 * mat.m33 + mat.m11 * mat.m23 * mat.m30 + mat.m13 * mat.m20 * mat.m31)
            - mat.m13 * mat.m21 * mat.m30
            - mat.m10 * mat.m23 * mat.m31
            - mat.m11 * mat.m20 * mat.m33);
    f -= mat.m03 * ((mat.m10 * mat.m21 * mat.m32 + mat.m11 * mat.m22 * mat.m30 + mat.m12 * mat.m20 * mat.m31)
            - mat.m12 * mat.m21 * mat.m30
            - mat.m10 * mat.m22 * mat.m31
            - mat.m11 * mat.m20 * mat.m32);
    
    return f;
}

void setIdentityMat44(mat44 *mat)
{
    mat->m00 = 1;
    mat->m01 = 0;
    mat->m02 = 0;
    mat->m03 = 0;

    mat->m10 = 0;
    mat->m11 = 1;
    mat->m12 = 0;
    mat->m13 = 0;

    mat->m20 = 0;
    mat->m21 = 0;
    mat->m22 = 1;
    mat->m23 = 0;

    mat->m30 = 0;
    mat->m31 = 0;
    mat->m32 = 0;
    mat->m33 = 1;
}

void setZeroMat44(mat44 *mat)
{
    mat->m00 = 0;
    mat->m01 = 0;
    mat->m02 = 0;
    mat->m03 = 0;

    mat->m10 = 0;
    mat->m11 = 0;
    mat->m12 = 0;
    mat->m13 = 0;

    mat->m20 = 0;
    mat->m21 = 0;
    mat->m22 = 0;
    mat->m23 = 0;

    mat->m30 = 0;
    mat->m31 = 0;
    mat->m32 = 0;
    mat->m33 = 0;
}

void transposeMat44(mat44 *mat)
{
    float m00 = mat->m00;
    float m01 = mat->m10;
    float m02 = mat->m20;
    float m03 = mat->m30;
    float m10 = mat->m01;
    float m11 = mat->m11;
    float m12 = mat->m21;
    float m13 = mat->m31;
    float m20 = mat->m02;
    float m21 = mat->m12;
    float m22 = mat->m22;
    float m23 = mat->m32;
    float m30 = mat->m03;
    float m31 = mat->m13;
    float m32 = mat->m23;
    float m33 = mat->m33;

    mat->m00 = m00;
    mat->m01 = m01;
    mat->m02 = m02;
    mat->m03 = m03;
    mat->m10 = m10;
    mat->m11 = m11;
    mat->m12 = m12;
    mat->m13 = m13;
    mat->m20 = m20;
    mat->m21 = m21;
    mat->m22 = m22;
    mat->m23 = m23;
    mat->m30 = m30;
    mat->m31 = m31;
    mat->m32 = m32;
    mat->m33 = m33;
}

void invertMat44(mat44 *mat)
{
    float det = detMat44(*mat);

    if (det != 0) {
        float determinant_inv = 1.0f / det;

        float t00 =  DET33(mat->m11, mat->m12, mat->m13, mat->m21, mat->m22, mat->m23, mat->m31, mat->m32, mat->m33);
        float t01 = -DET33(mat->m10, mat->m12, mat->m13, mat->m20, mat->m22, mat->m23, mat->m30, mat->m32, mat->m33);
        float t02 =  DET33(mat->m10, mat->m11, mat->m13, mat->m20, mat->m21, mat->m23, mat->m30, mat->m31, mat->m33);
        float t03 = -DET33(mat->m10, mat->m11, mat->m12, mat->m20, mat->m21, mat->m22, mat->m30, mat->m31, mat->m32);

        float t10 = -DET33(mat->m01, mat->m02, mat->m03, mat->m21, mat->m22, mat->m23, mat->m31, mat->m32, mat->m33);
        float t11 =  DET33(mat->m00, mat->m02, mat->m03, mat->m20, mat->m22, mat->m23, mat->m30, mat->m32, mat->m33);
        float t12 = -DET33(mat->m00, mat->m01, mat->m03, mat->m20, mat->m21, mat->m23, mat->m30, mat->m31, mat->m33);
        float t13 =  DET33(mat->m00, mat->m01, mat->m02, mat->m20, mat->m21, mat->m22, mat->m30, mat->m31, mat->m32);

        float t20 =  DET33(mat->m01, mat->m02, mat->m03, mat->m11, mat->m12, mat->m13, mat->m31, mat->m32, mat->m33);
        float t21 = -DET33(mat->m00, mat->m02, mat->m03, mat->m10, mat->m12, mat->m13, mat->m30, mat->m32, mat->m33);
        float t22 =  DET33(mat->m00, mat->m01, mat->m03, mat->m10, mat->m11, mat->m13, mat->m30, mat->m31, mat->m33);
        float t23 = -DET33(mat->m00, mat->m01, mat->m02, mat->m10, mat->m11, mat->m12, mat->m30, mat->m31, mat->m32);

        float t30 = -DET33(mat->m01, mat->m02, mat->m03, mat->m11, mat->m12, mat->m13, mat->m21, mat->m22, mat->m23);
        float t31 =  DET33(mat->m00, mat->m02, mat->m03, mat->m10, mat->m12, mat->m13, mat->m20, mat->m22, mat->m23);
        float t32 = -DET33(mat->m00, mat->m01, mat->m03, mat->m10, mat->m11, mat->m13, mat->m20, mat->m21, mat->m23);
        float t33 =  DET33(mat->m00, mat->m01, mat->m02, mat->m10, mat->m11, mat->m12, mat->m20, mat->m21, mat->m22);

        mat->m00 = t00*determinant_inv;
        mat->m11 = t11*determinant_inv;
        mat->m22 = t22*determinant_inv;
        mat->m33 = t33*determinant_inv;
        mat->m01 = t10*determinant_inv;
        mat->m10 = t01*determinant_inv;
        mat->m20 = t02*determinant_inv;
        mat->m02 = t20*determinant_inv;
        mat->m12 = t21*determinant_inv;
        mat->m21 = t12*determinant_inv;
        mat->m03 = t30*determinant_inv;
        mat->m30 = t03*determinant_inv;
        mat->m13 = t31*determinant_inv;
        mat->m31 = t13*determinant_inv;
        mat->m32 = t23*determinant_inv;
        mat->m23 = t32*determinant_inv;
    }
}

void negateMat44(mat44 *mat)
{
    mat->m00 = -mat->m00;
    mat->m01 = -mat->m01;
    mat->m02 = -mat->m02;
    mat->m03 = -mat->m03;

    mat->m10 = -mat->m10;
    mat->m11 = -mat->m11;
    mat->m12 = -mat->m12;
    mat->m13 = -mat->m13;

    mat->m20 = -mat->m20;
    mat->m21 = -mat->m21;
    mat->m22 = -mat->m22;
    mat->m23 = -mat->m23;

    mat->m30 = -mat->m30;
    mat->m31 = -mat->m31;
    mat->m32 = -mat->m32;
    mat->m33 = -mat->m33;
}

void scaleMat44(mat44 *mat, const vec3 scale)
{
    mat->m00 = mat->m00 * scale.x;
    mat->m01 = mat->m01 * scale.x;
    mat->m02 = mat->m02 * scale.x;
    mat->m03 = mat->m03 * scale.x;
    mat->m10 = mat->m10 * scale.y;
    mat->m11 = mat->m11 * scale.y;
    mat->m12 = mat->m12 * scale.y;
    mat->m13 = mat->m13 * scale.y;
    mat->m20 = mat->m20 * scale.z;
    mat->m21 = mat->m21 * scale.z;
    mat->m22 = mat->m22 * scale.z;
    mat->m23 = mat->m23 * scale.z;
}

void rotateMat44(mat44 *mat, const vec3 eulerAxis, const float angle)
{
    float c = (float) cos(angle);
    float s = (float) sin(angle);
    float oneminusc = 1.0f - c;
    float xy = eulerAxis.x*eulerAxis.y;
    float yz = eulerAxis.y*eulerAxis.z;
    float xz = eulerAxis.x*eulerAxis.z;
    float xs = eulerAxis.x*s;
    float ys = eulerAxis.y*s;
    float zs = eulerAxis.z*s;

    float f00 = eulerAxis.x*eulerAxis.x*oneminusc+c;
    float f01 = xy*oneminusc+zs;
    float f02 = xz*oneminusc-ys;
    float f10 = xy*oneminusc-zs;
    float f11 = eulerAxis.y*eulerAxis.y*oneminusc+c;
    float f12 = yz*oneminusc+xs;
    float f20 = xz*oneminusc+ys;
    float f21 = yz*oneminusc-xs;
    float f22 = eulerAxis.z*eulerAxis.z*oneminusc+c;

    float t00 = mat->m00 * f00 + mat->m10 * f01 + mat->m20 * f02;
    float t01 = mat->m01 * f00 + mat->m11 * f01 + mat->m21 * f02;
    float t02 = mat->m02 * f00 + mat->m12 * f01 + mat->m22 * f02;
    float t03 = mat->m03 * f00 + mat->m13 * f01 + mat->m23 * f02;
    float t10 = mat->m00 * f10 + mat->m10 * f11 + mat->m20 * f12;
    float t11 = mat->m01 * f10 + mat->m11 * f11 + mat->m21 * f12;
    float t12 = mat->m02 * f10 + mat->m12 * f11 + mat->m22 * f12;
    float t13 = mat->m03 * f10 + mat->m13 * f11 + mat->m23 * f12;

    mat->m20 = mat->m00 * f20 + mat->m10 * f21 + mat->m20 * f22;
    mat->m21 = mat->m01 * f20 + mat->m11 * f21 + mat->m21 * f22;
    mat->m22 = mat->m02 * f20 + mat->m12 * f21 + mat->m22 * f22;
    mat->m23 = mat->m03 * f20 + mat->m13 * f21 + mat->m23 * f22;
    mat->m00 = t00;
    mat->m01 = t01;
    mat->m02 = t02;
    mat->m03 = t03;
    mat->m10 = t10;
    mat->m11 = t11;
    mat->m12 = t12;
    mat->m13 = t13;
}

void translateMat44(mat44 *mat, const vec3 vec)
{
    mat->m30 += mat->m00 * vec.x + mat->m10 * vec.y + mat->m20 * vec.z;
    mat->m31 += mat->m01 * vec.x + mat->m11 * vec.y + mat->m21 * vec.z;
    mat->m32 += mat->m02 * vec.x + mat->m12 * vec.y + mat->m22 * vec.z;
    mat->m33 += mat->m03 * vec.x + mat->m13 * vec.y + mat->m23 * vec.z;
}
