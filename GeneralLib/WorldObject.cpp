#include "WorldObject.h"

#include "Model.h"


WorldObject::WorldObject(glm::vec3 position, glm::quat rotation, Model * model) :
	mPosition(position),
	mRotation(rotation),
	mpModel(model),
	mSpeed(glm::vec3(0.0f, 0.0f, 0.0f)),
	mAngularVelocity(glm::vec3(0.0f, 0.0f, 0.0f))
{

}


WorldObject::WorldObject(glm::vec3 position, Model * model) :
	mPosition(position),
	mRotation(glm::quat(0.0f, 0.0f, 0.0f, 1.0f)),
	mpModel(model),
	mSpeed(glm::vec3(0.0f, 0.0f, 0.0f)),
	mAngularVelocity(glm::vec3(0.0f, 0.0f, 0.0f))
{

}


glm::mat4 WorldObject::getModelMatrix() const
{
	glm::mat4 modelMatrix, translationMatrix;
	translationMatrix = glm::translate(glm::mat4(1.0f), mPosition);
	modelMatrix = translationMatrix * glm::toMat4(mRotation); // Move it to the game world!

	return modelMatrix;
}


void WorldObject::step(float deltaTime)
{
	mPosition += mSpeed * deltaTime;
	mRotation *= glm::quat(mAngularVelocity * deltaTime);
}