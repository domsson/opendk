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

		ShaderProgram sp = ShaderProgram();
		sp.addShader("./bin/shaders/vertexshader.vs", GL_VERTEX_SHADER);
		sp.addShader("./bin/shaders/fragmentshader.fs", GL_FRAGMENT_SHADER);
		sp.link();
		sp.use();
	}

	void DummyRenderer::render()
	{
		glUseProgram(shaderProgram);
		vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		vao->unbind();
	}
	
}
