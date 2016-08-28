#pragma once

#include <glm/glm.hpp>

#include "../Entity.hpp"

namespace OpenDK
{

	class Light: public Entity
	{
	public:

		Light();

		float getRadius() const;

		void setRadius(float radius);

		const glm::vec3& getColor() const;

		void setColor(const glm::vec3& color);

		float getIntensity() const;

		void setIntensity(float intensity);

	private:

		glm::vec3 color;
		float radius;
		float intensity;

	};

}
