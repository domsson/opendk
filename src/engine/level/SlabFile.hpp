#pragma once

#include "MapFile.hpp"
#include "TileType.hpp"

namespace OpenDK
{

	// TODO
	// Implement functionality to create SLB data from scratch
	// (or manipulate loaded SLB data in memory), then write
	// that data back out into a SLB file

	class SlabFile: public MapFile
	{
	public:

		/**
		 * Creates a new SLB file representation.
		 * Call `load()` to actually load in an SLB file.
		 */
		SlabFile();

		/**
		 * Creates a new SLB file representation by loading
		 * the given SLB file into memory.
		 * @param filePath The file path of the SLB file to load
		 */
		SlabFile(const std::string& filePath);

		/**
		 * Load the given SLB file into memory.
		 * @param filePath The file path of the SLB file to load
		 */
		bool load(const std::string& filePath);

		/**
		 * Load the given non-standard sized SLB file into memory.
		 * @param filePath The file path of the SLB file to load
		 * @param mapWidth The width of the map described with this SLB file
		 * @param mapHeight The height of the map described with this SLB file
		 */
		bool load(const std::string& filePath, int mapWidth, int mapHeight);

		/**
		 * Prints a simple representation of the SLB file (map layout)
		 * to the console, where every tile is two characters wide and
		 * one character height.
		 */
		void printMap() const;

		/**
		 * @return The byte value (tile type) of the tile at position x,y or -1
		 */
		TileType getTileType(int x, int y) const;

		/**
		 * @return The byte value (tile type) of the tile at index i or -1
		 */
		TileType getTileType(int i) const;

	private:

	};

}
