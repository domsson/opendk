#include "VertexBufferObject.hpp"

namespace OpenDK {

	const GLint VertexBufferObject::DEFAULT_CHUNK_SIZE = 3;
	const GLint VertexBufferObject::COLOR_CHUNK_SIZE = 2;

	VertexBufferObject::VertexBufferObject()
	: BufferObject(), chunkSize(DEFAULT_CHUNK_SIZE)
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
