#pragma once

#include <string>
#include <iostream> // Give you stuff like `cout`
#include <chrono>
#include <thread>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace OpenDK
{

	class OpenDK
	{
	private:
		sf::RenderWindow *window;

		int width;
		int height;
		std::string title;

		sf::Image gameIcon;
		bool iconLoaded;

		void initWindow();

	public:
		// Something
		OpenDK();
		~OpenDK();

		void run();
		void update();
		void render();
	};

}
