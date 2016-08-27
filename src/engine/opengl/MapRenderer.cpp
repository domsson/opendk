#include "MapRenderer.hpp"

namespace OpenDK
{

	MapRenderer::MapRenderer()
	: sp(nullptr), sp2(nullptr), tex(nullptr), block(nullptr),
	  col(488), singleColMode(false),
	  lightPos(glm::vec3(114.0f, 0.0f, 130.0f))
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

	void MapRenderer::moveLight(float offsetX, float offsetY, float offsetZ)
	{
		glm::vec3 move = glm::vec3(offsetX, offsetY, offsetZ);
		move = glm::rotateY(move, glm::radians(- camera.getRotation().y));

		lightPos = lightPos + move;
	}

	void MapRenderer::moveCam(float offsetX, float offsetY, float offsetZ)
	{
		glm::vec3 pos = camera.getPosition();
		glm::vec3 move = glm::vec3(offsetX, offsetY, offsetZ);
		move = glm::rotateY(move, glm::radians(- camera.getRotation().y));

		pos = pos + move;
		camera.setPosition(pos);
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
		glm::vec3 camRot = camera.getRotation();
		std::cout << "cam rot: " << camRot.x << ", " << camRot.y << ", " << camRot.z << std::endl;
		float camZoom = camera.getZoom();
		std::cout << "cam zoom: " << camZoom << std::endl;
	}

	void MapRenderer::initDummyData()
	{
		sp2 = new ShaderProgram();
		sp2->addShader("./bin/shaders/cube.vert", GL_VERTEX_SHADER);
		sp2->addShader("./bin/shaders/cube.frag", GL_FRAGMENT_SHADER);
		sp2->bindAttribute(ShaderAttribute::POSITION, "in_Position");
		sp2->bindAttribute(ShaderAttribute::COLOR, "in_Color");
		sp2->bindAttribute(ShaderAttribute::TEXTURE, "in_Unwrap");
		sp2->bindAttribute(ShaderAttribute::NORMALS, "in_Normal");
		sp2->link();

		sp = new ShaderProgram();
		sp->addShader("./bin/shaders/column.vert", GL_VERTEX_SHADER);
		sp->addShader("./bin/shaders/column.frag", GL_FRAGMENT_SHADER);
		sp->bindAttribute(ShaderAttribute::POSITION, "in_Position");
		sp->bindAttribute(ShaderAttribute::COLOR, "in_Color");
		sp->bindAttribute(ShaderAttribute::TEXTURE, "in_Unwrap");
		sp->bindAttribute(ShaderAttribute::NORMALS, "in_Normal");
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


		//camera.setPosition(42.5f, 0.0f, 42.5f);
		camera.setPosition(65.0f, 0.0f, 63.0f);
		camera.setRotation(-45.0f, 45.0f, 0.0f);
		camera.setZoom(2.4f);

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
		for (int y = 0; y < 85; ++y)
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
		for (int i = 0; i < 65025; ++i)
		{
			lightMap[i] = 0.0f;
		}

		float lightRadius = 7.0f;

		for (int y = (int)lightPos.z - (int)lightRadius; y < (int)lightPos.z + (int) lightRadius; ++y)
		{
			for (int x = (int)lightPos.x - (int)lightRadius; x < (int)lightPos.x + (int) lightRadius; ++x)
			{
				float xTerm = (float)x - lightPos.x;
				float yTerm = (float)y - lightPos.z;
				float distance = sqrt(xTerm*xTerm + yTerm*yTerm);

				if (distance < lightRadius)
				{
					lightMap[y * 255 + x] = 1.0f - (distance / lightRadius);
				}
			}
		}


		camera.update();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sp->use();

		glActiveTexture(GL_TEXTURE0);
		tex->bind();

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, tboTex);


		glUniformMatrix4fv(sp->getUniformLocation("viewMatrix"),       1, GL_FALSE, camera.getViewMatrixPtr());			// +4% cpu
		glUniformMatrix4fv(sp->getUniformLocation("projectionMatrix"), 1, GL_FALSE, camera.getProjectionMatrixPtr());	// +5% cpu

		// The following would be lighter on the GPU, heavier on the CPU
		//glm::mat4 projectionViewMatrix = camera.getProjectionMatrix() * camera.getViewMatrix();
		//glUniformMatrix4fv(	sp->getUniformLocation("modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionViewMatrix));

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
			int camX = camera.getPosition().x * 2 / 3;
			int camY = camera.getPosition().z * 2 / 3;

			int xStart = camX - 15;
			xStart = xStart < 0 ? 0 : xStart;

			int yStart = camY - 15;
			yStart = yStart < 0 ? 0 : yStart;

			int xEnd = camX + 15;
			xEnd = xEnd > 85 ? 85 : xEnd;

			int yEnd = camY + 15;
			yEnd = yEnd > 85 ? 85 : yEnd;


			//for (int y = 0; y < 85; ++y)
			for (int y = yStart; y < yEnd; ++y) // for now, just part of the map
			//for (int y = 0; y < 55; ++y) // for now, just part of the map
			{
				//for (int x = 0; x < 85; ++x)
				for (int x = xStart; x < xEnd; ++x) // for now, just part of the map
				//for (int x = 0; x < 55; ++x) // for now, just part of the map
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
		int x = tileX * 3 + subtileX;
		int y = tileY * 3 + subtileY;
		glm::mat4 columnMatrix = glm::translate(glm::mat4(), glm::vec3((float)x, 0.0f, (float)y));

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

		// LIGHT LEVELS!
		columnMatrix[0][3] = lightMap[(y+1) * 255 + x];
		columnMatrix[1][3] = lightMap[y * 255 + x + 1];
		columnMatrix[2][3] = lightMap[(y-1) * 255 + x];
		columnMatrix[3][3] = lightMap[y * 255 + x - 1];
		/*
		columnMatrix[0][3] = 1.0f;
		columnMatrix[1][3] = 1.0f;
		columnMatrix[2][3] = 1.0f;
		columnMatrix[3][3] = 1.0f;
		*/

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
