#pragma once
//=====================================================
//追加のインクルードはここから
//=====================================================
#include "../Character.h"

//=====================================================
//
//ギミックキャラクターの基底クラスとなるクラス
//
//=====================================================
class CGimmickCharacter : public CCharacter
{
public:
	//コンストラクタ
	CGimmickCharacter();

	//デストラクタ
	~CGimmickCharacter();

	//初期化処理
	bool init() override;


	/*
	* @desc 初期化処理
	* @param 初期位置X
	* @param 初期位置Y
	* @tips create() メンバ関数の中でinit()メンバ関数を呼び出しているが
	*		今回、そのcreate()メンバ関数をオーバーロードして
	*		引数を受け取っているのでinit()メンバ関数も
	*		オーバーロードする必要がある。
	*/
	bool init(float posX, float posY);

	/**
	* @desc CREATE_FUNCマクロの中身をそのまま持ってきただけ
	* @tips 前回はギミック出撃データというギミック専用のクラスが存在されていたので
	*		このクラスに直書きしても問題は生じなかったが
	*		今回はマップの情報による出現位置の決定という項目が必要になる
	*		マップをシングルトン化したので直書きしても問題ないように思われるが
	*		このタイミングでのこの場所のマップのタイルの位置の情報が必要になる
	*		最終的に必要になるのは位置だけだ
	*		なので生成と同時に位置を取得したい
	*		だがしかし、cocos2dxの機能である自動でdeleteの機能も使いたい
	*		なのでcreate静的メンバ関数をカスタマイズする。
	*/
	//CREATE_FUNC(CGimmickCharacter);
	static CGimmickCharacter* create()
	{
		CGimmickCharacter* pRet = new(std::nothrow)CGimmickCharacter();
		if (pRet && pRet->init())
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}
	/*
	* @desc CREATE_FUNCマクロをオーバーライド
	* @param 初期位置X
	* @param 初期位置Y
	* @tips 初期位置を必要とするのは生成の段階ではなく
	*		initの段階である
	*/
	static CGimmickCharacter* create(float posX, float posY)
	{
		CGimmickCharacter* pRet = new(std::nothrow)CGimmickCharacter();

		//初期化処理に初期位置を渡す
		if (pRet && pRet->init(posX, posY))
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}
	//===============================================
	//
	//メンバに関するコードの追加はここから
	//
	//===============================================

	//移動処理
	void moveFunc() override;

	//アニメーション処理
	void animationFunc() override;

	/*
	//画面端判定処理
	void endOfScreen() override;
	*/
	//状態チェック
	void checkState() override;

	//反映処理
	void applyFunc() override;


	void collision() override;

	/**
	* @desc キャラクター1体との衝突判定処理
	* @param キャラクターのアドレス
	* @return true...衝突した
	*/
	bool collision(CCharacter* pChara)override;

	/**
	* @desc マップとの衝突判定
	* @return true...衝突した
	*/
	//bool collisionMap() override;

	/**
	*@desc	衝突判定後の処理
	*@param	衝突してきたキャラクター
	*/
	virtual void hits(CCharacter* pChara) override;


	void collisionBottomCallback(int event)override
	{
		CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		pPlayerCharacter->m_isDamage = true;
		pPlayerCharacter->m_hitPoint = 0;
		pPlayerCharacter->m_gameOver = true;
	}
	void collisionTopCallback(int event)override
	{
		CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		pPlayerCharacter->m_isDamage = true;
		pPlayerCharacter->m_hitPoint = 0;
		pPlayerCharacter->m_gameOver = true;
	}
	void collisionRightCallback(int event)override
	{
		CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		pPlayerCharacter->m_isDamage = true;
		pPlayerCharacter->m_hitPoint = 0;
		pPlayerCharacter->m_gameOver = true;
	}
	void collisionLeftCallback(int event)override
	{
		CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		pPlayerCharacter->m_isDamage = true;
		pPlayerCharacter->m_hitPoint = 0;
		pPlayerCharacter->m_gameOver = true;
	}

};



//==================================================================================
//ギミックを継承した回るブロック
//==================================================================================
class CRollGimmickCharacter : public CGimmickCharacter
{
public:
	//コンストラクタ
	CRollGimmickCharacter();

	//デストラクタ
	~CRollGimmickCharacter()override;

	//初期化処理
	bool init() override;

	//CREATE_FUNC(CGimmickCharacter);
	static CRollGimmickCharacter* create()
	{
		CRollGimmickCharacter* pRet = new(std::nothrow)CRollGimmickCharacter();
		if (pRet && pRet->init())
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}
	
	void collisionBottomCallback(int event)override
	{
		(*this->m_pActions)[0]->start();
	}
	void collisionTopCallback(int event)override
	{
		
	}
	void collisionRightCallback(int event)override
	{
		
	}
	void collisionLeftCallback(int event)override
	{
		
	}


};


//==================================================================================
//ギミックを継承したちくわブロック
//==================================================================================
class CTikuwaGimmickCharacter : public CGimmickCharacter
{
public:
	//コンストラクタ
	CTikuwaGimmickCharacter();

	//デストラクタ
	~CTikuwaGimmickCharacter()override;

	//初期化処理
	bool init() override;

	//CREATE_FUNC(CGimmickCharacter);
	static CTikuwaGimmickCharacter* create()
	{
		CTikuwaGimmickCharacter* pRet = new(std::nothrow)CTikuwaGimmickCharacter();
		if (pRet && pRet->init())
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	void collisionBottomCallback(int event)override
	{

	}
	void collisionTopCallback(int event)override
	{
		(*this->m_pActions)[0]->start();
	}
	void collisionRightCallback(int event)override
	{

	}
	void collisionLeftCallback(int event)override
	{

	}


};

//==================================================================================
//ギミックを継承した音符ブロック
//==================================================================================
class CNoteGimmickCharacter : public CGimmickCharacter
{
public:
	//コンストラクタ
	CNoteGimmickCharacter();

	//デストラクタ
	~CNoteGimmickCharacter()override;

	//初期化処理
	bool init() override;

	//CREATE_FUNC(CGimmickCharacter);
	static CNoteGimmickCharacter* create()
	{
		CNoteGimmickCharacter* pRet = new(std::nothrow)CNoteGimmickCharacter();
		if (pRet && pRet->init())
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	void collisionBottomCallback(int event)override
	{

	}
	void collisionTopCallback(int event)override
	{
		CCharacter* pPlayer = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		(*pPlayer->m_pActions)[0]->restart(pPlayer);
	}
	void collisionRightCallback(int event)override
	{

	}
	void collisionLeftCallback(int event)override
	{

	}


};

//==================================================================================
//ギミックを継承した音符ブロック
//==================================================================================
class CHatenaGimmickCharacter : public CGimmickCharacter
{
public:
	//コンストラクタ
	CHatenaGimmickCharacter();

	//デストラクタ
	~CHatenaGimmickCharacter()override;

	//初期化処理
	bool init() override;

	//CREATE_FUNC(CGimmickCharacter);
	static CHatenaGimmickCharacter* create()
	{
		CHatenaGimmickCharacter* pRet = new(std::nothrow)CHatenaGimmickCharacter();
		if (pRet && pRet->init())
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	void collisionBottomCallback(int event)override
	{
		(*this->m_pActions)[0]->start();
	}
	void collisionTopCallback(int event)override
	{

	}
	void collisionRightCallback(int event)override
	{

	}
	void collisionLeftCallback(int event)override
	{

	}


};

//==================================================================================
//ギミックを継承したワープ
//==================================================================================
class CWorpGimmickCharacter : public CGimmickCharacter
{
public:
	//コンストラクタ
	CWorpGimmickCharacter();

	//デストラクタ
	~CWorpGimmickCharacter()override;

	//初期化処理
	bool init() override;

	//多重ワープ防止
	int i = 0;

	//CREATE_FUNC(CGimmickCharacter);
	static CWorpGimmickCharacter* create()
	{
		CWorpGimmickCharacter* pRet = new(std::nothrow)CWorpGimmickCharacter();
		if (pRet && pRet->init())
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	void collisionBottomCallback(int event)override
	{
		if (i == 0)
		{
			CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
			pPlayerCharacter->m_nextStage = true;
			i++;
		}
	}
	void collisionTopCallback(int event)override
	{

	}
	void collisionRightCallback(int event)override
	{

	}
	void collisionLeftCallback(int event)override
	{

	}


};
