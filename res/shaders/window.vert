#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec3 currentPos;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
   currentPos = vec3(model * vec4(aPos, 1));

   gl_Position = camMatrix * vec4(currentPos, 1.0);
   texCoord = aTex;
}