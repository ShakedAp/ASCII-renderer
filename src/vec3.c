#include "vec3.h"
#include <math.h>

void addVec3(const vec3 left, const vec3 right, vec3 *output)
{
    output->x = left.x + right.x;
    output->y = left.y + right.y;
    output->z = left.z + right.z;
}

void subVec3(const vec3 left, const vec3 right, vec3 *output)
{
    output->x = left.x - right.x;
    output->y = left.y - right.y;
    output->z = left.z - right.z;
}

void crossVec3(const vec3 left, const vec3 right, vec3 *output)
{
    output->x = (left.y * right.z) - (left.z * right.y);
    output->y = (left.z * right.x) - (left.x * right.z);
    output->z = (left.x * right.y) - (left.y * right.x);
}


float dotVec3(const vec3 left, const vec3 right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

float lengthVec3(const vec3 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

void scaleVec3(vec3 *vec, const float scale)
{
    vec->x *= scale;
    vec->y *= scale;
    vec->z *= scale;
}

float angleVec3(const vec3 left, const vec3 right)
{
    float dot = dotVec3(left, right);
    return acos(dot/(lengthVec3(left) * lengthVec3(right)));
}

void normalizeVec3(vec3 *vec)
{
   float len = lengthVec3(*vec);

    vec->x /= len;
    vec->y /= len;
    vec->z /= len;
}

float distVec3(const vec3 left, vec3 right)
{
    float x = left.x - right.x;
    float y = left.y - right.y;
    float z = left.z - right.z;

    return sqrt(x * x + y * y + z * z);
}


void xrotateVec3(vec3 *vec, float angle)
{
    float x = vec->x;
    float y = vec->y * cos(angle) + vec->z * sin(angle);
    float z = -sin(angle) * vec->y + vec->z * cos(angle);

    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void yrotateVec3(vec3 *vec, float angle)
{
    float x = cos(angle) * vec->x -sin(angle) * vec->z;
    float y = vec->y;
    float z = sin(angle) * vec->x + cos(angle) * vec->z;

    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void zrotateVec3(vec3 *vec, float angle)
{
    float x = vec->x * cos(angle) + vec->y * sin(angle);
    float y = -sin(angle) * vec->x + cos(angle) * vec->y;
    float z = vec->z;

    vec->x = x;
    vec->y = y;
    vec->z = z;
}


void planeIntersectVec3(vec3 planePoint, vec3 planeNormal, vec3 lineStart, vec3 lineEnd, vec3 *output)
{
    vec3 lineStartToEnd, lineToIntersect;

    normalizeVec3(&planeNormal);
    float plane_d = -dotVec3(planeNormal, planePoint);
    float ad = dotVec3(lineStart, planeNormal);
    float bd = dotVec3(lineEnd, planeNormal);
    float t = (-plane_d - ad) / (bd - ad);

    subVec3(lineEnd, lineStart, &lineStartToEnd);
    lineToIntersect = lineStartToEnd;
    scaleVec3(&lineToIntersect, t);
    
    addVec3(lineStart, lineToIntersect, output);
}

int triangleClipPlane(vec3 planePoint, vec3 planeNormal, triangle inTri, triangle *outTri1, triangle *outTri2)
{
    normalizeVec3(&planeNormal);

    // calculate signed shortest distance from point to plane, plane normal must be normalised
    float dist[3];
    vec3 normalizedPoint = inTri.vert1;
    // normalizeVec3(&normalizedPoint);
    dist[0] = (planeNormal.x * normalizedPoint.x + planeNormal.y * normalizedPoint.y + planeNormal.z * normalizedPoint.z - dotVec3(planeNormal, planePoint));

    normalizedPoint = inTri.vert2;
    // normalizeVec3(&normalizedPoint);
    dist[1] = (planeNormal.x * normalizedPoint.x + planeNormal.y * normalizedPoint.y + planeNormal.z * normalizedPoint.z - dotVec3(planeNormal, planePoint));

    normalizedPoint = inTri.vert3;
    // normalizeVec3(&normalizedPoint);
    dist[2] = (planeNormal.x * normalizedPoint.x + planeNormal.y * normalizedPoint.y + planeNormal.z * normalizedPoint.z - dotVec3(planeNormal, planePoint));


    // Create two temporary storage arrays to classify points either side of plane
    // If distance sign is positive, point lies on "inside" of plane
    vec3 inside_points[3];  int nInsidePointCount = 0;
    vec3 outside_points[3]; int nOutsidePointCount = 0;

    if (dist[0] >= 0) { inside_points[nInsidePointCount++] = inTri.vert1; }
    else { outside_points[nOutsidePointCount++] = inTri.vert1; }
    if (dist[1] >= 0) { inside_points[nInsidePointCount++] = inTri.vert2; }
    else { outside_points[nOutsidePointCount++] = inTri.vert2; }
    if (dist[2] >= 0) { inside_points[nInsidePointCount++] = inTri.vert3; }
    else { outside_points[nOutsidePointCount++] = inTri.vert3; }

    // Now classify triangle points, and break the input triangle into 
    // smaller output triangles if required. There are four possible outcomes...


    if (nInsidePointCount == 0)
    {
        // All points lie on the outside of plane, so clip whole triangle it ceases to exist

        return 0; // No returned triangles are valid
    }

    if (nInsidePointCount == 3)
    {
        // All points lie on the inside of plane, so do nothing and allow the triangle to simply pass through
        *outTri1 = inTri;

        return 1; // Just the one returned original triangle is valid
    }
    return 0;

    if (nInsidePointCount == 1 && nOutsidePointCount == 2)
    {
        // Triangle should be clipped. As two points lie outside the plane, the triangle simply becomes a smaller triangle

        // The inside point is valid, so keep that...
        outTri1->vert1 = inside_points[0];

        // but the two new points are at the locations where the 
        // original sides of the triangle (lines) intersect with the plane
        planeIntersectVec3(planePoint, planeNormal, inside_points[0], outside_points[0], &outTri1->vert2);
        planeIntersectVec3(planePoint, planeNormal, inside_points[0], outside_points[1], &outTri1->vert3);

        return 1; // Return the newly formed single triangle
    }


    if (nInsidePointCount == 2 && nOutsidePointCount == 1)
    {
        // Triangle should be clipped. As two points lie inside the plane,
        // the clipped triangle becomes a "quad". Fortunately, we can
        // represent a quad with two new triangles

        // The first triangle consists of the two inside points and a new
        // point determined by the location where one side of the triangle
        // intersects with the plane
        outTri1->vert1 = inside_points[0];
        outTri1->vert2 = inside_points[1];
        planeIntersectVec3(planePoint, planeNormal, inside_points[0], outside_points[0], &outTri1->vert3);

        // The second triangle is composed of one of he inside points, a
        // new point determined by the intersection of the other side of the 
        // triangle and the plane, and the newly created point above
        outTri2->vert1 = inside_points[1];
        outTri2->vert2 = outTri1->vert3;
        planeIntersectVec3(planePoint, planeNormal, inside_points[1], outside_points[0], &outTri2->vert3);

        return 2; // Return two newly formed triangles which form a quad
    }

    return 0;
}