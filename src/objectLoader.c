#include "objectLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

triangle *loadFromObject(const char *objPath, int *trigLen)
{
    *trigLen = 0; 
    FILE *file = fopen(objPath, "r");
    if(!file) return NULL;

    int vertexAmount = 0, triangleAmount = 0;
    char *line = NULL;
    size_t len = 0;
    int read;

    while ((read = getline(&line, &len, file)) != -1)
    {
        if(line[0] == 'v')
            vertexAmount++;
        else if(line[0] == 'f')
            triangleAmount++;
    }
    rewind(file);

    vec3 verts[vertexAmount];
    triangle *trigs = (triangle *) malloc(sizeof(triangle) * triangleAmount);
    if(!trigs)
    {
        fprintf(stderr, "Couldn't allocate triangles for object.\n");
        return NULL;
    }
    vertexAmount = 0, triangleAmount = 0;
    
    while ((read = getline(&line, &len, file)) != -1)
    {
        if(line[0] == 'v')
        {
            vec3 vert = {0.0f, 0.0f, 0.0f};
            sscanf(line, "v %f %f %f", &vert.x, &vert.y, &vert.z);
            verts[vertexAmount++] = vert;
        }
        if(line[0] == 'f')
        {
            int f[3];            
            sscanf(line, "f %i %i %i", f, f+1, f+2);
            trigs[triangleAmount++] = (triangle) {verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1]};
        }
    }
    *trigLen = triangleAmount; 

    free(line);
    fclose(file);
    return trigs;
}