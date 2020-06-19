#pragma once
#include "GameObject.h"
#include "Shader.h"
#include "Game.h"
#include "Camera.h"
class CubeModel
{
public:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    Shader shader = Shader("cube.vert", "cube.frag");
    float vertices[8*6] =
    {
        -0.5, -0.5,  0.5, 1.0, 1.0, 1.0,
        -0.5,  0.5,  0.5, 1.0, 1.0, 1.0,
         0.5,  0.5,  0.5, 1.0, 1.0, 1.0,
         0.5, -0.5,  0.5, 1.0, 1.0, 1.0,
         0.5, -0.5, -0.5, 1.0, 1.0, 1.0,
         0.5,  0.5, -0.5, 1.0, 1.0, 1.0,
        -0.5,  0.5, -0.5, 1.0, 1.0, 1.0,
        -0.5, -0.5, -0.5, 1.0, 1.0, 1.0
    };

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

    inline CubeModel()
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
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
            glEnableVertexAttribArray(1);
            glBindVertexArray(0);

        shader.setMat4("projection", Game::GetInstance()->mainCamera->projection);
    }

};
class Cube : public GameObject
{
private:
    static CubeModel* model;

public:
    glm::vec3 color = glm::vec3(1);
    inline Cube()
    {
        if(!model)
            model = new CubeModel();
    }

    inline void Draw()
    {
        model->shader.Use();
        model->shader.setMat4("view", Game::GetInstance()->mainCamera->view);
        model->shader.setMat4("rotation", glm::rotate<float>(glm::mat4(1), glfwGetTime() * 0.0f, { 1, 0, 1 }));
        model->shader.setMat4("translate", glm::translate(glm::mat4(1),position));
        glBindVertexArray(model->VAO);
        glDrawElements(GL_TRIANGLES, sizeof(model->indices)/3, GL_UNSIGNED_INT, 0);
    }

    inline void Update()override {
        GameObject::Update();
    }

    inline ~Cube()
    {
        delete model;
    }
};

CubeModel* Cube::model = nullptr;
