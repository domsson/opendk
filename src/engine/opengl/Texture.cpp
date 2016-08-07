#include "Texture.hpp"

namespace OpenDK
{

	Texture::Texture()
	: id(0)
	{
		// Nothing
	}

	bool Texture::load(const std::string& filePath, bool hasAlpha)
	{
		sf::Image image;
		if (!image.loadFromFile(filePath))
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not load texture file " << filePath << std::endl;
			return false;
		}

		generateId();
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, image.getPixelsPtr());
		glGenerateMipmap(GL_TEXTURE_2D);
		unbind();

		return true;
	}

	void Texture::bind() const
	{
		if (id == 0)
		{
			std::cout << typeid(this).name() << ": [WRN] Tried to bind an uninitialized Texture" << std::endl;
			return;
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, id);
		}
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::free() const
	{
		if (id == 0)
		{
			std::cerr << typeid(this).name() << ": [WRN] Tried to free an uninitialized Texture" << std::endl;
			return;
		}
		else
		{
			glDeleteTextures(1, &id);
		}
	}

	void Texture::generateId()
	{
		if (id == 0)
		{
			glGenTextures(1, &id);
		}
	}

}
