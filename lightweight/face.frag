#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec3 color;
//uniform vec3 cameraPos;
//uniform samplerCube skybox;

in mat4 Model;
void main()
{             
    //vec3 I = normalize(Position - cameraPos);
    //vec3 R = reflect(I, normalize(Normal));
    //FragColor = vec4(texture(skybox, R).rgb, 1.0);
  
    vec3 lightPosition = vec3(0, 21, 0);
    vec3 resultColor= vec3(0.56,0,0.1 );

    vec3 directionToLight = lightPosition - Position;
    float distance = length(directionToLight);
    directionToLight = normalize(directionToLight);
    float strength = max(dot(directionToLight, Normal), 0.3) * 1000 / (distance*distance + 3*distance + 1);


    FragColor = vec4(color*strength, 1);
}