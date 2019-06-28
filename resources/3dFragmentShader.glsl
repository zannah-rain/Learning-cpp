#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoord; // The texture coordinate

uniform sampler2D ourTexture; // To pass in the actual texture data, not just the coords

void main()
{
	FragColor = texture(ourTexture, TexCoord) * vertexColor;
}