#include "Camera.hpp"

namespace OpenDK
{

	Camera::Camera()
	: Entity()
	{
		initViewMatrix();
		initProjectionMatrix();
	}

	void Camera::setZoom(float zoom)
	{
		this->zoom = (zoom <= 0) ? 0.1f : zoom;
	}

	float Camera::getZoom() const
	{
		return zoom;
	}

	const glm::mat4& Camera::getViewMatrix() const
	{
		return viewMatrix;
	}

	const float* Camera::getViewMatrixPtr() const
	{
		return glm::value_ptr(viewMatrix);
	}

	const glm::mat4& Camera::getProjectionMatrix() const
	{
		return projectionMatrix;
	}

	const float* Camera::getProjectionMatrixPtr() const
	{
		return glm::value_ptr(projectionMatrix);
	}

	void Camera::initViewMatrix()
	{
		updateViewMatrix();
	}

	void Camera::initProjectionMatrix()
	{
		updateProjectionMatrix();
	}

	void Camera::update()
	{
		updateViewMatrix();
		updateProjectionMatrix();
	}

	void Camera::updateViewMatrix()
	{
		glm::mat4 transToOrigin = glm::translate(glm::mat4(), position * -1.0f);
		glm::mat4 rotAroundY = glm::rotate(glm::mat4(), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotAroundX = glm::rotate(glm::mat4(), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotAroundZ = glm::rotate(glm::mat4(), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		viewMatrix = rotAroundZ * rotAroundX * rotAroundY * transToOrigin;
	}

	void Camera::updateProjectionMatrix()
	{
		// https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
		// LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR
		projectionMatrix = glm::ortho(-3.2f * zoom, 3.2f * zoom, -2.0f * zoom, 2.0f * zoom, -100.0f, 100.0f);

		/*
		glm::mat4 planeSwapMatrix;

		//	1  0  0  0
		//	0  0 -1  0
		//	0  1  0  0
		//	0  0  0  1

		planeSwapMatrix[0][0] =  1.0f;
		planeSwapMatrix[0][1] =  0.0f;
		planeSwapMatrix[0][2] =  0.0f;
		planeSwapMatrix[0][3] =  0.0f;

		planeSwapMatrix[1][0] =  0.0f;
		planeSwapMatrix[1][1] =  0.0f;
		planeSwapMatrix[1][2] =  1.0f;
		planeSwapMatrix[1][3] =  0.0f;

		planeSwapMatrix[2][0] =  0.0f;
		planeSwapMatrix[2][1] = -1.0f;
		planeSwapMatrix[2][2] =  0.0f;
		planeSwapMatrix[2][3] =  0.0f;

		planeSwapMatrix[3][0] =  0.0f;
		planeSwapMatrix[3][1] =  0.0f;
		planeSwapMatrix[3][2] =  0.0f;
		planeSwapMatrix[3][3] =  1.0f;

		projectionMatrix = projectionMatrix * planeSwapMatrix;
		*/
	}

}
