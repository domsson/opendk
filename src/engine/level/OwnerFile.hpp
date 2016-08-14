#pragma once

#include "MapFile.hpp"
#include "TileOwner.hpp"

namespace OpenDK
{

	class OwnerFile: public MapFile
	{
	public:

		/**
		 * Creates a new OWN file representation.
		 * Call `load()` to actually load in an OWN file.
		 */
		OwnerFile();

		/**
		 * Creates a new OWN file representation by loading
		 * the given OWN file into memory.
		 * @param filePath The file path of the OWN file to load
		 */
		OwnerFile(const std::string& filePath);

		/**
		 * Load the given OWN file into memory.
		 * @param filePath The file path of the OWN file to load
		 */
		bool load(const std::string& filePath);

		/**
		 * Load the given non-standard sized OWN file into memory.
		 * @param filePath The file path of the OWN file to load
		 * @param mapWidth The width of the map described with this OWN file
		 * @param mapHeight The height of the map described with this OWN file
		 */
		bool load(const std::string& filePath, int mapWidth, int mapHeight);

		/**
		 * Prints a simple representation of the OWN file (map layout)
		 * to the console, where every tile is two characters wide and
		 * one character height.
		 */
		void printMap() const;

		/**
		 * @return The byte value (tile type) of the tile at position x,y or -1
		 */
		TileOwner getTileOwner(int x, int y) const;

		/**
		 * @return The byte value (tile type) of the tile at index i or -1
		 */
		TileOwner getTileOwner(int i) const;

	private:

	};

}
