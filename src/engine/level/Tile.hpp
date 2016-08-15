#pragma once

#include "TileType.hpp"
#include "TileOwner.hpp"
#include "Column.hpp"
#include "CubeType.hpp"

namespace OpenDK
{

	class Tile
	{
	public:

		Tile();
		Tile(TileType type);

		TileType getType() const;
		TileOwner getOwner() const;

		const Column& getColumn(int x, int y) const;

	private:

		TileType type;
		TileOwner owner;

		Column columns[9];
		void generateColumns();

	};

}
