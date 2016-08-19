#include "Map.hpp"

namespace OpenDK
{

		Map::Map()
		: width(-1), height(-1), tiles(nullptr)
		{
		}

		Map::Map(const SlabFile& slabFile)
		: width(-1), height(-1), tiles(nullptr)
		{
			loadFromSLB(slabFile);
		}

		Map::~Map()
		{
			if (tiles == nullptr)
			{
				delete tiles;
			}
			else
			{
				delete[] tiles;
			}
		}

		void Map::loadFromSLB(const SlabFile& slabFile)
		{
			//width  = slabFile.getMapWidth();
			//height = slabFile.getMapHeight();
			width = 85;
			height = 85;

			tiles = new Tile[width * height];

			std::cout << "LOADING TILES\n";
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					std::cout << "tile " << (y*width+x) << "... ";
					tiles[(y * width + x)] = Tile(slabFile.getTileType(x, y));
				}
			}
			std::cout << std::endl;
		}

		Tile* Map::getTile(int x, int y)
		{
			return &tiles[(y * width + x)];
		}

}
