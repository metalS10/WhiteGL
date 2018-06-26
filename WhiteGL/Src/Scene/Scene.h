#pragma once
#include "../AllController/AllController.h"
#include "../Data/Sound/Sound.h"
#include <Windows.h>
#include <vector>

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

	//BGM
	CSound* BGM = NULL;

	//BGM��BPM
	float m_bgmBpm = 0;
	//BPM�ɍ��킹�ē��������߂̃J�E���^�[
	int m_bpmCounter = 0;
	//2������
	double m_halfNotes = 0;		
	//4
	double m_quarterNotes = 0;
	//8
	double m_eighthNotes = 0;

	
	//���g��,�ŏ���ms,update��ms
	LARGE_INTEGER m_nFreq, m_nInit, m_nAfter;

	//�񕪉����A�l�������A��������(ms)
	double Time = 0, HalfTime = 0, QuarterTime = 0, EighthTime = 0;

	CSound* m_attackSE = NULL;
	CSound* m_avoidanceSE = NULL;
	CSound* m_enemyDestroySE = NULL;

	//���𑜓x�J�E���^�Ή�����(Windows NT(/2000) 3.1 �ȍ~,Windows95(/98)�ȍ~)
	bool m_queryPC = false;

	int Delay = 0;

	bool m_BGMStart = false;
public:

	//�R���X�g���N�^
	CScene();

	//�f�X�g���N�^
	virtual ~CScene() ;
	//����������
	virtual bool init();

	//�X�V����
	virtual void update() {};
	//�Q�[���{�̍X�V
	virtual void sceneUpdate() {};

	//�`��pUpdate
	virtual void rendUpdate() ;

	//bpm���̏����ׂ����X�V����
	//virtual void bpmUpdate();

	//�J�����V�F�C�N�̃Z�b�g
	void SetCameraShake(float range, int count, int frame);

	//�J�����V�F�C�N
	void cameraShake();


	void moveScene(CScene* scene);

	//�������ɍ��킹�ČĂ΂��֐�
	virtual void halfUpdate();
	virtual void qauarterUpdate();
	virtual void eighthUpdate();

};
