#include "MapFile.hpp"

namespace OpenDK
{

	const int MapFile::DEFAULT_MAP_WIDTH  = 85;
	const int MapFile::DEFAULT_MAP_HEIGHT = 85;

	MapFile::MapFile()
	: mapLayout(nullptr), mapWidth(DEFAULT_MAP_WIDTH), mapHeight(DEFAULT_MAP_HEIGHT)
	{
		// Nothing to do
	}

	MapFile::~MapFile()
	{
		delete[] mapLayout;
	}

	bool MapFile::load(const std::string& filePath)
	{
		std::ifstream is(filePath, std::ifstream::binary | std::ifstream::in);
		if (!is.is_open())
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not open map file" << filePath << std::endl;
			return false;
		}

		is.seekg (0, is.end);
		int length = is.tellg();
		is.seekg (0, is.beg);

		mapLayout = new char [length];
		is.read(mapLayout, length);
		is.close();

		return true;
	}

	void MapFile::printMap() const
	{
		if (mapLayout == nullptr)
		{
			std::cerr << typeid(this).name() << ": [WRN] Can not print the map layout "
					<< "without having successfully read a map file first" << std::endl;
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

	int MapFile::getMapHeight() const
	{
		return (mapLayout == nullptr) ? -1 : mapHeight;
	}

	int MapFile::getMapWidth() const
	{
		return (mapLayout == nullptr) ? -1 : mapWidth;
	}

	char MapFile::getTileValue(int x, int y) const
	{
		if (mapLayout == nullptr)
		{
			std::cerr << typeid(this).name() << ": [WRN] Could not get tile value "
				<< "without having successfully read a map file first" << std::endl;
			return -1;
		}
		return getTileValue(pos(x, y));
	}

	char MapFile::getTileValue(int i) const
	{
		if (i < 0 || i >= mapWidth * mapHeight)
		{
			std::cerr << typeid(this).name()
				<< ": [WRN] Could not get tile value, index out of bounds" << std::endl;
			return -1;
		}
		return mapLayout[i];
	}

	int MapFile::pos(int x, int y) const
	{
		return (y * mapWidth + x);
	}

}
