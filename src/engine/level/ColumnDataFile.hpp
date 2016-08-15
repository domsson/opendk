#pragma once

#include <cmath>

#include "MapFile.hpp"

namespace OpenDK
{

	class ColumnDataFile: public MapFile
	{
	public:

		ColumnDataFile();

		ColumnDataFile(const std::string& filePath);

		bool load(const std::string& filePath);

		bool load(const std::string& filePath, int mapWidth, int mapHeight);

		std::int16_t getColumnIndex(int tileX, int tileY, int colX, int colY) const;

	private:

		int colDatPos(int x, int y) const;

		int colDatBufferPos(int x, int y) const;
	};

}
