#version 450 core

layout (location = 0) in vec3 aVertexPosition;
layout (location = 1) in vec3 aVertexColor;
layout (location = 2) in vec2 aVertexTextureCoordinates;


layout (location = 0) out vec3 v_Color;
layout (location = 1) out vec2 v_TextureCoordinates;

uniform mat4 trs;

void main(){
    gl_Position = trs * vec4(aVertexPosition, 1.0);
    v_Color = aVertexColor;
    v_TextureCoordinates = aVertexTextureCoordinates;
}
