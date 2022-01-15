#ifndef CUBE_H  
#define CUBE_H

#include <glm/glm.hpp>
#include <GL/gl.h>

using namespace glm;

class Cube{
    private:
        vec3 vertexs[8];
        int faces[6][4];
        vec3 color;
    public:
        Cube();
        void setColor(GLfloat r, GLfloat g, GLfloat b);
        void drawCube();
};

#endif