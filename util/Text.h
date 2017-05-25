//
// Created by Danilo on 18/05/2017.
//

#ifndef MXYZPTLK_V1_TEXT_H
#define MXYZPTLK_V1_TEXT_H

#define glText(...) var_glText((glText_args){__VA_ARGS__});

#include "Vectors.h"

typedef struct structString{
    char* value;
    int length;
} String;

typedef struct{
    String string;
    Vector c;
    void* font;
} glText_args;

/* WRITING */
int len(char*);
String str(char* string);
String format(char*, ...);

void _glText(String string, Vector c, void* font);
void var_glText(glText_args in);

#endif //MXYZPTLK_V1_TEXT_H
