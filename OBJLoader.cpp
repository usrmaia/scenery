#include "OBJLoader.h"
#include <vector>
#include <windows.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <math.h>

using namespace glm;
using namespace std;

void OBJLoader::calculate_x_y(float x, float y){
    if(x > this->x_max) this->x_max = x;
    else if(x < this->x_min) this->x_min = x;

    if(y > this->y_max) this->y_max = y;
    else if(y < this->y_min) this->y_min = y;
}

vec4 OBJLoader::getXY(){
    vec4 xy = vec4(this->x_min, this->x_max, this->y_min, this->y_max);

    return xy;
}

vec3 OBJLoader::loadVertex(string s){
    float x, y, z;
    sscanf(s.c_str(), "v %f %f %f", &x, &y, &z);
    vec3 result(x, y, z);

    calculate_x_y(result.x, result.y);

    return result;
}

vec3 OBJLoader::loadNormal(string s){
    float x, y, z;
    sscanf(s.c_str(), "vn %f %f %f", &x, &y, &z);
    vec3 result(x, y, z);

    return result;
}

face OBJLoader::loadFace(string s){
    int v1, v2, v3, n1, n2, n3;
    sscanf(s.c_str(), "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
    face result(v1, v2, v3, n1, n2, n3);

    return result;
}

void OBJLoader::Loader(const char *file_path){
    std::fstream arq(file_path);
    std::string line = "";

    if(!arq.is_open()){
        cout<<"ERRO::Couldn't Open File "<<file_path<<"\n";
    }

    while(getline(arq, line)){
        if(line.find("v ") != string::npos){
            vec3 vertex = loadVertex(line);
            vertexs.push_back(vertex);
        }else if(line.find("vn ") != string::npos){
            vec3 normal = loadNormal(line);
            normals.push_back(normal);
        }else if(line.find("f ") != string::npos){
            face face = loadFace(line);
            faces.push_back(face);
        }
    }

    /* std::cout<<"Total vertexs: "<<vertexs.size()<<"\n";
    std::cout<<"Total normals: "<<normals.size()<<"\n";
    std::cout<<"Total faces: "<<faces.size()<<"\n"; */
}

vector<vec3> OBJLoader::getVertexs(){
    return vertexs;
}

vector<vec3> OBJLoader::getNormals(){
    return normals;
}

vector<face> OBJLoader::getFaces(){
    return faces;
}