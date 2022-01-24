#ifndef OBJDISPLAY_H_
#define OBJDISPLAY_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <vector>
#include <windows.h>
#include "OBJLoader.h"

using namespace glm;
using namespace std;

class OBJDisplay{
    private:
        vector<vec3> vertexs;
        vector<vec3> normals;
        vector<face> faces;

        vec3 light_position, amb, diff, cam_position, eye_position, light_intensity, light_direction;
        vec4 specular;
        float x_min, x_max, y_min, y_max;
        unsigned int id_texture;

        vec3 calculateLightAmb();
        vec3 calculateLightDiff(vec3 face, vec3 normal);
        vec3 calculateLightSpecular(vec3 face, vec3 normal);

        vec3 PhongLighting(vec3 point, vec3 normal);
        bool spotLight(vec3 light_position, vec3 light_direction, vec3 point);
        void toColorLight(vec3 point, vec3 normal, float s, float t);
    public:
        void setObjectAmb(vec3 amb);
        void setObjectDiff(vec3 diff);
        void setObjectSpecular(vec4 specular);

        void setLightIntensity(vec3 light_intensity);
        void setLightPosition(vec3 light_position);
        void setLightDirection(vec3 light_direction);
        void setEyePosition(vec3 eye_position);

        void setVertexs_Texture(OBJLoader obj, unsigned int id_texture);

        void getDisplayOBJ();
};

#endif