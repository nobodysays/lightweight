#pragma once
#include <iostream>
#include "helpfile.h"
#include <vector>
class Texture
{
public:
	GLuint texture;
    Texture(){}
   void LoadTexture(const char* path);
   void LoadCubemap(std::vector<std::string> faces);
   GLuint operator*();
};

