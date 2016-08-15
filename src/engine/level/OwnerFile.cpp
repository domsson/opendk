#include "OwnerFile.hpp"

namespace OpenDK
{

	OwnerFile::OwnerFile()
	: MapFile()
	{
		// TODO
	}

	OwnerFile::OwnerFile(const std::string& filePath)
	: MapFile()
	{
		load(filePath);
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
		for (int y = 0; y < mapHeight * 3; y += 3)
		{
			for (int x = 0; x < mapWidth * 3; x += 3)
			{
				is.seekg(colPos(x, y));
				is.get(mapLayout[i++]);
			}
		}

		is.close();
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
		MapFile::printMap();
	}

	TileOwner OwnerFile::getTileOwner(int x, int y) const
	{
		return static_cast<TileOwner>(getTileValue(x, y));
	}

	TileOwner OwnerFile::getTileOwner(int i) const
	{
		return static_cast<TileOwner>(getTileValue(i));
	}

}
