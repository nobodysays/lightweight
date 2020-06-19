#pragma once
#include "GameObject.h"
#include "helpfile.h"

class Camera : public GameObject
{
public:
    glm::mat4 view       = glm::mat4(1);
    glm::mat4 projection = glm::perspective(90.f, (float)800/600, 0.01f, 100.0f);
    //glm::mat4 projection = glm::mat4(1)'
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    //glm::vec3 cameraMovingFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    GLfloat yaw = -90.0f;
    GLfloat pitch = 0.0f;
    GLfloat sensitivity = 0.03f;

    Camera();
    //class Cube* cube;
    void Update() override;
};

