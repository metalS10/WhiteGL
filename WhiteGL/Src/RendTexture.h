#pragma once
/**
*RendTexture.h
*
*	2017/10/10	Mat
*		テクスチャの読み込み、描画
*/

#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "image.h"
#include "Vec2.h"
#include "Vec4.h"
#include "Constants.h"
#pragma warning(disable:4996)


enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
};
class CRendTexture
{
	
	int i = 0;
	GLuint g_texID;
	std::vector<CVec2> initializePos;
	std::vector<CVec2> endPos;
	std::vector<CVec4> rect;
	std::vector<TEX_TYPE> texType;
	CVec2 vec2;

public:

	/*
	void render()
	{
	static const GLfloat vtx[] = {
	0, 120,
	200, 120,
	200, 320,
	0, 320,
	};
	glVertexPointer(2, GL_FLOAT, 0, vtx);

	//テクスチャの領域指定
	static const GLfloat texuv[] = {
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	};



	/*
	//cameraPos
	gluLookAt(
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, -10.0f,
	0.0f, 1.0f, 0.0f
	);
	//
	glTranslated(0.0f, 0.0f, -579.41f);

	glTexCoordPointer(2, GL_FLOAT, 0, texuv);
	//テクスチャの画像指定
	glBindTexture(GL_TEXTURE_2D, g_texID);

	glDrawArrays(GL_QUADS, 0, 4);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	*/

	void render();
	

	/*
	void setupTexture(GLuint texID, const char *file, const int width, const int height)
	{
	// 画像データのロード
	std::ifstream fstr(file, std::ios::binary);
	assert(fstr);

	const size_t fileSize = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
	fstr.seekg(0, fstr.beg);
	std::vector<char> textureBuffer(fileSize);
	fstr.read(&textureBuffer[0], fileSize);

	//画像データとテクスチャiDを結びつける
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &textureBuffer[0]);

	//テクスチャの各種設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}
	*/

	/**
	*テクスチャの読み込み、IDの設定、画像範囲
	*
	*@param	texID	ID
	*@param	file	ファイルパス
	*@param	posLeft		画像の左の位置
	*@param	posRight	画像の右の位置
	*@param	posBottom	画像の下の位置
	*@param	posTop		画像の上の位置
	*@param	rect		矩形
	*/
	void setupTexture(const char *file, const float posLeft, const float posRight, const float posBottom, const float posTop, const CVec4 rect4, const TEX_TYPE tex_type);

	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
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
			memcpy(*outData + (row_bytes * (outHeight - 1 - i)), row_pointers[i], row_bytes);
		}

		/* Clean up after the read,
		* and free any memory allocated */
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

		/* Close the file */
		fclose(fp);
		/* That's it */
		return true;
	}
	
	

};