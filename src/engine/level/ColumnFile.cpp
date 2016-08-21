#include "ColumnFile.hpp"

namespace OpenDK
{

		const size_t ColumnFile::EXPECTED_FILE_SIZE = 49160;
		const size_t ColumnFile::COL_ENTRY_SIZE = 24;

		ColumnFile::ColumnFile()
		: columnData(nullptr), numColumns(-1)
		{
		}

		ColumnFile::ColumnFile(const std::string& filePath)
		: columnData(nullptr), numColumns(-1)
		{
			load(filePath);
		}

		ColumnFile::~ColumnFile()
		{
			delete[] columnData;
		}

		bool ColumnFile::load(const std::string& filePath)
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

			if (length != EXPECTED_FILE_SIZE)
			{
				std::cerr << typeid(this).name() << ": [ERR] Refusing to open CLM file, size mismatch: "
						<< length << " found, expected " << EXPECTED_FILE_SIZE << std::endl;
				return false;
			}

			columnData = new char [length - 8];

			/*
			char numEntries[2];
			is.seekg(1);
			is.read(numEntries, 2); // 0=08 1=00

			numColumns = 0x0000; // init to all zeroes
			numColumns = numColumns | (numEntries[0] << 8); // 0: 08, after shift: [08] 00
			numColumns = numColumns | (numEntries[1] << 0); // 1: 00, after shift:  00 [00]
			*/

			is.seekg(7);
			is.read(columnData, length - 8);
			is.close();

			return true;
		}

		std::int16_t ColumnFile::getCubeType(int columnIndex, int height) const
		{
			if (height < 0 || height > 7)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get cube type, "
						<< "given height value is invalid - should be in the range 0..7" << std::endl;
				return -1;
			}
			int offset = 8 + (columnIndex * COL_ENTRY_SIZE) + (height * 2);

			// TODO I really don't get why it is this way round...
			// This is "extracting" little endian data.
			// And while the files do seem to be little endian,
			// my architecture is as well! So what the hell...
			std::int16_t columnType = 0x0000;
			columnType = columnType | (columnData[offset+0] << 8);
			columnType = columnType | (columnData[offset+1] << 0);

			// The following two work nicely... but don't swap the byte order.

			//std::int16_t columnType;
			//std::memcpy(&columnType, columnData + offset, 2);

			//std::int16_t columnType = *(reinterpret_cast<std::int16_t *>(columnData + offset));

			return columnType;
		}
}
