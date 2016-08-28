#include "Light.hpp"

namespace OpenDK
{

	Light::Light()
	: Entity(),
	  color(glm::vec3(1.0f, 1.0f, 1.0f)),
	  radius(7.0f),
	  intensity(1.0f)
	{
		// Nothing
	}

	float Light::getRadius() const
	{
		return radius;
	}

	void Light::setRadius(float radius)
	{
		this->radius = radius;
	}

	const glm::vec3& Light::getColor() const
	{
		return color;
	}

	void Light::setColor(const glm::vec3& color)
	{
		this->color.x = color.x;
		this->color.y = color.y;
		this->color.z = color.z;
	}

	float Light::getIntensity() const
	{
		return intensity;
	}

	void Light::setIntensity(float intensity)
	{
		this->intensity = intensity;
	}

}
