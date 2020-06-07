#version 330 core
layout(location = 0) out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;
in vec2 offsetVec;

uniform sampler2D ourTexture;
uniform vec2 offset;

void main()
{
    vec2 tc = vec2(TexCoord.x + offset.x, TexCoord.y + offset.y);
    FragColor = texture(ourTexture, tc);
}