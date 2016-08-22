#pragma once

#include <cmath>

#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include "../level/Map.hpp"
#include "../level/SlabFile.hpp"
#include "../level/CubeDataFile.hpp"
#include "../level/ColumnFile.hpp"
#include "../level/OwnerFile.hpp"
#include "../level/ColumnFile.hpp"
#include "../level/ColumnDataFile.hpp"
#include "../level/CubeSide.hpp"
#include "BlockGeometry.hpp"

namespace OpenDK
{

	class MapRenderer
	{
	public:

		MapRenderer();
		~MapRenderer();

		void initDummyData();
		void render();

		// TODO remove this later, just dirty coding for now
		void moveCam(float offsetX, float offsetY, float offsetZ = 0.0f);
		void zoomCam(float zoomChange);
		void debugCamCoords() const;

	private:
		ShaderProgram* sp;
		Texture* tex;
		BlockGeometry* block;

		SlabFile slb;
		ColumnFile clm;
		ColumnDataFile dat;
		CubeDataFile cbd;

		sf::Clock clock;

		Camera camera;

		glm::mat4 modelMatrix;

		void renderBlock(const VertexArrayObject& vao, int tileX, int tileY, int blockX, int blockY);
		void renderCube(const VertexArrayObject& vao, int tileX, int tileY, int cubeX, int cubeY, int cubeZ, std::int16_t cubeIndex);
		int getSuitableSprite(TileType tileType) const;

	};

}
