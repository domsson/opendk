#pragma once

#include <cmath>		// std::floor()
#include <cstdint>		// std::int16_t
#include <string>
#include <iostream>		// std::cout
#include <fstream>		// std::ifstream
#include <iomanip>		// std::setw()
#include <typeinfo>

#include <glm/glm.hpp>

namespace OpenDK
{

	class ThingFile
	{
	public:

		static const std::size_t HEADER_SIZE;
		static const std::size_t CHUNK_SIZE;

		ThingFile();

		ThingFile(const std::string& filePath);

		~ThingFile();

		bool load(const std::string& filePath);

		std::size_t getSize() const;

		int getThingCount() const;

		int getThingCount(int thingType) const;

		int getThingCount(int thingType, int thingSubtype) const;

		glm::vec3 getThingLocation(int thingIndex) const;

		std::uint8_t getThingType(int thingIndex) const;

		std::uint8_t getThingSubtype(int thingIndex) const;

		std::uint8_t getThingOwner(int thingIndex) const;

		// makes sense only for thing type 1 (item)
		std::int16_t getSensitiveTile(int thingIndex) const;

	private:

		char* data;
		std::size_t size;

	};

	/*
		Each entry:
		-----------
		0-5: Location
		6: Thing type
		7: Thing subtype (eg creature race, trap type)
		8: Owner
		9-20: Type specific data
	*/

}
