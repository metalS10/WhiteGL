#pragma once
#include "../Character.h"
#include "../../Scene/Scene.h"

//=====================================================
//
//敵キャラクターの基底クラスとなるクラス
//
//=====================================================
class CEnemyCharacter : public CCharacter
{
public:
	//コンストラクタ
	CEnemyCharacter();

	//デストラクタ
	~CEnemyCharacter();

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
	* @tips 前回は敵出撃データという敵専用のクラスが存在されていたので
	*		このクラスに直書きしても問題は生じなかったが
	*		今回はマップの情報による出現位置の決定という項目が必要になる
	*		マップをシングルトン化したので直書きしても問題ないように思われるが
	*		このタイミングでのこの場所のマップのタイルの位置の情報が必要になる
	*		最終的に必要になるのは位置だけだ
	*		なので生成と同時に位置を取得したい
	*		だがしかし、cocos2dxの機能である自動でdeleteの機能も使いたい
	*		なのでcreate静的メンバ関数をカスタマイズする。
	*/
	//CREATE_FUNC(CEnemyCharacter);
	static CEnemyCharacter* create()
	{
		CEnemyCharacter* pRet = new(std::nothrow)CEnemyCharacter();
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
	static CEnemyCharacter* create(float posX, float posY)
	{
		CEnemyCharacter* pRet = new(std::nothrow)CEnemyCharacter();

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

	//4分音符更新
	void quarterUpdate() override;

	void hitsPlayerCharacter(CCharacter* pChara);

	void hitsBulletCharacter(CCharacter* pChara);

	void DamageInterval();


	//===========================================
	//こちらでしか使っていないメンバ変数
	//===========================================
	//プレイヤー
	CCharacter* pPlayerChara;

	//プレイヤー内の今の敵を消すための1フレームのための変数
	int m_enemyDeadOneFrame = 0;

	void isDeath();

	bool Troi = false;

	int beatsCounter = 0;
};