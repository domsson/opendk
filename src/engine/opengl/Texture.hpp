#pragma once

#include <GL/glew.h>

#include <SFML/Graphics.hpp>

namespace OpenDK
{

	class Texture
	{
	public:
		Texture();

		bool load(const std::string& filePath);

		void bind() const;
		void unbind() const;

	private:
		GLuint id;

		void generateId();
	};

}
