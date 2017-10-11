#include "RendTexture.h"

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

void CRendTexture::setupTexture(const char *file, const float posLeft, const float posRight, const float posBottom, const float posTop, const CVec4 rect4, const TEX_TYPE tex_type)
{
	CImage* tex = NULL;

	//画像データとテクスチャiDを結びつける
	glBindTexture(GL_TEXTURE_2D, g_texID);

	switch (tex_type)
	{
	case TEX_TYPE::BMP:
		tex = new CBmpImage();
		if (tex->load(file) == false)
		{
			std::cerr << "ERROR : 画像の読み込みに失敗" << std::endl;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->m_width, tex->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->m_bits);

		break;

	case TEX_TYPE::PNG:
		tex = new CPngImage();
		if (tex->load(file) == false)
		{
			std::cerr << "ERROR : 画像の読み込みに失敗" << std::endl;
		}

		if (tex->m_format == PNG_COLOR_TYPE_RGBA)
		{
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->m_width, tex->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->m_bits);
		}
		else if (tex->m_format == PNG_COLOR_TYPE_RGB)
		{
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->m_width, tex->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->m_bits);
		}
		else if (tex->m_format == PNG_COLOR_TYPE_PALETTE)
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
		else if (tex->m_format == PNG_COLOR_TYPE_GRAY)
		{
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, tex->m_width, tex->m_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, tex->m_bits);
			//grayってどう描画するんだろう
		}
		break;

	default:
		break;
	}


	//色々設定
	initializePos.push_back(CVec2(posLeft, posBottom));
	endPos.push_back(CVec2(posRight, posTop));
	texType.push_back(tex_type);

	//画像の矩形範囲を設定
	CVec4 changerect4 = CVec4(rect4.x / tex->m_width, rect4.y / tex->m_width, rect4.z / tex->m_height, rect4.w / tex->m_height);
	rect.push_back(CVec4(changerect4));

	//texIDを空いているところへ
	glGenTextures(1, &g_texID);

	if (tex == NULL)
	{
		std::cerr << "BMP,PNG,JPEGなんでもないです" << std::endl;
	}
	else
	{
		SAFE_DELETE(tex);
	}
}
