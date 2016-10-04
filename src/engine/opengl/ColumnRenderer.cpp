#include "ColumnRenderer.hpp"

namespace OpenDK
{

	ColumnRenderer::ColumnRenderer()
	: sp(nullptr), tex(nullptr), cube(nullptr), col(488)
	{
	}

	ColumnRenderer::~ColumnRenderer()
	{
		tex->free();
		delete sp;
		delete tex;
		delete cube;
	}

	void ColumnRenderer::moveCam(float offsetX, float offsetY, float offsetZ)
	{
		glm::vec3 pos = camera.getPosition();
		glm::vec3 move = glm::vec3(offsetX, offsetY, offsetZ);
		move = glm::rotateY(move, glm::radians(- camera.getRotation().y));

		pos = pos + move;
		camera.setPosition(pos);
	}

	void ColumnRenderer::rotateCam(float rotX, float rotY, float rotZ)
	{
		glm::vec3 rot = camera.getRotation();
		camera.setRotation(glm::vec3(rot.x + rotX, rot.y + rotY, rot.z + rotZ));
	}

	void ColumnRenderer::zoomCam(float zoomChange)
	{
		camera.setZoom(camera.getZoom() + zoomChange);
	}

	void ColumnRenderer::debugCamCoords() const
	{
		glm::vec3 camPos = camera.getPosition();
		std::cout << "cam pos: " << camPos.x << ", " << camPos.y << ", " << camPos.z << std::endl;
		glm::vec3 camRot = camera.getRotation();
		std::cout << "cam rot: " << camRot.x << ", " << camRot.y << ", " << camRot.z << std::endl;
		float camZoom = camera.getZoom();
		std::cout << "cam zoom: " << camZoom << std::endl;
	}

	void ColumnRenderer::init()
	{
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
		cube = new CubeGeometry();

		// CAMERA INIT
		camera.setPosition(65.0f, 0.0f, 63.0f);
		camera.setRotation(45.0f, 45.0f, 0.0f);
		camera.setZoom(2.4f);

		// LOAD LEVEL DATA
		//slb.load("./bin/levels/MAP00001.SLB");
		//own.load("./bin/levels/MAP00001.OWN");
		clm.load("./bin/levels/MAP00001.CLM");
		dat.load("./bin/levels/MAP00001.DAT");
		cbd.load("./bin/data/CUBE.DAT");

		//
		// CUBES.DAT -> GPU
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
		glUniform1i(sp->getUniformLocation("cubes"), 1);
	}

	void ColumnRenderer::nextCol()
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

	void ColumnRenderer::prevCol()
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

	void ColumnRenderer::debugDAT() const
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

	void ColumnRenderer::debugCol() const
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

	void ColumnRenderer::update()
	{
		camera.update();
	}

	void ColumnRenderer::render()
	{
		sp->use();

		glActiveTexture(GL_TEXTURE0);
		tex->bind();

		glActiveTexture(GL_TEXTURE1);
		tboCubes.bindTexture();

		glUniformMatrix4fv(sp->getUniformLocation("viewMatrix"),       1, GL_FALSE, camera.getViewMatrixPtr());
		glUniformMatrix4fv(sp->getUniformLocation("projectionMatrix"), 1, GL_FALSE, camera.getProjectionMatrixPtr());

		VertexArrayObject vao = cube->getVAO();
		vao.bind();

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

		vao.unbind();
	}

	void ColumnRenderer::renderColumn(const VertexArrayObject& vao, int tileX, int tileZ, int subtileX, int subtileZ, int column)
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

		glUniformMatrix4fv(sp->getUniformLocation("columnInfo"), 1, GL_FALSE, glm::value_ptr(columnMatrix));

		if (vao.hasIBO())
		{
			glDrawElementsInstanced(GL_TRIANGLES, vao.getIBO()->getSize(), GL_UNSIGNED_INT, 0, 9);
		}
		else // We *know* all cubes have an IBO, but better be safe than sorry
		{
			glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 9);
		}
	}

}
