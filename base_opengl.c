#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <ctype.h>

#include "util/Vectors.h"
#include "util/Text.h"
#include "util/Colors.h"
#include "util/Collections.h"

/* STRUCTURAL VARIABLES */
int WIDTH = 700, HEIGHT = 600;
Vector WORLD_DIMENSIONS;
Vector CAMERA_AXIS;
char CURRENT_CAMERA_AXIS;
int PLOT_TRACKING = 1;
int PAUSE_TIMER = 0;


/* PROJECT VARIABLES */
GLfloat ctrlpoints[5][3] = {{ -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0}, {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}, {6.0, -2.0, 0.0}};
float surface[4][4][3] = {
        {{-1.5, -1.5, 4.0},  {-0.5, -1.5, 2.0},  {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
        {{-1.5, -0.5, 1.0},  {-0.5, -0.5, 3.0},  {0.5, -0.5, 0.0},  {1.5, -0.5, -1.0}},
        {{-1.5, 0.5,  4.0},  {-0.5, 0.5,  0.0},  {0.5, 0.5,  3.0},  {1.5, 0.5,  4.0}},
        {{-1.5, 1.5,  -2.0}, {-0.5, 1.5,  -2.0}, {0.5, 1.5,  0.0},  {1.5, 1.5,  -1.0}}
};

Array *points;

/* EXPLICIT DECLARATIONS */
Vector GetOGLPos(int x, int y);


/* PROJECT FUNCTIONS */
void init(void){
    /* enable alpha coloring */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    array_new(&(points), sizeof(Vector*));
}

void draw(void){
    int i, j, s;

    /* SPLINE */
    glColor1ub(COLOR_WHITE()); //glColor3f(1.0, 1.0, 1.0);
    glMap2f(GL_MAP2_VERTEX_3,
            0.0, 1.0, 3, 4,
            0.0, 1.0, 3, 4,
            &surface[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glBegin(GL_LINE_STRIP);
    s = 70;
    for (i = 0; i <= s; i++)
        for(j = 0; j <= s; j++)
            //glEvalCoord2f(i/((float)s), j/((float)s));
    glEnd();
    glDisable(GL_MAP2_VERTEX_3);


    glPushMatrix();
    glColor4ub(255, 255, 0, 140);
    glutSolidSphere(.125f, 15, 15);
    glPopMatrix();

    /* CONTROL POINTS */
    for (i=0; i<4; i++){
        for(j=0; j<4; j++) {
            glPushMatrix();
            glColor4ub(255, 0, 0, 140);
            glTranslatef(surface[i][j][0], surface[i][j][1], surface[i][j][2]);
            glutSolidSphere(.05f, 15, 15);
            glScalef(0.5f, .5f, .5f);
            glText(format("%.2f, %.2f, %.2f", surface[i][j][0], surface[i][j][1], surface[i][j][2]), nullVector());
            glPopMatrix();
        }
    }

    /* CLICKED POINTS */
    for(i=0; i<points->size; i++){
        Vector *p = (Vector*)points->buffer[i];

        glPushMatrix();
        glColor4ub(0, 0, 255, 140);
        glTranslatef(p->x, p->y, p->z);
        glutSolidSphere(.05f, 15, 15);
        glPopMatrix();
    }
}

void click(int x, int y){
    Vector p = GetOGLPos(x, y);
    Vector *point = (Vector*)malloc(sizeof(Vector*));
    vector_set(point, p.x, p.y, p.z);

    glPushMatrix();
    array_add(points, point);
    printf("%f, %f, %f\n", point->x, point->y, point->z);

    glPopMatrix();
}


/* DEVELOPER FUNCTIONS */
void glDirector(Vector p, float size, Color color, int plot){
    float axis_size = size;
    float glyph_padding = size * 0.05f;

    if(plot == 0) return;

    glPushMatrix();

    glLineWidth(1.0f);
    glColor1ub(color);

    /* Z */
    glBegin(GL_LINES);
    glVertex3f(p.x, p.y, p.z);
    glVertex3f(p.x, p.y, p.z+axis_size);
    glEnd();
    glText(str("Z"), *createVector(p.x, p.y, p.z+axis_size + glyph_padding));

    /* Y */
    glBegin(GL_LINES);
    glVertex3f(p.x, p.y, p.z);
    glVertex3f(p.x, axis_size+p.y, p.z);
    glEnd();
    glText(str("Y"), *createVector(p.x, p.y+axis_size + glyph_padding, p.z));

    /* X */
    glBegin(GL_LINES);
    glVertex3f(p.x, p.y, p.z);
    glVertex3f(axis_size+p.x, p.y, p.z);
    glEnd();
    glText(str("X"), *createVector(p.x+axis_size + glyph_padding, p.y, p.z));

    glTranslatef(p.x, p.y, p.z);
    glutWireCube(size*0.1);

    glPopMatrix();
}

void glStatistics(int plot){
    int l=1;
    float relative_padding = 0.025f;
    Vector padding = {WORLD_DIMENSIONS.x * relative_padding, WORLD_DIMENSIONS.y * relative_padding, WORLD_DIMENSIONS.z * relative_padding};
    int size = 3;

    if(plot == 0) return;

    glPushMatrix();
    glLoadIdentity();

    glColor4ub(0,0,255,255);

    glText(format("x_angle: %d", ((int)(CAMERA_AXIS.x) % 360)), *createVector(-WORLD_DIMENSIONS.x/2 + padding.x, WORLD_DIMENSIONS.y/2 - padding.y*l, 0), GLUT_BITMAP_8_BY_13); l++;
    glText(format("y_angle: %d", ((int)(CAMERA_AXIS.y) % 360)), *createVector(-WORLD_DIMENSIONS.x/2 + padding.x, WORLD_DIMENSIONS.y/2 - padding.y*l, 0), GLUT_BITMAP_8_BY_13); l++;
    glText(format("z_angle: %d", ((int)(CAMERA_AXIS.z) % 360)), *createVector(-WORLD_DIMENSIONS.x/2 + padding.x, WORLD_DIMENSIONS.y/2 - padding.y*l, 0), GLUT_BITMAP_8_BY_13); l++;
    l++;
    glText(format("curent_axis: %c", CURRENT_CAMERA_AXIS), *createVector(-WORLD_DIMENSIONS.x/2 + padding.x, WORLD_DIMENSIONS.y/2 - padding.y*l, 0), GLUT_BITMAP_8_BY_13); l++;

    glPopMatrix();

}

void glPlane(int plot){
    if(plot==0) return;

    Vector size = WORLD_DIMENSIONS;

    glColor4ub(255,255,255,50);

    glBegin(GL_QUADS);
    glVertex3f(-size.x/2, 0, size.z/2);
    glVertex3f(-size.x/2, 0, -size.z/2);
    glVertex3f(size.x/2, 0, -size.z/2);
    glVertex3f(size.x/2, 0, size.z/2);
    glEnd();
}


/* STRUCTURAL FUNCTIONS */
Vector GetOGLPos(int x, int y) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    return *createVector(posX, posY, posZ);
}

char *keyboard_modifiers(int mod){
    char ms[3] = {0,0,0};
    /*
     * 0 = SHIFT
     * 1 = CTRL
     * 2 = ALT
     * */

    switch (mod){
        case GLUT_ACTIVE_SHIFT:
            ms[0] = 1;
            break;
        case GLUT_ACTIVE_CTRL:
            ms[1] = 1;
            break;
        case GLUT_ACTIVE_ALT:
            ms[2] = 1;
            break;
        default: break;
    }

    return ms;
}

void keyboard(unsigned char key, int x, int y){
    char* mods = keyboard_modifiers(glutGetModifiers());

    float angle_mod = 1.0f - mods[0] * 2.0f;

    switch(tolower(key)){
        /* INTERACTIONS */
        case 'z':
            CAMERA_AXIS.z += 5*angle_mod;
            CURRENT_CAMERA_AXIS = 'z';
            break;
        case 'y':
            CAMERA_AXIS.y += 5*angle_mod;
            CURRENT_CAMERA_AXIS = 'y';
            break;
        case 'x':
            CAMERA_AXIS.x += 5*angle_mod;
            CURRENT_CAMERA_AXIS = 'x';
            break;
        default:
            break;
    }
}

void special_keyboard(int key, int x, int y){
    switch (key){
        case GLUT_KEY_F4:
            PLOT_TRACKING = !(PLOT_TRACKING);
            break;
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y){
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) click(x, y);
            break;
        default:
            break;
    }
}

void update(void){
    float pitch = CAMERA_AXIS.x, yaw = CAMERA_AXIS.y, roll = CAMERA_AXIS.z;

    /* reset modelview */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1.0);

    /* rotate */
    glRotatef(pitch, 1, 0, 0);
    glRotatef(roll, 0, 0, 1);
    glRotatef(yaw, 0, 1, 0);
}


/* CORE FUNCTIONS */
void timer(int t){
    if(!PAUSE_TIMER)
        glutPostRedisplay();
    glutTimerFunc(56, timer, 0);
}

void setup(void){
    /* initialize world variables */
    CAMERA_AXIS = nullVector();
    WORLD_DIMENSIONS = nullVector();
    WORLD_DIMENSIONS.x = 20.0f;
    WORLD_DIMENSIONS.y = 20.0f;
    WORLD_DIMENSIONS.z = 20.0f;

    /* enable depth testing */
    glEnable(GL_DEPTH);

    /* set projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*glFrustum(-5,5,-5,5,1,3);*/
    glOrtho(-WORLD_DIMENSIONS.x/2.f, WORLD_DIMENSIONS.x/2.f, -WORLD_DIMENSIONS.y/2.f, WORLD_DIMENSIONS.y/2.f,
            -WORLD_DIMENSIONS.z/2.f, WORLD_DIMENSIONS.z/2.f);
    glTranslated(0,0,-WORLD_DIMENSIONS.z/10.f);

    /* reset modelview */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1.0);

    /* init project data */
    init();
}

void display(void){
    /* clear screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* call update camera functions */
    update();

    /* call developer functions */
    glDirector(nullVector(), WORLD_DIMENSIONS.y*0.05f, COLOR_GREEN(), PLOT_TRACKING);
    glStatistics(PLOT_TRACKING);
    glPlane(PLOT_TRACKING);

    /* call draw project functions */
    draw();

    /* action drawer */
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    /* initial data */
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WIDTH, HEIGHT);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Spline Curve");

    /* initialize data */
    setup();

    /* define functions */
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);
    glutMouseFunc(mouse);

    /* jumpstart */
    timer(0);
    glutMainLoop();
    return 0;
}

