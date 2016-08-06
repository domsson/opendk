#include "ShaderProgram.hpp"

namespace OpenDK
{
	ShaderProgram::ShaderProgram()
	: id(0)
	{
		generateId();
	}

	void ShaderProgram::addShader(const GLchar* file, GLenum shaderType)
	{
		Shader shader;
		if (shader.create(file, shaderType))
		{
			shaders[shaderType] = shader;
			glAttachShader(id, shader.getId());
		}
	}

	GLuint ShaderProgram::getId() const
	{
		return id;
	}

	bool ShaderProgram::link()
	{
		return link(true);
	}

	bool ShaderProgram::link(bool deleteShaders)
	{
		glLinkProgram(id);

		GLint logLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

		GLchar infoLog[logLength];
		glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);

		if (linkStatus != GL_TRUE)
		{
			std::cerr << typeid(this).name() << ": Failed to link shader program. Log:" << std::endl;
			std::cerr << infoLog << std::endl;
			return false;
		}
		
		if (deleteShaders)
		{
			freeShaders();	 // deletes the individual shaders from opengl
		}
		shaders.clear(); // deletes all shaders from the map

		return true;
	}
	
	void ShaderProgram::freeShaders() const
	{
		for (const auto &shader : shaders)
		{
			shader.second.free();
		}
	}
	
	void ShaderProgram::use()
	{
		glUseProgram(id);
	}

	void ShaderProgram::generateId()
	{
		if (id == 0)
		{
			id = glCreateProgram();
		}
	}

}
