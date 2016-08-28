#include "Entity.hpp"

namespace OpenDK
{

	Entity::Entity()
	: position(glm::vec3(0.0f, 0.0f, 0.0f)),
	  rotation(glm::vec3(0.0f, 0.0f, 0.0f))
	{
		// Nothing
	}

	const glm::vec3& Entity::getPosition() const
	{
		return position;
	}

	void Entity::setPosition(float x, float y, float z)
	{
		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
	}

	void Entity::setPosition(const glm::vec3& position)
	{
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}

	const glm::vec3& Entity::getRotation() const
	{
		return rotation;
	}

	void Entity::setRotation(float x, float y, float z)
	{
		this->rotation.x = x;
		this->rotation.y = y;
		this->rotation.z = z;
	}

	void Entity::setRotation(const glm::vec3& rotation)
	{
		this->rotation.x = rotation.x;
		this->rotation.y = rotation.y;
		this->rotation.z = rotation.z;
	}

}
