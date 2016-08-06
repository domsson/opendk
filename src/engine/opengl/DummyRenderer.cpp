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
		vbo = new VertexBufferObject();
		vao = new VertexArrayObject();

		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		vbo->setData(vertices, sizeof(vertices));
		vao->addVBO(*vbo, ShaderAttribute::POSITION);

		Shader vs = Shader();
		vs.create("./bin/shaders/vertexshader.vs", GL_VERTEX_SHADER);

		Shader fs = Shader();
		fs.create("./bin/shaders/fragmentshader.fs", GL_FRAGMENT_SHADER);

		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vs.getId());
		glAttachShader(shaderProgram, fs.getId());
		glLinkProgram(shaderProgram);

		glUseProgram(shaderProgram);

		vs.free();
		fs.free();
	}

	void DummyRenderer::render()
	{
		glUseProgram(shaderProgram);
		vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		vao->unbind();
	}
	
}
