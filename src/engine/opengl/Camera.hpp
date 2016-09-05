#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../Entity.hpp"

namespace OpenDK
{

	class Camera: public Entity
	{
	public:

		Camera();

		const glm::mat4& getViewMatrix() const;

		const float* getViewMatrixPtr() const;

		const glm::mat4& getProjectionMatrix() const;

		const float* getProjectionMatrixPtr() const;

		void setZoom(float zoom);

		float getZoom() const;

		void update();

	private:

		float zoom;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

		void initViewMatrix();

		void initProjectionMatrix();

		void updateViewMatrix();

		void updateProjectionMatrix();

	};

}
