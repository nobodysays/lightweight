#version 410 core
layout (location = 0) in vec3 aPos;

layout (std140) uniform Matrices
{
    mat4 projection;
};

void main()
{
    gl_PointSize= 4;
    gl_Position = vec4(aPos, 1);
}
