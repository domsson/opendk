#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "Shader.hpp"
#include "ShaderProgram.hpp"
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
		VertexBufferObject *vbo;
		GLuint shaderProgram;
	};

}
