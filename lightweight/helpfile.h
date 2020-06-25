#pragma once
#pragma comment(lib, "glfw3.lib")
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template <typename T>
void Clamp(T& value, const T& min, const T& max)
{
    if (value > max)
        value = max;
    if (value < min)
        value = min;
}


