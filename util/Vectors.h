//
// Created by Danilo on 04/04/2017.
//

#ifndef DORMOUSE_V2_VECTORS_H
#define DORMOUSE_V2_VECTORS_H

#include <math.h>
#include <malloc.h>

typedef struct structVector{
    float x;
    float y;
    float z;
} Vector;

Vector *createVector(float, float, float);

/* VECTOR */
Vector nullVector();

void vector_set(Vector*, float, float, float);

Vector addVector(Vector, Vector);
Vector subtractVector(Vector, Vector);
Vector multiplyVector(Vector v1, Vector v2);
Vector rotateVector(Vector *m, Vector v);

Vector divideScalarVector(Vector v1, float s);
Vector multiplyScalarVector(Vector v1, float s);
float distanceVector(Vector v1, Vector v2);

float moduleVector(Vector v);
Vector normalizeVector(Vector v);
float dotVector(Vector v1, Vector v2);
Vector crossVector(Vector v1, Vector v2);

/* OTHERS */

float radians(float deg);


#endif //DORMOUSE_V2_VECTORS_H
