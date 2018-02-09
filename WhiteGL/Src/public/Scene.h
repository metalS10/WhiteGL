#pragma once
#include "../MSlib.h"

//シーンの親となるクラス
class CScene
{
protected:

	float cameraMoveX = 0.0f;
	float cameraPosX = 0.0f;

	//多分全部に必要
	CGameEngine& m_game = MS::CMS::getInstance()->getGame();
	Input::CGameInput* input = MS::CMS::getInstance()->getInput();
public:
	CScene() { init(); };
	

	//デストラクタ
	virtual ~CScene() {};
	//初期化処理
	virtual bool init() {

		m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true);
		m_game.allTextureDelete();
		return true; };
	//更新処理
	virtual void update() {};
	//描画用Update
	virtual void RendUpdate() {};

	void moveScene(CScene* scene)
	{

	}
};
