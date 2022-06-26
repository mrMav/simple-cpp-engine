#version 460 core

in vec3 vertexColor;

out vec4 FragColor;

uniform vec3 uColor;
uniform float uTime;

void main(){

    float v = (sin(uTime));
    FragColor = vec4(vertexColor * v, 1.0);

}