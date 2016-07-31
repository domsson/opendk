#include "OpenDK.hpp"

namespace OpenDK
{

	static const std::string TITLE = "OpenDK";
	static const std::string VERSION = "0.0.1";

	static const int INITIAL_WIDTH = 800;
	static const int INITIAL_HEIGHT = 600;
	static const std::string GAME_ICON = "icon.png";

	static const int TARGET_FPS = 60;
	static const float SECONDS_PER_FRAME = 1.0 / TARGET_FPS;

	OpenDK::OpenDK()
		: window(nullptr), width(INITIAL_WIDTH), height(INITIAL_HEIGHT), title(TITLE),
		iconLoaded(false)
	{
		iconLoaded = gameIcon.loadFromFile(GAME_ICON);
		initWindow();
	}

	OpenDK::~OpenDK()
	{
		window->close();
		delete window;
	}

	void OpenDK::initWindow()
	{
		window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Close);
		window->setMouseCursorVisible(false);
		if (iconLoaded)
		{
			window->setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());
		}
	}

	void OpenDK::run()
	{
		//std::cout << "Hello World!" << std::endl;
		sf::Clock clock;

		while (window->isOpen())
		{
			sf::Event event;
		    while (window->pollEvent(event))
		    {
		        // "close requested" event: we close the window
		        if (event.type == sf::Event::Closed)
		            window->close();
		    }

			float elapsedSeconds = clock.restart().asSeconds();

			if (elapsedSeconds < SECONDS_PER_FRAME)
			{
				long sleepingTime = (SECONDS_PER_FRAME - elapsedSeconds) * 1000.0;
				if (sleepingTime > 0)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(sleepingTime));
				}
			}

			update();
			render();
		}
	}

	void OpenDK::update()
	{
		// Nothing yet, how sad
	}

	void OpenDK::render()
	{
	    // Clear screen
        window->clear();
        // Update the window
        window->display();
	}

}
