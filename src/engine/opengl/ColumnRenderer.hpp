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

#include "../level/CubeDataFile.hpp"
#include "../level/ColumnFile.hpp"
#include "../level/ColumnFile.hpp"
#include "../level/ColumnDataFile.hpp"
#include "../level/CubeSide.hpp"

namespace OpenDK
{

	class ColumnRenderer
	{
	public:

		ColumnRenderer();
		~ColumnRenderer();

		void init();
		void update();
		void render();

		void moveCam(float offsetX, float offsetY, float offsetZ = 0.0f);
		void rotateCam(float rotX, float rotY, float rotZ);
		void zoomCam(float zoomChange);
		void debugCamCoords() const;
		void nextCol();
		void prevCol();
		void debugDAT() const;
		void debugCol() const;

	private:

		ShaderProgram* sp;
		Texture* tex;
		CubeGeometry* cube;

		ColumnFile clm;
		ColumnDataFile dat;
		CubeDataFile cbd;

		std::int16_t col;

		GLuint tboTex;

		sf::Clock clock;

		Camera camera;

		TextureBufferObject tboCubes;

		glm::mat4 modelMatrix;
		glm::vec3 camPosBefore;

		void renderColumn(const VertexArrayObject& vao, int tileX, int tileZ, int subtileX, int subtileZ, int column = -1);

	};

}
