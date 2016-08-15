#pragma once

#include "SlabFile.hpp"
#include "Tile.hpp"

namespace OpenDK
{

	class Map
	{
	public:

		Map();

		Map(const SlabFile& slabFile);

		~Map();

		void loadFromSLB(const SlabFile& slabFile);

		Tile* getTile(int x, int y);

	private:

		int width;
		int height;

		Tile* tiles;

	};

}
