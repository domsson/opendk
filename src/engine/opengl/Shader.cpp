#include "Shader.hpp"

namespace OpenDK
{

	const GLenum Shader::DEFAULT_SHADER_TYPE = GL_VERTEX_SHADER;

	Shader::Shader()
	: shaderType(DEFAULT_SHADER_TYPE) //, source(nullptr)
	{
	}

	Shader::Shader(const GLchar* filePath, GLenum shaderType)
	: shaderType(shaderType) //, source(nullptr)
	{
		create(filePath, shaderType);
	}

	bool Shader::create(const GLchar* filePath, GLenum shaderType)
	{
		this->shaderType = shaderType;
	
		/*
		if (!load(filePath))
		{
			std::cerr << typeid(this).name() << ": Failed to open Shader file " << filePath << std::endl;
			return false;
		}		
		if (!init())
		{
			std::cerr << typeid(this).name() << ": Shader compilation failed." << std::endl;
			return false;
		}
		return true;
		*/

		// LOAD

		std::ifstream shaderFile(filePath);
		if (!shaderFile.is_open())
		{
			std::cerr << typeid(this).name() << ": Failed to open Shader file " << filePath << std::endl;
			return false;
		}
		// read the file's buffer contents into a string stream		
		std::stringstream fileStream;
		fileStream << shaderFile.rdbuf();
		// close the file handle
		shaderFile.close();
		// place the string contents into our source code variable
		std::string fileContents = fileStream.str();
		const GLchar* source = fileContents.c_str();
		//const GLchar* source = fileStream.str().c_str();

		// INIT
		generateId();
		std::cout << "Shader source: " << source << std::endl;
		glShaderSource(id, 1, &source, 0);

		GLchar infoLog[512];
		glCompileShader(id);
		glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus != GL_TRUE)
		{
			glGetShaderInfoLog(id, 512, 0, infoLog);
			std::cerr << typeid(this).name() << ": Shader compilation failed.\n" << infoLog << std::endl;
			return false;
		}
		
		return true;
	}

	/*
	bool Shader::load(const GLchar* filePath)
	{
		// open the file
		std::ifstream shaderFile(filePath);
		if (!shaderFile.is_open())
		{
			return false;
		}
		// read the file's buffer contents into a string stream		
		std::stringstream fileStream;
		fileStream << shaderFile.rdbuf();
		// close the file handle
		shaderFile.close();
		// place the string contents into our source code variable
		strcpy(source, fileStream.str().c_str());
		//source = fileStream.str().c_str();
		return true;
	}

	bool Shader::init()
	{
		generateId();
		std::cout << "Shader source: " << source << std::endl;
		glShaderSource(id, 1, &source, 0);

		glCompileShader(id);
		glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus == GL_TRUE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	*/

	bool Shader::created() const
	{
		if (id == 0 || compileStatus == GL_FALSE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void Shader::free()
	{
		glDeleteShader(id);
		id = 0;
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
