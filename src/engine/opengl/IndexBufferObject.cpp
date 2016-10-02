#include "IndexBufferObject.hpp"

namespace OpenDK
{

	IndexBufferObject::IndexBufferObject()
	: BufferObject()
	{
		setBufferType(GL_ELEMENT_ARRAY_BUFFER);
	}

}
