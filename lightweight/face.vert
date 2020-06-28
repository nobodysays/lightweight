#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;
out mat4 Model;
out vec3 color;
out matrices{
    mat4 view;
    mat4 model;
    mat4 projection;
} mats;

layout(std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 translate;
uniform mat4 scale;

void main()
{
    mat4 model = translate*scale;

    mats.view = view;
    mats.model = model;
    mats.projection = projection;
    Position = vec3(model * vec4(aPos, 1.0));
    Model = model;
    Normal = aNormal;
    color = vec3(0.4, 0,0.7);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
} 