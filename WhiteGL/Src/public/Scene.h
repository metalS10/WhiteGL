#pragma once
#include "../MSlib.h"

//�V�[���̐e�ƂȂ�N���X
class CScene
{
protected:

	float cameraMoveX = 0.0f;
	float cameraPosX = 0.0f;

	//�����S���ɕK�v
	CGameEngine& m_game = MS::CMS::getInstance()->getGame();
	Input::CGameInput* input = MS::CMS::getInstance()->getInput();
public:
	CScene() { init(); };
	

	//�f�X�g���N�^
	virtual ~CScene() {};
	//����������
	virtual bool init() {

		m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true);
		m_game.allTextureDelete();
		return true; };
	//�X�V����
	virtual void update() {};
	//�`��pUpdate
	virtual void RendUpdate() {};

	void moveScene(CScene* scene)
	{

	}
};
