#version 410 core
layout (triangles) in;
layout (line_strip, max_vertices = 5) out;

in matrices{
    mat4 view;
    mat4 model;
    mat4 projection;
} mats;

 vec3 GetNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
} 
uniform float time;
out vec3 color;
void main() {    
     vec3 normal = GetNormal();
     mat3 normalMatrix = mat3(transpose(inverse(mats.view * mats.model)));
     normal = normalize(vec3(mats.projection * vec4(normalMatrix * normal, 0.0)));
     vec3 center = vec3(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3;
    gl_Position = gl_in[0].gl_Position;
    color = vec3(1, 1, 0);
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    color = vec3(1, 0.4, 0);
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
    color = vec3(0.1, 0.4, 0);
    EmitVertex();
    EndPrimitive();
    gl_Position = vec4(center, 1);
    color = vec3(1);
    EmitVertex();
    gl_Position = vec4(center  + normal, 1);
    color = vec3(1);
    EmitVertex();
    EndPrimitive();


}  