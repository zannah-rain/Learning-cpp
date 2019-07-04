#version 330 core
layout (location = 0) in vec3 aPos; // The position variable has attribute position 0
layout (location = 1) in vec4 aColor; // The color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // The texture coordinate variable has position 2

out vec4 vertexColor; // Specify a color output to the fragment shader
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0); // Transformations have to be in opposite order!
	vertexColor = aColor; // Just set the output color to dark red
	TexCoord = aTexCoord; // Just passing this variable to the fragment shader
}