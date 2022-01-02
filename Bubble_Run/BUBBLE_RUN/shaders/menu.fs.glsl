#version 330

in vec3 vColor;

out vec3 fFragColor;

uniform vec3 uColor;

void main() {
    fFragColor = uColor;
}