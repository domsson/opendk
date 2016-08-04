#include "IndexBufferObject.hpp"

namespace OpenDK
{

	IndexBufferObject::IndexBufferObject()
	: BufferObject()
	{
		// Nothing
	}

	IndexBufferObject::IndexBufferObject(GLuint data[], GLsizeiptr size)
	: BufferObject(data, size)
	{
		// Nothing
	}

}
