#include "RendTexture.h"

void CRendTexture::update(std::vector<CAnimation*>* anim)
{
	for (int i = 0 ; i <= anim->size();i++)
	{
		

		CVec4* texRect = (*anim)[i]->animUpdate();

		glBindTexture(GL_TEXTURE_2D, (GLuint)i);



		//画像の矩形範囲を設定
		CVec4 changerect4 = CVec4(texRect->x / tex[i]->m_width, texRect->y / tex[i]->m_width, texRect->z / tex[i]->m_height, texRect->w / tex[i]->m_height);
		if (rect.size() <= i)
		{
			rect.push_back(CVec4(changerect4));

			//texIDを空いているところへ
			glGenTextures(1, &g_texID);
		}
		else
			rect[i] = CVec4(changerect4);

		
	}
}

void CRendTexture::render()
{
	for (int texID = 0;texID < g_texID;texID++)
	{
		if (texType[texID] == TEX_TYPE::BMP)
		{
			//場所指定
			const GLfloat vtx2[] = {
				initializePos[texID].x, initializePos[texID].y,
				endPos[texID].x, initializePos[texID].y,
				endPos[texID].x, endPos[texID].y,
				initializePos[texID].x, endPos[texID].y,
			};
			glVertexPointer(2, GL_FLOAT, 0, vtx2);

			//テクスチャの領域指定
			const GLfloat texuv[] = {
				rect[texID].x, rect[texID].z,
				rect[texID].y, rect[texID].z,
				rect[texID].y, rect[texID].w,
				rect[texID].x, rect[texID].w,
			};
			//頂点の設定
			glTexCoordPointer(2, GL_FLOAT, 0, texuv);

			//テクスチャの画像指定
			glBindTexture(GL_TEXTURE_2D, texID);
		}
		else if (texType[texID] == TEX_TYPE::PNG)
		{
			//場所指定
			const GLfloat vtx2[] = {
				initializePos[texID].x, initializePos[texID].y,
				endPos[texID].x, initializePos[texID].y,
				endPos[texID].x, endPos[texID].y,
				initializePos[texID].x, endPos[texID].y,
			};
			glVertexPointer(2, GL_FLOAT, 0, vtx2);

			//テクスチャの領域指定
			const GLfloat texuv[] = {
				rect[texID].x, rect[texID].w,
				rect[texID].y, rect[texID].w,
				rect[texID].y, rect[texID].z,
				rect[texID].x, rect[texID].z,
			};
			//頂点の設定
			glTexCoordPointer(2, GL_FLOAT, 0, texuv);

			//テクスチャの画像指定
			glBindTexture(GL_TEXTURE_2D, texID);
		}

		//四角ポリゴン表示
		glDrawArrays(GL_QUADS, 0, 4);



		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}

void CRendTexture::setupTexture(const char *file, const TEX_TYPE tex_type, GLuint texID)
{

	//画像データとテクスチャiDを結びつける
	glBindTexture(GL_TEXTURE_2D, texID);

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
			// The following two lines enable semi transparent
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			int width, height;
			bool hasAlpha;
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

	default:
		break;
	}


	texType.push_back(tex_type);
}

void CRendTexture::setupTextureSize(CVec4 texSize, CVec4 texRect, GLuint texID)
{
	glBindTexture(GL_TEXTURE_2D, texID);
	
	//色々設定
	if (initializePos.size() <= texID)
	initializePos.push_back(CVec2(texSize.x, texSize.z));
	else
	initializePos[texID] = CVec2(texSize.x, texSize.z);

	if (endPos.size() <= texID)
	endPos.push_back(CVec2(texSize.y, texSize.w));
	else
	endPos[texID] = CVec2(texSize.y, texSize.w);


	//画像の矩形範囲を設定
	CVec4 changerect4 = CVec4(texRect.x / tex[texID]->m_width, texRect.y / tex[texID]->m_width, texRect.z / tex[texID]->m_height, texRect.w / tex[texID]->m_height);
	if (rect.size() <= texID)
	{
		rect.push_back(CVec4(changerect4));

		//texIDを空いているところへ
		glGenTextures(1, &g_texID);
	}
	else
	rect[texID] = CVec4(changerect4);
	
	

	if (tex[texID] == NULL)
	{
		std::cerr << "BMP,PNG,JPEGなんでもないです" << std::endl;
	}
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