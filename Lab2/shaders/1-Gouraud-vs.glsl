#version 330 core

in vec3 vPos;
in vec3 vNorm;

uniform mat4 W;
uniform mat4 PV;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float alpha;

out vec3 color;

void main(void)
{
    vec3 FragPos = vec3(W * vec4(vPos, 1.0f)); //vertices in WCS
    vec3 NormalWCS = transpose(inverse(mat3(W))) * vNorm; //normals in WCS
    
    gl_Position = PV * vec4(vPos, 1.0f);
    
    //ambient
    float ambientStrength = 0.2;
    vec3 ambient = lightColor * ambientStrength * Ka;
    
    //diffuse
    vec3 L = normalize(lightPos - FragPos);
    vec3 N = normalize(NormalWCS);
    float NL = max(dot(N, L), 0);
    vec3 diffuse = lightColor * Kd * NL;
    
    //specular
    vec3 R = reflect(-L, N);
    vec3 V = normalize(viewPos - FragPos);
    float RV = max(dot(R, V), 0);
    vec3 specular = lightColor * Ks * pow(RV, alpha);
    
    //combine
    color = ambient + diffuse + specular;
}
