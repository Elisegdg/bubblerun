#version 330 core

const int MAX_POINT_LIGHTS = 5;

in vec3 vPosition_vs; //Position du sommet transformé dans l'espace view
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace view
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform vec3 uKdiffuseD;
uniform vec3 uKspecularD;
uniform vec3 uKdiffuseP;
uniform vec3 uKspecularP;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;
uniform vec3 uLightIntensityPonctual;

uniform sampler2D uTexture;

vec3 directionalLightBlinnPhong(){
    vec3 w0 = normalize(-vPosition_vs);
    vec3 wi = normalize(uLightDir_vs);
    vec3 halfVector = (w0 + wi)/2;
    vec3 directionalLight = uLightIntensity * (uKdiffuseD * (dot(wi, vNormal_vs)) + uKspecularD * (pow(dot(halfVector,vNormal_vs), uShininess)));
    return directionalLight;
}

vec3 pointLightBlinnPhong(){
    vec3 w0 = normalize(-vPosition_vs);
    vec3 wi = normalize(uLightPos_vs - vPosition_vs);
    vec3 halfVector = (w0 + wi)/2;
    float d = distance(uLightPos_vs,vPosition_vs);
    vec3 pointLight = (uLightIntensityPonctual / (d*d)) * (uKdiffuseP * (dot(wi, vNormal_vs)) + uKspecularP * (pow(dot(halfVector,vNormal_vs), uShininess)));
    return pointLight;
}


void main()
{    
    vec4 color = texture(uTexture, vTexCoords);

    vec3 dirLight = directionalLightBlinnPhong();

    vec3 pointLight = pointLightBlinnPhong();

    fFragColor = (dirLight+pointLight)*color.rgb;
}