#include "helpfile.h"
#include "Shader.h"
#include "Game.h"
#include <iostream>
struct Plane
{
    glm::vec3 normal;
    float d;
    Plane(glm::vec3 n, float d) : normal(n), d(d){}
};
class Frustum {
public:
    const float fovy=45;  //
    const float aspect = 4./3.;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    const float alpha = fovy / 2.;

    const float near = 0.1f;//
    const float far = 1.f;//
     
    Plane* planes[6];
    Shader shader = Shader("Frustum.vert", "Frustum.frag");
    float vertices[8 * 6] =
    {
        -1., -1.,  1., 1.0, 1.0, 1.0,
        -1.,  1.,  1., 1.0, 1.0, 1.0,
         1.,  1.,  1., 1.0, 1.0, 1.0,
         1., -1.,  1., 1.0, 1.0, 1.0,
         1., -1., -1., 1.0, 1.0, 1.0,
         1.,  1., -1., 1.0, 1.0, 1.0,
        -1.,  1., -1., 1.0, 1.0, 1.0,
        -1., -1., -1., 1.0, 1.0, 1.0
    };
    glm::vec3 position = { 0, -2, 10 };
    GLuint indices[12 * 3] = {
        0, 3, 1,
        3, 2, 1,

        3, 4, 2,
        2, 4, 5,

        1, 2, 6,
        6, 2, 5,

        0, 1, 7,
        7, 1 ,6,

        7, 6, 5,
        7, 5, 4,

        0, 7, 3,
        3, 7, 4
    };
    Frustum()
    {


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);

            glBindVertexArray(0);

        shader.setMat4("projection", Game::GetInstance()->mainCamera->projection);
        shader.setMat4("translate", glm::translate(glm::mat4(1), position));

         
        planes[0] = new Plane(glm::vec3(0, 0, -1), -glm::dot(glm::vec3(0, 0, -1), position - glm::vec3(0, 0, -0.5) ));  //front!
        planes[1] = new Plane(glm::vec3(0, 0, 1), -glm::dot(glm::vec3(0, 0, 1),   position - glm::vec3(0, 0, 0.5) ));   //back !
        planes[2] = new Plane(glm::vec3(0, 1, 0), -glm::dot(glm::vec3(0, 1, 0),   position - glm::vec3(0, 0.5, 0) ));   // bot!
        planes[3] = new Plane(glm::vec3(0, -1, 0), -glm::dot(glm::vec3(0, -1, 0), position - glm::vec3(0, -0.5, 0)));   //top!
        planes[4] = new Plane(glm::vec3(1, 0, 0), -glm::dot(glm::vec3(1, 0, 0),   position - glm::vec3(0.5, 0, 0)));    //right!
        planes[5] = new Plane(glm::vec3(-1, 0, 0), -glm::dot(glm::vec3(-1, 0, 0), position - glm::vec3(-0.5, 0, 0)));   //left!

    }
    void Draw()
    {
        shader.Use();
        shader.setMat4("view", Game::GetInstance()->mainCamera->view);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / 3, GL_UNSIGNED_INT, 0);
    }
    bool InFrustum(glm::vec3 p, float radius)
    {
        for (size_t i = 2; i < 6; i++)
        {
            glm::vec3 norm = planes[i]->normal;
            auto d = planes[i]->d;
            auto dot = glm::dot(p, norm);
            auto res = dot + d + 2 * radius;
            if (res < 0)
            {
                return false;
            }

        }
        return true;
    }
};