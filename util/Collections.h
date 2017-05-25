//
// Created by Danilo on 23/05/2017.
//

#ifndef MXYZPTLK_V1_COLLECTIONS_H
#define MXYZPTLK_V1_COLLECTIONS_H

#define DEFAULT_ARRAY_CAPACITY 3
#define DEFAULT_ARRAY_MAX_ELEMENTS 300

typedef struct structArray{
    int size;
    int capacity;

    int unitary_size;

    void **buffer;
} Array;

/* FRONT FUNCTIONS */
void array_new(Array **self, int unity);
void array_destroy(Array *self);
void array_add(Array *self, void *element);
void array_remove(Array *self, int index, void **out);

/* BACK FUNCTION */
static int expand_capacity(Array *self);

#endif //MXYZPTLK_V1_COLLECTIONS_H


