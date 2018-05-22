#pragma once
#include "../../Character/Character.h"

class CCharacter;

//音に合わせて動かす動きの親
class CNotes
{
private:

public:
	//コンストラクタ
	CNotes() {};
	~CNotes() {};
	//開始処理
	virtual void start(CCharacter* pChara) = 0;
	//更新処理
	virtual void update(CCharacter* pChara) = 0;
	//停止
	virtual void stop() = 0;
	//再開
	virtual void restart(){	stop();	start();}
};

//音楽に合わせてアニメーションさせるクラス
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