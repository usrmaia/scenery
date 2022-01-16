#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <vector>
#include <windows.h>

using namespace glm;

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

class OBJ{
    std::vector<vec3> vertexs;
    std::vector<vec3> normals;
    std::vector<face> faces;
    vec3 light_position, amb, diff, cam_position, eye_position, light_intensity, light_direction;
    vec4 specular;
    public:
        void setObjectAmb(vec3 amb);
        void setObjectDiff(vec3 diff);
        void setObjectSpecular(vec4 specular);

        void setLightIntensity(vec3 light_intensity);
        void setLightPosition(vec3 light_position);
        void setLightDirection(vec3 light_direction);
        void setEyePosition(vec3 eye_position);

        bool spotLight(vec3 light_position, vec3 light_direction, vec3 point);

        vec3 calculateLightAmb();
        vec3 calculateLightDiff(vec3 face, vec3 normal);
        vec3 calculateLightSpecular(vec3 face, vec3 normal);
        vec3 PhongLighting(vec3 point, vec3 normal);

        vec3 getVertex(std::string s);
        vec3 getNormal(std::string s);
        face getFace(std::string s);
        void load(const char *file_path);

        void getOBJ();
};
