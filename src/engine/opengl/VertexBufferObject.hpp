#pragma once

#include "BufferObject.hpp"

namespace OpenDK {

	class VertexBufferObject: public BufferObject
	{
	public:
		static const GLint DEFAULT_CHUNK_SIZE;

		/**
		 * Creates a Vertex Buffer Object with.
		 * Most relevant are GL_ARRAY_BUFFER for Vertex Buffer Objects
		 * and GL_ELEMENT_ARRAY_BUFFER for Index Buffer Objects.
		 */
		VertexBufferObject();
		VertexBufferObject(GLfloat data[], GLsizeiptr size);
		VertexBufferObject(GLfloat data[], GLsizeiptr size, GLint chunkSize);

		void setChunkSize(GLint chunkSize);
		GLint getChunkSize();

	private:
		GLint chunkSize;
	};

}
