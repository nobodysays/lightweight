#include "Frustum.h"
#include "Game.h"
#include "Camera.h"
Frustum::Frustum(float fovy, float aspect, float near, float far) : fovy(fovy), aspect(aspect), near(near), far(far)
{

    planes[0] = new Plane(glm::normalize(glm::cross(glm::vec3( 0, 1, 0), glm::vec3(-1, 0, 0))),
        -glm::dot(glm::normalize(glm::cross(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0))), glm::vec3(0, 0, -far))); //far

    planes[1] = new Plane(glm::vec3(0, 0, -1), - near);   //near

    planes[2] = new Plane(glm::normalize(glm::cross(glm::vec3(-w / 2, 0, -far), glm::vec3(0, 1, 0))),
        -glm::dot(glm::normalize(glm::cross(glm::vec3(-w / 2, 0, -far), glm::vec3(0, 1, 0))), glm::vec3(-w / 2, 0, -far)));   //left

    planes[3] = new Plane(-glm::normalize(glm::cross(glm::vec3(w / 2, 0, -far), glm::vec3(0, 1, 0))),
        -glm::dot(-glm::normalize(glm::cross(glm::vec3(w / 2, 0, -far), glm::vec3(0, 1, 0))),  glm::vec3(w / 2, 0, -far)));   //right


    planes[4] = new Plane(-glm::normalize(glm::cross(glm::vec3(0, h / 2, -far), glm::vec3(-1, 0, 0))),
        -glm::dot(-glm::normalize(glm::cross(glm::vec3(0, h / 2, -far), glm::vec3(-1, 0, 0))), glm::vec3(0, h / 2, -far)));   //top


    planes[5] = new Plane(-glm::normalize(glm::cross(glm::vec3(0, -h / 2, -far), glm::vec3(1, 0, 0))),
        -glm::dot(-glm::normalize(glm::cross(glm::vec3(0, -h / 2, -far), glm::vec3(1, 0, 0))),  glm::vec3(0, -h / 2, -far)));   //bot

}

bool Frustum::IsSphereInFrustum(const glm::vec3& pos, const float& radius)
{
    //glm::vec3 positionInViewSpace = Game::GetInstance()->mainCamera->view * glm::vec4(pos, 1);//model space to view space
    for (size_t i = 0; i < 6; i++) // for each sides of frustum
    {
        auto norm = planes[i]->normal;
        auto d = planes[i]->d;
        auto dot = glm::dot(pos, norm);
        auto res = dot + d + 2 * radius;
        if (res < 0)
            return false;
    }
    return true;
}
