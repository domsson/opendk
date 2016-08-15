#pragma once

#include <iostream>
#include <typeinfo>

#include "Cube.hpp"
#include "CubeType.hpp"
#include "../opengl/CubeGeometry.hpp"

namespace OpenDK
{

	class Column
	{
	public:

		Column();

		~Column();

		bool setCube(CubeType cubeType, int height);

		const Cube* getCube(int height) const;

	private:

		Cube* cubes;

	};

}
