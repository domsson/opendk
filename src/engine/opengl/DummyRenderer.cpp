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
			 0.5f,  0.5f,  0.5f,	// 7 (=2)

			 0.5f, -0.5f, -0.5f,	// 8 (=5)
			-0.5f, -0.5f, -0.5f,	// 9
			-0.5f,  0.5f, -0.5f,	// 10
			 0.5f,  0.5f, -0.5f,	// 11 (=6)

			 -0.5f, -0.5f, -0.5f,	// 12 (=9)
			 -0.5f, -0.5f,  0.5f,	// 13 (=0)
			 -0.5f,  0.5f,  0.5f,	// 14 (=3)
			 -0.5f,  0.5f, -0.5f,	// 15 (=10)

			 -0.5f,  0.5f,  0.5f,	// 16 (=3)
			  0.5f,  0.5f,  0.5f,	// 17 (=2)
			  0.5f,  0.5f, -0.5f,	// 18 (=6)
			 -0.5f,  0.5f, -0.5f,	// 19 (=10)

			 -0.5f, -0.5f, -0.5f,	// 20 (=9)
			  0.5f, -0.5f, -0.5f,	// 21 (=5)
			  0.5f, -0.5f,  0.5f,	// 22 (=1)
			 -0.5f, -0.5f,  0.5f	// 23 (=0)
		};

		GLubyte colors[] = {
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,

			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,

			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,

			255, 255, 255,
			255, 255, 255,
			255, 255, 255,
			255, 255, 255,

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
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		};

		GLuint indices[] = {
			 0,  1,  2,  2,  3,  0,	// Front side
			 4,  5,  6,  6,  7,  4,	// Right side
			 8,  9, 10, 10, 11,  8,	// Back side
			12, 13, 14, 14, 15, 12, // Left side
			16, 17, 18, 18, 19, 16,	// Top side
			20, 21, 22, 22, 23, 20	// Bottom side
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

		Texture tex2;
		tex2.load("./bin/textures/block0.bmp");

		// 'tis just a test

		SlabFile slb;
		slb.load("./bin/levels/MAP00001.SLB");
		slb.printMap();

		OwnerFile own;
		own.load("./bin/levels/MAP00001.OWN");
		//own.printMap();

		// scale, rotate, translate (note: glm operations should be in reverse!)

		//modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(35.264f), glm::vec3(0.0f, 1.0f, 0.0f));
		//projectionMatrix = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
		projectionMatrix = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.01f, 100.0f); // LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR
	}

	void DummyRenderer::render()
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sp->use();

		/*
		sf::Time elapsed = clock.restart();
		float elapsedSeconds = elapsed.asSeconds();

		modelMatrix = glm::rotate(modelMatrix, std::sin(elapsedSeconds), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, std::sin(elapsedSeconds), glm::vec3(1.0f, 0.0f, 0.0f));
		*/

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
