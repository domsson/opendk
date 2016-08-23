#include "CubeDataFile.hpp"

namespace OpenDK
{

		const size_t CubeDataFile::EXPECTED_FILE_SIZE = 9220;
		//const size_t CubeDataFile::HEADER_SIZE = 22;
		const size_t CubeDataFile::HEADER_SIZE = 4;
		const size_t CubeDataFile::CHUNK_SIZE = 18;
		const size_t CubeDataFile::ENTRY_SIZE = 2;

		CubeDataFile::CubeDataFile()
		: data(nullptr), size(0)
		{
		}

		CubeDataFile::CubeDataFile(const std::string& filePath)
		: data(nullptr), size(0)
		{
			load(filePath);
		}

		CubeDataFile::~CubeDataFile()
		{
			delete[] data;
		}

		bool CubeDataFile::load(const std::string& filePath)
		{
			std::ifstream is(filePath, std::ifstream::binary | std::ifstream::in);
			if (!is.is_open())
			{
				std::cerr << typeid(this).name() << ": [ERR] Could not open file" << filePath << std::endl;
				return false;
			}

			is.seekg (0, is.end);
			int length = is.tellg();
			is.seekg (0, is.beg);

			if (length != EXPECTED_FILE_SIZE)
			{
				std::cerr << typeid(this).name() << ": [ERR] Refusing to open cube file, size mismatch: "
						<< length << " found, expected " << EXPECTED_FILE_SIZE << std::endl;
				return false;
			}

			size = length - HEADER_SIZE;
			data = new char [size];

			// TODO We should do like we did with one of the other files:
			// Only read in the actual payload. Ignore the useless 6 bytes
			// of padding (or 'flags') after each cube entry.

			is.seekg(HEADER_SIZE);
			is.read(data, size);
			is.close();

			return true;
		}

		size_t CubeDataFile::getSize() const
		{
			return size;
		}

		std::int16_t CubeDataFile::getCubeSprite(int cubeIndex, int cubeSide) const
		{
			if (cubeSide < 0 || cubeSide > 5)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get cube sprite, "
						<< "given side value is invalid - should be in the range 0..5" << std::endl;
				return -1;
			}

			size_t offset = (cubeIndex * CHUNK_SIZE) + (cubeSide * ENTRY_SIZE);

			if (offset + ENTRY_SIZE > size)
			{
				std::cerr << typeid(this).name() << ": [ERR] Can't get cube sprite, "
						<< "given cube index is out of range: " << cubeIndex << std::endl;
				return -1;
			}

			/*
			std::int16_t cubeSprite = 0x0000;
			size_t shift = (ENTRY_SIZE - 1) * 8;

			for (size_t byte = 0; byte < ENTRY_SIZE; ++byte)
			{
				cubeSprite |= (data[offset + byte] << shift);
				shift -= 8;
			}

			return cubeSprite;
			*/

			return *(reinterpret_cast<std::int16_t *>(data + offset));
		}
}
