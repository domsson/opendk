#include "Cube.hpp"

namespace OpenDK
{

	Cube::Cube()
	: type(CubeType::CUBE_UNDEFINED)
	{
	}

	Cube::Cube(CubeType type)
	: type(type)
	{
		create(type);
	}

	void Cube::create(CubeType type)
	{
		this->type = type;
		int x, y;
		texOffset(x, y);
		geom.create(x, y);
	}

	CubeType Cube::getType() const
	{
		return type;
	}

	const CubeGeometry& Cube::getGeometry() const
	{
		return geom;
	}

	void Cube::texOffset(int& x, int& y) const
	{
		switch (type)
		{
			case CubeType::PATH_1:
				x = 96;
				y = 96;
				break;
			case CubeType::EARTH_1:
			case CubeType::EARTH_2:
			case CubeType::EARTH_3:
			case CubeType::EARTH_4:
				x = 64;
				y = 0;
				break;
			case CubeType::GOLD_1:
			case CubeType::GOLD_2:
			case CubeType::GOLD_3:
				x = 0;
				y = 320;
				break;
			case CubeType::ROCK_1:
			case CubeType::ROCK_2:
			case CubeType::ROCK_3:
				x = 64;
				y = 288;
				break;
			case CubeType::CLAIMED_NON_CENTRE:
				x = 0;
				y = 704;
				break;
			case CubeType::BRICK:
			case CubeType::WALL_BOTTOM:
			case CubeType::WALL_CENTRE_1:
			case CubeType::WALL_CENTRE_2:
			case CubeType::WALL_CENTRE_3:
			case CubeType::WALL_CENTRE_4:
			case CubeType::WALL_CENTRE_5:
			case CubeType::WALL_CORNER_1:
			case CubeType::WALL_CORNER_2:
			case CubeType::WALL_CORNER_3:
			case CubeType::WALL_CORNER_4:
			case CubeType::WALL_BLANK_TOP_1:
			case CubeType::WALL_BLANK_TOP_2:
				x = 0;
				y = 448;
				break;
			case CubeType::HEART_PEDESTAL_CENTRE:
			case CubeType::HEART_PEDESTAL_EDGE:
			case CubeType::HEART_PEDESTAL_PILLAR_1:
			case CubeType::HEART_PEDESTAL_PILLAR_2:
				x= 64;
				y = 1952;
			default:
				x = 32;
				y = 0;
		}
	}

}
