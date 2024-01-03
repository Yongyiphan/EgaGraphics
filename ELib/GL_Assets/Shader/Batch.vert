#version 450 core

layout (location = 0) in vec3 aVertexPosition;
layout (location = 1) in vec3 aVertexColor;
layout (location = 2) in vec2 aVertexTextureCoordinates;
layout (location = 3) in float aVertexTexSlotID;


layout (location = 0) out vec3 v_Color;
layout (location = 1) out vec2 v_TextureCoordinates;
layout (location = 2) out float v_TexSlotID;

uniform mat4 proj_view;

void main(){
    gl_Position = proj_view * vec4(aVertexPosition, 1.0);
    v_Color = aVertexColor;
    v_TextureCoordinates = aVertexTextureCoordinates;
    v_TexSlotID = aVertexTexSlotID;
}
