#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform vec4 grabberColor;


void main()
{
   if(texCoord.y > 1.0-0.1f) {
      FragColor = grabberColor;
   } else {
      FragColor = vec4(0.3, 0.3, 0.3, 0.3);
   }
}