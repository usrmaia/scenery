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

void OBJ::setObjectSpecular(vec4 specular){
    this->specular = specular;
}

void OBJ::setLightIntensity(vec3 light_intensity){
    this->light_intensity = light_intensity;
}

void OBJ::setLightPosition(vec3 light_position){
    this->light_position = light_position;
}

void OBJ::setLightDirection(vec3 light_direction){
    this->light_direction = light_direction;
}

void OBJ::setEyePosition(vec3 eye_position){
    this->eye_position = eye_position;
}

bool OBJ::spotLight(vec3 light_position, vec3 light_direction, vec3 point){
    vec3 dist_lp_p = light_position - point;
    vec3 l = (dist_lp_p)/sqrt(dist_lp_p.x*dist_lp_p.x + dist_lp_p.y*dist_lp_p.y + dist_lp_p.z*dist_lp_p.z);
    vec3 dist_p_lp = point - light_direction;
    vec3 d = (dist_p_lp)/sqrt(dist_p_lp.x*dist_p_lp.x + dist_p_lp.y*dist_p_lp.y + dist_p_lp.z*dist_p_lp.z);

    float scalar_l_d = dot(l, d);
    float angle = cos(45);

    //printf("%f < %f\n", scalar_l_d, angle);

    /* d = (point - light_position);
    float dist = sqrt(d.x*d.x + d.y*d.y + d.z*d.z);
    dist = 1/(dist*dist);
    //printf("%f ", dist);
    //printf("%f %f %f \n", this->light_intensity.x, this->light_intensity.y, this->light_intensity.z);

    setLightIntensity(vec3(dist, dist, dist)); */

    if(-scalar_l_d > angle){
        return true;
    }else{
        return false;
    }
}

vec3 OBJ::calculateLightAmb(){
    vec3 ia = this->light_intensity; //iluminação ambiente
    return this->amb * ia;
}

vec3 OBJ::calculateLightDiff(vec3 point, vec3 normal){
    vec3 l = normalize(this->light_position - point);
    vec3 n = normalize(normal);

    float scalar_product_l_n = dot(l, n);
    float angle_l_n = acos(scalar_product_l_n); //difusa do angulo
    angle_l_n = cos(angle_l_n);

    vec3 id = this->light_intensity; //itensidade/cor da luz
    vec3 kd = this->diff; //reflexao/cor do material/objeto

    vec3 rd = vec3(id * kd * angle_l_n);
    return rd;
}

vec3 OBJ::calculateLightSpecular(vec3 point, vec3 normal){
    vec3 v = normalize(this->eye_position - point);
    vec3 r;

    vec3 l = normalize(this->light_position - point);
    vec3 n = normalize(normal);

    float scalar_product_l_n = dot(l, n);
    float angle_l_n = acos(scalar_product_l_n);

    float angle_r_n = angle_l_n;
    float angle_v_n = acos(dot(v, n));

    float angle_v_r = angle_v_n - angle_v_n;
    if(angle_v_r < 0) angle_v_r *= -1;
    angle_v_r = cos(angle_v_r);

    float specular = pow((angle_v_r), this->specular[3]);
    vec3 is = this->light_intensity; //luz especular
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
    int v1, v2, v3, n1, n2, n3;
    sscanf(s.c_str(), "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
    face result(v1, v2, v3, n1, n2, n3);

    return result;
}

void OBJ::load(const char *file_path){
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

    /* std::cout<<"Total vertexs: "<<vertexs.size()<<"\n";
    std::cout<<"Total normals: "<<normals.size()<<"\n";
    std::cout<<"Total faces: "<<faces.size()<<"\n"; */
}

void OBJ::getOBJ(){
    int v1, v2, v3, n1, n2, n3;

    glBegin(GL_TRIANGLES);
    for(int i = 0; i < faces.size(); i++){
        v1 = faces[i].vertex[0] - 1;
        v2 = faces[i].vertex[1] - 1;
        v3 = faces[i].vertex[2] - 1;
        n1 = faces[i].normal[0] - 1;
        n2 = faces[i].normal[1] - 1;
        n3 = faces[i].normal[2] - 1;
        //printf("vertex %d %d %d normal %d %d %d \n", v1, v2, v3, n1, n2, n3);
        vec3 point = vec3(vertexs[v1].x, vertexs[v1].y, vertexs[v1].z);
        vec3 normal = vec3(normals[n1].x, normals[n1].y, normals[n1].z);

        if(spotLight(this->light_position, this->light_direction, point)){
            vec3 color = PhongLighting(point, normal);
            glColor3f(color.r, color.g, color.b);
        }else{
            glColor3f(this->amb.r, this->amb.g, this->amb.b);
        }

        glVertex3f(vertexs[v1].x, vertexs[v1].y, vertexs[v1].z);



        point = vec3(vertexs[v2].x, vertexs[v2].y, vertexs[v2].z);
        normal = vec3(normals[n2].x, normals[n2].y, normals[n2].z);

        if(spotLight(this->light_position, this->light_direction, point)){
            vec3 color = PhongLighting(point, normal);
            glColor3f(color.r, color.g, color.b);
        }else{
            glColor3f(this->amb.r, this->amb.g, this->amb.b);
        }

        glVertex3f(vertexs[v2].x, vertexs[v2].y, vertexs[v2].z);



        point = vec3(vertexs[v3].x, vertexs[v3].y, vertexs[v3].z);
        normal = vec3(normals[n3].x, normals[n3].y, normals[n3].z);

        if(spotLight(this->light_position, this->light_direction, point)){
            vec3 color = PhongLighting(point, normal);
            glColor3f(color.r, color.g, color.b);
        }else{
            glColor3f(this->amb.r, this->amb.g, this->amb.b);
        }

        glVertex3f(vertexs[v3].x, vertexs[v3].y, vertexs[v3].z);  
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