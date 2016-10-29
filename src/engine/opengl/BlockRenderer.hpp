#pragma once

#include <cmath>		// std::abs(), std::floor(), ...
#include <cstdlib>		// std::rand()
#include <iomanip>		// std::setw()
#include <vector>

#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "TextureBufferObject.hpp"
#include "CubeGeometry.hpp"
#include "Camera.hpp"

#include "../level/SlabFile.hpp"
#include "../level/CubeDataFile.hpp"
#include "../level/ColumnFile.hpp"
#include "../level/OwnerFile.hpp"
#include "../level/ColumnFile.hpp"
#include "../level/ColumnDataFile.hpp"
#include "../level/ThingFile.hpp"
#include "../level/CubeSide.hpp"
#include "../level/Light.hpp"

namespace OpenDK
{

	class BlockRenderer
	{
	public:

		BlockRenderer();
		~BlockRenderer();

		void init();
		void update();
		void render();

		void moveLight(float offsetX, float offsetY, float offsetZ);
		void moveLight(float offsetX, float offsetZ);
		void moveCam(float offsetX, float offsetY, float offsetZ = 0.0f);
		void rotateCam(float rotX, float rotY, float rotZ);
		void zoomCam(float zoomChange);
		void debugCamCoords() const;
		void debugDAT() const;
		void debugLight() const;

	private:

		ShaderProgram sp;
		Texture tex;
		CubeGeometry cube;

		SlabFile slb;
		OwnerFile own;
		ColumnFile clm;
		ColumnDataFile dat;
		CubeDataFile cbd;
		ThingFile tng;

		sf::Clock clock;

		Camera camera;

		TextureBufferObject tboCubes;

		TextureBufferObject tboColumns;
		GLshort columnsTBOData[9*2048]; // 18432

		TextureBufferObject tboLight;
		GLfloat lightTBOData[65025];

		TextureBufferObject tboVisibility;
		GLbyte visibilityTBOData[7225];

		std::vector<Light> lights;
		Light light;

		glm::mat4 modelMatrix;
		glm::vec3 camPosBefore;

		void updateLight();
		void renderBlock(const VertexArrayObject& vao, int slabX, int slabZ);
		float getLightLevelAt(int x, int z, int side) const;
		void bakeLight(const Light& l);
		bool bresenham(int x1, int y1, int const x2, int const y2, int lightHeight);
	};

}
