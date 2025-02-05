#version 330 core

in vec3 FragPos;
in vec3 NormalWCS;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float alpha;

out vec4 FragColor;

void main(void)
{
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
    vec3 overall = ambient + diffuse + specular;
    FragColor = vec4(overall, 1.0);
}

