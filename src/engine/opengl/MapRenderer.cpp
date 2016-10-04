#include "MapRenderer.hpp"

namespace OpenDK
{

	MapRenderer::MapRenderer()
	: cube(nullptr)
	{
	}

	MapRenderer::~MapRenderer()
	{
		tex.free();
		delete cube;
	}

	void MapRenderer::moveLight(float offsetX, float offsetY, float offsetZ)
	{
		glm::vec3 pos = light.getPosition();
		glm::vec3 move = glm::vec3(offsetX, offsetY, offsetZ);
		move = glm::rotateY(move, glm::radians(- camera.getRotation().y));

		pos = pos + move;
		light.setPosition(pos);
	}

	// Always puts the light one cube above the ground
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

	void MapRenderer::init()
	{
		// INIT COLUMN SHADER
		sp.init();
		sp.addShader("./bin/shaders/block.vert", GL_VERTEX_SHADER);
		sp.addShader("./bin/shaders/block.frag", GL_FRAGMENT_SHADER);
		sp.bindAttribute(ShaderAttribute::POSITION, "in_Position");
		sp.bindAttribute(ShaderAttribute::COLOR,    "in_Color");
		sp.bindAttribute(ShaderAttribute::TEXTURE,  "in_Unwrap");
		sp.bindAttribute(ShaderAttribute::NORMALS,  "in_Normal");
		sp.link();
		sp.use();

		// INIT CUBE SPRITE SHEET
		tex.loadAtlas("./bin/textures/block0.bmp", 32, 32);
		//glActiveTexture(GL_TEXTURE0);
		//tex.bind();
		glUniform1i(sp.getUniformLocation("atlas"), 0);
		//glUniform1i(sp->getUniformLocation("atlas"), 0);
		//tex.unbind();

		// INIT CUBE GEOMETRY
		cube = new CubeGeometry();

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
		std::cout << "Number of torches found: " << numLights << std::endl;

		for (int t = 0; t < numThings; ++t)
		{
			int type = tng.getThingType(t);
			if (type == 1) // item / decoration
			{
				int subtype = tng.getThingSubtype(t);
				if (subtype == 2) // torch
				{
					glm::vec3 loc = tng.getThingLocation(t);

					Light l;
					l.setPosition(loc.x, loc.z, loc.y);
					l.setRadius(6.5f);
					l.setIntensity(1.8f);
					lights.push_back(l);
				}
			}
		}

		// INIT LIGHT (HAND OF EVIL)
		light.setPosition(glm::vec3(114.0f, 2.0f, 130.0f));
		light.setIntensity(2.0f);
		light.setRadius(9.0f);

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

		tboCubes.setDrawType(GL_STATIC_DRAW);
		tboCubes.setData(cubesTBOData, sizeof(cubesTBOData));
		glUniform1i(sp.getUniformLocation("cubes"), 1);

		//
		// LIGHT MAP -> BUFFER TEXTURE -> GPU (YOU BETTER HAVE SOME VRAM)
		// will have to set/update the light map data every frame.. ugh
		//
		tboLight.setDrawType(GL_STREAM_DRAW);
		tboLight.setData(lightTBOData, sizeof(lightTBOData));
		glUniform1i(sp.getUniformLocation("light"), 2);

		//
		// VISIBILITY MAP -> BUFFER TEXTURE -> GPU (YES! WE EAT MORE VRAM)
		//
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

		tboVisibility.setDrawType(GL_STREAM_DRAW);
		tboVisibility.setData(visibilityTBOData, sizeof(visibilityTBOData));
		glUniform1i(sp.getUniformLocation("visibility"), 3);

		//
		// COLUMN MAP -> BUFFER TEX -> GPU (OOOOOH BOY)
		//
		for (size_t col = 0; col < 2048; ++col)
		{
			columnsTBOData[(col * 9)] = (GLshort) clm.getBaseBlockType(col);

			for (size_t cube = 0; cube < 8; ++cube)
			{
				columnsTBOData[(col * 9) + cube + 1] = (GLshort) clm.getCubeType(col, cube);
			}
		}

		tboColumns.setDrawType(GL_STATIC_DRAW);
		tboColumns.setData(columnsTBOData, sizeof(columnsTBOData));
		glUniform1i(sp.getUniformLocation("columns"), 4);

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
						lightTBOData[z * 255 + x] += l.getIntensity() / (1.0 + b*distance*distance);
					}
				}
			}
		}
	}

	void MapRenderer::update()
	{
		updateLight();
		camera.update();
	}

	void MapRenderer::updateLight()
	{
		// Reset / initialize the light map
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

		// Every WIP source code needs at least one 'wurst' variable
		float wurst = 500.0f;

		for (size_t i = 0; i < lights.size(); ++i)
		{
			lights[i].setIntensity(1.8f + ((std::rand() % 100) / wurst) - 0.5);
			bakeLight(lights[i]);
		}

		bakeLight(light);
		tboLight.updateData(&lightTBOData);
	}

	void MapRenderer::render()
	{
		// scale, rotate, translate (note: glm operations should be in reverse!)

		sp.use();

		glActiveTexture(GL_TEXTURE0);
		tex.bind();

		glActiveTexture(GL_TEXTURE1);
		tboCubes.bindTexture();

		glActiveTexture(GL_TEXTURE2);
		tboLight.bindTexture();

		glActiveTexture(GL_TEXTURE3);
		tboVisibility.bindTexture();

		glActiveTexture(GL_TEXTURE4);
		tboColumns.bindTexture();

		glUniformMatrix4fv(sp.getUniformLocation("viewMatrix"),       1, GL_FALSE, camera.getViewMatrixPtr());
		glUniformMatrix4fv(sp.getUniformLocation("projectionMatrix"), 1, GL_FALSE, camera.getProjectionMatrixPtr());

		VertexArrayObject vao = cube->getVAO();
		vao.bind();


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


		for (int z = zStart; z < zEnd; ++z)
		{
			for (int x = xStart; x < xEnd; ++x)
			{
				renderBlock(vao, x, z);
			}
		}

		vao.unbind();
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

		glUniformMatrix4fv(sp.getUniformLocation("columnInfo"), 1, GL_FALSE, glm::value_ptr(columnMatrix));

		if (vao.hasIBO())
		{
			glDrawElementsInstanced(GL_TRIANGLES, vao.getIBO()->getSize(), GL_UNSIGNED_INT, 0, 9);
		}
		else // We *know* all cubes have an IBO, but better be safe than sorry
		{
			glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 9);
		}
	}

	void MapRenderer::renderBlock(const VertexArrayObject& vao, int slabX, int slabZ)
	{
		int x = slabX * 3;
		int z = slabZ * 3;

		glm::mat4 columnMatrix = glm::translate(glm::mat4(), glm::vec3((float)x, 0.0f, (float)z));

		// mat4[col][row]
		columnMatrix[0][0] = dat.getColumnIndex(slabX, slabZ, 0, 0);
		columnMatrix[0][1] = dat.getColumnIndex(slabX, slabZ, 0, 1);
		columnMatrix[0][2] = dat.getColumnIndex(slabX, slabZ, 0, 2);
		columnMatrix[1][0] = dat.getColumnIndex(slabX, slabZ, 1, 0);
		columnMatrix[1][1] = dat.getColumnIndex(slabX, slabZ, 1, 1);
		columnMatrix[1][2] = dat.getColumnIndex(slabX, slabZ, 1, 2);
		columnMatrix[2][0] = dat.getColumnIndex(slabX, slabZ, 2, 0);
		columnMatrix[2][1] = dat.getColumnIndex(slabX, slabZ, 2, 1);
		columnMatrix[2][2] = dat.getColumnIndex(slabX, slabZ, 2, 2);

		glUniformMatrix4fv(sp.getUniformLocation("columnInfo"), 1, GL_FALSE, glm::value_ptr(columnMatrix));

		if (vao.hasIBO())
		{
			glDrawElementsInstanced(GL_TRIANGLES, vao.getIBO()->getSize(), GL_UNSIGNED_INT, 0, (1+8)*9); // (base block + 8 cubes) * 9 columns
		}
		else // We *know* all cubes have an IBO, but better be safe than sorry
		{
			glDrawArraysInstanced(GL_TRIANGLES, 0, 3, (1+8)*9); // (base block + 8 cubes) * 9 columns
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
		int column = dat.getColumnIndex(x1, y1);
		int height = clm.getColumnHeight(column);
		if (height > lightHeight) { return false; }

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
				int column = dat.getColumnIndex(x1, y1);
				int height = clm.getColumnHeight(column);
				if (height > lightHeight) { return false; }
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
				int column = dat.getColumnIndex(x1, y1);
				int height = clm.getColumnHeight(column);
				if (height > lightHeight) { return false; }
			}
		}

		return true; // yes, you can put some light there
	}

}
