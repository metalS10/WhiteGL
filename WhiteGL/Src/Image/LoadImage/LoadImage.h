#pragma once

#include "GL/glew.h"
#pragma warning(disable:4996)

namespace loadImage
{
	class CLoadImage
	{
	public:
		//PngImage�̃��[�h�֐�(���ꂾ���߂��Ⴍ���ᒷ���̂ŕ����܂���)
		static bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

		
	};
}