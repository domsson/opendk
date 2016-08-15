#include "Column.hpp"

namespace OpenDK
{

	Column::Column()
	: cubes(new Cube[8])
	{
	}

	Column::~Column()
	{
		delete[] cubes;
	}

	bool Column::setCube(CubeType cubeType, int height)
	{
		if (height < 0 || height > 7)
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not set cube in column, "
					<< " invalid height value given (" << height << ")" << std::endl;
			return false;
		}

		cubes[height].create(cubeType); // = Cube(cubeType);
		return true;
	}

	const Cube* Column::getCube(int height) const
	{
		if (height < 0 || height > 7)
		{
			std::cerr << typeid(this).name() << ": [WRN] Could not get cube from column, "
					<< " invalid height value given (" << height << ")" << std::endl;
			return nullptr;
		}
		return cubes[height].getType() == CubeType::CUBE_UNDEFINED ? nullptr : &cubes[height];
	}

}
