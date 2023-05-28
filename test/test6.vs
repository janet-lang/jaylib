#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;

// Input uniform values
uniform mat4 mvp;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoord;
out vec4 fragColor;

void main() {
    // Send vertex attributes to fragment shader
    fragTexCoord = vertexTexCoord * -1;
    fragColor = vec4(vertexPosition, 1);

    // Calculate final vertex position
    gl_Position = mvp*vec4(vertexPosition, 1);
}
