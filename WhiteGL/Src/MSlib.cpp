#include "MSlib.h"

using namespace MS;

//共有インスタンス本体
CMS* CMS::m_pSharedMS = NULL;

//コンストラクタ
CMS::CMS() {}

//共有インスタンスの取得
CMS* CMS::getInstance()
{
	if (CMS::m_pSharedMS == NULL)
	{
		CMS::m_pSharedMS = new CMS();
	}
	return CMS::m_pSharedMS;
}

//共有インスタンスの破棄
void CMS::removeInstance()
{
	SAFE_DELETE(CMS::m_pSharedMS);
}

//デストラクタ
CMS::~CMS()
{
	removeInstance();
}

CGameEngine& CMS::getGame()
{
	return game;
}
GLFWwindow* CMS::getWindow()
{
	return window;
}
Input::CGameInput* CMS::getInput()
{
	return input;
}

void CMS::setTexID(int ID,int idType)
{
	TexID[idType] = ID;
}

int CMS::getTexID(int idType)
{
	return 	TexID[idType];
}

void CMS::setScene(CScene* scene)
{
	m_pScene = scene;
}

CScene* CMS::getScene()
{
	return m_pScene;
}