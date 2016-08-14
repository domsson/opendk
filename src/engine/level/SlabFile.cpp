#include "SlabFile.hpp"

namespace OpenDK
{

	SlabFile::SlabFile()
	: MapFile()
	{
		// Nothing to do
	}

	SlabFile::SlabFile(const std::string& filePath)
	: MapFile()
	{
		load(filePath);
	}

	bool SlabFile::load(const std::string& filePath)
	{
		std::ifstream is(filePath, std::ifstream::binary | std::ifstream::in);
		if (!is.is_open())
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not open SLB file" << filePath << std::endl;
			return false;
		}

		// get length of file:
		is.seekg (0, is.end);	 // Sets the position of the next character to be extracted from the input stream.
		int length = is.tellg(); // Returns the position of the current character in the input stream.
		is.seekg (0, is.beg);

		if (length != 2 * mapWidth * mapHeight)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't process SLB file, size does not fit a map of size "
					<< mapWidth << "x" << mapHeight << std::endl;
			return false;
		}

		mapLayout = new char [mapWidth * mapHeight];

		int i = 0;
		while (is.good())
		{
			is.seekg (i * 2); // start from the beginning
			is.get(mapLayout[i++]);
		}
		is.close();

		return true;
	}

	bool SlabFile::load(const std::string& filePath, int mapWidth, int mapHeight)
	{
		if (mapWidth <= 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Loading SLB file aborted, "
					<< "invalid map width given (" << mapWidth << ")" << std::endl;
			return false;
		}
		if (mapHeight <= 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Loading SLB file aborted, "
					<< "invalid map height given (" << mapHeight << ")" << std::endl;
			return false;
		}
		this->mapWidth = mapWidth;
		this->mapHeight = mapHeight;

		return load(filePath);
	}

	void SlabFile::printMap() const
	{
		MapFile::printMap();
	}

	char SlabFile::getTileType(int x, int y) const
	{
		return getTileValue(x, y);
	}

	char SlabFile::getTileType(int i) const
	{
		return getTileValue(i);
	}

}
