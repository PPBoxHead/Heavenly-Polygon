#version 330 core


layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the texture coordinates has attribute position 2
layout (location = 3) in vec3 aNormal;

out vec3 ourColor; // output a color to the fragment shader
noperspective out vec2 uvCoord;

uniform vec2 screen_resolution;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// FIXME: This function is not working properly, returns Z=0 in some situations
vec4 to_low_precision(vec4 position,vec2 resolution)
{
	//Perform perspective divide
	vec3 perspective_divide = position.xyz / vec3(position.w);
	
	//Convert to screenspace coordinates
	vec2 screen_coords = (perspective_divide.xy 
							+ vec2(1.0,1.0)) 
							* vec2(resolution.x,resolution.y) 
							* 0.5;

	//Truncate to integer
	vec2 screen_coords_truncated = vec2(int(screen_coords.x),
										int(screen_coords.y));
	
	//Convert back to clip range -1 to 1
	vec2 reconverted_xy = ((screen_coords_truncated * vec2(2,2))
							 / vec2(resolution.x,resolution.y)) 
							- vec2(1,1);

	//Construct return value
	vec4 ps1_pos = vec4(reconverted_xy.x,
						reconverted_xy.y,
						perspective_divide.z,
						position.w);

	ps1_pos.xyz = ps1_pos.xyz * vec3(	position.w,
										position.w,
										position.w);

	return ps1_pos;
}

void main()
{
    vec4 final_position = projection * view * model * vec4(aPos, 1.0);

    // Quantize position to lower precision
    gl_Position = to_low_precision(final_position, screen_resolution);

    ourColor = aColor; // set ourColor to the input color we got from the vertex data
	uvCoord = aTexCoord; // set uvCoord to the input texture coordinates we got from the vertex data
}