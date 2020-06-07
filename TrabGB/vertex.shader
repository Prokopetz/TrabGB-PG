#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 transform;

out vec3 vertexColor;
out vec2 TexCoord;


void main()
{
    gl_Position = transform * position;
    vertexColor = color;
    TexCoord = aTexCoord;
}