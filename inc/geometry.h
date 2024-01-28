#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

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
    std::vector<Point3D> points;
    std::vector<Vertex> vertices;
} Object3D;

typedef struct {
    std::vector<Point2D> points;
    std::vector<Vertex> vertices;
} Object2D;

void saveObj3D(const Object3D &obj, const std::string filename);
void saveObj2D(const Object2D &obj, const std::string filename);

void loadObj3D(Object3D &obj, const std::string filename);
void loadObj2D(Object2D &obj, const std::string filename);

void loadObjs(std::vector<Object2D> &objs2D, std::vector<Object3D> &objs3D,
              int argc, char *argv[]);

void project3DTo2D(const Object3D &obj3D, Object2D &obj2D, float depth,
                   float centerX, float centerY, float scale);

void rotate(Object3D &obj, const float rx, const float ry, const float rz);

void rotateX(float &y, float &z, float angle);
void rotateY(float &x, float &z, float angle);
void rotateZ(float &x, float &y, float angle);
