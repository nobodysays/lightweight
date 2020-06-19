#pragma once
#include "helpfile.h"
#include "Shader.h"
#include "GameObject.h"
#include <iostream>
struct Plane
{
    glm::vec3 normal;
    float d;
    Plane(glm::vec3 n, float d) : normal(n), d(d){}
};
class Frustum :public GameObject
{
public:
    const float fovy=45;  //
    const float aspect = 4./3.;
    const float near = 3.f;//
    const float far = 15.f;//
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    const float alpha = fovy / 2.;
    const float h = 2 * far * tan(alpha);
    const float w = aspect * h;


     
    Plane* planes[6];
    Shader shader = Shader("Frustum.vert", "Frustum.frag");

    //const float d =  near;
    const float wn = near * w /far;
    const float hn = near * h / far;
    float vertices[9 * 3] =
    {
        position.x,     position.y,       position.z,       // 0 view point
        position.x-w/2, position.y + h/2, position.z - far, // 1 left top
        position.x+w/2, position.y + h/2, position.z - far, // 2 right top
        position.x+w/2, position.y - h/2, position.z - far, // 3 tight bot
        position.x-w/2, position.y - h/2, position.z - far, // 4 left bot
        position.x - wn / 2, position.y + hn / 2, position.z - near, // 5 left top
        position.x + wn / 2, position.y + hn / 2, position.z - near, // 6 right top
        position.x + wn / 2, position.y - hn / 2, position.z - near, // 7 tight bot
        position.x - wn / 2, position.y - hn / 2, position.z - near, // 8 left bot
    };
    //glm::vec3 position = { 0, -2, 10 };
    GLuint indices[12 * 2] = {
        0, 1,
        0, 2,
        0, 3,
        0, 4,
        1, 2,
        2, 3, 
        3, 4, 
        4, 1,

        5, 6,
        6, 7, 
        7, 8, 
        8, 5
    };
    Frustum();
    void Draw();
    bool InFrustum(glm::vec3 p, float radius);

    //glm::mat4 projection;
};