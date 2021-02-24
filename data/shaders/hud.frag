in vec2 textCoords;
out vec4 FragColor;

uniform sampler2D envMap;

void main()
{
    FragColor = texture(envMap, textCoords);
}
