#include "Tile.hpp"

namespace OpenDK
{
		Tile::Tile()
		: type(TileType::TYPE_UNDEFINED), owner(TileOwner::PLAYER_UNDEFINED)
		{
			generateColumns();
		}

		Tile::Tile(TileType type)
		: type(type), owner(TileOwner::PLAYER_UNDEFINED)
		{
			generateColumns();
		}

		TileType Tile::getType() const
		{
			return type;
		}

		TileOwner Tile::getOwner() const
		{
			return owner;
		}

		const Column& Tile::getColumn(int x, int y) const
		{
			return columns[(y * 3 + x)];
		}

		void Tile::generateColumns()
		{
			int height;
			CubeType cubeType;

			switch (type)
			{
				case TileType::EARTH: // 2
					height = 7;
					cubeType = CubeType::EARTH_1;
					break;
				case TileType::PATH: // 10
					height = 1;
					cubeType = CubeType::PATH_1;
					break;
				case TileType::LAND: // 11
					height = 1;
					cubeType = CubeType::CLAIMED_NON_CENTRE;
					break;
				case TileType::WALL:	// 4-9
				case TileType::WALL_2:
				case TileType::WALL_3:
				case TileType::WALL_4:
				case TileType::WALL_5:
				case TileType::WALL_6:
					height = 7;
					cubeType = CubeType::BRICK;
					break;
				case TileType::DUNGEON_HEART:
					height = 2;
					cubeType = CubeType::HEART_PEDESTAL_CENTRE;
					break;
				case TileType::ROCK: // 0
				case TileType::TYPE_UNDEFINED:
				default:
					height = 7;
					cubeType = CubeType::ROCK_1;
			}

			std::cout << std::endl;
			std::cout << "GENERATING COLUMNS:\n";
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					std::cout << "col (" << x << "," << y << ")... ";

					columns[(y * 3 + x)].setCube(cubeType, 0); // only lowest one for now

					/*
					for (int h = 0; h < height; ++h)
					{
						std::cout << "cube " << h << "... ";
						col.setCube(cubeType, h);
					}
					*/
				}
			}
			std::cout << std::endl;
		}

}
