#pragma once

class CCharacter;
class CNotesUI;


//音に合わせて動かす動きの親
class CNotes
{
private:

public:
	//コンストラクタ
	CNotes() {};
	~CNotes() {};
	//2
	virtual void half(CCharacter* pChara) = 0;
	//4
	virtual void quarter(CCharacter* pChara) = 0;
	//8
	virtual void eighth(CCharacter* pChara) = 0;
};

//音楽に合わせてアニメーションさせるクラス
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

//音に合わせて動かす動きの親
class CNotes2
{
private:

protected:
	//コンストラクタ
	CNotes2() {};
	~CNotes2() {};
	//2
	virtual void half(CNotesUI* pChara) = 0;
	//4
	virtual void quarter(CNotesUI* pChara) = 0;
	//8
	virtual void eighth(CNotesUI* pChara) = 0;
};

//音楽に合わせてアニメーションさせるクラス
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