#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 normal;
in vec3 currentPos;


uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

uniform sampler2D tex0;

uniform sampler2D tex1;




void main()
{
   float ambient = 0.20f;
   float specularIntensity = 0.50f;

   vec3 unitNormal = normalize(normal);
   vec3 lightDirection = normalize(lightPos - currentPos);

   float diffuse = max(dot(normal, lightDirection), 0.0f);
   vec3  viewDirection = normalize(camPos - currentPos);
   vec3 reflectionDirection = reflect(-lightDirection, normal);
   float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
   float specular = specAmount * specularIntensity;

   FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient) + texture(tex1, texCoord).r * specular;
}