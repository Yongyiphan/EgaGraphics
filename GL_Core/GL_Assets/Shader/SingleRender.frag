#version 450 core

layout (location = 0) in vec3 v_Color;
layout (location = 1) in vec2 v_TextureCoordinates;

layout (location = 0) out vec4 FragmentColor;

void main(){
    FragmentColor = vec4(v_Color, 1.0);
}