#include "MapRenderer.hpp"

namespace OpenDK
{
	MapRenderer::MapRenderer()
	: sp(nullptr), tex(nullptr), block(nullptr)
	{
	}

	MapRenderer::~MapRenderer()
	{
		tex->free();
		delete sp;
		delete tex;
		delete block;
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

	void MapRenderer::debugCamCoords() const
	{
		glm::vec3 camPos = camera.getPosition();
		std::cout << "cam pos: " << camPos.x << ", " << camPos.y << ", " << camPos.z << std::endl;
	}

	void MapRenderer::initDummyData()
	{
		sp = new ShaderProgram();
		sp->addShader("./bin/shaders/cube.vert", GL_VERTEX_SHADER);
		sp->addShader("./bin/shaders/cube.frag", GL_FRAGMENT_SHADER);
		sp->bindAttribute(ShaderAttribute::POSITION, "in_Position");
		sp->bindAttribute(ShaderAttribute::COLOR, "in_Color");
		sp->bindAttribute(ShaderAttribute::TEXTURE, "in_Unwrap");
		sp->link();

		tex = new Texture();
		tex->loadAtlas("./bin/textures/block0.bmp", 32, 32);

		slb.load("./bin/levels/MAP00001.SLB");

		block = new BlockGeometry();

		//camera.setPosition(-58.5f, 6.5f, 0.0f);
		camera.setPosition(-175.0f, 20.f, 0.0f);
		camera.setZoom(2.0f);

		slb.load("./bin/levels/MAP00001.SLB");
		//slb.printMap();
		//std::cout << "Slab type on 39,42: " << slb.getTileType(39,42) << std::endl;
		clm.load("./bin/levels/MAP00001.CLM");
		dat.load("./bin/levels/MAP00001.DAT");
		cbd.load("./bin/data/CUBE.DAT");

		// scale, rotate, translate (note: glm operations should be in reverse!)

		/*
		for (int y = 0; y < 3; ++y)
		{
			for (int x = 0; x < 3; ++x)
			{
				std::int16_t colIndex = dat.getColumnIndex(39, 42, x, y);
				std::cout << "column index  = " << std::dec << colIndex << std::endl;
				std::int8_t colHeight = clm.getColumnHeight(colIndex);
				std::cout << "column height = " << std::dec << static_cast<std::int16_t>(colHeight) << std::endl;
				bool isPermanent = clm.columnIsPermanent(colIndex);
				std::cout << "column perm.  = " << (isPermanent ? "y" : "n") << std::endl;

				for (int h = 0; h < 8; ++h)
				{
					std::int16_t cubeType = clm.getCubeType(colIndex, h);
					std::cout << "cube type  = " << std::dec << cubeType << std::endl;
					bool isSolid = clm.cubeIsSolid(colIndex, h);
					std::cout << "cube solid = " << (isSolid ? "y" : "n")  << std::endl;
				}
			}
		}
		*/
	}

	void MapRenderer::render()
	{
		camera.update();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sp->use();
		//tex->bind();
		tex->bind();

		glUniformMatrix4fv(sp->getUniformLocation("viewMatrix"),       1, GL_FALSE, camera.getViewMatrixPtr());			// +4% cpu
		glUniformMatrix4fv(sp->getUniformLocation("projectionMatrix"), 1, GL_FALSE, camera.getProjectionMatrixPtr());	// +5% cpu

		VertexArrayObject vao = block->getVAO();
		vao.bind();

		//for (int y = 0; y < 85; ++y)
		for (int y = 34; y < 51; ++y) // for now, just a fifth of the map
		{
			//for (int x = 0; x < 85; ++x)
			for (int x = 34; x < 51; ++x) // for now, just a fifth of the map
			{
				//renderBlock(vao, x, y);

				for (int r = 0; r < 3; ++r)
				{
					for (int c = 0; c < 3; ++c)
					{
						//renderBlock(vao, x, y, c, r);

						std::int16_t colIndex = dat.getColumnIndex(x, y, c, r);

						//for (int h = 0; h < 8; ++h)
						for (int h = 0; h < 1; ++h)
						{
							if (!clm.cubeIsSolid(colIndex, h))
							{
								continue;
							}
							std::int16_t cubeType = clm.getCubeType(colIndex, h);
							if (cubeType == 0)
							{
								continue;
							}
							renderCube(vao, x, y, c, r, h, cubeType);
						}
					}
				}
			}
		}
		vao.unbind();

	}

	void MapRenderer::renderBlock(const VertexArrayObject& vao, int tileX, int tileY, int blockX, int blockY)
	{
		modelMatrix = glm::translate(glm::mat4(), glm::vec3((float)tileX*3+blockX, 0.0f, (float)tileY*3+blockY));

		// For "block.vert" shader
		//int sprite = getSuitableSprite(slb.getTileType(tileX, tileY));
		//glUniform2i(sp->getUniformLocation("sprites"), sprite, sprite);

		// For "cube.vert" shader
		int sprite = getSuitableSprite(slb.getTileType(tileX, tileY));
		GLint sides[6] = {sprite, sprite, sprite, sprite, sprite, sprite};
		glUniform1iv(sp->getUniformLocation("sides"), 6, sides);	// +3% cpu

		// Pass matrices to shaders
		glUniformMatrix4fv(sp->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));	// +6% cpu

		if (vao.hasIBO())
		{
			glDrawElements(GL_TRIANGLES, vao.getIBO()->getSize(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

	void MapRenderer::renderCube(const VertexArrayObject& vao, int tileX, int tileY, int cubeX, int cubeY, int cubeZ, std::int16_t cubeIndex)
	{
		modelMatrix = glm::translate(glm::mat4(), glm::vec3((float)tileX*3+cubeX, (float)cubeZ, (float)tileY*3+cubeY));

		// For "block.vert" shader
		//int sprite = getSuitableSprite(slb.getTileType(tileX, tileY));
		//glUniform2i(sp->getUniformLocation("sprites"), sprite, sprite);

		// For "cube.vert" shader
		//int sprite = getSuitableSprite(slb.getTileType(tileX, tileY));
		GLint sides[6] = {
			cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_TOP),
			cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_BOTTOM),
			cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_FRONT),
			cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_RIGHT),
			cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_BACK),
			cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_LEFT)
		};
		glUniform1iv(sp->getUniformLocation("sides"), 6, sides);	// +3% cpu

		// Pass matrices to shaders
		glUniformMatrix4fv(sp->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));	// +6% cpu

		if (vao.hasIBO())
		{
			glDrawElements(GL_TRIANGLES, vao.getIBO()->getSize(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

	int MapRenderer::getSuitableSprite(TileType tileType) const
	{
		switch (tileType)
		{
			case TileType::EARTH: // 2
				return 27;
				break;
			case TileType::PATH: // 10
				return 30;
				break;
			case TileType::LAND: // 11
				return 176;
				break;
			case TileType::WALL:	// 4-9
			case TileType::WALL_2:
			case TileType::WALL_3:
			case TileType::WALL_4:
			case TileType::WALL_5:
			case TileType::WALL_6:
				return 112;
				break;
			case TileType::DUNGEON_HEART:
				return 490;
				break;
			case TileType::ROCK: // 0
			case TileType::TYPE_UNDEFINED:
			default:
				return 271;
		}
	}

}
