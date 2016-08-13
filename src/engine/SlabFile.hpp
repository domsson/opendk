#pragma once

#include <string>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <iomanip>		// std::setw()
#include <typeinfo>

namespace OpenDK
{

	// TODO
	// Implement functionality to create SLB data from scratch
	// (or manipulate loaded SLB data in memory), then write
	// that data back out into a SLB file

	class SlabFile
	{
	public:

		/**
		 * If no width is supplied, the default width of original
		 * Dungeon Keeper maps will be used, which is 85.
		 */
		static const int DEFAULT_MAP_WIDTH;

		/**
		 * If no height is supplied, the default height of original
		 * Dungeon Keeper maps will be used, which is 85.
		 */
		static const int DEFAULT_MAP_HEIGHT;

		/**
		 * Creates a new SLB file representation.
		 * Call `load()` to actually load in an SLB file.
		 */
		SlabFile();

		/**
		 * Creates a new SLB file representation by loading
		 * the given SLB file into memory.
		 */
		SlabFile(const std::string& filePath);

		/**
		 * Destruct this object.
		 * Deletes the SLB file's representation from memory.
		 */
		~SlabFile();

		bool load(const std::string& filePath);
		bool load(const std::string& filePath, int mapWidth, int mapHeight);

		void printMap() const;

		int getMapHeight() const;
		int getMapWidth() const;

		char getTileType(int x, int y) const;

	private:

		char* mapLayout;
		int mapWidth;
		int mapHeight;

		int pos(int x, int y) const;
	};

}
