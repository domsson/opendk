#include "DummyRenderer.hpp"

namespace OpenDK
{
	DummyRenderer::DummyRenderer()
	: vao(nullptr), sp(nullptr), tex(nullptr)
	{
	}

	DummyRenderer::~DummyRenderer()
	{
		vao->free();
		tex->free();
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
			-0.5f, -0.5f,  0.5f,	// 0: bottom left front
			 0.5f, -0.5f,  0.5f,	// 1: bottom right front
			 0.5f,  0.5f,  0.5f,	// 2: top right front
			-0.5f,  0.5f,  0.5f,	// 3: top left front

			 0.5f, -0.5f,  0.5f,	// 4 (=1)
			 0.5f, -0.5f, -0.5f,	// 5
			 0.5f,  0.5f, -0.5f,	// 6
			 0.5f,  0.5f,  0.5f		// 7 (=2)
		};

		GLubyte colors[] = {
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,

			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255
		};

		GLfloat unwrap[] = {
			0.0f, 1.0f,	// 0: bottom left front
			1.0f, 1.0f,	// 1: bottom right front
			1.0f, 0.0f,	// 2: top right front
			0.0f, 0.0f,	// 3: top left front

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		};

		GLuint indices[] = {
			0, 1, 2, 2, 3, 0,	// Front side
			4, 5, 6, 6, 7, 4	// Right side
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
		modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		projectionMatrix = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
		//projectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	}

	void DummyRenderer::render()
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sp->use();

		// Pass them to the shaders
        glUniformMatrix4fv(sp->getUniformLocation("modelMatrix"),       1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(sp->getUniformLocation("viewMatrix"),        1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(sp->getUniformLocation("projectionMatrix"),  1, GL_FALSE, glm::value_ptr(projectionMatrix));

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
