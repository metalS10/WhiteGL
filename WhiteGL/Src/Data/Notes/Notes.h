#pragma once
#include "../../Character/Character.h"

class CCharacter;

//���ɍ��킹�ē����������̐e
class CNotes
{
private:

public:
	//�R���X�g���N�^
	CNotes() {};
	~CNotes() {};
	//�J�n����
	virtual void start(CCharacter* pChara) = 0;
	//�X�V����
	virtual void update(CCharacter* pChara) = 0;
	//��~
	virtual void stop() = 0;
	//�ĊJ
	virtual void restart(){	stop();	start();}
};

//���y�ɍ��킹�ăA�j���[�V����������N���X
class CNotesAnimation : CNotes
{
private:

public:
	CNotesAnimation();
	~CNotesAnimation();
	virtual void start(CCharacter* pChara)override;
	virtual void update(CCharacter* pChara)override;
	virtual void stop() override;
};