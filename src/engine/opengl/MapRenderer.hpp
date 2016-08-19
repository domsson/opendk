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
#include "../level/OwnerFile.hpp"
#include "../level/ColumnFile.hpp"
#include "../level/ColumnDataFile.hpp"
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

	private:
		ShaderProgram* sp;
		Texture* tex;
		Texture* atlas;
		Map* map;

		BlockGeometry* block;

		SlabFile slb;

		sf::Clock clock;

		Camera camera;

		glm::mat4 modelMatrix;

		void renderBlock(const VertexArrayObject& vao, int x, int y);
		int getSuitableSprite(TileType tileType) const;

	};

}
