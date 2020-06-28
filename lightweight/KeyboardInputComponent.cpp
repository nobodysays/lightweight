#include "KeyboardInputComponent.h"
#include "Camera.h"
void CameraKeyboardInputComponent::Process(GameObject& go, const double& deltaTime)
{
    auto win = Game::GetInstance()->window;

    auto cam = Game::GetInstance()->mainCamera;
    if (glfwGetKey(win, GLFW_KEY_W))
    {
        cam->position += cam->cameraFront * speed * (float)deltaTime;
    }
    if (glfwGetKey(win, GLFW_KEY_S))
    {
        cam->position -= cam->cameraFront * speed * (float)deltaTime;
    }
    if (glfwGetKey(win, GLFW_KEY_A))
    {
        cam->position += glm::cross(cam->cameraUp, cam->cameraFront) * speed * (float)deltaTime;
    }
    if (glfwGetKey(win, GLFW_KEY_D))
    {
        cam->position -= glm::cross(cam->cameraUp, cam->cameraFront) * speed * (float)deltaTime;
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        //speed *= 4;
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
    {
        //speed /= 4;
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT))
    {
        cam->position -= cam->cameraUp * speed * (float)deltaTime;
    }
    if (glfwGetKey(win, GLFW_KEY_SPACE))
    {
        cam->position += cam->cameraUp * speed * (float)deltaTime;
    }
    if (glfwGetKey(win, GLFW_KEY_Q))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(win, GLFW_KEY_E))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(win, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(win, true);
}
//float speed = 40.f;
void UnitsKeyboardInputComponent::Process(GameObject& go, const double& deltaTime)
{
    /*auto win = Game::GetInstance()->window;

    if (glfwGetKey(win, GLFW_KEY_UP))
    {
        go.position -= glm::vec3(0, 0, 1) * (float)deltaTime * speed;
    }
    if (glfwGetKey(win, GLFW_KEY_DOWN))
    {
        go.position += glm::vec3(0, 0, 1) * (float)deltaTime * speed;
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT))
    {
        go.position -= glm::vec3(1, 0, 0) * (float)deltaTime * speed;
    }
    if (glfwGetKey(win, GLFW_KEY_RIGHT))
    {
        go.position += glm::vec3(1, 0, 0) * (float)deltaTime * speed;
    }
    if (glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT))
    {
        go.position += glm::vec3(0, -1, 0) *(float) deltaTime *speed;
    }
    if (glfwGetKey(win, GLFW_KEY_ENTER))
    {
        go.position += glm::vec3(0, 1, 0) * (float)deltaTime * speed;
    }
    if (glfwGetKey(win, GLFW_KEY_Q))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(win, GLFW_KEY_E))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (glfwGetKey(win, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(win, true);*/
}
