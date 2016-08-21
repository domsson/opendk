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

			is.seekg(HEADER_SIZE - 1);
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
			size_t offset = 8 + (columnIndex * CHUNK_SIZE) + (height * ENTRY_SIZE);

			if (offset + ENTRY_SIZE > size)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get cube type, "
						<< "given column index is out of range: " << columnIndex << std::endl;
				return -1;
			}

			// TODO
			// I really don't get why it is this way round...
			// This is "extracting" little endian data.
			// And while the files do seem to be little endian,
			// my architecture is as well! So what the hell...
			std::int16_t columnType = 0x0000;
			size_t shift = (ENTRY_SIZE - 1) * 8;

			for (size_t byte = 0; byte < ENTRY_SIZE; ++byte)
			{
				columnType |= (data[offset + byte] << shift);
				shift -= 8;
			}

			// The following two work nicely, but they don't swap the byte order.

			// 1: Using memcpy
			//std::int16_t columnType;
			//std::memcpy(&columnType, columnData + offset, 2);

			// 2: Using cast and pointers
			//std::int16_t columnType = *(reinterpret_cast<std::int16_t *>(columnData + offset));

			return columnType;
		}
}
