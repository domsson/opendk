#include "ShaderProgram.hpp"

namespace OpenDK
{

	ShaderProgram::ShaderProgram()
	: id(0)
	{
		// Nothing?
	}

	void ShaderProgram::setVertexShader(const GLchar* file)
	{
	}

	void ShaderProgram::setFragmentShader(const GLchar* file)
	{
	}

	GLuint ShaderProgram::getId() const
	{
		return id;
	}

	void ShaderProgram::build()
	{
	}
	
	void ShaderProgram::use()
	{
	}

}
