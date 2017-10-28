#pragma once
//============================================
//追加のインクルードはここから
//============================================
#include "Character.h"


//==================================================
//プレイヤーキャラクター
//	今回は更新処理が内部で行われているので
//	入力処理も内部で行い
//	入力による移動処理というカテゴリで扱う
//==================================================
class CPlayerCharacter : public CCharacter
{
public:
	//コンストラクタ
	CPlayerCharacter();

	//デストラクタ
	~CPlayerCharacter();

	//初期化処理
	bool init() override;

	//CREATE_FUNC(CPlayerCharacter);


	//==================================================================
	//
	//	定数に関するコードの追加はここから
	//
	//==================================================================

	//プレイヤーの状態
	enum class STATE : int
	{
		STAND		=	0,
		JUMPING		=	0,
		WALK		=	1,
		DAMAGE		=	2,
		FALING		=	3,
		ATTACK		=	4,
		NOR			=	5,
		AVOIDANCE	=	6,
		DASH		=	7,
		SUPERJUMP	=	8,
		SUPERFALING	=	9,
	};

	//プレイヤーが行えるアクション
	enum class ACTION :int
	{
		JUMP			=	0,
		ATTACK			=	1,
		ATTACK_NOR		=	2,
		DAMAGE			=	3,
		SUPERJUMP		=	4,
	};

	//==================================================================
	//
	//	メンバに関するコードの追加はここから
	//
	//==================================================================

	//更新処理
	void update(float deltaTime)override;

	/**
	*	@desc入力処理
	*	@tips 移動処理で呼び出す
	*/
	void inputFunc();

	//移動処理
	void moveFunc() override;

	//アニメーション処理
	void animationFunc() override;
	
	/*
	//画面範囲端判定処理
	void endOfScreen() override;
	*/
	//反映処理
	void applyFunc() override;
	
	void collision() override;

	//状態チェック
	void checkState() override;

	/**
	*	@descキャラクター１体との衝突判定処理
	*	@param	キャラクターのアドレス
	*	@return true...衝突した
	*/
	bool collision(CCharacter* pChara)override;
	
	//多重ダメージ防止
	void DamageInterval();

	//ジャスト回避(減らすだけ
	void DodgeInterval();


	/**
	*@desc	下領域と衝突した際のイベントコールバック
	*@param	マップチップID
	*		画面端下の際は0
	*/
	void collisionBottomCallback(int event)override
	{
		//ジャンプを停止させる
		//(*this->m_pActions)[(int)ACTION::JUMP]->stop();
		//(*this->m_pActions)[(int)ACTION::SUPERJUMP]->stop();
	}
	void collisionTopCallback(int event)override {}
	void collisionRightCallback(int event)override {}
	void collisionLeftCallback(int event)override {}


	/**
	*@desc	マップとの衝突判定
	*@return	true...衝突した
	*/
	//bool collisionMap() override;

	/**
	*@desc	衝突判定後の処理
	*@param	衝突してきたキャラクター
	*/
	virtual void hits(CCharacter* pChara)override;
	/*
	//ゲームパッド入力処理を取得
	CInputInterface* pGamepadInput = CInputManager::getInstance()->
		get(ControllerType::Gamepad)->get(0);

	//キーボード入力処理を取得
	CInputInterface* pKeybordInput = CInputManager::getInstance()->
		get(ControllerType::Keybord)->get(0);

	*/


	void Allfalse();
};