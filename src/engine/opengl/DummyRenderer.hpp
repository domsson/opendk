#pragma once

#include <cmath>

#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"

namespace OpenDK
{

	class DummyRenderer
	{
	public:

		DummyRenderer();
		~DummyRenderer();

		void initDummyData();
		void render();

	private:
		VertexArrayObject *vao;
		ShaderProgram* sp;
		Texture* tex;

		sf::Clock clock;

		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};

}
