#pragma once

#include <cstdint>		// std::int16_t
#include <cstring>		// std::memcpy
#include <string>		// std::string
#include <iostream>		// std::cout
#include <fstream>		// std::ifstream
#include <iomanip>		// std::setw()
#include <typeinfo>		// typeid()

namespace OpenDK
{

	class CubeDataFile
	{
	public:

		static const size_t EXPECTED_FILE_SIZE;
		static const size_t HEADER_SIZE;
		static const size_t CHUNK_SIZE ;
		static const size_t ENTRY_SIZE ;

		CubeDataFile();

		CubeDataFile(const std::string& filePath);

		~CubeDataFile();

		bool load(const std::string& filePath);

		size_t getSize() const;

		std::int16_t getCubeSprite(int cubeIndex, int cubeSide) const;

	private:

		char* data;
		size_t size;
	};

}
