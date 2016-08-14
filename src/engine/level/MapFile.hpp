#pragma once

#include <string>
#include <iostream>		// std::cout
#include <fstream>		// std::ifstream
#include <iomanip>		// std::setw()
#include <typeinfo>

namespace OpenDK
{

	class MapFile
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
		 * Creates a new map related file representation.
		 * Call `load()` to actually load in a map related file.
		 */
		MapFile();

		/**
		 * Destruct this object.
		 * Deletes the file's representation from memory.
		 */
		~MapFile();

		/**
		 * Load the given map related file into memory.
		 * @param filePath The file path of the map related file to load
		 */
		virtual bool load(const std::string& filePath) = 0;

		/**
		 * Load the given non-standard sized map related file into memory.
		 * @param filePath The file path of the map related file to load
		 * @param mapWidth The width of the map described with this file
		 * @param mapHeight The height of the map described with this file
		 */
		virtual bool load(const std::string& filePath, int mapWidth, int mapHeight) = 0;

		/**
		 * Prints a simple representation of the map related file
		 * (map layout) to the console.
		 */
		virtual void printMap() const = 0;

		/**
		 * @return The width of the loaded map layout or -1 if none loaded yet
		 */
		int getMapWidth() const;

		/**
		 * @return The height of the loaded map layout or -1 if none loaded yet
		 */
		int getMapHeight() const;

		/**
		 * @return The byte value of the tile at position x,y or -1
		 */
		char getTileValue(int x, int y) const;

		/**
		 * @return The byte value of the tile at index i or -1
		 */
		char getTileValue(int i) const;

	protected:

		/**
		 * The data from the map related file (not necessarily as in the file)
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

	};

}
