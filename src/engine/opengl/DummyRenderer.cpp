#include "DummyRenderer.hpp"

namespace OpenDK
{
	DummyRenderer::DummyRenderer()
	: vao(nullptr), vbo(nullptr)
	{
	}

	DummyRenderer::~DummyRenderer()
	{
		vbo->free();
		vao->free();
		delete vbo;
		delete vao;
	}

	void DummyRenderer::initDummyData()
	{
		Shader vs = Shader();
		vs.create("./bin/shaders/vertexshader.vs", GL_VERTEX_SHADER);

		vbo = new VertexBufferObject();
		vao = new VertexArrayObject();

		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		vbo->setData(vertices, sizeof(vertices));
		vao->addVBO(*vbo, ShaderAttribute::POSITION);

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

		GLuint vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		//GLuint shaderProgram;
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glUseProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void DummyRenderer::render()
	{
		glUseProgram(shaderProgram);
		vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		vao->unbind();
	}
	
}
