#pragma once

namespace OpenDK
{

	enum TileType
	{
		TYPE_UNDEFINED	= -1, // not present in the original game
		ROCK			= 0,
		GOLD			= 1,
		EARTH			= 2,
		EARTH_TORCH		= 3,
		WALL			= 4,	// 5, 6, 7, 8, 9
		WALL_2			= 5,
		WALL_3			= 6,
		WALL_4			= 7,
		WALL_5			= 8,
		WALL_6			= 9,
		PATH			= 10,	// unclaimed path
		LAND			= 11, 	// claimed land
		LAVA			= 12,
		WATER			= 13,
		PORTAL			= 14,
		TREASURE_ROOM	= 16,
		LIBRARY			= 18,
		PRISON			= 20,
		TORTURE_ROOM	= 22,
		TRAINING_ROOM	= 24,
		DUNGEON_HEART	= 26,
		WORKSHOP		= 28,
		SCAVENGER_ROOM	= 30,
		TEMPLE			= 32,
		GRAVEYARD		= 34,
		HATCHERY		= 36,
		LAIR			= 38,
		BARRACKS		= 40,
		WOODEN_DOOR		= 42,	// 43
		BRACED_DOOR		= 44,	// 45
		IRON_DOOR		= 46,	// 47
		MAGIC_DOOR		= 48,	// 49
		BRIDGE			= 51,
		GEM				= 52,
		GUARDPOST		= 53
	};

}

// http://keeper.lubiki.pl/dk1_docs/dk_mapfiles_ref.htm#mapfl_intro_overview
// http://keeper.lubiki.pl/dk1_docs/dk_scripting_ref.htm
