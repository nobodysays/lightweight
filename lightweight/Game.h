#pragma once
#include "helpfile.h"
//#include "Camera.h"
class Game
{
private:
    inline Game(){}
    static Game* instance;
public:
    GLuint uboMatrices;
    static Game* GetInstance();
    GLFWwindow* window = nullptr;
    class Camera* mainCamera = nullptr;
    class World* world = nullptr;
};



