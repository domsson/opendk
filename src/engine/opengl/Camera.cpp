#include "Camera.hpp"

namespace OpenDK
{

	Camera::Camera()
	: position(glm::vec3(0.0f, 0.0f, -3.0f)),
	  rotation(glm::vec3(45.0f, 35.265f, 0.0f)),
	  zoom(1.0f)
	{
		initViewMatrix();
		initProjectionMatrix();
	}

	const glm::vec3& Camera::getPosition() const
	{
		return position;
	}

	void Camera::setPosition(float x, float y, float z)
	{
		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
	}

	void Camera::setPosition(const glm::vec3& position)
	{
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}

	const glm::vec3& Camera::getRotation() const
	{
		return rotation;
	}

	void Camera::setRotation(float x, float y, float z)
	{
		this->rotation.x = x;
		this->rotation.y = y;
		this->rotation.z = z;
	}

	void Camera::setRotation(const glm::vec3& rotation)
	{
		this->rotation.x = rotation.x;
		this->rotation.y = rotation.y;
		this->rotation.z = rotation.z;
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
		// TODO - figure out if we can avoid re-creating the matrix over and over
		viewMatrix = glm::mat4();
		viewMatrix = glm::translate(viewMatrix, position);
		viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

		//viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		//viewMatrix = glm::rotate(viewMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//viewMatrix = glm::rotate(viewMatrix, glm::radians(35.264f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera::updateProjectionMatrix()
	{
		// LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR
		//projectionMatrix = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		//projectionMatrix = glm::ortho(-4.0f * zoom, 4.0f * zoom, -3.0f * zoom, 3.0f * zoom, -100.0f, 100.0f);
		projectionMatrix = glm::ortho(-3.2f * zoom, 3.2f * zoom, -2.0f * zoom, 2.0f * zoom, -100.0f, 100.0f);
		// glOrtho( -width/2*zoom, width/2*zoom, -height/2*zoom, height/2*zoom, -1, 1 );
	}

}
