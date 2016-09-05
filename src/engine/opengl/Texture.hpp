#pragma once

#include <iostream>
#include <typeinfo>

#include <GL/glew.h>

#include <SFML/Graphics.hpp>

namespace OpenDK
{

	class Texture
	{
	public:

		/**
		 * Create an empty Texture. You need to call load()
		 * before anything useful can be done with it.
		 */
		Texture();

		/**
		 * Load an image file into this Texture. This will initialize
		 * this Texture and upload its data to OpenGL / the GPU.
		 * @param filePath file path to the image that is to be loaded
		 * @param hasAlpha if true, the texture will have an alpha channel
		 */
		bool load(const std::string& filePath, bool hasAlpha = true);

		/**
		 * Load an image file into this Texture. This will initialize
		 * this Texture and upload its data to OpenGL / the GPU.
		 * The texture will be initialized as array texture, which is
		 * suitable for a texture atlas (sprite sheet).
		 * @param filePath file path to the image that is to be loaded
		 * @param spriteWidth width of the individual sprites within the atlas
		 * @param spriteHeight height of the individual sprites within the atlas
		 * @param hasAlpha if true, the texture will have an alpha channel
		 */
		bool loadAtlas(const std::string& filePath, int spriteWidth, int spriteHeight, bool hasAlpha = true);

		/**
		 * @return the width of the image in pixels
		 */
		unsigned int getWidth() const;

		/**
		 * @return the height of the image in pixels
		 */
		unsigned int getHeight() const;

		/**
		 * @return true if the image has an alpha channel, false otherwise
		 */
		bool hasAlpha() const;

		/**
		 * @return true if the image is an array texture (sprite sheet), false otherwise
		 */
		bool isAtlas() const;

		/**
		 * Bind this Texture in the OpenGL state machine
		 * so it can be used, for example for rendering.
		 */
		void bind() const;

		/**
		 * Unbind all textures from the OpenGL state machine
		 * in order to prevent unintentional use / modification.
		 */
		void unbind() const;

		/**
		 * Delete this texture from OpenGL / the GPU.
		 */
		void free() const;

	private:

		// This texture's OpenGL name/id (0 if not yet assigned)
		GLuint id;

		unsigned int width;
		unsigned int height;
		bool alpha;

		bool atlas;
		unsigned int spriteWidth;
		unsigned int spriteHeight;

		void generateId();
	};

}
