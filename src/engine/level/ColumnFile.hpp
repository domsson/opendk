#pragma once

#include <cstdint>
#include <string>
#include <iostream>		// std::cout
#include <fstream>		// std::ifstream
#include <iomanip>		// std::setw()
#include <typeinfo>

namespace OpenDK
{

	class ColumnFile
	{
	public:

		static const std::size_t EXPECTED_FILE_SIZE;
		static const std::size_t HEADER_SIZE;
		static const std::size_t CHUNK_SIZE;
		static const std::size_t ENTRY_SIZE;

		ColumnFile();

		ColumnFile(const std::string& filePath);

		~ColumnFile();

		bool load(const std::string& filePath);

		std::size_t getSize() const;

		// height: 0-7, 0 being the floor
		std::int16_t getCubeType(int columnIndex, int height) const;

		bool cubeIsSolid(int columnIndex, int height) const;

		std::int16_t getBaseBlockType(int columnIndex) const;

		bool columnIsPermanent(int columnIndex) const;

		std::int8_t getColumnHeight(int columnIndex) const;

		std::int16_t getColumnUses(int columnIndex) const;

	private:

		char* data;
		std::size_t size;

	};

}
