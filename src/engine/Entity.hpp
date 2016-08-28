#pragma once

#include <glm/glm.hpp>

namespace OpenDK
{

	class Entity
	{
	public:

		Entity();

		const glm::vec3& getPosition() const;

		void setPosition(float x, float y, float z);

		void setPosition(const glm::vec3& position);

		const glm::vec3& getRotation() const;

		void setRotation(float x, float y, float z);

		void setRotation(const glm::vec3& rotation);

	protected:

		glm::vec3 position;
		glm::vec3 rotation;

	};

}
