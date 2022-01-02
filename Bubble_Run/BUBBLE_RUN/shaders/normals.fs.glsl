#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragColor;

void main()
{
	fFragColor = vec3(normalize(vNormal_vs));
}