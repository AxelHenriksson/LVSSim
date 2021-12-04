#version 330 core
out vec4 FragColor;

in vec3 color;

in vec2 texCoord;

uniform vec4 lightColor;
uniform sampler2D tex0;

void main()
{
   FragColor = lightColor * texture(tex0, texCoord);
}