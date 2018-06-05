#pragma once

class CCharacter;
class CNotesUI;


//���ɍ��킹�ē����������̐e
class CNotes
{
private:

public:
	//�R���X�g���N�^
	CNotes() {};
	~CNotes() {};
	//2
	virtual void half(CCharacter* pChara) = 0;
	//4
	virtual void quarter(CCharacter* pChara) = 0;
	//8
	virtual void eighth(CCharacter* pChara) = 0;
};

//���y�ɍ��킹�ăA�j���[�V����������N���X
class CNotesAnimation : CNotes
{
private:

public:
	CNotesAnimation();
	~CNotesAnimation();
	virtual void half(CCharacter* pChara)override;
	virtual void quarter(CCharacter* pChara)override;
	virtual void eighth(CCharacter* pChara) override;
};

//���ɍ��킹�ē����������̐e
class CNotes2
{
private:

protected:
	//�R���X�g���N�^
	CNotes2() {};
	~CNotes2() {};
	//2
	virtual void half(CNotesUI* pChara) = 0;
	//4
	virtual void quarter(CNotesUI* pChara) = 0;
	//8
	virtual void eighth(CNotesUI* pChara) = 0;
};

//���y�ɍ��킹�ăA�j���[�V����������N���X
class CNotesAnimation2 : CNotes2
{
private:

public:
	CNotesAnimation2();
	~CNotesAnimation2();
	virtual void half(CNotesUI* pChara)override;
	virtual void quarter(CNotesUI* pChara)override;
	virtual void eighth(CNotesUI* pChara) override;
};