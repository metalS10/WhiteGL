/**
*	main.cpp
*		2017/09/29	Mats
*/

#include "Constants.h"
#include "GameMain.h"
#include "RendTexture.h"
#include "FPS.h"
#include "Animation.h"


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
	
	rendTex->setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 0);
	rendTex->setupTextureSize(CVec4(0.0f, 200.0f, 100.0f, 300.0f), CVec4(0.0f, 200.0f, 0.0f, 200.0f), 0);


	rendTex->setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 1);
	rendTex->setupTextureSize(CVec4(200.0f, 400.0f, 100.0f, 300.0f), CVec4(100.0f, 200.0f, 100.0f, 200.0f), 1);

	rendTex->setupTexture(PASS"player.bmp", TEX_TYPE::BMP, 2);
	rendTex->setupTextureSize(CVec4(400.0f, 464.0f, 100.0f, 164.0f), CVec4(0.0f, 64.0f, 128.0f, 192.0f), 2);

	rendTex->setupTexture(PASS"kuribo.png", TEX_TYPE::PNG, 3);
	rendTex->setupTextureSize(CVec4(0.0f, 100.0f, 300.0f, 400.0f), CVec4(0.0f, 64.0f, 0.0f, 64.0f), 3);

	rendTex->setupTexture(PASS"player.png", TEX_TYPE::PNG, 4);
	rendTex->setupTextureSize(CVec4(100.0f, 200.0f, 300.0f, 400.0f), CVec4(0.0f, 64.0f, 0.0f, 64.0f), 4);

	


	gameMain = new CGameMain();
	FPS *fps = new FPS(60);//秒間60フレーム(可変sleep)

	int i = 0;
	int j = 0;
	std::vector<CAnimation*>* m_pAnim = new std::vector<CAnimation*>();
	m_pAnim->push_back(new CNotAnimation());
	m_pAnim->push_back(new CNotAnimation());
	m_pAnim->push_back(new CNotAnimation());
	m_pAnim->push_back(new CNotAnimation());
	m_pAnim->push_back(new CListAnimation(60,true));

	(*m_pAnim)[0]->addChipData(new CVec4(0.0f, 200.0f, 0.0f, 200.0f));
	(*m_pAnim)[1]->addChipData(new CVec4(100.0f, 200.0f, 100.0f, 200.0f));
	(*m_pAnim)[2]->addChipData(new CVec4(0.0f, 64.0f, 128.0f, 192.0f));
	(*m_pAnim)[3]->addChipData(new CVec4(0.0f, 64.0f, 0.0f, 64.0f));

	(*m_pAnim)[4]->addChipData(new CVec4(0.0f, 64.0f, 0.0f, 64.0f));
	(*m_pAnim)[4]->addChipData(new CVec4(64.0f, 128.0f, 0.0f, 64.0f));
	(*m_pAnim)[4]->addChipData(new CVec4(128.0f, 192.0f, 0.0f, 64.0f));





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

		fps->GetFPS();//FPSを得る
		if (fps->draw) {//秒間60フレームのタイミングで描画
			rendTex->update(m_pAnim);

			int l = 0;
		}

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
