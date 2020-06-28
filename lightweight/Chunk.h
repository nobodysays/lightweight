#pragma once
#include "helpfile.h"
#include "GameObject.h"
#include "Shader.h"
#include "Game.h"
#include "Camera.h"
class FaceModel
{
public:
    GLuint leftVAO;
    GLuint leftVBO;
    GLuint leftEBO;

    GLuint rightVAO;
    GLuint rightVBO;
    GLuint rightEBO;

    GLuint frontVAO;
    GLuint frontVBO;
    GLuint frontEBO;

    GLuint backVAO;
    GLuint backVBO;
    GLuint backEBO;

    GLuint topVAO;
    GLuint topVBO;
    GLuint topEBO;

    GLuint bottomVAO;
    GLuint bottomVBO;
    GLuint bottomEBO;
    Shader shader = Shader("face.vert", "face.frag");
    float left[4 * 3] =
    {
        -0.5, -0.5,-0.5,
        -0.5, -0.5, 0.5,
        -0.5,  0.5, 0.5,
        -0.5,  0.5,-0.5
    };
    float right[4 * 3] =
    {
         0.5, -0.5, 0.5,
         0.5, -0.5,-0.5,
         0.5,  0.5,-0.5,
         0.5,  0.5, 0.5
    };
    float front[4 * 3] =
    {
         -0.5, -0.5, 0.5,
          0.5, -0.5, 0.5,
          0.5,  0.5, 0.5,
         -0.5,  0.5, 0.5
    };
    float back[4 * 3] =
    {
          0.5, -0.5,-0.5,
         -0.5, -0.5,-0.5,
         -0.5,  0.5,-0.5,
          0.5,  0.5,-0.5

    };
    float top[4 * 3] =
    {
         -0.5,  0.5, 0.5,
          0.5,  0.5, 0.5,
          0.5,  0.5,-0.5,
         -0.5,  0.5,-0.5
    };
    float bottom[4 * 3] =
    {
         -0.5, -0.5,-0.5,
           0.5, -0.5,-0.5,
           0.5, -0.5, 0.5,
          -0.5, -0.5, 0.5
    };
    GLuint indices[2 * 3]{
        0, 1, 2,
        2, 3, 0
    };
    inline FaceModel()
    {

        glGenVertexArrays(1, &leftVAO);
        glGenBuffers(1, &leftEBO);
        glGenBuffers(1, &leftVBO);

        glBindVertexArray(leftVAO);
        glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(left), left, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leftEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        //
        glGenVertexArrays(1, &rightVAO);
        glGenBuffers(1, &rightEBO);
        glGenBuffers(1, &rightVBO);

        glBindVertexArray(rightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(right), right, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rightEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        //
        glGenVertexArrays(1, &frontVAO);
        glGenBuffers(1, &frontEBO);
        glGenBuffers(1, &frontVBO);

        glBindVertexArray(frontVAO);
        glBindBuffer(GL_ARRAY_BUFFER,frontVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(front), front, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, frontEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        //

        glGenVertexArrays(1, &backVAO);
        glGenBuffers(1, &backEBO);
        glGenBuffers(1, &backVBO);

        glBindVertexArray(backVAO);
        glBindBuffer(GL_ARRAY_BUFFER, backVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(back), back, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        //
        glGenVertexArrays(1, &topVAO);
        glGenBuffers(1, &topEBO);
        glGenBuffers(1, &topVBO);

        glBindVertexArray(topVAO);
        glBindBuffer(GL_ARRAY_BUFFER, topVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(top), top, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, topEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        //
        glGenVertexArrays(1, &bottomVAO);
        glGenBuffers(1, &bottomEBO);
        glGenBuffers(1, &bottomVBO);

        glBindVertexArray(bottomVAO);
        glBindBuffer(GL_ARRAY_BUFFER, bottomVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(bottom), bottom, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bottomEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        shader.bindBlock("Matrices", 0);
    }

};





struct Face
{
    static FaceModel* model;
    glm::vec3 position;
    Face()
    {
        if (!model)
            model = new FaceModel();
    }
    virtual void Draw()
    {
        model->shader.Use();
        model->shader.setFloat("time", glfwGetTime());
        model->shader.setMat4("scale", glm::scale(glm::mat4(1), glm::vec3(1)));
        model->shader.setMat4("translate", glm::translate(glm::mat4(1), position));
    }
};

struct LeftFace : Face
{
    void Draw() override
    {
        Face::Draw();
        glBindVertexArray(model->leftVAO);
        glDrawElements(GL_TRIANGLES, sizeof(model->indices) / 3, GL_UNSIGNED_INT, 0);
    }
};

struct RightFace : Face
{
    void Draw() override
    {
        Face::Draw();
        glBindVertexArray(model->rightVAO);
        glDrawElements(GL_TRIANGLES, sizeof(model->indices) / 3, GL_UNSIGNED_INT, 0);
    }
};

struct BottomFace : Face
{
    void Draw() override
    {
        Face::Draw();
        glBindVertexArray(model->bottomVAO);
        glDrawElements(GL_TRIANGLES, sizeof(model->indices) / 3, GL_UNSIGNED_INT, 0);
    }
};
struct TopFace : Face
{
    void Draw() override
    {
        Face::Draw();
        glBindVertexArray(model->topVAO);
        glDrawElements(GL_TRIANGLES, sizeof(model->indices) / 3, GL_UNSIGNED_INT, 0);
    }
};

struct BackFace : Face
{
    void Draw() override
    {
        Face::Draw();
        glBindVertexArray(model->backVAO);
        glDrawElements(GL_TRIANGLES, sizeof(model->indices) / 3, GL_UNSIGNED_INT, 0);
    }
};
struct FrontFace : Face
{
    void Draw() override
    {
        Face::Draw();
        glBindVertexArray(model->frontVAO);
        glDrawElements(GL_TRIANGLES, sizeof(model->indices) / 3, GL_UNSIGNED_INT, 0);
    }
};
#define c 10
class ChunkBlock
{
public:
    Face* faces[6];
    GLuint visibleFaces=0;
    glm::vec3 position;
    void AddFace(Face* face)
    {
        face->position = position;
        faces[visibleFaces++] = face;
    }

    void Draw()
    {
        for (size_t i = 0; i < visibleFaces; i++)
        {
            faces[i]->Draw();
        }
    }
};
class StoneBlock : public ChunkBlock
{

};

enum BlockIds
{
    AIR = 0,
    STONE, 
    GRASS
};

class Chunk : public GameObject
{
public:

    ChunkBlock* blocks[c][c][c];

    void Update(const double&) override;
    inline Chunk(glm::vec3 position) 
    {
        this->position = position;
        for (size_t x = 0; x < c; x++)
            for (size_t y = 0; y < c; y++)
                for (size_t z = 0; z < c; z++)
                {
                    if ((x-5) * (x - 5) + (z-5) * (z - 5) <= c)
                    {
                        blocks[x][y][z] = new StoneBlock();
                    }
                    else
                        blocks[x][y][z] = nullptr;
                }
    }
    void GenerateMesh();
    inline void Render() override
    {
        for (size_t x = 0; x < c; x++)
        {
            for (size_t y = 0; y < c; y++)
            {
                for (size_t z = 0; z < c; z++)
                {
                    if (blocks[x][y][z] && Game::GetInstance()->mainCamera->IsSphereInFrustum(blocks[x][y][z]->position, 0.1))
                    {
                        blocks[x][y][z]->Draw();
                    }
                }
            }
        }
    }
private:
};

