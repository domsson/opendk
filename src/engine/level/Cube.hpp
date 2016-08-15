#pragma once

#include "CubeType.hpp"
#include "../opengl/CubeGeometry.hpp"

namespace OpenDK
{

	class Cube
	{
	public:

		Cube();

		Cube(CubeType type);

		void create(CubeType type);

		CubeType getType() const;
		const CubeGeometry& getGeometry() const;

	private:

		CubeType type;
		CubeGeometry geom;

		void texOffset(int& x, int& y) const;

	};

}
