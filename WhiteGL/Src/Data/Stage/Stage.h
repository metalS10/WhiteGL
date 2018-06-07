#pragma once
#include "../Sound/Sound.h"
#include "../../Constants.h"
#include "../Map/Map.h"

//�X�e�[�W���̓����𓮂���

//�e�X�e�[�W�̂��ƂƂȂ�N���X
class CStage
{
protected:
	bool Boss = false;

	CSound* bgm;
public:
	CStage(){}
	~CStage(){}
	//����������(�w��̃}�b�v���J��)
	virtual void init() {}
	//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
	virtual CStage* changeStage() { return NULL; }
	//�X�e�[�W�w���BGM��Ԃ��B
	virtual CSound* getBGM() { return NULL; }

};

//�X�e�[�W1-1
class CStage1_1 : public CStage
{
public:
	CStage1_1() {}
	~CStage1_1() {}
	//����������(�w��̃}�b�v���J��)
	virtual void init() override;
	//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
	virtual CStage* changeStage() override;
	//�X�e�[�W�w���BGM��Ԃ��B
	virtual CSound* getBGM() override;
};
//�X�e�[�W1-2
class CStage1_2 : public CStage
{
public:
	CStage1_2() {}
	~CStage1_2() {}
	//����������(�w��̃}�b�v���J��
	virtual void init() override;
	//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
	virtual CStage* changeStage() override;
	//�X�e�[�W�w���BGM��Ԃ�
	virtual CSound* getBGM() override;
};