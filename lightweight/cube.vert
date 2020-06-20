#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;
out mat4 Model;

layout(std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 translate;
uniform mat4 rotation;

void main()
{
    mat4 model = translate*rotation;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model*vec4(aPos, 1.0));
    Model = model;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
} 