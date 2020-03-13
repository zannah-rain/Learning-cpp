#version 330 core
layout (location = 0) in vec3 aPos; // The position variable has attribute position 0
layout (location = 1) in vec4 aColor; // The color variable has attribute position 1

out vec4 vertexColor; // Specify a color output to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec4 3d_Position;

void main()
{
	3d_Position = projection * view * model * vec4(aPos, 1.0); // Transformations have to be in opposite order!
	gl_Position = vec4(3d_Position.x, 3d_Position.y-0.1, 0.0, 1.0); // Strip the Z component to make all UI elements draw on top of everything else
	vertexColor = aColor; // Just set the output color to dark red
}