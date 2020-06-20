#pragma once
#include "helpfile.h"
//#include "Camera.h"
class Game
{
private:
    inline Game(){}
public:
    GLuint uboMatrices;
    static Game* instance;
    static Game* GetInstance();
    GLFWwindow* window = nullptr;
    class Camera* mainCamera = nullptr;
};



