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
		vbos[shaderAttribute] = vbo;
		bind();
		vbo.bind();
		glVertexAttribPointer(shaderAttribute, vbo.getChunkSize(), GL_FLOAT, false, 0, 0);
		glEnableVertexAttribArray(shaderAttribute);	// Enable the new VBO
		vbo.unbind();
		unbind();
	}

	VertexBufferObject VertexArrayObject::getVBO(ShaderAttribute shaderAttribute)
	{
		// TODO return by value, reference, pointer? what's best here?
		return vbos[shaderAttribute];
	}

	GLuint VertexArrayObject::getId() const
	{
		return id;
	}

	void VertexArrayObject::bind() const
	{
		glBindVertexArray(id);
	}

	void VertexArrayObject::unbind() const
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
