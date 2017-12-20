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

void CMS::setTexID(int ID,int idType)
{
	TexID[idType] = ID;
}

int CMS::getTexID(int idType)
{
	return 	TexID[idType];
}