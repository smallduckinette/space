out vec2 textCoords;

uniform vec3 range;

void main() {
    vec2 positions[4] = vec2[](
        vec2(-1, 1 - range.y * 2),
        vec2(-1 + range.x * 2, 1 - range.y * 2),
        vec2(-1, 1),
        vec2(-1 + range.x * 2, 1)
    );

    const vec2 coords[4] = vec2[](
        vec2(0, 1),
        vec2(1, 1),
        vec2(0, 0),
        vec2(1, 0)
    );

    textCoords = coords[gl_VertexID];
    gl_Position = vec4(positions[gl_VertexID], 0, 1.0);
}
