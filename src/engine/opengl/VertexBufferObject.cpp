#include "VertexBufferObject.hpp"

namespace OpenDK {

	const GLint VertexBufferObject::DEFAULT_CHUNK_SIZE = 3;

	VertexBufferObject::VertexBufferObject()
	: BufferObject(), chunkSize(DEFAULT_CHUNK_SIZE)
	{
		// Nothing
	}

	VertexBufferObject::VertexBufferObject(GLfloat data[], GLsizeiptr size)
	: BufferObject(data, size), chunkSize(DEFAULT_CHUNK_SIZE)
	{
		// Nothing
	}

	VertexBufferObject::VertexBufferObject(GLfloat data[], GLsizeiptr size, GLint chunkSize)
	: BufferObject(data, size), chunkSize(chunkSize)
	{
		// Nothing
	}

	void VertexBufferObject::setChunkSize(GLint chunkSize)
	{
		this->chunkSize = (chunkSize > 0) ? chunkSize : DEFAULT_CHUNK_SIZE;
	}

	GLint VertexBufferObject::getChunkSize() const
	{
		return chunkSize;
	}

}
