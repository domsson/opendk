#pragma once

namespace OpenDK
{

	enum ShaderAttribute
	{
		POSITION = 0,	// Vertex positions (geometry itself)
		COLOR    = 1,	// Vertex colors
		TEXTURE  = 2,	// Texture unwrap coordinates
		NORMALS  = 3,	// Vertex normals
		LIGHT    = 4,	// Light level (brightness)
		SPRITE   = 5	// Sprite/texture index
	};

}
