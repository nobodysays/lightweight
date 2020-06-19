#include "Frustum.h"
#include "Game.h"
#include "Camera.h"
Frustum::Frustum()
{


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    planes[0] = new Plane(glm::normalize(glm::cross(glm::vec3( 0, 1, 0), glm::vec3(-1, 0, 0))),
        -glm::dot(glm::normalize(glm::cross(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0))), position + glm::vec3(0, 0, -far))); //far
    planes[1] = new Plane(glm::vec3(0, 0, -1), position.z - near);   //near

    planes[2] = new Plane(glm::normalize(glm::cross(glm::vec3(-w / 2, 0, -far), glm::vec3(0, 1, 0))),
        -glm::dot(glm::normalize(glm::cross(glm::vec3(-w / 2, 0, -far), glm::vec3(0, 1, 0))), position + glm::vec3(-w / 2, 0, -far)));   //left

    planes[3] = new Plane(-glm::normalize(glm::cross(glm::vec3(w / 2, 0, -far), glm::vec3(0, 1, 0))),
        -glm::dot(-glm::normalize(glm::cross(glm::vec3(w / 2, 0, -far), glm::vec3(0, 1, 0))), position + glm::vec3(w / 2, 0, -far)));   //right


    planes[4] = new Plane(-glm::normalize(glm::cross(glm::vec3(0, h / 2, -far), glm::vec3(-1, 0, 0))),
        -glm::dot(-glm::normalize(glm::cross(glm::vec3(0, h / 2, -far), glm::vec3(-1, 0, 0))), position + glm::vec3(0, h / 2, -far)));   //top


    planes[5] = new Plane(-glm::normalize(glm::cross(glm::vec3(0, -h / 2, -far), glm::vec3(1, 0, 0))),
        -glm::dot(-glm::normalize(glm::cross(glm::vec3(0, -h / 2, -far), glm::vec3(1, 0, 0))), position + glm::vec3(0, -h / 2, -far)));   //bot

}

void Frustum::Draw()
{
    //position = Game::GetInstance()->mainCamera->position;
    shader.setMat4("projection", Game::GetInstance()->mainCamera->projection);
    shader.setMat4("translate", glm::translate(glm::mat4(1), position));

    shader.Use();
    shader.setMat4("view", Game::GetInstance()->mainCamera->view);
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, sizeof(indices) / 2, GL_UNSIGNED_INT, 0);

    planes[0]->d = -glm::dot(glm::normalize(glm::cross(glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0))), position + glm::vec3(0, 0, -far));  //far
    planes[1]->d =  position.z - near;   //near

    planes[2]->d = -glm::dot(glm::normalize(glm::cross(glm::vec3(-w / 2, 0, -far), glm::vec3(0, 1, 0))), position + glm::vec3(-w / 2, 0, -far));   //left

    planes[3]->d = -glm::dot(-glm::normalize(glm::cross(glm::vec3(w / 2, 0, -far), glm::vec3(0, 1, 0))), position + glm::vec3(w / 2, 0, -far));   //right


    planes[4]->d = -glm::dot(-glm::normalize(glm::cross(glm::vec3(0, h / 2, -far), glm::vec3(-1, 0, 0))), position + glm::vec3(0, h / 2, -far));   //top


    planes[5]->d =-glm::dot(-glm::normalize(glm::cross(glm::vec3(0, -h / 2, -far), glm::vec3(1, 0, 0))), position + glm::vec3(0, -h / 2, -far));   //bot


}

bool Frustum::InFrustum(glm::vec3 p, float radius)
{
    for (size_t i = 0; i < 6; i++)
    {

        glm::vec3 norm = planes[i]->normal;
        auto d = planes[i]->d;
        auto dot = glm::dot(p, norm);
        auto res = dot + d + 2 * radius;
        //std::cout << res<<std::endl;
        if (res < 0)
        {
            return false;
        }

    }
    return true;
}
