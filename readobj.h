#ifndef READOBJ_H
#define READOBJ_H

#include <glm/glm.hpp>
#include <GL/gl.h>

using namespace glm;

class ReadOBJ{
    private:
        vec3 vertexs[8];
        int faces[6][4];
        vec3 color;
    public:
        ReadOBJ();
        void getVertexs();
        void getFaces();
};

#endif