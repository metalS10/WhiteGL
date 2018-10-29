#include "GameEngine.h"
#include "../GLFWEW/GLFWEW.h"


CGameEngine::CGameEngine()
{

}
CGameEngine::~CGameEngine()
{

}
//描画初期化(ステージ移動時等)
void CGameEngine::renderInit()
{
	m_renderer->init();
}
void CGameEngine::changeStageInit()
{
	m_renderer->changeStageInit();
}

GLFWwindow* CGameEngine::init(int w,int h,const char* file)
{

	m_renderer = new render::CRenderer();

	if (isInitialized)
	{
		return m_Window;
	}
	m_Window = GLFWEW::Window::Instance().Init(w, h, file);
	if (m_Window == NULL)
	{
		return NULL;
	}

	//GL_TRUE/GL_FALSEはOpenGLの真偽値マクロ
	//OpenGLおよびGLFWの初期化、成功するとGL_TRUEが返ってくる
	if (glfwInit() != GL_TRUE)
	{
		return NULL;
	}

	/*
	*memo
	*glfwCreateWindowはグラフィックス描画用のウィンドウを作成する関数
	*	引数:描画範囲の縦、横、ウィンドウのタイトルバーに表示される文字、フルスクリーンモード用のパラメータ
	*/
	if (!m_Window)
	{
		glfwTerminate();
		return NULL;
	}

	//指定したウィンドウに対応するOpenGLコンテキストを描画対象に設定する関数
	glfwMakeContextCurrent(m_Window);
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
		return NULL;
	}
	glOrtho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1.0f, 1.0f);

	isInitialized = true;

	return m_Window;
}

/**
*ゲームエンジンのインスタンスを取得する
*
*@return ゲームエンジンのインスタンス
*/
CGameEngine& CGameEngine::Instance()
{
	static CGameEngine instance;
	return instance;
}

/**
*	ゲームパッドの状態を取得する
*/
const GamePad& CGameEngine::GetGamePad() const
{
	return GLFWEW::Window::Instance().GetGamePad();
}


void CGameEngine::update()
{
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();

	m_renderer->render();

	//renderer->update(m_pAnim);
	/*
	GameEngine& game = GameEngine::Instance();
	const GamePad gamepad = game.GetGamePad();
	if (gamepad.buttons !=0 )
	{
	//GamePad::DPAD_LEFT

	}
	*/
}

void CGameEngine::update60()
{
	

	if (m_hitStop > 0)
	{
		m_hitStop--;
	}
	else if (m_hitStop < 0)
	{
		m_hitStop = 0;
	}
}




void CGameEngine::GameEnd()
{
	gameNow = false;
}




void CGameEngine::HitStop(float time)
{
	m_hitStop = time;
}

render::CRenderer* CGameEngine::getRenderer()
{
	return m_renderer;
}

