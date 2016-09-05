#pragma once

#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"

namespace OpenDK
{

	class CubeGeometry
	{
	public:

		CubeGeometry();

		void create();

		const VertexArrayObject& getVAO() const;

	private:

		VertexArrayObject vao;

	};

}
