#pragma once

#include "GL/glew.h"
#pragma warning(disable:4996)

namespace loadImage
{
	class CLoadImage
	{
	public:
		//PngImageのロード関数(これだけめちゃくちゃ長いので分けました)
		static bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

		
	};
}