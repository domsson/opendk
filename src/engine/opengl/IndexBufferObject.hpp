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

	private:

		// Nothing
	};

}
