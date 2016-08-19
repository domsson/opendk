#include "MapRenderer.hpp"

namespace OpenDK
{
	MapRenderer::MapRenderer()
	: sp(nullptr), tex(nullptr), atlas(nullptr), map(nullptr)
	{
	}

	MapRenderer::~MapRenderer()
	{
		tex->free();
		atlas->free();
		delete sp;
		delete tex;
		delete atlas;
		delete map;
	}

	void MapRenderer::moveCam(float offsetX, float offsetY, float offsetZ)
	{
		glm::vec3 pos = camera.getPosition();
		camera.setPosition(glm::vec3(pos.x + offsetX, pos.y + offsetY, pos.z + offsetZ));
	}

	void MapRenderer::zoomCam(float zoomChange)
	{
		camera.setZoom(camera.getZoom() + zoomChange);
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

		atlas = new Texture();
		atlas->loadAtlas("./bin/textures/block0.bmp", 32, 32);

		slb.load("./bin/levels/MAP00001.SLB");

		// scale, rotate, translate (note: glm operations should be in reverse!)
	}

	void MapRenderer::render()
	{
		camera.update();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sp->use();
		//tex->bind();
		atlas->bind();


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

/*
		for (int y = 0; y < 85; ++y)
		{
			for (int x = 0; x < 85; ++x)
			{
				Cube cube(getSuitableCubeType(slb.getTileType(x, y)));

				for (int r = 0; r < 3; ++r)
				{
					for (int c = 0; c < 3; ++c)
					{
						renderCube(cube, x+c, y+r);
					}
				}
			}
		}
*/

		//modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, 0.0f));
	}

	void MapRenderer::renderCube(const Cube& cube, int x, int y)
	{
		modelMatrix = glm::mat4();
		modelMatrix = glm::translate(modelMatrix, glm::vec3((float)x, (float)y, 0.0f));

		const GLfloat* uvOffsets = cube.getGeometry().getTexCoords();
		VertexArrayObject vao = cube.getGeometry().getVAO();

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
	}

	CubeType MapRenderer::getSuitableCubeType(TileType tileType) const
	{
		switch (tileType)
		{
			case TileType::EARTH: // 2
				return CubeType::EARTH_1;
				break;
			case TileType::PATH: // 10
				return CubeType::PATH_1;
				break;
			case TileType::LAND: // 11
				return CubeType::CLAIMED_NON_CENTRE;
				break;
			case TileType::WALL:	// 4-9
			case TileType::WALL_2:
			case TileType::WALL_3:
			case TileType::WALL_4:
			case TileType::WALL_5:
			case TileType::WALL_6:
				return CubeType::BRICK;
				break;
			case TileType::DUNGEON_HEART:
				return CubeType::HEART_PEDESTAL_CENTRE;
				break;
			case TileType::ROCK: // 0
			case TileType::TYPE_UNDEFINED:
			default:
				return CubeType::ROCK_1;
		}
	}

}
