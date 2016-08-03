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
		window.create(sf::VideoMode(width, height), title, sf::Style::Close);
		window.setMouseCursorVisible(false);
		if (iconLoaded)
		{
			window.setIcon(gameIcon.getSize().x, gameIcon.getSize().y, gameIcon.getPixelsPtr());
		}
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
		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		// Shaders
		const GLchar* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 position;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"}\0";
		const GLchar* fragmentShaderSource = "#version 330 core\n"
			"out vec4 color;\n"
			"void main()\n"
			"{\n"
			"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";

		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		GLuint shaderProgram;
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glUseProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0); 
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
		// Nothing yet, how sad
	}

	void OpenDK::render()
	{
		glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);		

        // Update the window
        window.display();
	}

}
