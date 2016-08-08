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
		delete sp;
		delete tex;
	}

	void DummyRenderer::initDummyData()
	{
		VertexBufferObject vboPos;
		VertexBufferObject vboCol;
		VertexBufferObject vboUvw;
		IndexBufferObject ibo;
		vao = new VertexArrayObject();

		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,	// 0: bottom left
			 0.5f, -0.5f, 0.0f,	// 1: bottom right
			 0.5f,  0.5f, 0.0f,	// 2: top right
			-0.5f,  0.5f, 0.0f	// 3: top left
		};

		GLubyte colors[] = {
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255
		};

		GLfloat unwrap[] = {
			0.0f, 1.0f,	// 0: bottom left
			1.0f, 1.0f,	// 1: bottom right
			1.0f, 0.0f,	// 2: top right
			0.0f, 0.0f	// 3: top left
		};

		GLuint indices[] = {
			0, 1, 2, 2, 3, 0
		};

		vboPos.setData(vertices, sizeof(vertices));
		vboCol.setData(colors, sizeof(colors));
		vboUvw.setData(unwrap, sizeof(unwrap));
		vboUvw.setChunkSize(2);

		ibo.setData(indices, sizeof(indices));

		vao->addVBO(vboPos, ShaderAttribute::POSITION);
		vao->addVBO(vboCol, ShaderAttribute::COLOR);
		vao->addVBO(vboUvw, ShaderAttribute::TEXTURE);
		vao->setIBO(ibo);

		sp = new ShaderProgram();
		sp->addShader("./bin/shaders/temp.vert", GL_VERTEX_SHADER);
		sp->addShader("./bin/shaders/temp.frag", GL_FRAGMENT_SHADER);
		sp->bindAttribute(ShaderAttribute::POSITION, "position");
		sp->bindAttribute(ShaderAttribute::COLOR, "color");
		sp->bindAttribute(ShaderAttribute::TEXTURE, "texCoord");
		sp->link();

		tex = new Texture();
		tex->load("./bin/textures/placeholder.png");

		// 'tis just a test
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	}

	void DummyRenderer::render()
	{
		sp->use();
		tex->bind();
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
