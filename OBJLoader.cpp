#include "OBJLoader.h"
#include <vector>
#include <windows.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <math.h>

using namespace glm;

void OBJ::setObjectAmb(vec3 amb){
    this->amb = amb;
}

void OBJ::setObjectDiff(vec3 diff){
    this->diff = diff;
}

void OBJ::setObjectSpecular(vec3 specular){
    this->specular = specular;
}

void OBJ::setLightPosition(vec3 light_position){
    this->light_position = light_position;
}

void OBJ::setEyePosition(vec3 eye_position){
    this->eye_position = eye_position;
}

vec3 OBJ::calculateLightAmb(){
    vec3 ia = vec3(1, 1, 1); //iluminação ambiente
    return this->amb * ia;
}

vec3 OBJ::calculateLightDiff(vec3 point, vec3 normal){
    vec3 p = point;
    vec3 l = normalize(this->light_position - p);
    vec3 n = normalize(normal);

    float scalar_product_l_n = dot(l, n);
    float angle_l_n = acos(scalar_product_l_n); //difusa do angulo
    angle_l_n = cos(angle_l_n);

    vec3 id = vec3(1, 1, 1); //itensidade/cor da luz
    vec3 kd = this->diff; //reflexao/cor do material/objeto

    vec3 rd = vec3(id * kd * angle_l_n);
    return rd;
}

vec3 OBJ::calculateLightSpecular(vec3 point, vec3 normal){
    vec3 v = normalize(this->eye_position);
    vec3 r;

    vec3 p = point;
    vec3 l = normalize(this->light_position - p);
    vec3 n = normalize(normal);

    float scalar_product_l_n = dot(l, n);
    float angle_l_n = acos(scalar_product_l_n);

    float angle_r_n = angle_l_n;
    float angle_v_n = acos(dot(v, n));

    float angle_v_r = angle_v_n - angle_v_n;
    if(angle_v_r < 0) angle_v_r *= -1;
    angle_v_r = cos(angle_v_r);

    float specular = pow((angle_v_r), 14);
    vec3 is = vec3(1, 1, 1); //luz especular
    vec3 ks = this->specular; //objeto especular

    vec3 rs = vec3(is * ks * specular);

    return rs;
}

vec3 OBJ::PhongLighting(vec3 point, vec3 normal){
    vec3 color_amb = calculateLightAmb();
    vec3 color_diff = calculateLightDiff(point, normal);
    vec3 color_specular = calculateLightSpecular(point, normal);
    return vec3(color_amb + color_diff + color_specular);
}

vec3 OBJ::getVertex(std::string s){
    float x, y, z;
    sscanf(s.c_str(), "v %f %f %f", &x, &y, &z);
    vec3 result(x, y, z);

    return result;
}

vec3 OBJ::getNormal(std::string s){
    float x, y, z;
    sscanf(s.c_str(), "vn %f %f %f", &x, &y, &z);
    vec3 result(x, y, z);

    return result;
}

face OBJ::getFace(std::string s){
    int v1, v2, v3, v4, f;
    //sscanf(s.c_str(), "f %d//%d %d//%d %d//%d ", &v1, &f, &v2, &f, &v3, &f, &v4, &f);
    //face result(v1, v2, v3, v4, f);
    sscanf(s.c_str(), "f %d//%d %d//%d %d//%d", &v1, &f, &v2, &f, &v3, &f);
    face result(v1, v2, v3, 0, f);

    return result;
}

void OBJ::load(unsigned &id, const char *file_path){
    std::fstream arq(file_path);
    std::string line = "";

    if(!arq.is_open()){
        std::cout<<"ERRO::Couldn't Open File "<<file_path<<"\n";
    }

    while(getline(arq, line)){
        if(line.find("v ") != std::string::npos){
            vec3 vertex = getVertex(line);
            vertexs.push_back(vertex);
        }else if(line.find("vn ") != std::string::npos){
            vec3 normal = getNormal(line);
            normals.push_back(normal);
        }else if(line.find("f ") != std::string::npos){
            face face = getFace(line);
            faces.push_back(face);
        }
    }

    std::cout<<"Total vertexs: "<<vertexs.size()<<"\n";
    std::cout<<"Total normals: "<<normals.size()<<"\n";
    std::cout<<"Total faces: "<<faces.size()<<"\n";
}

void OBJ::getOBJ(unsigned &id){
    //id = glGenLists(1);
    
    /* glNewList(id, GL_COMPILE_AND_EXECUTE);
    glPolygonMode(GL_FRONT, GL_FILL); */

    unsigned index;
    int v1, v2, v3, v4;

    glBegin(GL_TRIANGLES);
    for(int i = 0; i < faces.size(); i++){
        index = faces[i].index - 1;
        v1 = faces[i].vertex[0] - 1;
        v2 = faces[i].vertex[1] - 1;
        v3 = faces[i].vertex[2] - 1;
        //v4 = faces[i].vertex[3] - 1;

        //glNormal3fv(&normals[index].x);
        
        vec3 point = vec3(vertexs[v1].x, vertexs[v1].y, vertexs[v1].z);
        vec3 normal = normals[index];
        vec3 color = PhongLighting(point, normal);
        glColor3f(color.r, color.g, color.b);
            
        glVertex3f(vertexs[v1].x, vertexs[v1].y, vertexs[v1].z);
        //printf("%f %f %f  ", vertexs[v1].x, vertexs[v1].y, vertexs[v1].z);
        glVertex3f(vertexs[v2].x, vertexs[v2].y, vertexs[v2].z);
        //printf("%f %f %f  ", vertexs[v2].x, vertexs[v2].y, vertexs[v2].z);
        glVertex3f(vertexs[v3].x, vertexs[v3].y, vertexs[v3].z);
        //printf("%f %f %f\n", vertexs[v3].x, vertexs[v3].y, vertexs[v3].z);
        //glVertex3f(vertexs[v4].x, vertexs[v4].y, vertexs[v4].z);
        //printf("%f %f %f\n", vertexs[v4].x, vertexs[v4].y, vertexs[v4].z);
        
    }
    glEnd();

    /* for(int i = 0; i < faces.size(); i++){
        unsigned index = faces[i].index - 1;
        int v1 = faces[i].vertex[0] - 1;
        int v2 = faces[i].vertex[1] - 1;
        int v3 = faces[i].vertex[2] - 1;
        int v4 = faces[i].vertex[3] - 1;
        
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
            glVertex3f(vertexs[v1].x, vertexs[v1].y, vertexs[v1].z);
            glVertex3f(vertexs[v2].x, vertexs[v2].y, vertexs[v2].z);
            glVertex3f(vertexs[v3].x, vertexs[v3].y, vertexs[v3].z);
        glEnd();
    } */
}