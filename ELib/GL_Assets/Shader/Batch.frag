#version 450 core

layout (location = 0) in vec3 v_Color;
layout (location = 1) in vec2 v_TextureCoordinates;
layout (location = 2) in float v_TexSlotID;

layout (location = 0) out vec4 FragmentColor;

uniform sampler2D all_textures[16];
uniform int font_index[16];
uniform int ignore_tex;

void main(){
    int texid = int(v_TexSlotID);
    // No textures so use color;
    if(texid == 16 || ignore_tex == 0){
        FragmentColor = vec4(v_Color, 1.0);
    }
    else{
        if(font_index[texid] == 0){
            FragmentColor = texture(all_textures[texid], v_TextureCoordinates);
        }
        else{
            vec4 font = vec4(1.0, 1.0, 1.0, texture(all_textures[texid], v_TextureCoordinates).r);
            FragmentColor = vec4(v_Color, 1.0) * font;
        }
    }
}