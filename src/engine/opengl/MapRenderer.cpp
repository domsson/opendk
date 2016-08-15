#include "MapRenderer.hpp"

namespace OpenDK
{
	MapRenderer::MapRenderer()
	: sp(nullptr), tex(nullptr)
	{
	}

	MapRenderer::~MapRenderer()
	{
		tex->free();
		delete sp;
		delete tex;
		delete map;
	}

	void MapRenderer::initDummyData()
	{
		sp = new ShaderProgram();
		sp->addShader("./bin/shaders/temp.vert", GL_VERTEX_SHADER);
		sp->addShader("./bin/shaders/temp.frag", GL_FRAGMENT_SHADER);
		sp->bindAttribute(ShaderAttribute::POSITION, "position");
		sp->bindAttribute(ShaderAttribute::COLOR, "color");
		sp->bindAttribute(ShaderAttribute::TEXTURE, "texCoord");
		sp->link();

		tex = new Texture();
		tex->load("./bin/textures/block0.bmp");

		// scale, rotate, translate (note: glm operations should be in reverse!)

		//modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		viewMatrix = glm::rotate(viewMatrix, glm::radians(35.264f), glm::vec3(0.0f, 1.0f, 0.0f));
		//projectionMatrix = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
		projectionMatrix = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.01f, 100.0f); // LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR
	}

	void MapRenderer::render()
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sp->use();
		tex->bind();

		Cube c(CubeType::BRICK);

		VertexArrayObject vao = c.getGeometry().getVAO();

		// Pass them to the shaders
		glUniformMatrix4fv(sp->getUniformLocation("modelMatrix"),       1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(sp->getUniformLocation("viewMatrix"),        1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(sp->getUniformLocation("projectionMatrix"),  1, GL_FALSE, glm::value_ptr(projectionMatrix));

		vao.bind();
		if (vao.hasIBO())
		{
			glDrawElements(GL_TRIANGLES, vao.getIBO()->getSize(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		vao.unbind();

		//modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, 0.0f));
	}

}
