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
		static const size_t COL_ENTRY_SIZE;

		ColumnFile();

		ColumnFile(const std::string& filePath);

		~ColumnFile();

		bool load(const std::string& filePath);

		// height: 0-7, 0 being the floor
		std::int16_t getCubeType(int columnIndex, int height) const;

	private:

		char* columnData;

		std::int16_t numColumns;

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
