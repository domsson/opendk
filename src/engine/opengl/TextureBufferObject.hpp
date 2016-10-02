#pragma once

#include "BufferObject.hpp"

namespace OpenDK
{

	class TextureBufferObject: public BufferObject
	{
	public:

		/**
		 * Creates a TextureBufferObject without its data being set yet.
		 * This means you will have to call setData() on it before using it.
		 */
		TextureBufferObject();

		GLenum getInternalFormat() const;

		GLuint getTextureId() const;

		void bindTexture() const;

		void unbindTexture() const;

		void updateData(GLvoid* data) const;

	protected:

		void init(GLvoid* data);

	private:

		GLuint textureId;

	};

}
