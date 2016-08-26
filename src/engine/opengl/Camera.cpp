#include "Camera.hpp"

namespace OpenDK
{

	Camera::Camera()
	: position(glm::vec3(0.0f, 0.0f, 0.0f)),
	  //rotation(glm::vec3(45.0f, 35.265f, 0.0f)),
	  rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
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
		// Way nicer than what we had before!
		// Now we just need to get the translation
		// to take the camera's rotation into account

		glm::mat4 transToOrigin = glm::translate(glm::mat4(), position * -1.0f);
		glm::mat4 rotAroundX = glm::rotate(glm::mat4(), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotAroundY = glm::rotate(glm::mat4(), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

		viewMatrix = rotAroundX * rotAroundY * transToOrigin;
	}

	void Camera::updateProjectionMatrix()
	{

		//projectionMatrix = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		// https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
		// LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR
		projectionMatrix = glm::ortho(-3.2f * zoom, 3.2f * zoom, -2.0f * zoom, 2.0f * zoom, -100.0f, 100.0f);

		glm::mat4 planeSwapMatrix;

		// http://gamedev.stackexchange.com/questions/128946/should-i-use-the-x-y-plane-when-using-an-orthographic-projection-in-opengl/128953#128953
		//
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

		// This will make our map, which lies in the X-Z plane,
		// be in the X-Y plane, which is a lot easier to deal with.
		// For example, an unrotated, default cam, looking to -Z
		// will actually look 'on top' of the map.

		projectionMatrix = projectionMatrix * planeSwapMatrix;



	}

}
