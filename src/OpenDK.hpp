#pragma once

#include <string>
#include <iostream> // Gives you stuff like `cout`
#include <chrono>
#include <thread>

#include <GL/glew.h>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#include "engine/opengl/MapRenderer.hpp"

namespace OpenDK
{

	class OpenDK
	{
	public:
		OpenDK();
		~OpenDK();

		void run();
		void update();
		void render();

	private:
		MapRenderer mapRenderer;

		sf::Window window;

		int width;
		int height;
		std::string title;

		sf::Image gameIcon;
		bool iconLoaded;

		int mouseX;
		int mouseY;

		void initWindow();
		void initGLEW();
		void initGL();
	};

}
