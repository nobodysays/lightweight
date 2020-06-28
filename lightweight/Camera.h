#pragma once
#include "GameObject.h"
#include "helpfile.h"
#include "Frustum.h"
class Camera : public GameObject
{
public:
    const float fovy = 45.;
    const float aspect = 4. / 3;
    const float near = 0.01;
    const float far = 100.0f;
    glm::mat4 view       = glm::mat4(1);
    glm::mat4 projection = glm::perspective(fovy, aspect, near, far);
    void Update(const double&) override;
    Camera();
    bool IsSphereInFrustum(const glm::vec3& position, const float& radius);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    GLfloat yaw = -90.0f;
    GLfloat pitch = 0.0f;
private:
    GLfloat sensitivity = 0.03f;
    Frustum* frustum = nullptr;
};

