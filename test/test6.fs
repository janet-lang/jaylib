#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float time;
uniform vec2 freq;
uniform vec4 params;
uniform int width;
uniform int height;

// Output fragment color
out vec4 finalColor;

void main() {
    vec2 freq = freq.xy;
    vec2 amp = params.xy;
    vec2 speed = params.zw;

    float pixelWidth = 1.0 / width;
    float pixelHeight = 1.0 / height;
    float aspect = pixelHeight / pixelWidth;

    vec2 p = fragTexCoord;
    p.x += cos(fragTexCoord.y * freq.x / ( pixelWidth * 1000.0) + (time * speed.x)) * amp.x * pixelWidth;
    p.y += sin(fragTexCoord.x * freq.y * aspect / ( pixelHeight * 1000.0) + (time * speed.y)) * amp.y * pixelHeight;

    vec4 texelColor = texture(texture0, fragTexCoord);

    finalColor = texture(texture0, p)*colDiffuse*fragColor;
}
