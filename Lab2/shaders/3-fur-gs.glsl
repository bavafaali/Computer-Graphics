#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 50) out;

uniform float furLength = 0.06; // Length of the fur strands
uniform mat4 PV;

in Vertex {
    vec4 normal;
    //vec4 color;
} vertex[];

out vec4 vertex_color;

float random(vec3 st) {
    return fract(sin(dot(st.xyz, vec3(12.9898, 78.233, 45.543))) * 43758.5453);
}


void furStrand2p(vec3 p0, vec3 p1, vec3 n0, vec3 n1, vec3 col, float blending_factor) {
    
    vec3 Norm = mix(n0, n1, blending_factor);
    
    vec3 vert = mix(p0, p1, blending_factor);
    
    gl_Position = PV * vec4(vert, 1.0);
    vertex_color = vec4(col, 1.0);
    EmitVertex();
    
    gl_Position = PV * vec4(vert + Norm * furLength, 1.0);
    EmitVertex();
    EndPrimitive();
}

vec3 furStrand(vec3 p0, vec3 p1, vec3 p2, vec3 n0, vec3 n1, vec3 n2, vec3 col) {
    vec3 V0 = p0 - p1;
    vec3 V1 = p2 - p1;
    
    vec3 Norm = normalize(cross(V1, V0) + random(vec3(0.2, 0.5, 0.7)));
    
    // Center of the triangle
    vec3 Center = (p0 + p1 + p2) / 3.0;
    
    gl_Position = PV * vec4(Center, 1.0);
    vertex_color = vec4(col, 1.0);
    EmitVertex();

    gl_Position = PV * vec4(Center + Norm * furLength, 1.0);
    EmitVertex();
    EndPrimitive();
    
    furStrand2p(p0, Center, n0, Norm, vec3(0, 1, 0), 1.0/3.0);
    furStrand2p(p1, Center, n1, Norm, vec3(0, 1, 0), 1.0/3.0);
    furStrand2p(p2, Center, n2, Norm, vec3(0, 1, 0), 1.0/3.0);
    
    furStrand2p(p0, Center, n0, Norm, vec3(0, 1, 0), 2.0/3.0);
    furStrand2p(p1, Center, n1, Norm, vec3(0, 1, 0), 2.0/3.0);
    furStrand2p(p2, Center, n2, Norm, vec3(0, 1, 0), 2.0/3.0);

    return Center;
}

void main() {

    //Three lines for the 3 vertex normals
    for (int i = 0; i < 3; i++) {
        
        vec3 P = gl_in[i].gl_Position.xyz;
        vec3 N = vertex[i].normal.xyz;
        
        gl_Position = PV * vec4(P, 1.0);
        EmitVertex();
        
        gl_Position = PV * vec4(P + N * furLength, 1.0);
        EmitVertex();
        
        EndPrimitive();
    }
    
    vec3 P0 = gl_in[0].gl_Position.xyz;
    vec3 P1 = gl_in[1].gl_Position.xyz;
    vec3 P2 = gl_in[2].gl_Position.xyz;
    
    vec3 N0 = vertex[0].normal.xyz;
    vec3 N1 = vertex[1].normal.xyz;
    vec3 N2 = vertex[2].normal.xyz;
    
    //magenta
    vec3 C = furStrand(P0, P1, P2, N0, N1, N2, vec3(1, 0, 1));
    //green
    vec3 C1 = furStrand(C, P1, P2, N0, N1, N2, vec3(0, 1, 0));
    //yellow
    vec3 C2 = furStrand(P0, C, P2, N0, N1, N2, vec3(1, 1, 0));
    //blue
    vec3 C3 = furStrand(P0, P1, C, N0, N1, N2, vec3(0, 0, 1));

    furStrand2p(P0, P1, N0, N1, vec3(0, 1, 0), 1.0/3.0);
    furStrand2p(P0, P2, N0, N2, vec3(0, 1, 0), 1.0/3.0);
    furStrand2p(P2, P1, N2, N1, vec3(0, 1, 0), 1.0/3.0);
    furStrand2p(P0, P1, N0, N1, vec3(0, 1, 0), 2.0/3.0);
    furStrand2p(P0, P2, N0, N2, vec3(0, 1, 0), 2.0/3.0);
    furStrand2p(P2, P1, N2, N1, vec3(0, 1, 0), 2.0/3.0);
    
}
