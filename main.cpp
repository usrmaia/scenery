//g++ main.cpp -lGL -lglut -lGLU
//g++ main.cpp cube.cpp -lopengl32 -lfreeglut -lglu32

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "cube.h"
#include "OBJLoader.h"

using namespace glm;

OBJ cube;
OBJ cylinder;
static unsigned id_cube;
static unsigned id_cylinder;

GLdouble left, right, bottom, top, near_val, far_val;
GLdouble    eyeX, eyeY, eyeZ, //posicao da camera
            centerX, centerY, centerZ, //para onde olha
            upX, upY, upZ; //topo da camera
GLfloat increment;
int angle_obj;

void init();
void display_func();
void special_func(int key, int x, int y);
void keyboard_func(unsigned char key, int x, int y);
void idle_func();
void center_line();
void walls();
void light();
void objects();

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);                          
    glutInitWindowSize(500, 500);
    glutCreateWindow("Scenery");

    init();
    glutDisplayFunc(display_func); 

    glutKeyboardFunc(keyboard_func);
    glutSpecialFunc(special_func);
    //glutMouseFunc(mouse_func);
    //glutMotionFunc(motion_func);
    //glutReshapeFunc(reshape_func);
    glutIdleFunc(idle_func);

    glutMainLoop();
}

void init(){
    glClearColor(0, 0, 0, 1);
    glLineWidth(3);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    cube.load(id_cube, "Modelos3D/Modelos/fertility.obj");
    cylinder.load(id_cylinder, "Modelos3D/Modelos/cilindro.obj");

    left = -1, right = 1, bottom = -1, top = 1, near_val = 2, far_val = 200;
    
    eyeX = 10, eyeY = 10, eyeZ = 10, 
    centerX = 0, centerY = 0, centerZ = 0,
    upX = 0, upY = 1, upZ = 0;

    increment = 0;
    angle_obj = 0;
}

void display_func(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(left, right, bottom, top, near_val, far_val);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    center_line();
    walls();
    objects();

    glutSwapBuffers();
    //glutPostRedisplay();
}

void special_func(int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP:
            centerY += 1;
            //printf("CenterX = %f, CenterY = %f\n", centerX, centerY);
            break;
        case GLUT_KEY_LEFT:
            centerX -= 1;
            //printf("CenterX = %f, CenterY = %f\n", centerX, centerY);
            break;
        case GLUT_KEY_DOWN:
            centerY -= 1;
            //printf("CenterX = %f, CenterY = %f\n", centerX, centerY);
            break;
        case GLUT_KEY_RIGHT:
            centerX += 1;
            //printf("CenterX = %f, CenterY = %f\n", centerX, centerY);
            break;
        case GLUT_KEY_PAGE_UP:
            eyeY += 0.5;
            //printf("eyeY = %f\n", eyeY);
            break;
        case GLUT_KEY_PAGE_DOWN:
            eyeY -= 0.5;
            //printf("eyeY = %f\n", eyeY);
            break;
    }
    glutPostRedisplay();
}

void keyboard_func(unsigned char key, int x, int y){
    switch (key){
        case 'w':
            eyeZ += 0.5;
            //printf("eyeX = %f, eyeY = %f, eyeZ = %f\n", eyeX, eyeY, eyeZ);
            break;
        case 'a':
            eyeX -= 0.5;
            //printf("eyeX = %f, eyeZ = %f\n", eyeX, eyeZ);
            break;
        case 's':
            eyeZ -= 0.5;
            //printf("eyeX = %f, eyeZ = %f\n", eyeX, eyeZ);
            break;
        case 'd':
            eyeX += 0.5;
            //printf("eyeX = %f, eyeZ = %f\n", eyeX, eyeZ);
            break;
    }
    glutPostRedisplay();
}

void idle_func(){
    angle_obj += 1;
    glutPostRedisplay();
}

void center_line(){
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(-1000, 0, 0);
        glVertex3f(1000, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, -1000);
        glVertex3f(0, 0, 1000);
    glEnd();
}

void walls(){
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(0.6, 0.6, 0.8);
            glVertex3f(0, 0, 5);
            glVertex3f(10, 0, 5);
            glVertex3f(10, 0, -5);
            glVertex3f(0, 0, -5);

            glColor3f(0.7, 0.7, 0.8);
            glVertex3f(0, 0, -5);
            glVertex3f(0, 10, -5);
            glVertex3f(10, 10, -5);
            glVertex3f(10, 0, -5);

            glColor3f(0.4, 0.4, 0.5);
            glVertex3f(0, 0, 5);
            glVertex3f(0, 10, 5);
            glVertex3f(0, 10, -5);
            glVertex3f(0, 0, -5);

            glColor3f(0.4, 0.4, 0.5);
            glVertex3f(10, 0, 5);
            glVertex3f(10, 10, 5);
            glVertex3f(10, 10, -5);
            glVertex3f(10, 0, -5);

            glColor3f(0.9, 0.6, 0.0);
            glVertex3f(0, 10, 5);
            glVertex3f(10, 10, 5);
            glVertex3f(10, 10, -5);
            glVertex3f(0, 10, -5);
            
            glColor3f(0.95, 0.8, 0.0);
            glVertex3f(-50, -0.1, 50);
            glVertex3f(50, -0.1, 50);
            glVertex3f(50, -0.1, -50);
            glVertex3f(-50, -0.1, -50);
        glEnd();
    glPopMatrix();
}

void objects(){
    glPushMatrix();
        cube.setObjectAmb(vec3(0.3, 0, 0.3));
        cube.setObjectDiff(vec3(0.7, 0, 0.7));
        cube.setObjectSpecular(vec3(1, 0, 1));

        cube.setLightPosition(vec3(10, 10, 10));
        cube.setEyePosition(vec3(eyeX, eyeY, eyeZ));

        glTranslatef(3, 2, 0);
        glScalef(2, 2, 2);
        glRotated(angle_obj, 0, 1, 0);
        
        cube.getOBJ(id_cube);
        //glCallList(id_cube);
    glPopMatrix();

    glPushMatrix();
        //glColor3f(0, 1, 1);
        glTranslatef(7.5, 2, 0);
        glScalef(2, 2, 2);
        cylinder.getOBJ(id_cylinder);
        //glCallList(id_cylinder);
    glPopMatrix();
}