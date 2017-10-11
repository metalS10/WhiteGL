/**
*	main.cpp
*		2017/09/29	Mats
*/

#include "Constants.h"
#include "GameMain.h"
#include "RendTexture.h"



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

	CRendTexture* rendTex = new CRendTexture();

	rendTex->setupTexture(PASS"Sparrow.bmp", 0.0f, 200.0f, 100.0f, 300.0f, CVec4(0.0f, 200.0f, 0.0f, 200.0f),TEX_TYPE::BMP);

	rendTex->setupTexture(PASS"Sparrow.bmp", 200.0f, 400.0f, 100.0f, 300.0f, CVec4(100.0f, 200.0f, 100.0f, 200.0f),TEX_TYPE::BMP);

	rendTex->setupTexture(PASS"player.bmp", 400.0f, 464.0f, 100.0f, 164.0f, CVec4(0.0f, 64.0f, 128.0f, 192.0f), TEX_TYPE::BMP);

	rendTex->setupTexture(PASS"kuribo.png", 0.0f, 100.0f, 300.0f, 400.0f, CVec4(0.0f, 64.0f, 0.0f, 64.0f),TEX_TYPE::PNG);

	rendTex->setupTexture(PASS"kuribo.png", 100.0f, 300.0f, 300.0f, 500.0f, CVec4(0.0f, 64.0f, 0.0f, 64.0f), TEX_TYPE::PNG);


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

		rendTex->render();
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
