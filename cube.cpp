#include "cube.h"
#include <glm/glm.hpp>
#include <GL/gl.h>

using namespace glm;

Cube::Cube(){
    vertexs[0] = vec3(-1, -1, -1);
    vertexs[1] = vec3(-1, -1,  1);
    vertexs[2] = vec3(-1,  1, -1);
    vertexs[3] = vec3(-1,  1,  1);
    vertexs[4] = vec3( 1, -1, -1);
    vertexs[5] = vec3( 1, -1,  1);
    vertexs[6] = vec3( 1,  1, -1);
    vertexs[7] = vec3( 1,  1,  1);

    faces[0][0] = 0; faces[0][1] = 4; faces[0][2] = 5; faces[0][3] = 1;
    faces[1][0] = 0; faces[1][1] = 1; faces[1][2] = 3; faces[1][3] = 2;
    faces[2][0] = 0; faces[2][1] = 2; faces[2][2] = 6; faces[2][3] = 4;
    faces[3][0] = 4; faces[3][1] = 6; faces[3][2] = 7; faces[3][3] = 5;
    faces[4][0] = 5; faces[4][1] = 7; faces[4][2] = 3; faces[4][3] = 1;
    faces[5][0] = 2; faces[5][1] = 3; faces[5][2] = 7; faces[5][3] = 6;

    color = vec3(0.5, 1, 0.5);
}

void Cube::setColor(GLfloat r, GLfloat g, GLfloat b){
    color = vec3(r, g, b);
}

void Cube::drawCube(){
    vec3 vertex;

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_QUADS);
        for(int i = 0; i < 6; i++){
            for (int j = 0; j < 4; j++){
                vertex = vertexs[faces[i][j]];
                glVertex3f(vertex.x, vertex.y, vertex.z);
            }
        }
    glEnd();

    glColor3f(1, 1, 1);
    for(int i = 0; i < 6; i++){
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < 4; j++){
            vertex = vertexs[faces[i][j]];
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
        glEnd();
    }
}