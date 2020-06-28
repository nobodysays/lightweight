//#pragma once
#include "helpfile.h"
#include "Shader.h"
#include "Cube.h"
#include "Game.h"
#include "KeyboardInputComponent.h"
#include "MouseInputComponent.h"
#include "Camera.h"
#include "Frustum.h"
#include "World.h"
#include "Chunk.h"
//#include "Texture.h"
#include "stb_image.h"
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
    glfwSetWindowPos(glfwWin, 800, 300);
    Game::GetInstance()->window = glfwWin;
    glfwMakeContextCurrent(glfwWin);
    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, displayWidth, displayHeight);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glfwSwapInterval(0);
    glfwSetInputMode(glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    constexpr int w = 22;
    constexpr int h = 5;
    constexpr int d = 1;
    Camera camera;
    World world;
    camera.position = { 0, 0, 0 };
    Game::GetInstance()->mainCamera = &camera;
    Game::GetInstance()->world = &world;
    world.Generate();
    Cube* cubes[w][h][d];
    auto keyboardInputComponent = new CameraKeyboardInputComponent();
    auto mouseInputComponent = new MouseInputComponent();
    camera.AddComponent(mouseInputComponent);
    camera.AddComponent(keyboardInputComponent);
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < d; k++)
            {
                cubes[i][j][k] = new Cube();

                cubes[i][j][k]->position = { i - w / 2, j - h / 2,-6 - k };
            }
            
        }

    GLuint uboMatrices;
    glGenBuffers(1, &uboMatrices);

    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

    Game::GetInstance()->uboMatrices = uboMatrices;

    glm::mat4 projection = Game::GetInstance()->mainCamera->projection;
    glBindBuffer(GL_UNIFORM_BUFFER, Game::GetInstance()->uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    int entitycounter;







    float quadVertices[] = {
        // координаты  // цвета
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    GLuint quadVAO;
    GLuint quadVBO;

    glGenBuffers(1, &quadVBO);
    glGenVertexArrays(1, &quadVAO);



    Shader shader("quad.vert", "quad.frag");
    glm::vec2 translations[100];
    int index = 0;
    float offset = 0.1f;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    unsigned int instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);

    //shader.Use();
    //for (unsigned int i = 0; i < 100; i++)
    //{
    //    std::stringstream ss;
    //    std::string index;
    //    ss << i;
    //    index = ss.str();
    //    shader.setVec2(("offsets[" + index + "]").c_str(), translations[i]);
    //}
















    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        // Positions         // Texture Coords
         0,   0,   0,  0, 0,
         0.5, 0,   0,  1, 0, // Bottom Right
         0.5, 0.5, 0,  1, 1, // Bottom Left
         0,   0.5, 0,  0, 1 // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO


    // Load and create a texture 
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Load image, create texture and generate mipmaps
    int width, height;
    unsigned char* image = stbi_load("stone.png", &width, &height, 0, 3);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.


    Shader ourShader("test.vert", "test.frag");
    ourShader.bindBlock("Matrices", 0);


    constexpr auto n = 2;
    double lastTime = 0;
    double deltaTime = 0;
    while (!glfwWindowShouldClose(glfwWin))
    {
        showFPS(glfwWin);
        glfwPollEvents();
        glClearColor(0.03f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        entitycounter = 0;
        for (size_t i = 0; i < w; i++)
            for (size_t j = 0; j < h; j++)
                for (size_t k = 0;k < d; k++)
                    cubes[i][j][k]->Update(deltaTime);

        for (size_t i = 0; i < w; i++)
            for (size_t j = 0; j < h; j++)
                for (size_t k = 0; k < d; k++)
                    cubes[i][j][k]->Render();


        //std::cout <<"entities: "<< entitycounter << std::endl;
        shader.Use();
        glBindVertexArray(quadVAO);
        //glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100);
        glBindVertexArray(0);
        //glDrawArrays(GL_TRIANGLES, 0, 6);w
        // Bind Texture
        //glBindTexture(GL_TEXTURE_2D, texture);
        camera.Update(deltaTime);
        world.Update(deltaTime);
        glfwSwapBuffers(glfwWin);
    }
}
