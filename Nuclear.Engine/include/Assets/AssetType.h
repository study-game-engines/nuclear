#pragma once
#include <NE_Common.h>

namespace Nuclear
{
	namespace Assets
	{
		enum class AssetType : Uint8
		{
			Unknown,
			Scene,

			Texture,				//Importing & Loading done
			Mesh,
			Material,
			Animations,
			AudioClip,
			Font,
			Shader,
			Script
		};

	}
}