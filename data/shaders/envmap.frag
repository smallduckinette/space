smooth in vec3 eyeDirection;
out vec4 FragColor;

uniform samplerCube envMap;

void main()
{
    FragColor = texture(envMap, eyeDirection);
}
