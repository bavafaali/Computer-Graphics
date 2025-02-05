#version 330 core


in vec3 vPos;
in vec3 vNorm;

out Vertex {
    vec4 normal;
    //vec4 color;
} vertex;

void main() {
    vertex.normal = vec4(vNorm, 1.0f);
    gl_Position = vec4(vPos, 1.0f);
}
