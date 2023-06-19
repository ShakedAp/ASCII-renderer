#include "camera.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//                                                                       Pitch  Yaw   Roll
vec3 positionCamera = (vec3) {0.0f, 0.0f, 0.0f}, rotationCamera = (vec3) {0.0f, 0.0f, 0.0f};
vec3 lookDirCamera = (vec3) {0.0f, 0.0f, 1.0f};
vec3 vUp = (vec3) {0.0f, 1.0f, 0.0f};

void calcProjectionCamera(float fov, float aspectRatio, float nearPlane, float farPlane, mat44 *projMat)
{
    setIdentityMat44(projMat);
    float tanhfov = (float) tanf(fov / 2);

    projMat->m00 = 1/(aspectRatio * tanhfov);
    projMat->m11 = 1/tanhfov;
    projMat->m22 = -(nearPlane + farPlane) / (farPlane - nearPlane);
    projMat->m23 = -1;
    projMat->m32 = -(2 * farPlane * nearPlane) / (farPlane - nearPlane);
}

void calcViewMatrixCamera(mat44 *viewMat)
{
    vec3 target = lookDirCamera; 
    xrotateVec3(&target, rotationCamera.x);
    yrotateVec3(&target, rotationCamera.y);
    zrotateVec3(&target, rotationCamera.z);
    addVec3(positionCamera, target, &target);
    pointAtMat44(positionCamera, target, vUp, viewMat);
    invertMat44(viewMat);
}

void pointAtMat44(vec3 pos, vec3 target, vec3 up, mat44 *output)
{
        // Calculate new forward direction
    vec3 newForward, a, newUp, newRight;
    subVec3(target, pos, &newForward);
    normalizeVec3(&newForward);

    // Calculate new Up direction
    a = newForward;
    scaleVec3(&a, dotVec3(up, newForward));
    subVec3(up, a, &newUp);
    normalizeVec3(&newUp);

    // New Right direction is easy, its just cross product
    crossVec3(newUp, newForward, &newRight);

    // Construct Dimensioning and Translation Matrix	
    output->m00 = newRight.x;	output->m01 = newRight.y;	output->m02 = newRight.z;	output->m03 = 0.0f;
    output->m10 = newUp.x;		output->m11 = newUp.y;		output->m12 = newUp.z;		output->m13 = 0.0f;
    output->m20 = newForward.x;	output->m21 = newForward.y;	output->m22 = newForward.z;	output->m23 = 0.0f;
    output->m30 = pos.x;			output->m31 = pos.y;			output->m32 = pos.z;			output->m33 = 1.0f;
}