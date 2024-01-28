#pragma once

#include <stdint.h>

typedef struct {
    float x, y, z;
} Point3D;

typedef struct {
    float x, y;
} Point2D;

typedef struct {
    uint16_t start, end;
} Vertex;

typedef struct {
    Point3D *points;
    Vertex *vetices;
} object3D;

typedef struct {
    Point2D *points;
    Vertex *vetices;
} object2D;
