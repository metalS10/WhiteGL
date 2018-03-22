#include "RendTexture.h"

void CRendTexture::update(std::vector<CAnimation*>* anim)
{
	for (int i = 1 ; i <= anim->size();i++)
	{
		GLuint texID = i - 1;
		(*anim)[texID]->update();
		CVec4 texRect = (*anim)[texID]->getCurrentChip();



		glBindTexture(GL_TEXTURE_2D, g_texID[texID]);


		//画像の矩形範囲を設定
		CVec4 changerect4 = CVec4(texRect.x / tex[texID]->m_width, (texRect.x + texRect.z) / tex[texID]->m_width, texRect.y / tex[texID]->m_height, (texRect.y + texRect.w) / tex[texID]->m_height);
		rect[texID] = CVec4(changerect4);
	}
	this->fadeSearch();
}
void CRendTexture::fadeSearch()
{
	for (int i = 0;i <= MAX_TEXTURE_NUMBER;i++)
	{
		//フェードインアウト
		if (actionFade[i])
		{
			//フェードアウト
			if (fadeOut[i])
			{
				colorRGBA[i].w -= actionFadeInterval[i];
				if (colorRGBA[i].w <= 0.0f)
				{
					colorRGBA[i].w = 0.0f;
					actionFade[i] = false;
				}
			}
			//フェードイン
			else
			{
				colorRGBA[i].w += actionFadeInterval[i];
				if (colorRGBA[i].w >= 100.0f)
				{
					colorRGBA[i].w = 100.0f;
					actionFade[i] = false;
				}
			}

			glBindTexture(GL_TEXTURE_2D, g_texID[i]);
		}
	}
}

void CRendTexture::render()
{
	// The following two lines enable semi transparent
	glEnable(GL_BLEND);
	for (int texID = 0;texID < MAX_TEXTURE_NUMBER;texID++)
	{
		if (g_texID[texID] != 0)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


			if (texType[texID] == TEX_TYPE::BMP)
			{
				//場所指定
				const GLfloat vtx2[] = {
					_rectPos[texID].x, _rectPos[texID].z,
					_rectPos[texID].y, _rectPos[texID].z,
					_rectPos[texID].y, _rectPos[texID].w,
					_rectPos[texID].x, _rectPos[texID].w,
				};
				glVertexPointer(2, GL_FLOAT, 0, vtx2);

				const GLfloat color[] = {
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
				};
				glColorPointer(4, GL_FLOAT, 0, color);

				//テクスチャの領域指定
				const GLfloat texuv[] = {
					rect[texID].x, rect[texID].z,
					rect[texID].y, rect[texID].z,
					rect[texID].y, rect[texID].w,
					rect[texID].x, rect[texID].w,
				};
				//頂点の設定
				glTexCoordPointer(2, GL_FLOAT, 0, texuv);

			}
			else if (texType[texID] == TEX_TYPE::PNG)
			{
				//場所指定
				const GLfloat vtx2[] = {
					_rectPos[texID].x, _rectPos[texID].z,
					_rectPos[texID].y, _rectPos[texID].z,
					_rectPos[texID].y, _rectPos[texID].w,
					_rectPos[texID].x, _rectPos[texID].w,
				};
				glVertexPointer(2, GL_FLOAT, 0, vtx2);

				const GLfloat color[] = {
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,

				};
				glColorPointer(4, GL_FLOAT, 0, color);

				//テクスチャの領域指定
				const GLfloat texuv[] = {
					rect[texID].x, rect[texID].w,
					rect[texID].y, rect[texID].w,
					rect[texID].y, rect[texID].z,
					rect[texID].x, rect[texID].z,
				};
				//頂点の設定
				glTexCoordPointer(2, GL_FLOAT, 0, texuv);

			}
			else if (texType[texID] == TEX_TYPE::QUAD)
			{
				//場所指定
				const GLfloat vtx2[] = {
					_rectPos[texID].x, _rectPos[texID].z,
					_rectPos[texID].y, _rectPos[texID].z,
					_rectPos[texID].y, _rectPos[texID].w,
					_rectPos[texID].x, _rectPos[texID].w,
				};
				glVertexPointer(2, GL_FLOAT, 0, vtx2);

				const GLfloat color[] = {
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
					colorRGBA[texID].x*0.01f,colorRGBA[texID].y*0.01f,colorRGBA[texID].z*0.01f,colorRGBA[texID].w*0.01f,
				};
				glColorPointer(4, GL_FLOAT, 0, color);

				//テクスチャの領域指定
				const GLfloat texuv[] = {
					rect[texID].x, rect[texID].w,
					rect[texID].y, rect[texID].w,
					rect[texID].y, rect[texID].z,
					rect[texID].x, rect[texID].z,
				};
				//頂点の設定
				glTexCoordPointer(2, GL_FLOAT, 0, texuv);
			}

			//テクスチャの画像指定
			glBindTexture(GL_TEXTURE_2D, g_texID[texID]);
			//四角ポリゴン表示
			glDrawArrays(GL_QUADS, 0, 4);



			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
	}
}

void CRendTexture::setupTexture(const char *file, const TEX_TYPE tex_type, GLuint texID)
{
	//texIDを空いているところへ
	glGenTextures(1, &g_texID[texID]);

	//画像データとテクスチャiDを結びつける
	glBindTexture(GL_TEXTURE_2D, g_texID[texID]);

	texScale[texID] = CVec2(1, 1);

	switch (tex_type)
	{
	case TEX_TYPE::BMP:
		tex[texID] = new CBmpImage();
		if (tex[texID]->load(file) == false)
		{
			std::cerr << "ERROR : 画像の読み込みに失敗" << std::endl;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex[texID]->m_width, tex[texID]->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex[texID]->m_bits);

		break;

	case TEX_TYPE::PNG:
		tex[texID] = new CPngImage();
		if (tex[texID]->load(file) == false)
		{
			std::cerr << "ERROR : 画像の読み込みに失敗" << std::endl;
		}

		if (tex[texID]->m_format == PNG_COLOR_TYPE_RGBA)
		{
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex[texID]->m_width, tex[texID]->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex[texID]->m_bits);
		}
		else if (tex[texID]->m_format == PNG_COLOR_TYPE_RGB)
		{
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex[texID]->m_width, tex[texID]->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex[texID]->m_bits);
		}
		else if (tex[texID]->m_format == PNG_COLOR_TYPE_PALETTE)
		{
			GLubyte* textureImage;		

			int width, height;
			bool hasAlpha = true;	//とりあえずPngはAlphaあるでしょ
			const char* filename = file;
			bool success = loadPngImage(filename, width, height, hasAlpha, &textureImage);
			if (!success) {
				std::cout << "Unable to load png file" << std::endl;
				return;
			}
			std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
				height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
				textureImage);

			SAFE_DELETE(textureImage);
		}
		else if (tex[texID]->m_format == PNG_COLOR_TYPE_GRAY)
		{
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, tex[texID]->m_width, tex[texID]->m_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, tex[texID]->m_bits);
			//grayってどう描画するんだろう
		}

		break;

	case TEX_TYPE::QUAD:
		tex[texID] = new CPngImage();

		tex[texID]->m_width = 1;tex[texID]->m_height = 1;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ONE, 1, 1, 0, GL_ONE, GL_UNSIGNED_BYTE, 0);
		break;


	default:
		break;
	}
	//初期化
	glBindTexture(GL_TEXTURE_2D, 0);

	colorRGBA[texID] = (CVec4(100.0f, 100.0f, 100.0f, 100.0f));
	texType[texID] = (tex_type);
}

void CRendTexture::setupTextureSize(const CVec2 texPos,const CVec4 texRect,const GLuint texID)
{
	//glBindTexture(GL_TEXTURE_2D, g_texID[texID]);

	//float Xright = texRect.x + texRect.z;
	//float Ytop = texRect.y + texRect.w;

	//横幅縦幅をセット
	texWH[texID] = CVec2(((texRect.x + texRect.z) - texRect.x) * 0.5f, ((texRect.y + texRect.w) - texRect.y) * 0.5f);
	_rectPos[texID] = CVec4(texPos.x - texWH[texID].x, texPos.x + texWH[texID].x, texPos.y - texWH[texID].y, texPos.y + texWH[texID].y);
	_position[texID] = texPos;

	//画像の矩形範囲を設定
	CVec4 changerect4 = CVec4(texRect.x / tex[texID]->m_width, (texRect.x + texRect.z) / tex[texID]->m_width, texRect.y / tex[texID]->m_height, (texRect.y + texRect.w) / tex[texID]->m_height);
	rect[texID] = CVec4(changerect4);
	
	
	

	if (tex[texID] == NULL)
	{
		std::cerr << "BMP,PNG,JPEGなんでもないです" << std::endl;
	}
}

void CRendTexture::deleteTexture(const GLuint texID)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &g_texID[texID]);
	g_texID[texID] = 0;
	rect[texID] = {};
	_rectPos[texID] = {};
}

bool CRendTexture::loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	FILE *fp;

	if ((fp = fopen(name, "rb")) == NULL)
		return false;

	/* Create and initialize the png_struct
	* with the desired error handler
	* functions.  If you want to use the
	* default stderr and longjump method,
	* you can supply NULL for the last
	* three parameters.  We also supply the
	* the compiler header file version, so
	* that we know if the application
	* was compiled with a compatible version
	* of the library.  REQUIRED
	*/
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL);

	if (png_ptr == NULL) {
		fclose(fp);
		return false;
	}

	/* Allocate/initialize the memory
	* for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	/* Set error handling if you are
	* using the setjmp/longjmp method
	* (this is the normal method of
	* doing things with libpng).
	* REQUIRED unless you  set up
	* your own error handlers in
	* the png_create_read_struct()
	* earlier.
	*/
	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated
		* with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		/* If we get here, we had a
		* problem reading the file */
		return false;
	}

	/* Set up the output control if
	* you are using standard C streams */
	png_init_io(png_ptr, fp);

	/* If we have already
	* read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);

	/*
	* If you have enough memory to read
	* in the entire image at once, and
	* you need to specify only
	* transforms that can be controlled
	* with one of the PNG_TRANSFORM_*
	* bits (this presently excludes
	* dithering, filling, setting
	* background, and doing gamma
	* adjustment), then you can read the
	* entire image (including pixels)
	* into the info structure with this
	* call
	*
	* PNG_TRANSFORM_STRIP_16 |
	* PNG_TRANSFORM_PACKING  forces 8 bit
	* PNG_TRANSFORM_EXPAND forces to
	*  expand a palette into RGB
	*/
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 width, height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
		&interlace_type, NULL, NULL);
	outWidth = width;
	outHeight = height;

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*outData = (unsigned char*)malloc(row_bytes * outHeight);

	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < outHeight; i++) {
		// note that png is ordered top to
		// bottom, but OpenGL expect it bottom to top
		// so the order or swapped
		memcpy(*outData + (row_bytes * i), row_pointers[i], row_bytes);
	}

	/* Clean up after the read,
	* and free any memory allocated */
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	/* Close the file */
	fclose(fp);
	/* That's it */
	return true;
}

void CRendTexture::setupTextureColor(const CVec4 color, const GLuint texID)
{
	colorRGBA[texID] = color;
}

void CRendTexture::TextureFade(const GLuint texID, const bool out,const float fadeInterval)
{
	actionFade[texID] = true;
	actionFadeInterval[texID] = fadeInterval;
	fadeOut[texID] = out;
	this->fadeSearch();

}

void CRendTexture::setScale(const CVec2 Size, const GLuint texID)
{
	texScale[texID] = Size;
	_rectPos[texID] = CVec4(_position[texID].x - texWH[texID].x * Size.x, _position[texID].x + texWH[texID].x * Size.x, _position[texID].y - texWH[texID].y * Size.y, _position[texID].y + texWH[texID].y * Size.y);
}

void CRendTexture::setPosition(const CVec2 position, const GLuint texID)
{
	_position[texID] = position;
	_rectPos[texID] = CVec4(
		_position[texID].x - texWH[texID].x * texScale[texID].x,
		_position[texID].x + texWH[texID].x * texScale[texID].x,
		_position[texID].y - texWH[texID].y * texScale[texID].y,
		_position[texID].y + texWH[texID].y * texScale[texID].y);
}

void CRendTexture::setMapPosition(const CVec2 position, const GLuint texID)
{
	_position[texID] = position;
	CVec4 defrect = _rectPos[texID];
	_rectPos[texID] = CVec4(_position[texID].x + defrect.x, _position[texID].x + defrect.y, _position[texID].y + defrect.z, _position[texID].y + defrect.w);
}


void CRendTexture::setTextureRect(const CVec4 Rect,const GLuint texID)
{
	glBindTexture(GL_TEXTURE_2D, g_texID[texID]);


	//画像の矩形範囲を設定
	CVec4 changerect4 = CVec4(Rect.x / tex[texID]->m_width, (Rect.x + Rect.z) / tex[texID]->m_width, Rect.y / tex[texID]->m_height, (Rect.y + Rect.w) / tex[texID]->m_height);

	rect[texID] = CVec4(changerect4);
}

void CRendTexture::SetProgressBarWH(const GLuint texID,const CVec4 Rect, const CVec2 position)
{
	CVec2 vec2;
	glBindTexture(GL_TEXTURE_2D, g_texID[texID]);
	if (Rect.z >= 0)
	{
		texWH[texID] = CVec2(Rect.z, 5.0f);
		vec2 = CVec2(position.x + Rect.z, position.y);
	}
	else
	{
		texWH[texID] = CVec2(0.0f, 5.0f);
		vec2 = CVec2(position.x + 0.0f, position.y);
	}
	_position[texID] = vec2;
	_rectPos[texID] = CVec4(
		_position[texID].x - texWH[texID].x * texScale[texID].x,
		_position[texID].x + texWH[texID].x * texScale[texID].x,
		_position[texID].y - texWH[texID].y * texScale[texID].y,
		_position[texID].y + texWH[texID].y * texScale[texID].y);
	

}

void CRendTexture::allTextureDelete()
{
	for (int i = 0;i < MAX_TEXTURE_NUMBER;i++)
	{
		if (i != MAX_TEXTURE_NUMBER - 1)
		{
			deleteTexture(i);
			SAFE_DELETE(tex[i]);
		}
	}
}
void CRendTexture::allTextureDeletenotPlayer()
{
	for (int i = 0;i < MAX_TEXTURE_NUMBER;i++)
	{
		if (i != PLAYER_ID && i != MAX_TEXTURE_NUMBER - 1 && i > 10)
		{
			deleteTexture(i);
			SAFE_DELETE(tex[i]);
		}
	}
}