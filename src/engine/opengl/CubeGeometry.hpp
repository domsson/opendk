#pragma once

#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"

namespace OpenDK
{

	class CubeGeometry
	{
	public:

		// TODO these two clearly don't belong here;
		// the approaching deadline makes me write horrible code :(
		static const unsigned int SPRITESHEET_WIDTH;
		static const unsigned int SPRITESHEET_HEIGHT;
		static const unsigned int SPRITE_WIDTH;
		static const unsigned int SPRITE_HEIGHT;

		CubeGeometry();

		CubeGeometry(int s, int t);

		void create(int s, int t);

		const VertexArrayObject& getVAO() const;

		const GLfloat* getTexCoords() const;

	private:

		VertexArrayObject vao;
		GLfloat texCoords[4];
	};

}
