#pragma once

#include <cstdint>
#include <cstring>		// std::memcpy
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

		static const size_t EXPECTED_FILE_SIZE;
		static const size_t HEADER_SIZE;
		static const size_t CHUNK_SIZE;
		static const size_t ENTRY_SIZE;

		ColumnFile();

		ColumnFile(const std::string& filePath);

		~ColumnFile();

		bool load(const std::string& filePath);

		size_t getSize() const;

		// height: 0-7, 0 being the floor
		std::int16_t getCubeType(int columnIndex, int height) const;

		bool cubeIsSolid(int columnIndex, int height) const;

		std::int16_t getBaseBlockType(int columnIndex) const;

		bool columnIsPermanent(int columnIndex) const;

		std::int8_t getColumnHeight(int columnIndex) const;

	private:

		char* data;
		size_t size;

	/* // From KeeperFX
		struct Column { // sizeof=0x18
			short use;
			unsigned char bitfields;
			unsigned short solidmask;
			unsigned short baseblock;
			unsigned char orient;
			unsigned short cubes[COLUMN_STACK_HEIGHT];
		};
	*/

	};

}
