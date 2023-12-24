#version 450 core

layout (location = 0) in vec3 v_Color;
layout (location = 1) in vec2 v_TextureCoordinates;

layout (location = 0) out vec4 FragmentColor;

uniform sampler2D SingleTexture;
uniform int TextureFlag;
uniform int SingleTextureFlag;

void main(){
    bool UseTexture = bool(TextureFlag != 0);
    bool IsSingleTexture = bool(SingleTextureFlag != 0);
    if(UseTexture){
        if(IsSingleTexture){
            FragmentColor = texture(SingleTexture, v_TextureCoordinates);
        }

    }else{
        FragmentColor = vec4(v_Color, 1.0);
    }
}