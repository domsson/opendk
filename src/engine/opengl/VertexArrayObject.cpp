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
		unbind();
		vbo.unbind();
	}

	VertexBufferObject* VertexArrayObject::getVBO(ShaderAttribute shaderAttribute)
	{
		try
		{
			return &vbos.at(shaderAttribute);
		}
		catch (std::out_of_range)
		{
			return nullptr;
		}
	}

	void VertexArrayObject::setIBO(IndexBufferObject ibo)
	{
		this->ibo = ibo;
		bind();
		ibo.bind();
		unbind();
		ibo.unbind();
	}

	IndexBufferObject* VertexArrayObject::getIBO()
	{
		if (ibo.getId() == 0)
		{
			return nullptr;
		}
		else
		{
			return &ibo;
		}
	}

	bool VertexArrayObject::hasIBO() const
	{
		return (ibo.getId() != 0);
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
