#include "Texture.hpp"

namespace OpenDK
{

	Texture::Texture()
	: id(0), width(0), height(0), alpha(false),
	  atlas(false), spriteWidth(0), spriteHeight(0)
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

		width  = image.getSize().x;
		height = image.getSize().y;
		alpha  = hasAlpha;

		generateId();
		bind();
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			alpha ? GL_RGBA : GL_RGB,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_INT_8_8_8_8_REV,
			image.getPixelsPtr()
		);
		glGenerateMipmap(GL_TEXTURE_2D);
		unbind();

		return true;
	}

	bool Texture::loadAtlas(const std::string& filePath, int spriteWidth, int spriteHeight, bool hasAlpha)
	{
		sf::Image image;
		if (!image.loadFromFile(filePath))
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not load texture file " << filePath << std::endl;
			return false;
		}

		if (width % spriteWidth != 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not load texture atlas " << filePath
					<< " because given sprite width is not a multiple of the texture width" << std::endl;
			return false;
		}

		if (height % spriteHeight != 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not load texture atlas " << filePath
					<< " because given sprite height is not a multiple of the texture height" << std::endl;
			return false;
		}

		width  = image.getSize().x;
		height = image.getSize().y;
		alpha  = hasAlpha;
		atlas  = true;

		generateId();
		bind();

		glTexImage3D(
			GL_TEXTURE_2D_ARRAY,
			0,
			alpha ? GL_RGBA : GL_RGB,
			spriteWidth,
			spriteHeight,
			(width / spriteWidth) * (height / spriteHeight),
			0,
			GL_RGBA,
			GL_UNSIGNED_INT_8_8_8_8_REV,
			NULL
		);

		if (glGetError() != GL_NO_ERROR)
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not load texture atlas " << filePath
					<< ", ran into OpenGL error" << std::endl;
			return false;
		}

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glPixelStorei(GL_UNPACK_ROW_LENGTH, width);

		int cols = (int) (width / spriteWidth);
		int rows = (int) (height / spriteHeight);

		for (int y = 0; y < rows; ++y)
		{
			for (int x = 0; x < cols; ++x)
			{
				/*
					GLenum target,
					GLint level,
					GLint xoffset,
					GLint yoffset,
					GLint zoffset,
					GLsizei width,
					GLsizei height,
					GLsizei depth,
					GLenum format,
					GLenum type,
					const GLvoid * pixels
				 */
				glTexSubImage3D(
					GL_TEXTURE_2D_ARRAY,
					0,
					0,
					0,
					y * cols + x,
					spriteWidth,
					spriteHeight,
					1,
					alpha ? GL_RGBA : GL_RGB,
					GL_UNSIGNED_INT_8_8_8_8_REV,
					image.getPixelsPtr() + (y * spriteHeight * width + x * spriteWidth) * 4
				);
			}
		}

		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

		if (glGetError() != GL_NO_ERROR)
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not load texture atlas " << filePath
					<< ", ran into OpenGL error" << std::endl;
			return false;
		}

		unbind();

		return true;
	}

	unsigned int Texture::getWidth() const
	{
		return width;
	}

	unsigned int Texture::getHeight() const
	{
		return height;
	}

	bool Texture::hasAlpha() const
	{
		return alpha;
	}

	bool Texture::isAtlas() const
	{
		return atlas;
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
			glBindTexture((atlas ? GL_TEXTURE_2D_ARRAY : GL_TEXTURE_2D), id);
		}
	}

	void Texture::unbind() const
	{
		glBindTexture((atlas ? GL_TEXTURE_2D_ARRAY : GL_TEXTURE_2D), 0);
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
