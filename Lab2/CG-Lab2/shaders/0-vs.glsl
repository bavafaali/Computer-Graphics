#version 330 core

in vec3 vPos;
in vec3 vNorm;
out vec4 color;
uniform mat4 PV;

void main(void)
{
    color = abs(vec4(vNorm, 1.0));
    gl_Position = PV * vec4(vPos, 1.0f);
}
