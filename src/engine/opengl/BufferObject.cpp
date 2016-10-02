#include "BufferObject.hpp"

namespace OpenDK
{

	const GLenum BufferObject::DEFAULT_BUFFER_TYPE = GL_ARRAY_BUFFER;
	const GLenum BufferObject::DEFAULT_DRAW_TYPE = GL_STATIC_DRAW;
	const GLenum BufferObject::DEFAULT_DATA_TYPE = GL_FLOAT;

	BufferObject::BufferObject()
	: id(0), size(0), dataType(DEFAULT_DATA_TYPE), bufferType(DEFAULT_BUFFER_TYPE), drawType(DEFAULT_DRAW_TYPE)
	{
	}

	BufferObject::BufferObject(GLenum bufferType)
	: id(0), size(0), dataType(DEFAULT_DATA_TYPE), bufferType(bufferType), drawType(DEFAULT_DRAW_TYPE)
	{
	}

	BufferObject::BufferObject(GLenum bufferType, GLenum drawType)
	: id(0), size(0), dataType(DEFAULT_DATA_TYPE), bufferType(bufferType), drawType(drawType)
	{
	}

	void BufferObject::setBufferType(GLenum bufferType)
	{
		if (id != 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't set buffer type, BufferObject is already initialized" << std::endl;
			return;
		}
		this->bufferType = bufferType;
	}

	void BufferObject::setDrawType(GLenum drawType)
	{
		if (id != 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't set draw type, BufferObject is already initialized" << std::endl;
			return;
		}
		this->drawType = drawType;
	}

	void BufferObject::setData(GLbyte data[], GLsizeiptr size)
	{
		setData(data, size, GL_BYTE);
	}

	void BufferObject::setData(GLubyte data[], GLsizeiptr size)
	{
		setData(data, size, GL_UNSIGNED_BYTE);
	}

	void BufferObject::setData(GLshort data[], GLsizeiptr size)
	{
		setData(data, size, GL_SHORT);
	}

	void BufferObject::setData(GLushort data[], GLsizeiptr size)
	{
		setData(data, size, GL_UNSIGNED_SHORT);
	}

	void BufferObject::setData(GLint data[], GLsizeiptr size)
	{
		setData(data, size, GL_INT);
	}

	void BufferObject::setData(GLuint data[], GLsizeiptr size)
	{
		setData(data, size, GL_UNSIGNED_INT);
	}

	void BufferObject::setData(GLfloat data[], GLsizeiptr size)
	{
		setData(data, size, GL_FLOAT);
	}

	void BufferObject::setData(GLdouble data[], GLsizeiptr size)
	{
		setData(data, size, GL_DOUBLE);
	}

	void BufferObject::setData(GLvoid* data, GLsizeiptr size, GLenum type)
	{
		if (id != 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't set data, BufferObject is already initialized" << std::endl;
			return;
		}
		this->size = size;
		dataType = type;
		init(data);
	}

	GLuint BufferObject::getId() const
	{
		return id;
	}

	GLsizeiptr BufferObject::getSize() const
	{
		return size;
	}

	GLenum BufferObject::getDataType() const
	{
		return dataType;
	}

	GLenum BufferObject::getBufferType() const
	{
		return bufferType;
	}

	GLenum BufferObject::getDrawType() const
	{
		return drawType;
	}

	void BufferObject::bind() const
	{
		glBindBuffer(bufferType, id);
	}

	void BufferObject::unbind() const
	{
		glBindBuffer(bufferType, 0);
	}

	void BufferObject::free()
	{
		glDeleteBuffers(1, &id);
	}

	void BufferObject::generateId()
	{
		if (id == 0)
		{
			glGenBuffers(1, &id);
		}
	}

	void BufferObject::init(GLvoid* data) {
		generateId();
		bind();
		glBufferData(bufferType, size, data, drawType);
		unbind();
	}

	bool BufferObject::operator==(const BufferObject& other) const {
		return id == other.id;
	}

}
