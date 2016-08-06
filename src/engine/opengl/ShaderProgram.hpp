#pragma once

#include <string>

#include <GL/glew.h>

namespace OpenDK
{

	class ShaderProgram
	{
	public:
		
		ShaderProgram();
		
		void setVertexShader(const GLchar* file);
		void setFragmentShader(const GLchar* file);

		GLuint getId() const;

		void build();
		void use();

	private:

		GLuint id;

	};

}
