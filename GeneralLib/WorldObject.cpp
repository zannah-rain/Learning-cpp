#include "WorldObject.h"

#include "Model.h"


C_WorldObject::C_WorldObject(glm::vec3 position, glm::quat rotation, C_Model * model) :
	m_Position(position),
	m_Rotation(rotation),
	mp_Model(model),
	m_Speed(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_AngularVelocity(glm::vec3(0.0f, 0.0f, 0.0f))
{

}


C_WorldObject::C_WorldObject(glm::vec3 position, C_Model * model) :
	m_Position(position),
	m_Rotation(glm::quat(0.0f, 0.0f, 0.0f, 1.0f)),
	mp_Model(model),
	m_Speed(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_AngularVelocity(glm::vec3(0.0f, 0.0f, 0.0f))
{

}


glm::mat4 C_WorldObject::getModelMatrix() const
{
	glm::mat4 modelMatrix, translationMatrix;
	translationMatrix = glm::translate(glm::mat4(1.0f), m_Position);
	modelMatrix = translationMatrix * glm::toMat4(m_Rotation); // Move it to the game world!

	return modelMatrix;
}


void C_WorldObject::step(float deltaTime)
{
	m_Position += m_Speed * deltaTime;
	m_Rotation *= glm::quat(m_AngularVelocity * deltaTime);
}