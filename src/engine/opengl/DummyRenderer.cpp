#include "DummyRenderer.hpp"

namespace OpenDK
{
	DummyRenderer::DummyRenderer()
	: vao(nullptr)
	{
	}

	DummyRenderer::~DummyRenderer()
	{
		vao->free();
		delete vao;
	}

	void DummyRenderer::initDummyData()
	{
		VertexBufferObject vboPos;
		VertexBufferObject vboCol;
		VertexBufferObject vboUvw;
		IndexBufferObject ibo;
		vao = new VertexArrayObject();

		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		GLfloat colors[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
		};

		GLfloat unwrap[] = {
			0.0f, 0.0f,
			0.5f, 1.0f,
			1.0f, 0.0f
		};

		GLuint indices[] = {
			0, 1, 2
		};

		vboPos.setData(vertices, sizeof(vertices));
		vboCol.setData(colors, sizeof(colors));
		vboUvw.setData(unwrap, sizeof(unwrap));
		vboUvw.setChunkSize(2);

		ibo.setData(indices, sizeof(indices));

		vao->addVBO(vboPos, ShaderAttribute::POSITION);
		vao->addVBO(vboCol, ShaderAttribute::COLOR);
		//vao->addVBO(vboUvw, ShaderAttribute::TEXTURE);
		vao->setIBO(ibo); // TODO this will lead to a segfault in glDrawElements ...

		ShaderProgram sp = ShaderProgram();
		sp.addShader("./bin/shaders/temp.vert", GL_VERTEX_SHADER);
		sp.addShader("./bin/shaders/temp.frag", GL_FRAGMENT_SHADER);
		sp.link();
		sp.use();

		//Texture tex;
		//tex.load("./bin/textures/placeholder.png");
	}

	void DummyRenderer::render()
	{
		glUseProgram(shaderProgram);
		vao->bind();
		if (vao->hasIBO())
		{
			glDrawElements(GL_TRIANGLES, vao->getIBO()->getSize(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		vao->unbind();
	}

}
