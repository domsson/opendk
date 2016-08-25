#include "ColumnFile.hpp"

namespace OpenDK
{

		const size_t ColumnFile::EXPECTED_FILE_SIZE = 49160;
		const size_t ColumnFile::HEADER_SIZE = 8;
		const size_t ColumnFile::CHUNK_SIZE = 24;
		const size_t ColumnFile::ENTRY_SIZE = 2;

		ColumnFile::ColumnFile()
		: data(nullptr), size(0)
		{
		}

		ColumnFile::ColumnFile(const std::string& filePath)
		: data(nullptr), size(0)
		{
			load(filePath);
		}

		ColumnFile::~ColumnFile()
		{
			delete[] data;
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

			size = length - HEADER_SIZE;
			data = new char [size];

			is.seekg(HEADER_SIZE);
			is.read(data, size);
			is.close();

			return true;
		}

		size_t ColumnFile::getSize() const
		{
			return size;
		}

		std::int16_t ColumnFile::getCubeType(int columnIndex, int height) const
		{
			if (height < 0 || height > 7)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get cube type, "
						<< "given height value is invalid - should be in the range 0..7" << std::endl;
				return -1;
			}

			// 8 because the actual cube data starts after 8 bytes into a chunk
			size_t offset = (columnIndex * CHUNK_SIZE) + 8 + (height * ENTRY_SIZE);

			if (offset + ENTRY_SIZE > size)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get cube type, "
						<< "given column index is out of range: " << columnIndex << std::endl;
				return -1;
			}

			// Variant 1: Using cast and pointers
			// http://stackoverflow.com/questions/544928/reading-integer-size-bytes-from-a-char-array
			return *(reinterpret_cast<std::int16_t *>(data + offset));

			// Variant 2: Using memcpy
			//std::int16_t columnType;
			//std::memcpy(&columnType, columnData + offset, 2);
		}

		bool ColumnFile::cubeIsSolid(int columnIndex, int height) const
		{
			if (height < 0 || height > 7)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get cube solidness, "
						<< "given height value is invalid - should be in the range 0..7" << std::endl;
				return -1;
			}

			size_t offset = (columnIndex * CHUNK_SIZE) + 3;

			if (offset + 1 > size)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get cube solidness, "
						<< "given column index is out of range: " << columnIndex << std::endl;
				return -1;
			}

			/*
			std::int8_t solidMask = data[offset];
			std::int8_t bitMask = 0x01 << height;
			return (solidMask & bitMask) > 0;
			*/
			return (data[offset] & (0x01 << height)) > 0;
		}

		std::int16_t ColumnFile::getBaseBlockType(int columnIndex) const
		{
			size_t offset = (columnIndex * CHUNK_SIZE) + 5;

			if (offset + 1 > size)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get base block type, "
						<< "given column index is out of range: " << columnIndex << std::endl;
				return -1;
			}

			return *(reinterpret_cast<std::int16_t *>(data + offset));
		}

		std::int16_t ColumnFile::getColumnUses(int columnIndex) const
		{
			size_t offset = (columnIndex * CHUNK_SIZE) + 0;

			if (offset + 2 > size)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get column uses, "
						<< "given column index is out of range: " << columnIndex << std::endl;
				return -1;
			}

			return *(reinterpret_cast<std::int16_t *>(data + offset));
		}

		bool ColumnFile::columnIsPermanent(int columnIndex) const
		{
			size_t offset = (columnIndex * CHUNK_SIZE) + 2;

			if (offset + 1 > size)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get column permanency, "
						<< "given column index is out of range: " << columnIndex << std::endl;
				return -1;
			}

			//return (data[offset] & 0x80) > 0;
			return (data[offset] & 0x01) > 0;
		}

		std::int8_t ColumnFile::getColumnHeight(int columnIndex) const
		{
			size_t offset = (columnIndex * CHUNK_SIZE) + 2;

			if (offset + 1 > size)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get column height, "
						<< "given column index is out of range: " << columnIndex << std::endl;
				return -1;
			}

			return (data[offset] & 0xF0) >> 4;
		}

}
