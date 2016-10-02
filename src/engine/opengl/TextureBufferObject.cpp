#include "TextureBufferObject.hpp"

namespace OpenDK
{

	TextureBufferObject::TextureBufferObject()
	: BufferObject(), textureId(0)
	{
		setBufferType(GL_TEXTURE_BUFFER);
	}

	GLuint TextureBufferObject::getTextureId() const
	{
		return textureId;
	}

	void TextureBufferObject::bindTexture() const
	{
		glBindTexture(GL_TEXTURE_BUFFER, textureId);
	}

	void TextureBufferObject::unbindTexture() const
	{
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

	void TextureBufferObject::updateData(GLvoid* data) const
	{
		bind();
		glBufferSubData(GL_TEXTURE_BUFFER, 0, size, data);
		unbind();
	}

	void TextureBufferObject::init(GLvoid* data)
	{
		std::cout << "WOOOPOOLOO\n";
		generateId();
		bind();
		glBufferData(bufferType, size, data, drawType);

		glGenTextures(1, &textureId);
		bindTexture();
		glTexBuffer(GL_TEXTURE_BUFFER, getInternalFormat(), getId());

		unbind();
		unbindTexture();
	}

	GLenum TextureBufferObject::getInternalFormat() const
	{
		switch (dataType)
		{
			case GL_BYTE:
				return GL_R8I;
			case GL_UNSIGNED_BYTE:
				return GL_R8UI;
			case GL_SHORT:
				return GL_R16I;
			case GL_UNSIGNED_SHORT:
				return GL_R16UI;
			case GL_INT:
				return GL_R32I;
			case GL_UNSIGNED_INT:
				return GL_R32UI;
			case GL_FLOAT:
			case GL_DOUBLE:
			default:
				return GL_R32F;
		}
	}

}
