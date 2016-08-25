#include "MapRenderer.hpp"

namespace OpenDK
{

	MapRenderer::MapRenderer()
	: sp(nullptr), sp2(nullptr), tex(nullptr), block(nullptr), col(488), singleColMode(false)
	{
	}

	MapRenderer::~MapRenderer()
	{
		tex->free();
		delete sp;
		delete sp2;
		delete tex;
		delete block;
	}

	void MapRenderer::moveCam(float offsetX, float offsetY, float offsetZ)
	{
		glm::vec3 pos = camera.getPosition();
		camera.setPosition(glm::vec3(pos.x + offsetX, pos.y + offsetY, pos.z + offsetZ));
	}

	void MapRenderer::rotateCam(float rotX, float rotY, float rotZ)
	{
		glm::vec3 rot = camera.getRotation();
		camera.setRotation(glm::vec3(rot.x + rotX, rot.y + rotY, rot.z + rotZ));
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
		sp2 = new ShaderProgram();
		sp2->addShader("./bin/shaders/cube.vert", GL_VERTEX_SHADER);
		sp2->addShader("./bin/shaders/cube.frag", GL_FRAGMENT_SHADER);
		sp2->bindAttribute(ShaderAttribute::POSITION, "in_Position");
		sp2->bindAttribute(ShaderAttribute::COLOR, "in_Color");
		sp2->bindAttribute(ShaderAttribute::TEXTURE, "in_Unwrap");
		sp2->link();

		sp = new ShaderProgram();
		sp->addShader("./bin/shaders/column.vert", GL_VERTEX_SHADER);
		sp->addShader("./bin/shaders/column.frag", GL_FRAGMENT_SHADER);
		sp->bindAttribute(ShaderAttribute::POSITION, "in_Position");
		sp->bindAttribute(ShaderAttribute::COLOR, "in_Color");
		sp->bindAttribute(ShaderAttribute::TEXTURE, "in_Unwrap");
		sp->link();
		sp->use();

		tex = new Texture();
		tex->loadAtlas("./bin/textures/block0.bmp", 32, 32);
		glActiveTexture(GL_TEXTURE0);
		tex->bind();
		glUniform1i(sp->getUniformLocation("atlas"), 0);
		tex->unbind();

		slb.load("./bin/levels/MAP00001.SLB");

		block = new BlockGeometry();

		//camera.setPosition(0.0f, 0.0f, 0.0f);
		//camera.setPosition(-34.0f, 0.0f, 0.0f);
		camera.setPosition(34.0f, 0.0f, 0.0f);
		//camera.setPosition(-88.5f, 10.0f, 0.0f);
		//camera.setPosition(-175.0f, 20.f, 0.0f);
		//camera.setPosition(-58.5f, 6.5f, 0.0f);
		//camera.setPosition(-400.0f, 60.f, 0.0f);
		camera.setZoom(2.0f);

		slb.load("./bin/levels/MAP00001.SLB");
		//slb.printMap();
		//std::cout << "Slab type on 39,42: " << slb.getTileType(39,42) << std::endl;
		clm.load("./bin/levels/MAP00001.CLM");
		dat.load("./bin/levels/MAP00001.DAT");
		cbd.load("./bin/data/CUBE.DAT");

		// scale, rotate, translate (note: glm operations should be in reverse!)

/*
		bool spritesUsed[544];

		for (int c = 0; c < 511; ++c)
		{
			for (int s = 0; s < 6; ++s)
			{
				int sprite = cbd.getCubeSprite(c, s);
				if (sprite < 544)
				{
					spritesUsed[sprite] = true;
				}
			}
		}

		std::cout << "UNUSED SPRITE INDICES: \n";

		int unusedCount = 0;

		for (int i = 0; i < 544; ++i)
		{
			if (spritesUsed[i] == false)
			{
				std::cout << i << ", ";
				++unusedCount;
			}
		}

		std::cout << "\nThat's a total of " << unusedCount << " unused." << std::endl;
*/

		GLshort cubesTBOData[3072];

		for (size_t c = 0; c < 512; ++c)
		{
			for (size_t s = 0; s < 6; ++s)
			{
				cubesTBOData[c * 6 + s] = (GLshort) cbd.getCubeSprite(c, s);
			}
		}

		GLuint tbo;
		glGenBuffers(1, &tbo);
		glBindBuffer(GL_TEXTURE_BUFFER, tbo);
		glBufferData(GL_TEXTURE_BUFFER, sizeof(cubesTBOData), cubesTBOData, GL_STATIC_DRAW);

		glGenTextures(1, &tboTex);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, tboTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R16I, tbo);

		glUniform1i(sp->getUniformLocation("cubes"), 1);

		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}

	void MapRenderer::nextCol()
	{
		++col;
		if (col > 2047) { col = 2047; }
		std::cout << "col=" << std::setw(4) << col;

		if (clm.columnIsPermanent(col))
		{
			std::cout << " (perm)";
		}
		std::cout << " (" << clm.getColumnUses(col) << " uses)" << std::endl;
	}

	void MapRenderer::prevCol()
	{
		--col;
		if (col < 0) { col = 0; }
		std::cout << "col=" << std::setw(4) << col;

		if (clm.columnIsPermanent(col))
		{
			std::cout << " (perm)";
		}
		std::cout << " (" << clm.getColumnUses(col) << " uses)" << std::endl;
	}

	void MapRenderer::debugDAT() const
	{
		for (int y = 0; y < 85; ++y) // for now, just a fifth of the map
		{
			for (int x = 0; x < 85; ++x)
			{
				for (int r = 0; r < 3; ++r)
				{
					for (int c = 0; c < 3; ++c)
					{
						std::int16_t colIndex = dat.getColumnIndex(x, y, c, r);
						std::cout << "x=" << x << " y=" << y
							<< " c=" << c << " r=" << r
							<< " -> " << colIndex << std::endl;
					}
				}
			}
		}
	}

	void MapRenderer::debugCol() const
	{
		std::cout << "COLUMN INFO\n";
		std::cout << "height: " << (int)clm.getColumnHeight(col) << std::endl;

		for (int h = 0; h < 8; ++h)
		{
			std::cout << "cube " << h << ": ";
			std::int16_t cubeIndex = clm.getCubeType(col, h);
			std::cout << std::setw(3) << cubeIndex << ":";
			std::cout << " T=" << std::setw(3) << cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_TOP);
			std::cout << " B=" << std::setw(3) << cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_BOTTOM);
			std::cout << " F=" << std::setw(3) << cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_FRONT);
			std::cout << " R=" << std::setw(3) << cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_RIGHT);
			std::cout << " B=" << std::setw(3) << cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_BACK);
			std::cout << " L=" << std::setw(3) << cbd.getCubeSprite(cubeIndex, CubeSide::CUBE_LEFT);
			std::cout << std::endl;
		}
	}

	void MapRenderer::switchMode()
	{
		if (singleColMode)
		{
			camera.setPosition(camPosBefore.x, camPosBefore.y, camPosBefore.z);
		}
		else
		{
			camPosBefore = camera.getPosition();
			camera.setPosition(0.0f, 0.0f, 0.0f);
		}
		singleColMode = !singleColMode;
	}

	void MapRenderer::render()
	{
		camera.update();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sp->use();

		glActiveTexture(GL_TEXTURE0);
		tex->bind();

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, tboTex);

		glUniformMatrix4fv(sp->getUniformLocation("viewMatrix"),       1, GL_FALSE, camera.getViewMatrixPtr());			// +4% cpu
		glUniformMatrix4fv(sp->getUniformLocation("projectionMatrix"), 1, GL_FALSE, camera.getProjectionMatrixPtr());	// +5% cpu

		VertexArrayObject vao = block->getVAO();
		vao.bind();


		if (singleColMode)
		{
			for (int h = 0; h < 8; ++h)
			{
				if (!clm.cubeIsSolid(col, h))
				{
					continue;
				}
				std::int16_t cubeType = clm.getCubeType(col, h);
				if (cubeType == 0)
				{
					continue;
				}
				renderColumn(vao, 0, 0, 0, 0, col);
			}
		}
		else
		{
			//for (int y = 0; y < 85; ++y)
			for (int y = 0; y < 42; ++y)
			//for (int y = 34; y < 51; ++y) // for now, just a fifth of the map
			{
				//for (int x = 0; x < 85; ++x)
				for (int x = 0; x < 42; ++x)
				//for (int x = 34; x < 51; ++x) // for now, just a fifth of the map
				{
					for (int r = 0; r < 3; ++r)
					{
						for (int c = 0; c < 3; ++c)
						{
							renderColumn(vao, x, y, c, r);
						}
					}
				}
			}
		}

		/*
		sp2->use();

		glActiveTexture(GL_TEXTURE0);
		tex->bind();

		glUniformMatrix4fv(sp2->getUniformLocation("viewMatrix"),       1, GL_FALSE, camera.getViewMatrixPtr());
		glUniformMatrix4fv(sp2->getUniformLocation("projectionMatrix"), 1, GL_FALSE, camera.getProjectionMatrixPtr());

		vao.bind();

		renderCube(vao, 0, 0, 38);
		*/

		vao.unbind();

	}

	void MapRenderer::renderCube(const VertexArrayObject& vao, int x, int y, int cube)
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(), glm::vec3((float)x, 0.0f, (float)y));
		glUniformMatrix4fv(sp2->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

		if (vao.hasIBO())
		{
			glDrawElements(GL_TRIANGLES, vao.getIBO()->getSize(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

	void MapRenderer::renderColumn(const VertexArrayObject& vao, int tileX, int tileY, int subtileX, int subtileY, int column)
	{
		if (column == -1)
		{
			column = dat.getColumnIndex(tileX, tileY, subtileX, subtileY);
		}
		glm::mat4 columnMatrix = glm::translate(glm::mat4(), glm::vec3((float)tileX*3+subtileX, 0.0f, (float)tileY*3+subtileY));

		// mat4[col][row]
		columnMatrix[0][0] = clm.getBaseBlockType(column);
		columnMatrix[0][1] = clm.getCubeType(column, 0);
		columnMatrix[0][2] = clm.getCubeType(column, 1);
		columnMatrix[1][0] = clm.getCubeType(column, 2);
		columnMatrix[1][1] = clm.getCubeType(column, 3);
		columnMatrix[1][2] = clm.getCubeType(column, 4);
		columnMatrix[2][0] = clm.getCubeType(column, 5);
		columnMatrix[2][1] = clm.getCubeType(column, 6);
		columnMatrix[2][2] = clm.getCubeType(column, 7);

		glUniformMatrix4fv(sp->getUniformLocation("columnInfo"), 1, GL_FALSE, glm::value_ptr(columnMatrix));

		if (vao.hasIBO())
		{
			glDrawElementsInstanced(GL_TRIANGLES, vao.getIBO()->getSize(), GL_UNSIGNED_INT, 0, 9);
		}
		else
		{
			glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 9);
		}
	}

}
