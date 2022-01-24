#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <vector>
#include <windows.h>

using namespace glm;
using namespace std;

struct face{
    int vertex[3];
    int normal[3];
    face(int v1, int v2, int v3, int n1, int n2, int n3){
        vertex[0] = v1;
        vertex[1] = v2;
        vertex[2] = v3;
        normal[0] = n1;
        normal[1] = n2;
        normal[2] = n3;
    }
};

class OBJLoader{
    private:
        vector<vec3> vertexs;
        vector<vec3> normals;
        vector<face> faces;

        float x_min, x_max, y_min, y_max;
        
        vec3 loadVertex(string s);
        vec3 loadNormal(string s);
        face loadFace(string s);
        void calculate_x_y(float x, float y);
    public:
        void Loader(const char *file_path);
        vector<vec3> getVertexs();
        vector<vec3> getNormals();
        vector<face> getFaces();
        vec4 getXY();
};

#endif