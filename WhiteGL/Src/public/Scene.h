#pragma once
#include "../MSlib.h"

//�V�[���̐e�ƂȂ�N���X
class CScene
{
protected:

	float cameraMoveX = 0.0f;
	float cameraPosX = 0.0f;
	float cameraMoveY = 0.0f;
	float cameraPosY = 0.0f;
	//�J�����V�F�C�N�X�C�b�`
	bool m_shake = false;
	//�h�炷�傫��
	float m_shakeRange = 0.0f;
	//�h�炵����
	int m_shakeCount = 0;
	//���t���[�����ɓ�����
	int m_shakeFrame = 0;
	int m_shakeFrameCount = 0;
	bool m_shakeFripFrop = false;
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
	//�Q�[���{�̍X�V
	virtual void sceneUpdate() {};

	//�`��pUpdate
	virtual void rendUpdate() {};

	//�J�����V�F�C�N�̃Z�b�g
	void SetCameraShake(float range, int count ,int frame) {
		m_shake = true;
		m_shakeRange = range;
		m_shakeCount = count;
		m_shakeFrame = frame;
	};

	//�J�����V�F�C�N
	void cameraShake()
	{
		if (this->m_shake)
		{
			this->m_shakeFrameCount++;
			if (this->m_shakeFrame <= this->m_shakeFrameCount)
			{
				if (m_shakeFripFrop)
				{
					this->m_shakeFrameCount = 0;

					this->cameraMoveY = this->m_shakeRange;

					this->m_shakeRange *= -0.5f;
					this->m_shakeFripFrop = true;
				}
				else
				{
					this->m_shakeFrameCount = 0;
					this->m_shakeCount--;

					this->cameraMoveY = this->m_shakeRange;

					this->m_shakeRange *= -1.0f;
					this->m_shakeFripFrop = false;
				}

				if (this->m_shakeCount <= 0)
				{
					this->cameraMoveY = 0.0f;
					this->m_shakeCount = 0;
					this->m_shake = false;
				}
			}
		}
	}


	void moveScene(CScene* scene)
	{

	}
};
