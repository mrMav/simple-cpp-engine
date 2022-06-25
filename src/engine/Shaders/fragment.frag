#version 460 core

in vec3 vertexColor;

out vec4 FragColor;

uniform vec3 uColor;
uniform float uTime;

void main(){

    //float v = sin(uTime) / 2.0 + 0.5;
    FragColor = vec4(vertexColor, 1.0);

}