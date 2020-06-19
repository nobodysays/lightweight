#include "MouseInputComponent.h"
#include "helpfile.h"
#include "Camera.h"
#include "Game.h"
void MouseInputComponent::Process(GameObject&)
{
    double x;
    double y;
    glfwGetCursorPos(Game::GetInstance()->window, &x, &y);
    Game::GetInstance()->mainCamera->yaw -= prevX - x;
    Game::GetInstance()->mainCamera->pitch += prevY - y;
    prevX = x;
    prevY = y;
}
