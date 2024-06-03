#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float time;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

// NOTE: Render size values must be passed from code
const float renderWidth = 600;
const float renderHeight = 600;

float offset[3] = float[](0.0, 0.85, .85);
float weight[3] = float[](0.17, 0.35, 0.27);

void main()
{
    // Texel color fetching from texture sampler
    vec3 texelColor = texture(texture0, fragTexCoord).rgb*weight[0];

    for (int i = 1; i < 3; i++)
    {
        texelColor += texture(texture0, fragTexCoord + vec2(offset[i])/renderWidth, 0.0).rgb*weight[i];
        texelColor += texture(texture0, fragTexCoord - vec2(offset[i])/renderWidth, 0.0).rgb*weight[i];
    }

    vec4 left = texture(texture0, fragTexCoord - vec2(1.0, 0.50)/renderWidth, 0.0);

    // Scanlines
    vec3 scanline = vec3(
        mod(fragTexCoord.x, 0.01) * 100.0 + 0.7,
        mod(fragTexCoord.y + time * 0.01, 0.005) * 100.0 + 0.7,
        mod(fragTexCoord.y + time * 0.01, 0.0075) * 100.0 + 0.66);

    scanline = clamp(pow(scanline, vec3(2.0)) + 0.1, vec3(0.0), vec3(1.0));
    texelColor = vec3(mix(left.r, texelColor.r, 0.5), texelColor.gb);

    finalColor = vec4(scanline, 1.0); // vec4(texelColor * texelColor * scanline, 1.0);
    finalColor = vec4(texelColor * scanline, 1.0);
}