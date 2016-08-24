#include "Shader.hpp"

namespace OpenDK
{

	const GLenum Shader::DEFAULT_SHADER_TYPE = GL_VERTEX_SHADER;

	Shader::Shader()
	: id(0), shaderType(DEFAULT_SHADER_TYPE), compileStatus(GL_FALSE)
	{
	}

	Shader::Shader(const GLchar* filePath, GLenum shaderType)
	: id(0), shaderType(shaderType), compileStatus(GL_FALSE)
	{
		create(filePath, shaderType);
	}

	bool Shader::create(const GLchar* filePath, GLenum shaderType)
	{
		this->shaderType = shaderType;
		return init(filePath) && compile();
	}

	bool Shader::init(const GLchar* filePath)
	{
		std::string fileContents;
		std::ifstream file;
		std::stringstream fileStream;
		const GLchar* shaderSource;

		file.open(filePath);
		if (!file.is_open())
		{
			std::cerr << typeid(this).name() << ": [ERR] Failed to open Shader file " << filePath << std::endl;
			return false;
		}

		fileStream << file.rdbuf();
		file.close();
		fileContents = fileStream.str();
		shaderSource = fileContents.c_str();

		generateId();
		glShaderSource(id, 1, &shaderSource, 0);
		return true;
	}

	bool Shader::compile()
	{
		glCompileShader(id);
		glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus != GL_TRUE)
		{
			GLint logLength;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

			GLchar infoLog[logLength];
			glGetShaderInfoLog(id, logLength, 0, infoLog);
			std::cerr << typeid(this).name() << ": [ERR] Shader compilation failed. Log:" << std::endl;
			std::cerr << infoLog << std::endl;
			return false;
		}
		return true;
	}

	bool Shader::created() const
	{
		return (id != 0 && compileStatus == GL_TRUE);
	}

	void Shader::free() const
	{
		glDeleteShader(id);
	}

	GLenum Shader::getShaderType() const
	{
		return shaderType;
	}

	GLuint Shader::getId() const
	{
		return id;
	}

	void Shader::generateId()
	{
		if (id == 0)
		{
			id = glCreateShader(shaderType);
		}
	}

}
