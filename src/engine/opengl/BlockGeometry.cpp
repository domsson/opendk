#include "BlockGeometry.hpp"

namespace OpenDK
{

	BlockGeometry::BlockGeometry()
	{
		create();
	}

	void BlockGeometry::create()
	{
		VertexBufferObject vboPos;
		VertexBufferObject vboCol;
		VertexBufferObject vboUvw;
		IndexBufferObject ibo;

		GLfloat vertices[] = {
			// TOP
			-0.5f,  0.5f,  0.5f,	// 16 (=3)
			 0.5f,  0.5f,  0.5f,	// 17 (=2)
			 0.5f,  0.5f, -0.5f,	// 18 (=6)
			-0.5f,  0.5f, -0.5f,	// 19 (=10)

			// FRONT
			-0.5f, -0.5f,  0.5f,	// 0: bottom left front
			 0.5f, -0.5f,  0.5f,	// 1: bottom right front
			 0.5f,  0.5f,  0.5f,	// 2: top right front
			-0.5f,  0.5f,  0.5f,	// 3: top left front

			// RIGHT
			 0.5f, -0.5f,  0.5f,	// 4 (=1)
			 0.5f, -0.5f, -0.5f,	// 5
			 0.5f,  0.5f, -0.5f,	// 6
			 0.5f,  0.5f,  0.5f,	// 7 (=2)

			// BACK
			 0.5f, -0.5f, -0.5f,	// 8 (=5)
			-0.5f, -0.5f, -0.5f,	// 9
			-0.5f,  0.5f, -0.5f,	// 10
			 0.5f,  0.5f, -0.5f,	// 11 (=6)

			// LEFT
			-0.5f, -0.5f, -0.5f,	// 12 (=9)
			-0.5f, -0.5f,  0.5f,	// 13 (=0)
			-0.5f,  0.5f,  0.5f,	// 14 (=3)
			-0.5f,  0.5f, -0.5f		// 15 (=10)

			/*
			// BOTTOM
			-0.5f, -0.5f, -0.5f,	// 20 (=9)
			 0.5f, -0.5f, -0.5f,	// 21 (=5)
			 0.5f, -0.5f,  0.5f,	// 22 (=1)
			-0.5f, -0.5f,  0.5f		// 23 (=0)
			*/
		};

		GLubyte colors[60];

		for (int i = 0; i < 60; ++i)
		{
			colors[i] = 255;
		}

		GLfloat unwrap[] = {
			0.0f, 1.0f,	// 0: bottom left front
			1.0f, 1.0f,	// 1: bottom right front
			1.0f, 0.0f,	// 2: top right front
			0.0f, 0.0f,	// 3: top left front

			0.0f, 1.0f,	// 0: bottom left front
			1.0f, 1.0f,	// 1: bottom right front
			1.0f, 0.0f,	// 2: top right front
			0.0f, 0.0f,	// 3: top left front

			0.0f, 1.0f,	// 0: bottom left front
			1.0f, 1.0f,	// 1: bottom right front
			1.0f, 0.0f,	// 2: top right front
			0.0f, 0.0f,	// 3: top left front

			0.0f, 1.0f,	// 0: bottom left front
			1.0f, 1.0f,	// 1: bottom right front
			1.0f, 0.0f,	// 2: top right front
			0.0f, 0.0f,	// 3: top left front

			0.0f, 1.0f,	// 0: bottom left front
			1.0f, 1.0f,	// 1: bottom right front
			1.0f, 0.0f,	// 2: top right front
			0.0f, 0.0f	// 3: top left front

			/*
			0.0f, 1.0f,	// 0: bottom left front
			1.0f, 1.0f,	// 1: bottom right front
			1.0f, 0.0f,	// 2: top right front
			0.0f, 0.0f	// 3: top left front
			*/
		};

		GLuint indices[] = {
			 0,  1,  2,  2,  3,  0,	// Top side
			 4,  5,  6,  6,  7,  4,	// Front side
			 8,  9, 10, 10, 11,  8,	// Right side
			12, 13, 14, 14, 15, 12, // Back side
			16, 17, 18, 18, 19, 16,	// Left side
			// 20, 21, 22, 22, 23, 20	// Bottom side
		};

		vboPos.setData(vertices, sizeof(vertices));
		vboCol.setData(colors, sizeof(colors));
		vboUvw.setData(unwrap, sizeof(unwrap));
		vboUvw.setChunkSize(2);

		ibo.setData(indices, sizeof(indices));

		vao.addVBO(vboPos, ShaderAttribute::POSITION);
		vao.addVBO(vboCol, ShaderAttribute::COLOR);
		vao.addVBO(vboUvw, ShaderAttribute::TEXTURE);
		vao.setIBO(ibo);
	}

	const VertexArrayObject& BlockGeometry::getVAO() const
	{
		return vao;
	}

}