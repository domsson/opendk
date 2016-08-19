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
		 */
		bool load(const std::string& filePath, bool hasAlpha = true);

		bool loadAtlas(const std::string& filePath, int spriteWidth, int spriteHeight, bool hasAlpha = true);

		unsigned int getWidth() const;

		unsigned int getHeight() const;

		bool hasAlpha() const;

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
