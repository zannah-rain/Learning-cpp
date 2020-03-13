#pragma once

#include "glm/glm.hpp"

#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"

class C_SpriteRenderer
{
public:
	C_SpriteRenderer(C_Shader &shader);
	~C_SpriteRenderer();

	void DrawSprite(C_Texture2D &texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));
private:
	C_Shader* m_Shader;
	GLuint quadVAO;

	void initRenderData();
};