#pragma once

#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"

namespace OpenDK
{

	class BlockGeometry
	{
	public:

		BlockGeometry();

		void create();

		const VertexArrayObject& getVAO() const;

	private:

		VertexArrayObject vao;

	};

}
