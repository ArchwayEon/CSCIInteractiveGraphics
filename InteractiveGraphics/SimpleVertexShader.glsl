#version 400
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
out vec4 fragColor;
void main()
{
   gl_Position = vec4(position, 1.0);
   fragColor = vec4(vertexColor, 1.0);
}