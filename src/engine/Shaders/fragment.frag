#version 460 core

out vec4 FragColor;

uniform vec3 uColor;
uniform float uTime;

void main(){

    float v = sin(uTime) / 2.0 + 0.5;
    FragColor = vec4(uColor.r, uColor.g, uColor.b * v, 1.0);

}