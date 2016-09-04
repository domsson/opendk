#include "MapRenderer.hpp"

namespace OpenDK
{

	MapRenderer::MapRenderer()
	: sp(nullptr), sp2(nullptr), tex(nullptr), block(nullptr),
	  col(488), singleColMode(false)
	{
		light.setPosition(glm::vec3(114.0f, 2.0f, 130.0f));
		light.setIntensity(2.0f);
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
		glm::vec3 pos = light.getPosition();
		glm::vec3 move = glm::vec3(offsetX, offsetY, offsetZ);
		move = glm::rotateY(move, glm::radians(- camera.getRotation().y));

		pos = pos + move;
		light.setPosition(pos);
	}

	// Always puts the light one cube above the ground (or is supposed to)
	void MapRenderer::moveLight(float offsetX, float offsetZ)
	{
		glm::vec3 pos = light.getPosition();
		glm::vec3 move = glm::vec3(offsetX, pos.y, offsetZ);
		move = glm::rotateY(move, glm::radians(- camera.getRotation().y));

		pos = pos + move;
		pos.y = clm.getColumnHeight(dat.getColumnIndex(pos.x, pos.z)) + 1;
		light.setPosition(pos);
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

	void MapRenderer::debugLight() const
	{
		glm::vec3 lightPos = light.getPosition();
		std::cout << "light pos: " << lightPos.x << ", " << lightPos.y << ", " << lightPos.z << std::endl;
	}

	void MapRenderer::initDummyData()
	{
		// INIT CUBE SHADER
		sp2 = new ShaderProgram();
		sp2->addShader("./bin/shaders/cube.vert", GL_VERTEX_SHADER);
		sp2->addShader("./bin/shaders/cube.frag", GL_FRAGMENT_SHADER);
		sp2->bindAttribute(ShaderAttribute::POSITION, "in_Position");
		sp2->bindAttribute(ShaderAttribute::COLOR, "in_Color");
		sp2->bindAttribute(ShaderAttribute::TEXTURE, "in_Unwrap");
		sp2->bindAttribute(ShaderAttribute::NORMALS, "in_Normal");
		sp2->link();

		// INIT COLUMN SHADER
		sp = new ShaderProgram();
		sp->addShader("./bin/shaders/column.vert", GL_VERTEX_SHADER);
		sp->addShader("./bin/shaders/column.frag", GL_FRAGMENT_SHADER);
		sp->bindAttribute(ShaderAttribute::POSITION, "in_Position");
		sp->bindAttribute(ShaderAttribute::COLOR, "in_Color");
		sp->bindAttribute(ShaderAttribute::TEXTURE, "in_Unwrap");
		sp->bindAttribute(ShaderAttribute::NORMALS, "in_Normal");
		sp->link();
		sp->use();

		// INIT CUBE SPRITE SHEET
		tex = new Texture();
		tex->loadAtlas("./bin/textures/block0.bmp", 32, 32);
		glActiveTexture(GL_TEXTURE0);
		tex->bind();
		glUniform1i(sp->getUniformLocation("atlas"), 0);
		tex->unbind();

		// INIT CUBE GEOMETRY
		block = new BlockGeometry();

		// CAMERA INIT
		camera.setPosition(65.0f, 0.0f, 63.0f);
		camera.setRotation(45.0f, 45.0f, 0.0f);
		camera.setZoom(2.4f);

		// LOAD LEVEL DATA
		slb.load("./bin/levels/MAP00001.SLB");
		own.load("./bin/levels/MAP00001.OWN");
		clm.load("./bin/levels/MAP00001.CLM");
		dat.load("./bin/levels/MAP00001.DAT");
		tng.load("./bin/levels/MAP00001.TNG");
		cbd.load("./bin/data/CUBE.DAT");

		// INIT TORCHES (WE IGNORE EVERYTHING ELSE FOR NOW)
		int numThings = tng.getThingCount();
		int numLights = tng.getThingCount(1, 2);
		//lights = new Light[numLights]; // torches!
		std::cout << "NUM TORCHES FOUND: " << numLights << std::endl;

		//int gimme = 0;
		int torch = 0;

		for (int t = 0; t < numThings; ++t)
		{
			int type = tng.getThingType(t);
			if (type == 1) // item / decoration
			{
				int subtype = tng.getThingSubtype(t);
				if (subtype == 2) // torch
				{
					++torch;
					glm::vec3 loc = tng.getThingLocation(t);

					if (torch==1) { light1.setPosition(loc.x, loc.z, loc.y); }
					if (torch==2) { light2.setPosition(loc.x, loc.z, loc.y); }
					if (torch==3) { light3.setPosition(loc.x, loc.z, loc.y); }
					if (torch==4) { light4.setPosition(loc.x, loc.z, loc.y); }
					if (torch==5) { light5.setPosition(loc.x, loc.z, loc.y); }
					if (torch==6) { light6.setPosition(loc.x, loc.z, loc.y); }
					if (torch==7) { light7.setPosition(loc.x, loc.z, loc.y); }
					if (torch==8) { light8.setPosition(loc.x, loc.z, loc.y); }

					/*
					if (torch++ == gimme)
					{
						glm::vec3 loc = tng.getThingLocation(t);
						light2.setPosition(loc.x, loc.z, loc.y);
					}
					*/
				}
			}
		}

		light1.setRadius(6.5f);
		light2.setRadius(6.5f);
		light3.setRadius(6.5f);
		light4.setRadius(6.5f);
		light5.setRadius(6.5f);
		light6.setRadius(6.5f);
		light7.setRadius(6.5f);
		light8.setRadius(6.5f);

		light1.setIntensity(1.8f);
		light2.setIntensity(1.8f);
		light3.setIntensity(1.8f);
		light4.setIntensity(1.8f);
		light5.setIntensity(1.8f);
		light6.setIntensity(1.8f);
		light7.setIntensity(1.8f);
		light8.setIntensity(1.8f);

		/*
		for (int t = 0; t < numLights; ++t)
		{
			std::cout << "torch " << t << ": "
				<< lights[t].getPosition().x << ", "
				<< lights[t].getPosition().y << ", "
				<< lights[t].getPosition().z << std::endl;
		}

		std::cout << "torch " << gimme << ": "
				<< light2.getPosition().x << ", "
				<< light2.getPosition().y << ", "
				<< light2.getPosition().z << std::endl;
		*/

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

		std::cout << "col of interest: " << dat.getColumnIndex(160, 130) << std::endl;

		//
		// CUBES.DAT -> BUFFER TEXTURE -> GPU
		//
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

		glActiveTexture(GL_TEXTURE1); // 1
		glBindTexture(GL_TEXTURE_BUFFER, tboTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R16I, tbo);

		glUniform1i(sp->getUniformLocation("cubes"), 1); // 1

		glBindBuffer(GL_TEXTURE_BUFFER, 0);

		//
		// LIGHT MAP -> BUFFER TEXTURE -> GPU (YOU BETTER HAVE SOME VRAM)
		//
		//GLhalf lightTBOData[65025];
		// will have to set/update the light map data every frame.. ugh

		//GLuint tboLight;
		glGenBuffers(1, &tboLight);
		glBindBuffer(GL_TEXTURE_BUFFER, tboLight);
		glBufferData(GL_TEXTURE_BUFFER, sizeof(lightTBOData), lightTBOData, GL_STREAM_DRAW);

		glGenTextures(1, &tboLightTex);

		glActiveTexture(GL_TEXTURE2); // 2
		glBindTexture(GL_TEXTURE_BUFFER, tboLightTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, tboLight);

		glUniform1i(sp->getUniformLocation("light"), 2); // 2

		glBindBuffer(GL_TEXTURE_BUFFER, 0);


		//
		// VISIBILITY MAP -> BUFFER TEXTURE -> GPU (YES! WE EAT MORE VRAM)
		//

		//visibilityTBOData[];
		for (int z = 0; z < 85; ++z)
		{
			for (int x = 0; x < 85; ++x)
			{
				TileType  type  = slb.getTileType(x, z);
				TileOwner owner = own.getTileOwner(x, z);

				if (owner == TileOwner::PLAYER0)
				{
					visibilityTBOData[z*85+x] = 1;
					continue;
				}
				if (type ==TileType::PORTAL ||
					type == TileType::GOLD ||
					type == TileType::GEM)
				{
					visibilityTBOData[z*85+x] = 1;
					continue;
				}
				visibilityTBOData[z*85+x] = 0;
			}
		}

		glGenBuffers(1, &tboVisibility);
		glBindBuffer(GL_TEXTURE_BUFFER, tboVisibility);
		glBufferData(GL_TEXTURE_BUFFER, sizeof(visibilityTBOData), visibilityTBOData, GL_STREAM_DRAW);

		glGenTextures(1, &tboVisibilityTex);

		glActiveTexture(GL_TEXTURE3); // 3
		glBindTexture(GL_TEXTURE_BUFFER, tboVisibilityTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R8I, tboVisibility);

		glUniform1i(sp->getUniformLocation("visibility"), 3); // 3

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
		std::cout << "base block: " << (int)clm.getBaseBlockType(col) << std::endl;

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

	void MapRenderer::bakeLight(const Light& l)
	{
		int slab = ((int)l.getPosition().z / 3) * 85 + ((int)l.getPosition().x / 3);
		if (visibilityTBOData[slab] == 0)
		{
			return;
		}

		int column = dat.getColumnIndex((int)l.getPosition().x, (int)l.getPosition().z);
		if ((int)l.getPosition().y < 8) // the "hand of evil" light could be higher up!
		{
			bool solid = clm.cubeIsSolid(column, (int)l.getPosition().y);
			if (solid)
			{
				return;
			}
		}

		// http://gamedev.stackexchange.com/questions/56897/glsl-light-attenuation-color-and-intensity-formula
		float b = l.getIntensity() / (l.getRadius()*l.getRadius() * 0.1f);

		for (int z = (int)l.getPosition().z - (int)l.getRadius(); z < (int)l.getPosition().z + (int)l.getRadius(); ++z)
		{
			for (int x = (int)l.getPosition().x - (int)l.getRadius(); x < (int)l.getPosition().x + (int)l.getRadius(); ++x)
			{
				int slab = (z / 3) * 85 + (x / 3);
				if (visibilityTBOData[slab] == 0)
				{
					continue;
				}

				float xTerm = (float)x - l.getPosition().x;
				float zTerm = (float)z - l.getPosition().z;
				float distance = sqrt(xTerm * xTerm + zTerm * zTerm);

				if (distance < l.getRadius())
				{
					if (bresenham((int)l.getPosition().x, (int)l.getPosition().z, x, z, (int)l.getPosition().y))
					{
						// lightMap[z * 255 + x] += 1.0f - (distance / l.getRadius());
						//lightMap[z * 255 + x] += l.getIntensity() / (1.0 + b*distance*distance);
						lightTBOData[z * 255 + x] += l.getIntensity() / (1.0 + b*distance*distance);

						/*
						if (lightMap[z * 255 + x] > 1.0f)
						{
							lightMap[z * 255 + x] = 1.0f;
						}
						*/
					}
				}
			}
		}
	}

	void MapRenderer::render()
	{
		/*
		for (int i = 0; i < 255*255; ++i)
		{
			//lightMap[i] = 0.0f;
			lightTBOData[i] = 0.3f; // bit of ambient light
		}
		*/

		for (int z = 0; z < 255; ++z)
		{
			for (int x = 0; x < 255; ++x)
			{
				int slabZ = z / 3;
				int slabX = x / 3;

				if (visibilityTBOData[slabZ * 85 + slabX])
				{
					lightTBOData[z*255+x] = 0.3f; // bit of ambient light
				}
				else
				{
					lightTBOData[z*255+x] = 0.0f; // nothing
				}
			}
		}

		float wurst = 300.0f;
		light1.setIntensity(1.8f + ((std::rand() % 100) / wurst) - 0.5);
		light2.setIntensity(1.8f + ((std::rand() % 100) / wurst) - 0.5);
		light3.setIntensity(1.8f + ((std::rand() % 100) / wurst) - 0.5);
		light4.setIntensity(1.8f + ((std::rand() % 100) / wurst) - 0.5);
		light5.setIntensity(1.8f + ((std::rand() % 100) / wurst) - 0.5);
		light6.setIntensity(1.8f + ((std::rand() % 100) / wurst) - 0.5);
		light7.setIntensity(1.8f + ((std::rand() % 100) / wurst) - 0.5);
		light8.setIntensity(1.8f + ((std::rand() % 100) / wurst) - 0.5);

		bakeLight(light);
		bakeLight(light1);
		bakeLight(light2);
		bakeLight(light3);
		bakeLight(light4);
		bakeLight(light5);
		bakeLight(light6);
		bakeLight(light7);
		bakeLight(light8);

		/*
		for (int z = 0; z < 85; ++z)
		{
			for (int x = 0; x < 85; ++x)
			{
				TileType  type  = slb.getTileType(x, z);
				TileOwner owner = own.getTileOwner(x, z);

				if (owner != TileOwner::PLAYER0 &&
					!(type == TileType::PORTAL ||
					  type == TileType::GOLD ||
					  type == TileType::GEM))
				{
					for (int cz = 0; cz < 3; ++cz)
					{
						for (int cx = 0; cx < 3; ++cx)
						{
							int columnIndex = (z * 3 + cz) * 255 + (x * 3 + cx);
							if (lightTBOData[columnIndex] == 0)
							{
								lightTBOData[columnIndex] = -0.3f;
							}
						}
					}
				}
			}
		}
		*/

		// send upated light map to GPU
		glBindBuffer(GL_TEXTURE_BUFFER, tboLight);
		glBufferSubData(GL_TEXTURE_BUFFER, 0, sizeof(lightTBOData), &lightTBOData);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);

		camera.update();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		sp->use();

		glActiveTexture(GL_TEXTURE0);
		tex->bind();

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, tboTex);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_BUFFER, tboLightTex);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_BUFFER, tboVisibilityTex);

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
			int camZ = camera.getPosition().z * 2 / 3;

			int xStart = camX - 15;
			xStart = xStart < 0 ? 0 : xStart;

			int zStart = camZ - 15;
			zStart = zStart < 0 ? 0 : zStart;

			int xEnd = camX + 15;
			xEnd = xEnd > 85 ? 85 : xEnd;

			int zEnd = camZ + 15;
			zEnd = zEnd > 85 ? 85 : zEnd;


			//for (int y = 0; y < 85; ++y)
			for (int z = zStart; z < zEnd; ++z) // for now, just part of the map
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
							renderColumn(vao, x, z, c, r);
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

	void MapRenderer::renderCube(const VertexArrayObject& vao, int x, int z, int cube)
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(), glm::vec3((float)x, 0.0f, (float)z));
		//glm::mat4 modelMatrix = glm::translate(glm::mat4(), glm::vec3((float)x, (float)y, 0.0f));
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

	void MapRenderer::renderColumn(const VertexArrayObject& vao, int tileX, int tileZ, int subtileX, int subtileZ, int column)
	{
		if (column == -1)
		{
			column = dat.getColumnIndex(tileX, tileZ, subtileX, subtileZ);
		}
		int x = tileX * 3 + subtileX;
		int z = tileZ * 3 + subtileZ;
		glm::mat4 columnMatrix = glm::translate(glm::mat4(), glm::vec3((float)x, 0.0f, (float)z));
		//glm::mat4 columnMatrix = glm::translate(glm::mat4(), glm::vec3((float)x, (float)y, 0.0f));

		// mat4[col][row]
		columnMatrix[0][0] = (int)clm.getBaseBlockType(column);
		columnMatrix[0][1] = clm.getCubeType(column, 0);
		columnMatrix[0][2] = clm.getCubeType(column, 1);
		columnMatrix[1][0] = clm.getCubeType(column, 2);
		columnMatrix[1][1] = clm.getCubeType(column, 3);
		columnMatrix[1][2] = clm.getCubeType(column, 4);
		columnMatrix[2][0] = clm.getCubeType(column, 5);
		columnMatrix[2][1] = clm.getCubeType(column, 6);
		columnMatrix[2][2] = clm.getCubeType(column, 7);

		// LIGHT LEVELS!
		columnMatrix[0][3] = getLightLevelAt(x, z, 0);
		columnMatrix[1][3] = getLightLevelAt(x, z, 1);
		columnMatrix[2][3] = getLightLevelAt(x, z, 2);
		columnMatrix[3][3] = getLightLevelAt(x, z, 3);

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

	// side: 0=front, 1=right, 2=back, 3=left
	float MapRenderer::getLightLevelAt(int x, int z, int side) const
	{
		int i;

		switch (side)
		{
			case 0:
			i = (z+1) * 255 + x;
			break;
			case 1:
			i = z * 255 + x + 1;
			break;
			case 2:
			i = (z-1) * 255 + x;
			break;
			case 3:
			i = z * 255 + x - 1;
			break;
			default:
			i = (z+1) * 255 + x;
		}

		//return (i < 0 || i >= 255*255) ? 0.0f : lightMap[i];
		return (i < 0 || i >= 255*255) ? 0.0f : lightTBOData[i];
	}

	bool MapRenderer::bresenham(int x1, int y1, int const x2, int const y2, int lightHeight)
	{
		int delta_x(x2 - x1);
		// if x1 == x2, then it does not matter what we set here
		signed char const ix((delta_x > 0) - (delta_x < 0));
		delta_x = std::abs(delta_x) << 1;

		int delta_y(y2 - y1);
		// if y1 == y2, then it does not matter what we set here
		signed char const iy((delta_y > 0) - (delta_y < 0));
		delta_y = std::abs(delta_y) << 1;

		//plot(x1, y1);
		// TODO
		int column = dat.getColumnIndex(x1, y1);
		int height = clm.getColumnHeight(column);
		if (height > lightHeight) { return false; }
		//if (height > 1) { return false; }

		if (delta_x >= delta_y)
		{
			// error may go below zero
			int error(delta_y - (delta_x >> 1));

			while (x1 != x2)
			{
				if ((error >= 0) && (error || (ix > 0)))
				{
					error -= delta_x;
					y1 += iy;
				}
				// else do nothing

				error += delta_y;
				x1 += ix;

				//plot(x1, y1);
				// TODO
				int column = dat.getColumnIndex(x1, y1);
				int height = clm.getColumnHeight(column);
				if (height > lightHeight) { return false; }
				//if (height > 1) { return false; }
			}
		}
		else
		{
			// error may go below zero
			int error(delta_x - (delta_y >> 1));

			while (y1 != y2)
			{
				if ((error >= 0) && (error || (iy > 0)))
				{
					error -= delta_y;
					x1 += ix;
				}
				// else do nothing

				error += delta_x;
				y1 += iy;

				//plot(x1, y1);
				// TODO
				int column = dat.getColumnIndex(x1, y1);
				int height = clm.getColumnHeight(column);
				if (height > lightHeight) { return false; }
				//if (height > 1) { return false; }
			}
		}

		return true; // yes, you can put some light there
	}

	/*
	// https://gist.github.com/yamamushi/5823518
	void MapRenderer::Bresenham3D(int x1, int y1, int z1, const int x2, const int y2, const int z2, WorldMap *output, int symbol)
	{
		int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
		int point[3] = { x1, y1, z1 };

		dx = x2 - x1;
		dy = y2 - y1;
		dz = z2 - z1;
		x_inc = (dx < 0) ? -1 : 1;
		l = abs(dx);
		y_inc = (dy < 0) ? -1 : 1;
		m = abs(dy);
		z_inc = (dz < 0) ? -1 : 1;
		n = abs(dz);
		dx2 = l << 1;
		dy2 = m << 1;
		dz2 = n << 1;

		if ((l >= m) && (l >= n)) {
			err_1 = dy2 - l;
			err_2 = dz2 - l;
			for (i = 0; i < l; i++) {
				output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
				if (err_1 > 0) {
					point[1] += y_inc;
					err_1 -= dx2;
				}
				if (err_2 > 0) {
					point[2] += z_inc;
					err_2 -= dx2;
				}
				err_1 += dy2;
				err_2 += dz2;
				point[0] += x_inc;
			}
		} else if ((m >= l) && (m >= n)) {
			err_1 = dx2 - m;
			err_2 = dz2 - m;
			for (i = 0; i < m; i++) {
				output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
				if (err_1 > 0) {
					point[0] += x_inc;
					err_1 -= dy2;
				}
				if (err_2 > 0) {
					point[2] += z_inc;
					err_2 -= dy2;
				}
				err_1 += dx2;
				err_2 += dz2;
				point[1] += y_inc;
			}
		} else {
			err_1 = dy2 - n;
			err_2 = dx2 - n;
			for (i = 0; i < n; i++) {
				output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
				if (err_1 > 0) {
					point[1] += y_inc;
					err_1 -= dz2;
				}
				if (err_2 > 0) {
					point[0] += x_inc;
					err_2 -= dz2;
				}
				err_1 += dy2;
				err_2 += dx2;
				point[2] += z_inc;
			}
		}
		output->getTileAt(point[0], point[1], point[2])->setSymbol(symbol);
	}
	*/

}
