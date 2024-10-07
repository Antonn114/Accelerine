#ifndef ACCELERINE_STRUCTS_H
#define ACCELERINE_STRUCTS_H

#include "core.h"

typedef struct v3 {
    float x, y, z;
} v3;

typedef struct face {
    int vertex_indices[3];
} face;

typedef struct mesh {
    v3 vertices[256];
    face faces[256];
    size_t vertex_count;
    size_t face_count;
} mesh;

#endif // ACCELERINE_STRUCTS_H