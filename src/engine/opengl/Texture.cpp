#include "Texture.hpp"

namespace OpenDK
{

	Texture::Texture()
	: id(0)
	{
		// Nothing
	}

	/*
		// Load an image file from a file
		sf::Image background;
		if (!background.loadFromFile("background.jpg"))
			return -1;
		// Create a 20x20 image filled with black color
		sf::Image image;
		image.create(20, 20, sf::Color::Black);
		// Copy image1 on image2 at position (10, 10)
		image.copy(background, 10, 10);
		// Make the top-left pixel transparent
		sf::Color color = image.getPixel(0, 0);
		color.a = 0;
		image.setPixel(0, 0, color);
		// Save the image to a file
		if (!image.saveToFile("result.png"))
			return -1;
	*/

	bool Texture::load(const std::string& filePath)
	{
		sf::Image image;
		if (!image.loadFromFile(filePath))
		{
			return false;
		}

		generateId();
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_INT, image.getPixelsPtr());
		glGenerateMipmap(GL_TEXTURE_2D);
		unbind();

		return true;
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::generateId()
	{
		if (id == 0)
		{
			glGenTextures(1, &id);
		}
	}

}
