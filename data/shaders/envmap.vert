smooth out vec3 eyeDirection;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    const vec2 positions[4] = vec2[](
        vec2(-1, -1),
        vec2(+1, -1),
        vec2(-1, +1),
        vec2(+1, +1)
    );

    vec4 pos = vec4(positions[gl_VertexID], 1.0, 1.0);

    mat4 inverseProjection = inverse(projectionMatrix);
    mat3 inverseModelview = transpose(mat3(viewMatrix));
    vec3 unprojected = (inverseProjection * pos).xyz;
    eyeDirection = inverseModelview * unprojected;

    gl_Position = pos;
}
