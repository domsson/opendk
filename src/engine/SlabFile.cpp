#include "SlabFile.hpp"

namespace OpenDK
{

	const int SlabFile::DEFAULT_MAP_WIDTH  = 85;
	const int SlabFile::DEFAULT_MAP_HEIGHT = 85;

	SlabFile::SlabFile()
	: mapLayout(nullptr), mapWidth(DEFAULT_MAP_WIDTH), mapHeight(DEFAULT_MAP_HEIGHT)
	{
		// TODO
	}

	SlabFile::SlabFile(const std::string& filePath)
	: mapLayout(nullptr), mapWidth(DEFAULT_MAP_WIDTH), mapHeight(DEFAULT_MAP_HEIGHT)
	{
		load(filePath);
	}

	SlabFile::~SlabFile()
	{
		delete[] mapLayout;
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

		mapLayout = new char [length];

		unsigned int pos = 0;
		while (is.good())
		{
			is.seekg (pos * 2); // start from the beginning
			is.get(mapLayout[pos++]);
		}
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
		if (mapLayout == nullptr)
		{
			std::cerr << typeid(this).name() << ": [WRN] Can not print the map layout "
					<< "without having successfully read a SLB file first" << std::endl;
			return;
		}

		for (int y = 0; y < mapHeight; ++y)
		{
			std::cout << std::endl;

			for (int x = 0; x < mapWidth; ++x)
			{
				char c = mapLayout[pos(x, y)];
				if (c == 0)
				{
					std::cout << std::setw(2) << "  ";
				}
				else
				{
					std::cout << std::setw(2) << +c;
				}
			}
		}
		std::cout << std::endl;
	}

	int SlabFile::getMapHeight() const
	{
		return (mapLayout == nullptr) ? -1 : mapHeight;
	}

	int SlabFile::getMapWidth() const
	{
		return (mapLayout == nullptr) ? -1 : mapWidth;
	}

	char SlabFile::getTileType(int x, int y) const
	{
		return (mapLayout == nullptr) ? -1 : mapLayout[pos(x, y)];
	}

	int SlabFile::pos(int x, int y) const
	{
		return (y * mapWidth + x);
	}

}
