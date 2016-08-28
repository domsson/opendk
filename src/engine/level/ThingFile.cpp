#include "ThingFile.hpp"

namespace OpenDK
{

	const std::size_t ThingFile::HEADER_SIZE = 2;
	const std::size_t ThingFile::CHUNK_SIZE = 21;

	ThingFile::ThingFile()
	: data(nullptr), size(0)
	{
	}

	ThingFile::ThingFile(const std::string& filePath)
	: data(nullptr), size(0)
	{
		load(filePath);
	}

	ThingFile::~ThingFile()
	{
		delete[] data;
	}

	bool ThingFile::load(const std::string& filePath)
	{
		std::ifstream is(filePath, std::ifstream::binary | std::ifstream::in);
		if (!is.is_open())
		{
			std::cerr << typeid(this).name() << ": [ERR] Could not open CLM file" << filePath << std::endl;
			return false;
		}

		is.seekg (0, is.end);
		int length = is.tellg();
		is.seekg (0, is.beg);

		size = length - HEADER_SIZE;
		data = new char [size];

		is.seekg(HEADER_SIZE);
		is.read(data, size);
		is.close();

		return true;
	}

	std::size_t ThingFile::getSize() const
	{
		return size;
	}

	int ThingFile::getThingCount() const
	{
		return std::floor(size / CHUNK_SIZE);
	}

	int ThingFile::getThingCount(int thingType) const
	{
		int num_things = getThingCount();
		int n = 0;

		for (int i = 0; i < num_things; ++i)
		{
			if (thingType == getThingType(i))
			{
				++n;
			}
		}

		return n;
	}

	int ThingFile::getThingCount(int thingType, int thingSubtype) const
	{
		int num_things = getThingCount();
		int n = 0;

		for (int i = 0; i < num_things; ++i)
		{
			if (thingType == getThingType(i)
				&& thingSubtype == getThingSubtype(i))
			{
				++n;
			}
		}

		return n;
	}

	glm::vec3 ThingFile::getThingLocation(int thingIndex) const
	{
		// TODO verify that this is correct
		std::size_t element_size = 1;

		std::size_t offset_x = thingIndex * CHUNK_SIZE + 1;
		std::size_t offset_y = thingIndex * CHUNK_SIZE + 3;
		std::size_t offset_z = thingIndex * CHUNK_SIZE + 5;

		if (offset_z + element_size > size)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't get thing location, "
					<< "given thing index is out of range: " << thingIndex << std::endl;
			return glm::vec3(-1.0f, -1.0f, -1.0f);
		}

		std::uint8_t x = *(reinterpret_cast<std::uint8_t *>(data + offset_x));
		std::uint8_t y = *(reinterpret_cast<std::uint8_t *>(data + offset_y));
		std::uint8_t z = *(reinterpret_cast<std::uint8_t *>(data + offset_z));

		return glm::vec3(x, y, z);
	}

	std::uint8_t ThingFile::getThingType(int thingIndex) const
	{
		std::size_t chunk_offset = 6;
		std::size_t element_size = 1;

		std::size_t offset = thingIndex * CHUNK_SIZE + chunk_offset;

		if (offset + element_size > size)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't get thing type, "
					<< "given thing index is out of range: " << thingIndex << std::endl;
			return -1;
		}

		return data[offset];
	}

	std::uint8_t ThingFile::getThingSubtype(int thingIndex) const
	{
		std::size_t chunk_offset = 7;
		std::size_t element_size = 1;

		std::size_t offset = thingIndex * CHUNK_SIZE + chunk_offset;

		if (offset + element_size > size)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't get thing subtype, "
					<< "given thing index is out of range: " << thingIndex << std::endl;
			return -1;
		}

		return data[offset];
	}

	std::uint8_t ThingFile::getThingOwner(int thingIndex) const
	{
		std::size_t chunk_offset = 8;
		std::size_t element_size = 1;

		std::size_t offset = thingIndex * CHUNK_SIZE + chunk_offset;

		if (offset + element_size > size)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't get thing owner, "
					<< "given thing index is out of range: " << thingIndex << std::endl;
			return -1;
		}

		return data[offset];
	}

	std::int16_t ThingFile::getSensitiveTile(int thingIndex) const
	{
		std::size_t chunk_offset = 11;
		std::size_t element_size = 2;

		std::size_t offset = thingIndex * CHUNK_SIZE + chunk_offset;

		if (offset + element_size > size)
		{
			std::cerr << typeid(this).name() << ": [ERR] Can't get sensitive tile, "
					<< "given thing index is out of range: " << thingIndex << std::endl;
			return -1;
		}

		return *(reinterpret_cast<std::int16_t *>(data + offset));
	}

}
