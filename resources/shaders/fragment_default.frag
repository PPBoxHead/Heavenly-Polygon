#version 330 core


out vec4 FragColor;

in vec3 ourColor;
in vec2 uvCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, uvCoord) * vec4(ourColor, 1.0); // display texture and multiply the vertex colors
    //FragColor = texture(ourTexture, uvCoord); // display only texture
    //FragColor = vec4(ourColor, 1.0); // display only vertex colors
    //FragColor = vec4(1.0); // display as white color
}