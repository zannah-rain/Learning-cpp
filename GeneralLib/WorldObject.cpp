#include "WorldObject.h"

#include "Model.h"


WorldObject::WorldObject(glm::vec3 position, glm::quat rotation, Model * model) :
	mPosition(position),
	mRotation(rotation),
	mpModel(model)
{

}


WorldObject::WorldObject(glm::vec3 position, Model * model) :
	mPosition(position),
	mRotation(glm::quat(0.0f, 0.0f, 0.0f, 1.0f)),
	mpModel(model)
{

}


glm::mat4 WorldObject::getModelMatrix() const
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, mPosition); // Move it to the game world!
	modelMatrix = glm::toMat4(mRotation) * modelMatrix; // Apply rotation!

	return modelMatrix;
}