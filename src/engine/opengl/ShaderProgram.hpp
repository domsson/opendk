#pragma once

#include <map>
#include <string>

#include <GL/glew.h>

#include "Shader.hpp"
#include "ShaderAttribute.hpp"

namespace OpenDK
{

	class ShaderProgram
	{
	public:

		ShaderProgram();

		void addShader(const GLchar* file, GLenum shaderType);

		void bindAttribute(ShaderAttribute location, const GLchar* attrName);
		GLint getUniformLocation(const std::string& name);

		GLuint getId() const;

		bool link();
		bool link(bool deleteShaders);
		void use();

	private:

		GLuint id;
		GLint linkStatus;
		std::map <GLenum, Shader> shaders;
		std::map <std::string, GLint> uniforms;

		GLint fetchUniformLocation(const std::string& name);

		void freeShaders() const;

		void generateId();

	};

}
