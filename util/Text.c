#include <GL/gl.h>
#include <GL/glut.h>
#include <stdarg.h>
#include <stdio.h>
#include "Text.h"

/* WRITING */
int len(char* string){
    int l = 0;

    while(string[l] != '\0') l++;

    return l;
}

String str(char* string){
    String cString;
    int i, l = len(string);

    cString.value = (char*)malloc(sizeof(char) * (l+1));
    for(i=0; i<l; i++){
        cString.value[i] = string[i];
    }

    cString.length = l;

    return cString;
}

String format(char* format, ...){
    va_list ap;
    char* result;
    int size;

    va_start(ap, format);
    size = _vscprintf(format, ap);
    result = (char*)malloc(sizeof(char) * (size+1));
    int r = vsnprintf(result, size+1, format, ap);

    return str(result);
}

/* OPENGL EXTENSION */
void _glText(String string, Vector c, void* font){
    int i;

    glPushMatrix();
    //glDisable(GL_DEPTH_TEST);
    glRasterPos3f(c.x, c.y, c.z);

    for(i=0; i< string.length; i++)
        glutBitmapCharacter(font, string.value[i]);

    //glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

void var_glText(glText_args in){
    String string = in.string;
    Vector c = in.c;
    void* font =  in.font ? in.font : GLUT_BITMAP_8_BY_13;

    _glText(string, c, font);
}