#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

//uniform vec3 cameraPos;
//uniform samplerCube skybox;
in mat4 Model;
void main()
{             
    //vec3 I = normalize(Position - cameraPos);
    //vec3 R = reflect(I, normalize(Normal));
    //FragColor = vec4(texture(skybox, R).rgb, 1.0);
  
    vec3 lightPosition = vec3(0, 3, 0);
    vec3 resultColor= vec3(0.56,0,0.1 );

    vec3 directionToLight = lightPosition - Position;
    directionToLight = normalize(directionToLight);
    float strength = max(dot(directionToLight, Normal), 0.3);


    FragColor = vec4(1, 1, 0, 1);
}