#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include <GL/glew.h>

namespace OpenDK
{
	
	class Shader
	{
	public:

		static const GLenum DEFAULT_SHADER_TYPE;

		Shader();
		Shader(const GLchar* filePath, GLenum shaderType);

		bool create(const GLchar* filePath, GLenum shaderType);
		bool created() const;

		GLuint getId() const;
		GLenum getShaderType() const;

		void free() const;

	private:

		GLuint id;
		GLenum shaderType;
		GLint compileStatus;

		bool init(const GLchar* filePath);
		bool compile();

		void generateId();
	};

}
