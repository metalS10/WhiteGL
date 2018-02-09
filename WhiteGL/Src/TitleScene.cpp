#include "TitleScene.h"

CTitle::CTitle()
{
	this->init();
	
}

CTitle::~CTitle()
{

}

bool CTitle::init()
{
	if (CScene::init() == false)
	{
		printf("シーン初期化に失敗");
		return false;
	}

	m_game.setupTexture(TITLE_BG, TEX_TYPE::PNG, 0, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT));
	//m_game.setScale(CVec2(1,1), 0);
	return true;
}

void CTitle::update()
{
	if (input->getOnKey(Input::Key::START) == true)
	{

		//ゲームメインシーンを生成
		MS::CMS::getInstance()->setScene(new CGameMain());
	}
	
}
