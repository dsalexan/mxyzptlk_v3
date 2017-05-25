//
// Created by Danilo on 23/05/2017.
//

#include <stdlib.h>
#include <mem.h>
#include "Collections.h"
#include "Vectors.h"

void array_new(Array **self, int unitary_size){
    Array *ar = calloc(1, sizeof(Array));
    void **buffer = malloc(DEFAULT_ARRAY_CAPACITY * (size_t)unitary_size);

    if(!buffer){
        free(ar);
        return;
    }

    ar->buffer = buffer;
    ar->capacity = DEFAULT_ARRAY_CAPACITY;
    ar->size = 0;
    ar->unitary_size = unitary_size;

    *self = ar;
}
void array_destroy(Array *self) {
    int i;
    for (i = 0; i < self->size; i++)
        free(self->buffer[i]);

    free(self->buffer);
    free(self);
}
void array_add(Array *self, void *element) {
    if (self->size >= self->capacity) {
        if (expand_capacity(self) != 1)
            return;
    }

    self->buffer[self->size] = element;
    self->size++;

    return;
}
void array_remove(Array *self, int index, void **out) {
    if (index >= self->size)
        return;

    if (out)
        *out = self->buffer[index];

    if (index != self->size - 1) {
        int block_size = (self->size - index) * sizeof(void*);

        memmove(&(self->buffer[index]),
                &(self->buffer[index + 1]),
                block_size);
    }
    self->size--;

    return;
}

static int expand_capacity(Array *self) {
    if (self->capacity == DEFAULT_ARRAY_MAX_ELEMENTS)
        return 0;

    //int new_capacity = self->capacity * self->exp_factor;
    int new_capacity = self->capacity + 1;

    size_t new_size = (size_t)(new_capacity * self->unitary_size);

    void **new_buff = malloc(new_size);

    if (!new_buff)
        return -1;

    memcpy(new_buff, self->buffer, new_size);

    Vector *p = (Vector*)new_buff[new_capacity-2];

    free(self->buffer);

    self->buffer = new_buff;
    self->capacity = new_capacity;

    return 1;
}