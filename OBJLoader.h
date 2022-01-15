#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <vector>
#include <windows.h>

using namespace glm;

struct face{
    unsigned index;
    int vertex[4];
    face(int a, int b, int c, int d, int e){
        vertex[0] = a;
        vertex[1] = b;
        vertex[2] = c;
        vertex[3] = d;
        index = e;
    }
};

class OBJ{
    std::vector<vec3> vertexs;
    std::vector<vec3> normals;
    std::vector<face> faces;
    vec3 light_position, amb, diff, specular, cam_position, eye_position;

    public:
        void setObjectAmb(vec3 amb);
        void setObjectDiff(vec3 diff);
        void setObjectSpecular(vec3 specular);
        void setLightPosition(vec3 position);
        void setEyePosition(vec3 eye_position);

        vec3 calculateLightAmb();
        vec3 calculateLightDiff(vec3 face, vec3 normal);
        vec3 calculateLightSpecular(vec3 face, vec3 normal);
        vec3 PhongLighting(vec3 point, vec3 normal);

        vec3 getVertex(std::string s);
        vec3 getNormal(std::string s);
        face getFace(std::string s);
        void load(unsigned &id, const char *file_path);

        void getOBJ(unsigned &id);
};
