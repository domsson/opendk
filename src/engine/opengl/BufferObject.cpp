#include "BufferObject.hpp"

namespace OpenDK
{

	const GLenum BufferObject::DEFAULT_BUFFER_TYPE = GL_ARRAY_BUFFER;
	const GLenum BufferObject::DEFAULT_DRAW_TYPE = GL_STATIC_DRAW;

	BufferObject::BufferObject()
	: id(0), size(0), bufferType(DEFAULT_BUFFER_TYPE), drawType(DEFAULT_DRAW_TYPE)
	{
	}

	BufferObject::BufferObject(GLenum bufferType)
	: id(0), size(0), bufferType(bufferType), drawType(DEFAULT_DRAW_TYPE)
	{
	}

	BufferObject::BufferObject(GLenum bufferType, GLenum drawType)
	: id(0), size(0), bufferType(bufferType), drawType(drawType)
	{
	}

	BufferObject::BufferObject(GLuint data[], GLsizeiptr size)
	: id(0), size(size), bufferType(GL_ELEMENT_ARRAY_BUFFER), drawType(GL_STATIC_DRAW)
	{
		initBuffer(data);
	}

	BufferObject::BufferObject(GLfloat data[], GLsizeiptr size)
	: id(0), size(size), bufferType(GL_ARRAY_BUFFER), drawType(GL_STATIC_DRAW)
	{
		initBuffer(data);
	}

	void BufferObject::setBufferType(GLuint bufferType)
	{
		if (id != 0)
		{
			std::cerr << typeid(this).name() << ": Can't set buffer type, BufferObject is already initialized" << std::endl;
			return;
		}
		this->bufferType = bufferType;
	}

	void BufferObject::setDrawType(GLuint drawType)
	{
		if (id != 0)
		{
			std::cerr << typeid(this).name() << ": Can't set draw type, BufferObject is already initialized" << std::endl;
			return;
		}
		this->drawType = drawType;
	}

	void BufferObject::setData(GLfloat data[], GLsizeiptr size)
	{
		if (id != 0)
		{
			std::cerr << typeid(this).name() << ": Can't set data, BufferObject is already initialized" << std::endl;
			return;
		}
		this->size = size;
		initBuffer(data);
	}

	void BufferObject::setData(GLuint data[], GLsizeiptr size)
	{
		if (id != 0)
		{
			std::cerr << typeid(this).name() << ": Can't set data, BufferObject is already initialized" << std::endl;
			return;
		}
		this->size = size;
		initBuffer(data);
	}

	GLuint BufferObject::getId()
	{
		return id;
	}

	GLsizeiptr BufferObject::getSize()
	{
		return size;
	}

	GLenum BufferObject::getBufferType()
	{
		return bufferType;
	}

	GLenum BufferObject::getDrawType()
	{
		return drawType;
	}

	void BufferObject::bind()
	{
		glBindBuffer(bufferType, id);
	}

	void BufferObject::unbind()
	{
		glBindBuffer(bufferType, 0);
	}

	void BufferObject::free()
	{
		glDeleteBuffers(1, &id);
	}

	void BufferObject::generateId()
	{
		glGenBuffers(1, &id);
	}

	void BufferObject::initBuffer(GLuint data[]) {
		generateId();
		bind();
		glBufferData(bufferType, size, data, drawType);
		unbind();
	}

	void BufferObject::initBuffer(GLfloat data[]) {
		generateId();
		bind();
		glBufferData(bufferType, size, data, drawType);
		unbind();
	}

}
