#include "helpfile.h"
#include "Shader.h"
#include "Cube.h"
#include "Game.h"
#include "KeyboardInputComponent.h"
#include "MouseInputComponent.h"
#include "Camera.h"
#include "Frustum.h"
double lastTime = 0;
int nbFrames = 0;


void showFPS(GLFWwindow* pWindow)
{
    // Measure speed
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;
    nbFrames++;
    if (delta >= 1.0) { // If last cout was more than 1 sec ago
        double fps = double(nbFrames) / delta;

        std::stringstream ss;
        ss << " [" << fps << " FPS]";

        glfwSetWindowTitle(pWindow, ss.str().c_str());

        nbFrames = 0;
        lastTime = currentTime;
    }
}

int main()
{
    constexpr size_t displayWidth = 800;
    constexpr size_t displayHeight =  600;
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* glfwWin = glfwCreateWindow(displayWidth, displayHeight, "title", nullptr, nullptr);
    Game::GetInstance()->window = glfwWin;
    glfwMakeContextCurrent(glfwWin);
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, displayWidth, displayHeight);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glfwSwapInterval(0);
    glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    constexpr int w = 200;
    constexpr int h = 200;
    constexpr int d = 1;
    Camera camera;
    //camera.position = { 0, 0, 4 };
    Game::GetInstance()->mainCamera = &camera;
    Cube* cubes[w][h][d];
    auto keyboardInputComponent = new CameraKeyboardInputComponent();
    auto mouseInputComponent = new MouseInputComponent();
    //camera.AddComponent(mouseInputComponent);
    //camera.AddComponent(keyboardInputComponent);
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < d; k++)
            {
                cubes[i][j][k] = new Cube();
                cubes[i][j][k]->AddComponent(new UnitsKeyboardInputComponent());
                cubes[i][j][k]->position = { i - w / 2, j - h / 2,10 + k };
            }
            
        }
    Frustum f;
    int entitycounter;
    while (!glfwWindowShouldClose(glfwWin))
    {
        showFPS(glfwWin);
        glfwPollEvents();
        glClearColor(0.03f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        entitycounter = 0;
        for (size_t i = 0; i < w; i++)
            for (size_t j = 0; j < h; j++)
                for (size_t k = 0;k < d; k++)
                {
                    if (f.InFrustum(cubes[i][j][k]->position, 0.5))
                    {
                        cubes[i][j][k]->Draw();  
                    }
                    cubes[i][j][k]->Update();
                }
        camera.Update();
        f.Draw();
        
        glfwSwapBuffers(glfwWin);
    }
}
