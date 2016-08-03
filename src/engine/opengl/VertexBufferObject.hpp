#pragma once

#include "BufferObject.hpp"

namespace OpenDK {

	class VertexBufferObject: public BufferObject
	{
	public:

		/**
		 * The default number of components per vertex attribute.
		 */
		static const GLint DEFAULT_CHUNK_SIZE;

		/**
		 * Creates a VertexBufferObject with default chunk size
		 * but without its data being set yet. This means you will have 
		 * to call setData() on it before you can use it with OpenGL.
		 */
		VertexBufferObject();

		/**
		 * Creates a VertexBufferObject from float data
		 * and with default chunk size.
		 * @param data An array of type GLfloat
		 */
		VertexBufferObject(GLfloat data[], GLsizeiptr size);

		/**
		 * Creates a VertexBufferObject from float data
		 * and with the given chunk size.
		 * @param data An array of type GLfloat
		 * @param size The number of elements in data
		 * @param chunkSize The number of components per vertex attribute
		 */
		VertexBufferObject(GLfloat data[], GLsizeiptr size, GLint chunkSize);

		/**
		 * Set the chunk size for this VertexBufferObject.
		 * @param chunkSize The number of components per vertex attribute
		 */
		void setChunkSize(GLint chunkSize);

		/**
		 * Get the chunk size for this VertexBufferObject.
		 * @return The number of components per vertex attribute
		 */
		GLint getChunkSize() const;

	private:
		
		/**
		 * The number of components per vertex attribute,
		 * which is three for most cases: xyz, rgb, uvw, ...
		 */
		GLint chunkSize;
	};

}
