#pragma once

#include "GL/glew.h"
#pragma warning(disable:4996)

namespace loadImage
{
	class CLoadImage
	{
	public:
		//PngImage‚Ìƒ[ƒhŠÖ”(‚±‚ê‚¾‚¯‚ß‚¿‚á‚­‚¿‚á’·‚¢‚Ì‚Å•ª‚¯‚Ü‚µ‚½)
		static bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

		
	};
}