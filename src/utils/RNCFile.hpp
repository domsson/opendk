#pragma once

#include <cstdint>

namespace OpenDK
{

	class RNCFile
	{
	public:

		static const std::uint32_t MAGIC_NUMBER;

		RNCFile();

		//void compress();
		void extract();

		//returntype getData() const;
		//void toFile(const std::string& filePath) const;

	private:

		/* Size of the original file */
		std::uint32_t extractedSize; // offset 4, size 4

		/* Size of the RNC data (excluding header) */
		std::uint32_t compressedSize; // offset 8, size 4

		/* Checksum of the original file */
		std::uint16_t extractedCRC; // offset 12, size 2

		/* Checksum of the RNC data */
		std::uint16_t compressedCRC; // offset 14, size 2

		/* Difference between compressed and uncompressed data in largest pack chunk (if larger than decompressed data) */
		std::uint8_t leeway; // offset 16, size 1

		/* Amount of pack chunks */
		std::uint8_t packCount; // offset 17, size 1
	};

}

// https://github.com/CorsixTH/CorsixTH/wiki/RNC
// http://segaretro.org/Rob_Northen_compression
