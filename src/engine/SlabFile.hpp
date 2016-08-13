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
		 * @param filePath The file path of the SLB file to load
		 */
		SlabFile(const std::string& filePath);

		/**
		 * Destruct this object.
		 * Deletes the SLB file's representation from memory.
		 */
		~SlabFile();

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
		char getTileType(int x, int y) const;

	private:

		/**
		 * The odd bytes (as the even bytes are all zero) of the loaded SLB file
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
