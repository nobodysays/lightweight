#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
	 GLuint program;
	 Shader(const char* vPath, const char* fPath, const char* gPath = nullptr);
	 void Use();
	 void setMat4(const char* value, glm::mat4 mat);
	 void setMat3(const char* value, glm::mat4 mat);
	 void setVec4(const char* value, glm::vec4 vec);
	 void setVec3(const char* value, glm::vec3 vec);
	 void setFloat(const char* value, float f);
	 void setInt(const char* value, int f);
};

