R"(
#version 330 core
layout (location = 0) in vec3 aPos; // The position variable has attribute position 0

out vec4 vertexColor; // Specify a color output to the fragment shader

void main()
{
	gl_Position = vec4(aPos, 1.0); // Append 1 to aPos
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // Just set the output color to dark red
}
)"