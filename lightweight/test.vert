#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;
    layout(std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
void main()
{
    gl_Position = projection*view*vec4(position, 1);
    ourColor = vec3(1);
    TexCoord = texCoord;
}