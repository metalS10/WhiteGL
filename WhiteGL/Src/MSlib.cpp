#include "MSlib.h"

using namespace MS;

//���L�C���X�^���X�{��
CMS* CMS::m_pSharedMS = NULL;

//�R���X�g���N�^
CMS::CMS() {}

//���L�C���X�^���X�̎擾
CMS* CMS::getInstance()
{
	if (CMS::m_pSharedMS == NULL)
	{
		CMS::m_pSharedMS = new CMS();
	}
	return CMS::m_pSharedMS;
}

//���L�C���X�^���X�̔j��
void CMS::removeInstance()
{
	SAFE_DELETE(CMS::m_pSharedMS);
}

//�f�X�g���N�^
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