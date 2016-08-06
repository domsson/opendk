#pragma once

#include <map>
#include <string>

#include <GL/glew.h>

#include "Shader.hpp"

namespace OpenDK
{

	class ShaderProgram
	{
	public:
		
		ShaderProgram();
		
		void addShader(const GLchar* file, GLenum shaderType);
		//void setVertexShader(const GLchar* file);
		//void setFragmentShader(const GLchar* file);

		GLuint getId() const;

		bool link();
		bool link(bool deleteShaders);
		void use();

	private:

		GLuint id;
		GLint linkStatus;
		std::map <GLenum, Shader> shaders;

		void freeShaders() const;

		void generateId();

	};

}
