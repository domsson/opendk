#include "IndexBufferObject.hpp"

namespace OpenDK
{

	IndexBufferObject::IndexBufferObject()
	: BufferObject()
	{
		// setBufferType(GL_ELEMENT_ARRAY_BUFFER);
	}

	IndexBufferObject::IndexBufferObject(GLuint data[], GLsizeiptr size)
	: BufferObject(data, size)
	{
		// Feeding GLuint data to BufferObject automatically makes it an IBO
		// (Meaning that we don't need to call setBufferType() manually)
	}

}
