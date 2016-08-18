#include "MapRenderer.hpp"

namespace OpenDK
{
	MapRenderer::MapRenderer()
	: sp(nullptr), tex(nullptr), map(nullptr)
	{
	}

	MapRenderer::~MapRenderer()
	{
		tex->free();
		delete sp;
		delete tex;
		delete map;
	}

	void MapRenderer::moveCam(float offsetX, float offsetY)
	{
		glm::vec3 pos = camera.getPosition();
		camera.setPosition(glm::vec3(pos.x + offsetX, pos.y + offsetY, pos.z));
	}

	void MapRenderer::initDummyData()
	{
		sp = new ShaderProgram();
		sp->addShader("./bin/shaders/temp.vert", GL_VERTEX_SHADER);
		sp->addShader("./bin/shaders/temp.frag", GL_FRAGMENT_SHADER);
		sp->bindAttribute(ShaderAttribute::POSITION, "in_Position");
		sp->bindAttribute(ShaderAttribute::COLOR, "in_Color");
		sp->bindAttribute(ShaderAttribute::TEXTURE, "in_Unwrap");
		sp->link();

		tex = new Texture();
		tex->load("./bin/textures/block0.bmp");

		// scale, rotate, translate (note: glm operations should be in reverse!)
	}

	void MapRenderer::render()
	{
		camera.update();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sp->use();
		tex->bind();

		Cube c(CubeType::BRICK);
		const GLfloat* uvOffsets = c.getGeometry().getTexCoords();
		//std::cout << "offsets: u_0=" << uvOffsets[0] << " v_0=" << uvOffsets[1] << " u_1=" << uvOffsets[2] << " v_1=" << uvOffsets[3];

		VertexArrayObject vao = c.getGeometry().getVAO();

		// Pass texture coords to shaders
		glUniform4fv(sp->getUniformLocation("uvOffsets"), 1, uvOffsets);

		// Pass matrices to shaders
		glUniformMatrix4fv(sp->getUniformLocation("modelMatrix"),       1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(sp->getUniformLocation("viewMatrix"),        1, GL_FALSE, camera.getViewMatrixPtr());
		glUniformMatrix4fv(sp->getUniformLocation("projectionMatrix"),  1, GL_FALSE, camera.getProjectionMatrixPtr());

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
