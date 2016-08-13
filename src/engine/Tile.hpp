#pragma once

#include "TileOwner.hpp"

namespace OpenDK
{

	class Tile
	{
	public:

		Tile();

		TileOwner getOwner() const;
		TileType getType() const;

	private:

		TileOwner owner;
		TileType type;

	};

}
