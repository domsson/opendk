#include "ShaderProgram.hpp"

namespace OpenDK
{
	ShaderProgram::ShaderProgram()
	: id(0)
	{
		generateId();
	}

	void ShaderProgram::addShader(const GLchar* file, const GLenum shaderType)
	{
		Shader shader(file, shaderType);
		addShader(shader);
	}

	void ShaderProgram::addShader(const Shader shader)
	{
		if (shader.created())
		{
			shaders[shader.getShaderType()] = shader;
			glAttachShader(id, shader.getId());
		}
	}

	void ShaderProgram::bindAttribute(const ShaderAttribute location, const GLchar* attrName)
	{
		if (id != 0)
		{
			glBindAttribLocation(id, location, attrName);
		}
	}

	GLint ShaderProgram::getUniformLocation(const std::string& name)
	{
		auto iterator = uniforms.find(name);
		if (iterator == uniforms.end())
		{
			GLint location = fetchUniformLocation(name);
			if (location >= 0) // Locations not available in shader will give -1
			{
				uniforms[name] = location;
			}
			return location;
		}
		else
		{
			return iterator->second;
		}
	}

	GLint ShaderProgram::fetchUniformLocation(const std::string& name)
	{
		return glGetUniformLocation(id, name.c_str());
	}

	GLuint ShaderProgram::getId() const
	{
		return id;
	}

	bool ShaderProgram::link(const bool deleteShaders)
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

	void ShaderProgram::free()
	{
		freeShaders();
		shaders.clear();
	}

	void ShaderProgram::generateId()
	{
		if (id == 0)
		{
			id = glCreateProgram();
		}
	}

}
