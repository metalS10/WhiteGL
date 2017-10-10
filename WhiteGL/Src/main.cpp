/**
*	main.cpp
*		2017/09/29	Mats
*/

#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Constants.h"
#include "GameMain.h"
#include "image.h"
#include "Vec2.h"
#include "Vec4.h"


enum class COL_TYPE : int
{
	RGB = 0,
	RGBA = 1,
};

enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
};

GLuint g_texID;
std::vector<CVec2> initializePos;
std::vector<CVec2> endPos;
std::vector<CVec4> rect;
std::vector<TEX_TYPE> texType;

CGameMain* gameMain;

/**
*GLFWからのエラー報告を処理する
*
*@param	error	エラー番号
*@para,	desc	エラー内容
*/
void ErrorCallback(int error, const char* desc)
{
	std::cerr << "ERROR : " << desc << std::endl;
}


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

void render()
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
void setupTexture(GLuint texID, const char *file, const float posLeft, const float posRight, const float posBottom, const float posTop, const CVec4 rect4, const TEX_TYPE tex_type)
{
	CImage* tex = NULL;

	//画像データとテクスチャiDを結びつける
	glBindTexture(GL_TEXTURE_2D, texID);

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
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_MAX_PALETTE_MATRICES_ARB, tex->m_width, tex->m_height, 0, GL_MAX_PALETTE_MATRICES_ARB, GL_UNSIGNED_BYTE, tex->m_bits);
			//paletteってどう描画するんだろう
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
}


/**
*	@file main.cpp
*/
//エントリーポイント
int main()
{
	glfwSetErrorCallback(ErrorCallback);

	//GL_TRUE/GL_FALSEはOpenGLの真偽値マクロ
	//OpenGLおよびGLFWの初期化、成功するとGL_TRUEが返ってくる
	if (glfwInit() != GL_TRUE)
	{
		return 1;
	}

	/*
	*memo
	*glfwCreateWindowはグラフィックス描画用のウィンドウを作成する関数
	*	引数:描画範囲の縦、横、ウィンドウのタイトルバーに表示される文字、フルスクリーンモード用のパラメータ
	*/
	GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE, "WhiteGL", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}

	//指定したウィンドウに対応するOpenGLコンテキストを描画対象に設定する関数
	glfwMakeContextCurrent(window);
	/*
	*memo
	*GLFWの次はGLEWの初期化
	*GLEWには終了させる関数がない、
	*	GLEWは複雑な終了処理を必要とするオブジェクトを作成しないため
	*	デフォルトの終了方法で十分
	*/
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "ERROR : GLEWの初期化に失敗。" << std::endl;
		glfwTerminate();
		return 1;
	}

	/*
	// モニタとの同期
	glfwSwapInterval(1);

	// 描画範囲の指定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, g_windowWidth, 0.0f, g_windowHeight, -1.0f, 1.0f);

	//テクスチャのロード
	glGenTextures(1, &g_texID);
	setupTexture(g_texID, PASS"Sparrow.bmp", 200, 200);
	*/
	// モニタとの同期
	//glfwSwapInterval(1);

	// 描画範囲の指定
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	glOrtho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);

	//================================
	//テクスチャの描画
	//================================
	//使用許可
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	setupTexture(g_texID, PASS"Sparrow.bmp", 0.0f, 200.0f, 100.0f, 300.0f, CVec4(0.0f, 200.0f, 0.0f, 200.0f), TEX_TYPE::BMP);

	setupTexture(g_texID, PASS"Sparrow.bmp", 200.0f, 400.0f, 100.0f, 300.0f, CVec4(100.0f, 200.0f, 100.0f, 200.0f),TEX_TYPE::BMP);

	setupTexture(g_texID, PASS"player.bmp", 400.0f, 464.0f, 100.0f, 164.0f, CVec4(0.0f, 64.0f, 128.0f, 192.0f), TEX_TYPE::BMP);

	setupTexture(g_texID, PASS"kuribo.png", 0.0f, 320.0f, 300.0f, 492.0f, CVec4(0.0f, 320.0f, 0.0f, 192.0f),TEX_TYPE::PNG);

	//透過設定
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gameMain = new CGameMain();

	/**
	*memo
	*メインループ
	*毎フレーム実行される
	*glfwWindowShouldCloseはウィンドウを閉じるべきかどうかを調べる関数
	*	引数で渡されたウィンドウに対してOS等から終了要求が来ていなければ0,着ていれば0以外を返す
	*GLFWで作成したウィンドウが1つだけなら終了判定はこの関数を見るだけで十分
	*/
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		render();
		gameMain->update();

		glfwSwapBuffers(window);
	}

	/*
	if (glfwWindowShouldClose(window))
	{
	return 0;
	}
	*/
	//描画使用許可の破棄
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glfwTerminate();

	return 0;
}
