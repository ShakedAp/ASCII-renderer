#ifndef __CAMERA_H
#define __CAMERA_H

#include <stdbool.h>
#include "vec3.h"
#include "mat44.h"

extern vec3 positionCamera, rotationCamera;

void calcProjectionCamera(float fov, float aspectRatio, float nearPlane, float farPlane, mat44 *projMat);
void calcViewMatrixCamera(mat44 *viewMat);
void pointAtMat44(vec3 pos, vec3 target, vec3 up, mat44 *output);

#endif