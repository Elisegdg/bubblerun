#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords;

out vec3 fFragColor;


uniform sampler2D uTexture;



void main(){
    vec4 color = texture(uTexture, vTexCoords);
    fFragColor = color.rgb;
    
}