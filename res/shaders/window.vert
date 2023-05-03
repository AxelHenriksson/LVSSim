#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec3 globalPos;
out vec3 localPos;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
   globalPos = vec3(model * vec4(aPos, 1));
   localPos = aPos;

   gl_Position = camMatrix * vec4(globalPos, 1.0);
   texCoord = aTex;
}