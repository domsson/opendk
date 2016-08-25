#pragma once

#include <cmath>
//#include <iomanip>		// setw

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
		void rotateCam(float rotX, float rotY, float rotZ);
		void zoomCam(float zoomChange);
		void debugCamCoords() const;
		void nextCol();
		void prevCol();
		void debugDAT() const;
		void debugCol() const;
		void switchMode();

	private:
		ShaderProgram* sp;
		ShaderProgram* sp2;
		Texture* tex;
		BlockGeometry* block;

		SlabFile slb;
		ColumnFile clm;
		ColumnDataFile dat;
		CubeDataFile cbd;

		std::int16_t col;

		GLuint tboTex;

		sf::Clock clock;

		Camera camera;

		bool singleColMode;

		glm::mat4 modelMatrix;
		glm::vec3 camPosBefore;

		void renderColumn(const VertexArrayObject& vao, int tileX, int tileY, int subtileX, int subtileY, int column = -1);
		void renderCube(const VertexArrayObject& vao, int x, int y, int cube);
	};

}
