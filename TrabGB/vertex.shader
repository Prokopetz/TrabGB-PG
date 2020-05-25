#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 transform;
uniform vec4 color;

out vec4 vertexColor;
void main()
{
    gl_Position = transform * position;
    vertexColor = color;
}