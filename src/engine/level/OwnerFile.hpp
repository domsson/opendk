#pragma once

#include <string>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <iomanip>		// std::setw()
#include <typeinfo>

#include "TileOwner.hpp"

namespace OpenDK
{

	class OwnerFile
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
		 * Destruct this object.
		 * Deletes the OWN file's representation from memory.
		 */
		~OwnerFile();

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
		 * @return The width of the loaded map layout or -1 if none loaded yet
		 */
		int getMapWidth() const;

		/**
		 * @return The height of the loaded map layout or -1 if none loaded yet
		 */
		int getMapHeight() const;

		/**
		 * @return The byte value (tile type) of the tile at position x,y or -1
		 */
		TileOwner getTileOwner(int x, int y) const;

	private:

		/**
		 * Every third byte (as they are tripled) of the loaded OWN file
		 */
		char* mapLayout;

		/**
		 * The width of the loaded map layout
		 */
		int mapWidth;

		/*
		 * The width of the loaded map layout
		 */
		int mapHeight;

		/**
		 * @return The position (index within mapLayout) of the tile at x,y
		 */
		int pos(int x, int y) const;

		/**
		 * @return The index position for the column at x,y within the OWN file
		 */
		int ownPos(int x, int y) const;

	};

}
