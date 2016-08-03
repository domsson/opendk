#include "VertexArrayObject.hpp"

namespace OpenDK
{

	VertexArrayObject::VertexArrayObject()
	: id(0)
	{
		generateId();
	}

	void VertexArrayObject::addVBO(VertexBufferObject vbo, ShaderAttribute shaderAttribute)
	{
		// TODO
	}

	VertexBufferObject VertexArrayObject::getVBO(ShaderAttribute shaderAttribute)
	{
		// TODO
		VertexBufferObject vbo;
		return vbo;
	}

	GLuint VertexArrayObject::getId()
	{
		return id;
	}

	void VertexArrayObject::bind()
	{
		glBindVertexArray(id);
	}

	void VertexArrayObject::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArrayObject::free()
	{
		glDeleteVertexArrays(1, &id);
	}

	void VertexArrayObject::generateId()
	{
		if (id == 0)
		{
			glGenVertexArrays(1, &id);
		}
	}

}
