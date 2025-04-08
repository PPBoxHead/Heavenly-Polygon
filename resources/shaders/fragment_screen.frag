#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform bool vfxEnabled = true;

uniform sampler2D screenTexture;  // The texture containing the screen image
uniform mat4 ditherMatrix;      // The texture containing the dither pattern
uniform int colDepth = 24;        // The color depth level
uniform bool ditherBanding = true;

void main() {
    vec2 dithSize = vec2(4, 4); // Dimensions of the dithering matrix
    vec2 bufSize = textureSize(screenTexture, 0);
    vec2 uv = TexCoords;

    vec4 color = texture(screenTexture, uv);

    if (vfxEnabled) {
        // Calculate the dithering offset
        ivec2 pos = ivec2(mod(floor(TexCoords * bufSize), 4.0)); // Calculate the position in the 4x4 dither matrix
        float ditherValue = ditherMatrix[pos.x][pos.y] - 0.5;

        color.rgb = round(color.rgb * float(colDepth) + ditherValue * (ditherBanding ? 1.0 : 0.0)) / float(colDepth);
    }

    FragColor = color;
}
