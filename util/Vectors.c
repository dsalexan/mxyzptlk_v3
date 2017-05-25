//
// Created by Danilo on 04/04/2017.
//

#include "Vectors.h"

Vector *createVector(float x, float y, float z){
    Vector *v = (Vector*)malloc(sizeof(Vector));

    v->x = x;
    v->y = y;
    v->z = z;

    return v;
}

Vector nullVector(){
    return *createVector(.0f, .0f, .0f);
}

void vector_set(Vector* v, float x, float y, float z){
    v->x = x;
    v->y = y;
    v->z = z;
}

Vector addVector(Vector v1, Vector v2){
    Vector v;

    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;

    return v;
}
Vector subtractVector(Vector v1, Vector v2){
    Vector v;

    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;

    return v;
}
Vector multiplyVector(Vector v1, Vector v2){
    Vector v;

    v.x = v1.x * v2.x;
    v.y = v1.y * v2.y;
    v.z = v1.z * v2.z;

    return v;
}
Vector rotateVector(Vector *m, Vector v){
    int i, j, k;
    float result[3][1], vetor[3][1], matriz[3][3];

    vetor[0][0] = v.x;
    vetor[1][0] = v.y;
    vetor[2][0] = v.z;

    matriz[0][0] = m[0].x;
    matriz[0][1] = m[0].y;
    matriz[0][2] = m[0].z;

    matriz[1][0] = m[1].x;
    matriz[1][1] = m[1].y;
    matriz[1][2] = m[1].z;

    matriz[2][0] = m[2].x;
    matriz[2][1] = m[2].y;
    matriz[2][2] = m[2].z;

    for(i=0; i<3; ++i) // linhas na matriz
        for(j=0; j<1; ++j) // colunas no vetor
            for(k=0; k<3; ++k) // colunas na matriz
            {
                result[i][j]+=matriz[i][k]*vetor[k][j];
            }

    return *createVector(result[0][0], result[1][0], result[2][0]);
}

Vector divideScalarVector(Vector v1, float s){
    Vector v;

    v.x = v1.x / s;
    v.y = v1.y / s;
    v.z = v1.z / s;

    return v;
}
Vector multiplyScalarVector(Vector v1, float s){
    Vector v;

    v.x = v1.x * s;
    v.y = v1.y * s;
    v.z = v1.z * s;

    return v;
}
float distanceVector(Vector v1, Vector v2){
    return sqrtf(powf(v1.x-v2.x, 2.0) + powf(v1.y - v2.y, 2) + powf(v1.z - v2.z, 2));
}

float moduleVector(Vector v){
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}
Vector normalizeVector(Vector v){
    float norma = moduleVector(v);
    return *createVector(v.x/norma, v.y/norma, v.z/norma);
}
float dotVector(Vector v1, Vector v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
Vector crossVector(Vector v1, Vector v2){
    Vector v;

    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.x * v2.z - v1.z * v2.x;
    v.z = v1.x * v2.y - v1.y * v2.x;

    return v;
}


/* OTHERS */
float radians(float deg){
    return (float)((double)deg * M_PI/180.0);
}