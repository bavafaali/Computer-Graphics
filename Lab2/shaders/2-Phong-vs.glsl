#version 330 core

in vec3 vPos;
in vec3 vNorm;

uniform mat4 W;
uniform mat4 PV;

out vec3 FragPos;
out vec3 NormalWCS;

void main(void)
{
    FragPos = vec3(W * vec4(vPos, 1.0f)); //vertices in WCS
    NormalWCS = transpose(inverse(mat3(W))) * vNorm; //normals in WCS
    
    gl_Position = PV * vec4(vPos, 1.0f);
}
