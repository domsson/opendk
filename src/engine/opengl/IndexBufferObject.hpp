#pragma once

#include "BufferObject.hpp"

namespace OpenDK {

	class IndexBufferObject: public BufferObject
	{
	public:

		/**
		 * Creates a IndexBufferObject without its data being set yet.
		 * This means you will have to call setData() on it before using it.
		 */
		IndexBufferObject();

		/**
		 * Creates a IndexBufferObject from int data.
		 * @param data An array of type GLuint
		 * @param size The size of data in bytes
		 */
		IndexBufferObject(GLuint data[], GLsizeiptr size);


	private:
		
		// Nothing
	};

}
