#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform bool vfxEnabled = true;

uniform vec2 screen_resolution = vec2(920.0, 720.0); // Resolution of the screen
uniform float scanline_intensity = 0.3;             // Intensity of scanline effect
uniform float color_bleed_weight = 0.35;            // Weight of color bleed effect
uniform sampler2D screenTexture;                    // The texture containing the screen image

void main() {
    // Fetch the base color from the texture
    vec4 color = texture(screenTexture, TexCoords);

    // Apply VFX if enabled
    if (vfxEnabled) {
        // Darken top halves of pixels (scanline effect)
        float color_dark_offset = 0.0;
        int y_pos = int(floor(TexCoords.y * screen_resolution.y * 2.0));
        if (int(floor(float(y_pos) / 2.0)) * 2 == y_pos) {
            color_dark_offset = scanline_intensity;
        }

        // Blend current pixel with neighboring pixels (color bleed effect)
        vec2 texel_size = 1.0 / screen_resolution; // Size of a single texel in UV space

        vec4 adjacent_pixel_color_average =
            texture(screenTexture, TexCoords - vec2(texel_size.x, 0.0)) * 0.5 +
            texture(screenTexture, TexCoords - vec2(0.0, texel_size.y)) * 0.5;

        vec4 this_pixel_color = texture(screenTexture, TexCoords);

        // Combine effects
        color = adjacent_pixel_color_average * color_bleed_weight +
                this_pixel_color * (1.0 - color_bleed_weight) -
                vec4(vec3(color_dark_offset), 0.0);
    }

    FragColor = color;
}
