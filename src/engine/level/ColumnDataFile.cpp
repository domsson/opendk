#include "ColumnDataFile.hpp"

namespace OpenDK
{

	ColumnDataFile::ColumnDataFile()
	: MapFile()
	{
		// TODO
	}

	ColumnDataFile::ColumnDataFile(const std::string& filePath)
	: MapFile()
	{
		load(filePath);
	}

	bool ColumnDataFile::load(const std::string& filePath)
	{
		std::ifstream is(filePath, std::ifstream::binary | std::ifstream::in);
		if (!is.is_open())
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not open DAT file" << filePath << std::endl;
			return false;
		}

		// get length of file:
		is.seekg (0, is.end);	 // Sets the position of the next character to be extracted from the input stream.
		int length = is.tellg(); // Returns the position of the current character in the input stream.
		is.seekg (0, is.beg);

		if (length != 2 * (mapWidth * 3 + 1) * (mapHeight * 3 + 1))
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't process DAT file, size does not fit a map of size "
					<< mapWidth << "x" << mapHeight << std::endl;
			return false;
		}

		mapLayout = new char [(mapWidth * 3) * (mapHeight * 3)];

		int i = 0;
		for (int y = 0; y < mapHeight * 3; ++y)
		{
			for (int x = 0; x < mapWidth * 3; x += 2)
			{
				// TODO this tries to write 255 times more often than fits into mapLayout
				// TODO this might be entirely wrong, i have no fucking idea anymore
				int p = colDatPos(x, y);

				if (i < (mapWidth * 3) * (mapHeight * 3))
				{
					is.seekg(p);
					is.read(&(mapLayout[i++]), 1);
					is.read(&(mapLayout[i++]), 1);
				}
				else
				{
					std::cerr << "reading failed" << std::endl;
				}
			}
		}

		is.close();
		return true;
	}

	bool ColumnDataFile::load(const std::string& filePath, int mapWidth, int mapHeight)
	{
		if (mapWidth <= 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Loading DAT file aborted, "
					<< "invalid map width given (" << mapWidth << ")" << std::endl;
			return false;
		}
		if (mapHeight <= 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Loading DAT file aborted, "
					<< "invalid map height given (" << mapHeight << ")" << std::endl;
			return false;
		}
		this->mapWidth = mapWidth;
		this->mapHeight = mapHeight;

		return load(filePath);
	}

	int ColumnDataFile::colDatPos(int x, int y) const
	{
		return (y * (mapWidth * 3 * 2 + 1) + x);
	}

	int ColumnDataFile::colDatBufferPos(int x, int y) const
	{
		return (y * (mapWidth * 3 * 2) + x);
	}

	std::int16_t ColumnDataFile::getColumnIndex(int tileX, int tileY, int colX, int colY) const
	{
		if (colX < 0 || colX > 2 || colY < 0 || colY > 2)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't get column data value, "
					<< "invalid column position given (" << colX << "," << colY << ")" << std::endl;
			return -1;
		}

		if (tileX < 0 || tileX >= mapWidth || tileY < 0 || tileY >= mapHeight)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't get column data value, "
					<< "invalid tile position given (" << tileX << "," << tileY << ")" << std::endl;
			return -1;
		}

		int i = colDatBufferPos(tileX + colX, tileY + colY);
		std::cout << "index: " << i << std::endl;
		std::cout << "val 1: " << std::hex << (std::int16_t)mapLayout[i] << std::endl;
		std::cout << "val 2: " << std::hex << (std::int16_t)mapLayout[i+1] << std::endl;
		std::int16_t value = 0x0000;
		/*
			numColumns = 0x0000; // init to all zeroes
			numColumns = numColumns | (numEntries[0] << 8); // 0: 08, after shift: [08] 00
			numColumns = numColumns | (numEntries[1] << 0); // 1: 00, after shift:  00 [00]
		 */
		value = value | (mapLayout[i+i] << 8);
		value = value | (mapLayout[i+0] << 0);
		return std::abs(value);
	}

	/*
	std::int16_t xFC6E = 0xFC6E; // this is what we want (i guess...)
	std::int16_t x6EFC = 0x6EFC; // this is how it is in the file

	std::cout << "0xFC6E = " << xFC6E << ", 0x6EFC = " << x6EFC << std::endl;
	*/

}
