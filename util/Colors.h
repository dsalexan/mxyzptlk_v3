
#ifndef MXYZPTLK_V1_COLORS_H
#define MXYZPTLK_V1_COLORS_H

#include <GL/gl.h>

#define newColor(...) var_color((color_args){__VA_ARGS__});

typedef struct structColor{
    int red;
    int green;
    int blue;

    int alpha;
} Color;

typedef struct {
    int red;
    int green;
    int blue;
    float alpha;

} color_args;

/* COMPLEX SHIT */
// base function
Color _newColor(int r, int g, int b, int a){
    Color c = {r, g, b, a};
    return c;
}

// function that makes data optional
Color var_color(color_args in){
    int r = in.red ? in.red : 0;
    int g = in.green ? in.green : 0;
    int b = in.blue ? in.blue : 0;
    float a = in.alpha ? in.alpha : 1.f;

    return _newColor(r, g, b, ((int)a * 255));
}

/* OPENGL EXTENTIONS */
void glColor1ub(Color c){
    glColor4ub(c.red, c.green, c.blue, c.alpha);
}

/* CONSTANTS */
Color COLOR_WHITE(){
    return newColor(255,255,255);
}

Color COLOR_GREEN(){
    return newColor(.green=255);
}

#endif //MXYZPTLK_V1_COLORS_H
