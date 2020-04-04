#version 400
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec3 vertexNormal;

out vec4 fragColor;
out vec3 fragNormal;
out vec3 fragPosition;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   vec4 worldPosition = world * vec4(position, 1.0);
   gl_Position = projection * view * worldPosition;

   vec3 worldNormal = mat3(world) * vertexNormal;

   fragPosition = vec3(worldPosition);
   fragNormal = normalize(worldNormal);
   fragColor = vertexColor;
}