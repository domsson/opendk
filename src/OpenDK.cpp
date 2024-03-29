#include "OpenDK.hpp"

namespace OpenDK
{

	static const std::string TITLE = "OpenDK";
	static const std::string VERSION = "0.0.1";

	//static const int INITIAL_WIDTH = 1280;
	//static const int INITIAL_HEIGHT = 800;
	static const int INITIAL_WIDTH = 640;
	static const int INITIAL_HEIGHT = 400;
	static const std::string GAME_ICON = "icon.png";

	static const int TARGET_FPS = 40;
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
		//sf::ContextSettings context(2, 0, 4, 3, 1);
		sf::ContextSettings context(2, 0, 0, 3, 1);
		window.create(sf::VideoMode(width, height), title, sf::Style::Close, context);
		window.setMouseCursorVisible(false);
		if (iconLoaded)
		{
			window.setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());
		}

		sf::ContextSettings settings = window.getSettings();
		std::cout << "depth bits:   " << settings.depthBits << std::endl;
		std::cout << "stencil bits: " << settings.stencilBits << std::endl;
		std::cout << "antialiasing: " << settings.antialiasingLevel << std::endl;
		std::cout << "gl version:   " << settings.majorVersion << "." << settings.minorVersion << std::endl;
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
		mapRenderer.init();
	}

	void OpenDK::run()
	{
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
		        if (event.type == sf::Event::Closed)
				{
					running = false;
				}
				else if (event.type == sf::Event::MouseWheelMoved)
				{
					mapRenderer.zoomCam(-0.2f * event.mouseWheel.delta);
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						running = false;
					}
					if (event.key.code == sf::Keyboard::C)
					{
						mapRenderer.debugCamCoords();
					}
					/*
					if (event.key.code == sf::Keyboard::F)
					{
						mapRenderer.debugCol();
					}
					*/
					if (event.key.code == sf::Keyboard::Q)
					{
						mapRenderer.debugLight();
					}
					/*
					if (event.key.code == sf::Keyboard::N)
					{
						mapRenderer.prevCol();
					}
					if (event.key.code == sf::Keyboard::M)
					{
						mapRenderer.nextCol();
					}
					if (event.key.code == sf::Keyboard::T)
					{
						mapRenderer.switchMode();
					}
					*/
				}
			}

			pinput(); // process input
			update(); // update the simulation
			render(); // render the current state
		}
		window.close();
	}

	void OpenDK::pinput()
	{
		bool ctrl = false;
		bool alt  = false;

		float camOffsetX = 0.0f;
		float camOffsetY = 0.0f;
		float camOffsetZ = 0.0f;

		float camRotateX = 0.0f;
		float camRotateY = 0.0f;
		float camRotateZ = 0.0f;

		float zoomChange = 0.0f;

		float lightOffsetX = 0.0f;
		//float lightOffsetY = 0.0f;
		float lightOffsetZ = 0.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			ctrl = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		{
			alt  = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (ctrl)
			{
				camRotateY += 0.6f;
			}
			else
			{
				camOffsetX -= 0.2f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (ctrl)
			{
				camRotateY -= 0.6f;
			}
			else
			{
				camOffsetX += 0.2f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (ctrl)
			{
				zoomChange -= 0.1f;
			}
			else if (alt)
			{
				camRotateX -= 0.6f;
			}
			else
			{
				camOffsetZ -= 0.2f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (ctrl)
			{
				zoomChange += 0.1f;
			}
			else if (alt)
			{
				camRotateX += 0.6f;
			}
			else
			{
				camOffsetZ += 0.2f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			zoomChange = -0.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			zoomChange =  0.1f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			lightOffsetZ -= 0.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			lightOffsetZ += 0.1f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			lightOffsetX -= 0.1f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			lightOffsetX += 0.1f;
		}

		mapRenderer.moveLight(lightOffsetX, lightOffsetZ);
		mapRenderer.moveCam(camOffsetX, camOffsetY, camOffsetZ);
		mapRenderer.rotateCam(camRotateX, camRotateY, camRotateZ);
		mapRenderer.zoomCam(zoomChange);
	}

	void OpenDK::update()
	{
		mapRenderer.update();
	}

	void OpenDK::render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mapRenderer.render();
        window.display();
	}

}
