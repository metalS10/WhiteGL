#include "GameEngine.h"




void CGameEngine::setupTexture(const char* file,TEX_TYPE texType,GLuint texID,CVec2 texPos,CVec4 texRect,CVec4 color)
{
	//================================
	//テクスチャの描画
	//================================
	//使用許可
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//色データをメモリに登録するための許可を得る
	glEnableClientState(GL_COLOR_ARRAY);

	if (rendTex == NULL)
		rendTex = new CRendTexture();

	rendTex->setupTexture(file, texType, texID);
	rendTex->setupTextureSize(texPos, texRect , texID);
	rendTex->setupTextureColor(color, texID);
}

void CGameEngine::setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect)
{
	//================================
	//テクスチャの描画
	//================================
	//使用許可
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//色データをメモリに登録するための許可を得る
	glEnableClientState(GL_COLOR_ARRAY);

	if (rendTex == NULL)
		rendTex = new CRendTexture();

	rendTex->setupTexture(file, texType, texID);
	rendTex->setupTextureSize(texPos, texRect, texID);
	rendTex->setupTextureColor(CVec4(100.0f,100.0f,100.0f,100.0f), texID);
}

void CGameEngine::setChipAnim(CAnimation *&&_val)
{
	m_pAnim->push_back(_val);
}

void CGameEngine::setChipData(GLuint texID,CVec4 rectData)
{
	(*m_pAnim)[texID]->addChipData(new CVec4(rectData));
}


GLFWwindow* CGameEngine::init(int w,int h,const char* file)
{
	if (isInitialized)
	{
		return m_Window;
	}
	m_Window = GLFWEW::Window::Instance().Init(w, h, file);
	if (m_Window == NULL)
	{
		return NULL;
	}
	m_pAnim = new std::vector<CAnimation*>();

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
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();

	rendTex->render();

	//rendTex->update(m_pAnim);
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
	rendTex->update(m_pAnim);
}
void CGameEngine::setScale(CVec2 scale, GLuint texID)
{
	rendTex->setScale(scale, texID);
}

void CGameEngine::inputKeyA()
{
	rendTex->TextureFade(6, true);
	//rendTex->deleteTexture(2);
}
void CGameEngine::inputKeyS()
{
	rendTex->TextureFade(6, false);
}
void CGameEngine::inputKeyZ()
{
	rendTex->setScale(CVec2(1, 1), 4);
}
void CGameEngine::inputKeyX()
{
	rendTex->setScale(CVec2(2, 2), 4);
}

void CGameEngine::setTextureRect(const CVec4 mrect,const GLuint texID)
{	
	rendTex->setTextureRect(mrect,texID);
}

void CGameEngine::setPosition(CVec2 pos, GLuint texID)
{
	rendTex->setPosition(pos, texID);
}

void CGameEngine::deleteTexture(const GLuint texID)
{
	rendTex->deleteTexture(texID);
}

void CGameEngine::loadTMXMap(CLayerData layerData,int width,int height)
{
	int countW = 0;
	int countH = height-1;
	int tileID = 0;
	for (int i = 0 ;i < layerData.m_gid.size();i++)
	{
		if (layerData.m_gid[i] != 0)
		{
			int gidten = (int)((layerData.m_gid[i] - layerData.m_firstgid + 1) / layerData.m_columns < 0.0 ? (layerData.m_gid[i] - layerData.m_firstgid + 1) / layerData.m_columns - 0.9 : (layerData.m_gid[i] - layerData.m_firstgid + 1) / layerData.m_columns);
			int gidone = (layerData.m_gid[i] - layerData.m_firstgid + 1) % (layerData.m_columns);
			float rectL = layerData.m_tileWidth * gidone - layerData.m_tileWidth;
			float rectB = layerData.m_tileHeight * gidten;
			setupTexture(layerData.m_imageSource.c_str(), TEX_TYPE::PNG, START_MAP_TEXTURE_NUMBER + tileID + countMap, CVec2(layerData.m_tileWidth * 0.5 + (layerData.m_tileWidth * countW), layerData.m_tileHeight * 0.5 + (layerData.m_tileHeight * countH)), CVec4(rectL, rectB, layerData.m_tileWidth, layerData.m_tileHeight));
			tileID++;
		}
		if (countW >= width-1)
		{
			countW = 0;
			countH--;
		}
		else
		{
			countW++;
		}
	}
	countMap += layerData.m_gid.size();
}
void CGameEngine::TMXMapSetPos(float x, float y)
{
	for (int i = 0;i < countMap;i++)
	{
		rendTex->setMapPosition(CVec2(x, y), START_MAP_TEXTURE_NUMBER + i);
	}
}
void CGameEngine::layerSetPos(float x, float y,GLuint texID)
{
	rendTex->setMapPosition(CVec2(x, y), texID);
}

/**
*	ゲームを実行する
*/
/*
void CGameEngine::Run()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();

	double prevTime = glfwGetTime();
	while (!window.ShowldClose())
	{
		const double curTime = glfwGetTime();
		const double delta = curTime - prevTime;
		prevTime = curTime;
		window.UpdateGamePad();
		window.SwapBuffers();
	}
}
*/


CRendTexture* CGameEngine::getRendTexture()
{
	return rendTex;
}
