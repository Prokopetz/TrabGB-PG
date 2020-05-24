#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 transform;

out vec4 vertexColor;
void main()
{
    gl_Position = transform * position;
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}