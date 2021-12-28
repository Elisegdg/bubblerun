#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vColor;

uniform mat4 uModelMatrix;

void main() {
    vColor = aVertexColor;
    gl_Position = vec4((uModelMatrix * vec4(aVertexPosition, 1)).xyz, 1);
    //gl_Position = vec4(aVertexPosition, 0, 1);
}