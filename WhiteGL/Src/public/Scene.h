#pragma once
#include "../MSlib.h"

//�V�[���̐e�ƂȂ�N���X
class CScene
{
protected:

	//�J�����̓������l��ݒ肷��ϐ�
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

	//�Q�[���G���W��
	CGameEngine& m_game = MS::CMS::getInstance()->getGame();
	//����
	Input::CGameInput* input = MS::CMS::getInstance()->getInput();
public:

	//�R���X�g���N�^
	CScene();

	//�f�X�g���N�^
	virtual ~CScene() {};
	//����������
	virtual bool init();

	//�X�V����
	virtual void update() {};
	//�Q�[���{�̍X�V
	virtual void sceneUpdate() {};

	//�`��pUpdate
	virtual void rendUpdate() {};

	//�J�����V�F�C�N�̃Z�b�g
	void SetCameraShake(float range, int count, int frame);

	//�J�����V�F�C�N
	void cameraShake();


	void moveScene(CScene* scene);
};
