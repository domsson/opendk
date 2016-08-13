#include "OwnerFile.hpp"

namespace OpenDK
{

	const int OwnerFile::DEFAULT_MAP_WIDTH  = 85;
	const int OwnerFile::DEFAULT_MAP_HEIGHT = 85;

	OwnerFile::OwnerFile()
	: mapLayout(nullptr), mapWidth(DEFAULT_MAP_WIDTH), mapHeight(DEFAULT_MAP_HEIGHT)
	{
		// TODO
	}

	OwnerFile::OwnerFile(const std::string& filePath)
	: mapLayout(nullptr), mapWidth(DEFAULT_MAP_WIDTH), mapHeight(DEFAULT_MAP_HEIGHT)
	{
		load(filePath);
	}

	OwnerFile::~OwnerFile()
	{
		delete[] mapLayout;
	}

	bool OwnerFile::load(const std::string& filePath)
	{
		std::ifstream is(filePath, std::ifstream::binary | std::ifstream::in);
		if (!is.is_open())
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not open OWN file" << filePath << std::endl;
			return false;
		}

		// get length of file:
		is.seekg (0, is.end);	 // Sets the position of the next character to be extracted from the input stream.
		int length = is.tellg(); // Returns the position of the current character in the input stream.
		is.seekg (0, is.beg);

		if (length != (mapWidth * 3 + 1) * (mapHeight * 3 + 1))
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't process OWN file, size does not fit a map of size "
					<< mapWidth << "x" << mapHeight << std::endl;
			return false;
		}

		mapLayout = new char [mapWidth * mapHeight];

		int i = 0;
		for (int y = 1; y < mapHeight * 3; y += 3)
		{
			for (int x = 1; x < mapWidth * 3; x += 3)
			{
				is.seekg(ownPos(x, y));
				is.get(mapLayout[i++]);
			}
		}
		return true;
	}

	bool OwnerFile::load(const std::string& filePath, int mapWidth, int mapHeight)
	{
		if (mapWidth <= 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Loading OWN file aborted, "
					<< "invalid map width given (" << mapWidth << ")" << std::endl;
			return false;
		}
		if (mapHeight <= 0)
		{
			std::cerr << typeid(this).name() << ": [ERR] Loading OWN file aborted, "
					<< "invalid map height given (" << mapHeight << ")" << std::endl;
			return false;
		}
		this->mapWidth = mapWidth;
		this->mapHeight = mapHeight;

		return load(filePath);
	}

	void OwnerFile::printMap() const
	{
		if (mapLayout == nullptr)
		{
			std::cerr << typeid(this).name() << ": [WRN] Can not print the map layout "
					<< "without having successfully read an OWN file first" << std::endl;
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

	int OwnerFile::getMapHeight() const
	{
		return (mapLayout == nullptr) ? -1 : mapHeight;
	}

	int OwnerFile::getMapWidth() const
	{
		return (mapLayout == nullptr) ? -1 : mapWidth;
	}

	TileOwner OwnerFile::getTileOwner(int x, int y) const
	{
		return (mapLayout == nullptr) ? TileOwner::PLAYER_UNKNOWN : static_cast<TileOwner>(mapLayout[pos(x, y)]);
	}

	int OwnerFile::pos(int x, int y) const
	{
		return (y * mapWidth + x);
	}

	int OwnerFile::ownPos(int x, int y) const
	{
		return (y * (mapWidth * 3 + 1) + x);
	}

}
