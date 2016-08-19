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
		: width(INITIAL_WIDTH), height(INITIAL_HEIGHT), title(TITLE),
		iconLoaded(false)
	{
		iconLoaded = gameIcon.loadFromFile(GAME_ICON);
		initWindow();
		initGLEW();
		initGL();
	}

	OpenDK::~OpenDK()
	{
		window.close();
	}

	void OpenDK::initWindow()
	{
		sf::ContextSettings context(2, 0, 0, 3, 2);
		window.create(sf::VideoMode(width, height), title, sf::Style::Close, context);
		window.setMouseCursorVisible(false);
		if (iconLoaded)
		{
			window.setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());
		}

		sf::ContextSettings settings = window.getSettings();
		std::cout << "depth bits:" << settings.depthBits << std::endl;
		std::cout << "stencil bits:" << settings.stencilBits << std::endl;
		std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
		std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;
	}

	void OpenDK::initGLEW()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
		}
	}

	void OpenDK::initGL()
	{
		glViewport(0, 0, INITIAL_WIDTH, INITIAL_HEIGHT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);	// Do not render hidden geometry
		glEnable(GL_CULL_FACE);		// Do not render back sides
		glCullFace(GL_BACK);		// cull back face (default)
		glFrontFace(GL_CCW);		// GL_CCW for counter clock-wise (default)
		//renderer.initDummyData();
		mapRenderer.initDummyData();
	}

	void OpenDK::run()
	{
		//std::cout << "Hello World!" << std::endl;
		sf::Clock clock;
		bool running = true;

		while (running)
		{

			float elapsedSeconds = clock.restart().asSeconds();

			if (elapsedSeconds < SECONDS_PER_FRAME)
			{
				long sleepingTime = (SECONDS_PER_FRAME - elapsedSeconds) * 1000.0;
				if (sleepingTime > 0)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(sleepingTime));
				}
			}

			sf::Event event;
			while (window.pollEvent(event))
		    {
		        // "close requested" event: we close the window
		        if (event.type == sf::Event::Closed)
				{
					running = false;
					// window.close();
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					running = false;
				}
			}

			update();
			render();
		}
		window.close();
	}

	void OpenDK::update()
	{
		float camOffsetX = 0.0f;
		float camOffsetY = 0.0f;
		float zoomChange = 0.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			camOffsetX =  0.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			camOffsetX = -0.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			camOffsetY = -0.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			camOffsetY =  0.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			zoomChange = -0.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			zoomChange =  0.1f;
		}

		mapRenderer.moveCam(camOffsetX, camOffsetY);
		mapRenderer.zoomCam(zoomChange);
	}

	void OpenDK::render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//renderer.render();
		mapRenderer.render();

        window.display();
	}

}
