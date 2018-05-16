#pragma once
//=====================================================
//追加のインクルードはここから
//=====================================================
#include "../Constants.h"
#include "../Vec2.h"

//=====================================================
//前方宣言に関するコードはここから書く
//=====================================================
class CCharacter;
typedef CVec2 Point;
//=====================================================
//アクションクラス
//=====================================================
class CAction
{
public:
	virtual ~CAction(){}
	//アクションを開始する際に呼び出す
	virtual void start() = 0;
	//アクションの更新処理
	virtual void update(CCharacter* pChara) = 0;
	//アクションを終了する際に呼び出す
	virtual void stop() = 0;

	/**
	*@desc	アクションの再起動
	*@param	再起動するキャラクター
	*@tips	標準的なアクションの再起動
	*		ここではキャラクターは使用しない
	*/
	virtual void restart(CCharacter* pChara)
	{
		//アクションの停止
		this->stop();

		//アクションの開始
		this->start();
	}
};

//====================================================
//ジャンプ
//	ジャンプに関する処理を行い内部処理として移動データに対して変更を加える
//		tips:
//			cocos2dxのActionクラスにもジャンプは存在するが
//			Actionクラスに依存しているので重力や摩擦やマップチップなどの影響を考えると
//			初めのうちは分離して考えたほうが理解しやすい
//====================================================
class CActionJump : public CAction
{
protected:
	//ジャンプ加速度
	float m_accele = 0.0f;
	//ジャンプブースト
	float m_boost = 0.0f;

	//現在のジャンプブースト
	float m_currentBoost = 0.0f;

	//ジャンプ中かどうかのフラグ	true...ジャンプ中
	bool m_isJumping = false;

	//ジャンプ開始フラグ
	bool m_isJumpStart = false;

public:

	CActionJump(float accele, float boost):
		m_accele(accele),m_boost(boost){}

	/**
	*	@descジャンプ
	*	@param 加速度
	*	@param ジャンプブースト
	*	@tips ジャンプボタンが押された際に値の設定とともに呼び出す
	*/
	void start() override
	{
		//ジャンプ開始
		this->m_isJumpStart = true;
	}

	/**
	*	@desc 更新処理
	*	@param ジャンプする対象のキャラクター
	*	@tips 上キーが押されたらこの関数を呼び出す
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc ジャンプ終了
	*	@tips 着地した際にこの関数を呼び出す
	*/
	void stop() override
	{
		//ジャンプ中フラグを下ろす
		this->m_isJumping = false;
	}

	/**
	*@desc	アクションの再起動
	*@param	再起動するキャラクター
	*@tips	キャラクターのY成分のリセットも行なう
	*/
	void restart(CCharacter* pChara)override;
};

//===========================================================
//回避アクション
//===========================================================
class CActionAvoidance : public CAction
{
protected:
	//回避加速度
	float m_accele = 0.0f;


	//ジャンプ中かどうかのフラグ	true...ジャンプ中
	bool m_isAvoidance = false;
	
	//ジャンプ開始フラグ
	bool m_isAvoidanceStart = false;

	//カウンター
	//回避行動インターバル
	int m_intarval = 0;
	//次発動可能インターバル
	int m_avoidanceIntarval = 0;
	int m_counter = 0;

public:

	CActionAvoidance(float accele ,int avoidanceIntarval, int intarval) :
		m_accele(accele),m_avoidanceIntarval(avoidanceIntarval), m_intarval(intarval) {}

	/**
	*	@descジャンプ
	*	@param 加速度
	*	@param ジャンプブースト
	*	@tips ジャンプボタンが押された際に値の設定とともに呼び出す
	*/
	void start() override
	{
		//ジャンプ開始
		this->m_isAvoidanceStart = true;
	}

	/**
	*	@desc 更新処理
	*	@param ジャンプする対象のキャラクター
	*	@tips 上キーが押されたらこの関数を呼び出す
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc ジャンプ終了
	*	@tips 着地した際にこの関数を呼び出す
	*/
	void stop() override
	{
		//ジャンプ中フラグを下ろす
		this->m_isAvoidance = false;
	}

	/**
	*@desc	アクションの再起動
	*@param	再起動するキャラクター
	*@tips	キャラクターのY成分のリセットも行なう
	*/
	void restart(CCharacter* pChara)override;
};



//====================================================
//敵死亡アクション
//====================================================
class CActionEnemyDead : public CAction
{
protected:
	//横移動速度
	float m_velX = 0.0f;

	//跳ねる速度
	float m_leapVelY = 0.0f;

	//アクション中かどうかのフラグtrue...アクション中
	bool m_inAction = false;

	//アクション開始フラグtrue...アクション開始
	bool m_isStart = false;

public:
	/**
	*@desc	コンストラクタ
	*@param	横移動速度
	*@param	跳ねる速度
	*/
	CActionEnemyDead(float velX, float leapVelY);

	/**
	*@desc	アクション開始
	*/
	void start() override;

	/**
	*@desc	更新処理
	*@param	アクションを行う対象のキャラクター
	*/
	void update(CCharacter* pChara) override;

	/**
	*@desc	アクション終了
	*/
	void stop() override;

	
};

//=============================================
//上下移動アクション
//=============================================
class CActionUpAndDownMove : public CAction
{
private:
	//アクション中かどうかのフラグ true...アクション中
	bool m_inAction = false;

	//基準位置
	Point m_basePos;

	//半径
	float m_radius = 0.0f;

	//速度
	float m_vel = 0.0f;

	//カウンター
	float m_counter = 0.0f;

public:
	/**
	*@desc	コンストラクタ
	*@param	基準位置
	*@param	半径
	*@param	速度
	*/
	CActionUpAndDownMove(Point basePos, float radius, float vel);

	/**
	*@desc	アクション開始
	*/
	void start() override;

	/*
	*@desc	更新処理
	*@param	アクションを行う対象のキャラクター
	*/
	void update(CCharacter* pChara)override;

	/*
	*@desc	アクション終了
	*/
	void stop() override;
};

//======================================================
//敵死亡アクション後に死亡位置から敵を出現させる
//======================================================
class CActionEnemyDeadAndCreateEnemy : public CAction
{
	//{ENEMY_TYPE}出現させる敵のタイプ
	int m_type;

	//アクション中かどうかのフラグ true...アクション中
	bool m_inAction = false;

	//アクション開始フラグ true...アクション開始
	bool m_isStart = false;

public:
	/**
	*@desc	コンストラクタ
	*@param	出現させる敵のタイプ
	*/
	CActionEnemyDeadAndCreateEnemy(int type);

	/**
	*@desc	アクション開始
	*/
	void start() override;

	/*
	*@desc	更新処理
	*@param	アクションを行う対象のキャラクター
	*/
	void update(CCharacter* pChara) override;

	/**
	*@desc	アクション終了
	*/
	void stop() override;
};

//======================================================
//敵生成アクション
//======================================================
class CActionCreateEnemy : public CAction
{
	//{ENEMY_TYPE}出現させる敵のタイプ
	int m_type;

	int m_ShotCount = 0;

	//アクション中かどうかのフラグ true...アクション中
	bool m_inAction = false;

	//アクション開始フラグ true...アクション開始
	bool m_isStart = false;

public:
	/**
	*@desc	コンストラクタ
	*@param	出現させる敵のタイプ
	*/
	CActionCreateEnemy(int type);

	/**
	*@desc	アクション開始
	*/
	void start() override;

	/*
	*@desc	更新処理
	*@param	アクションを行う対象のキャラクター
	*/
	void update(CCharacter* pChara) override;

	/**
	*@desc	アクション終了
	*/
	void stop() override;
};

//=============================================
//まっすぐ移動アクション
//=============================================
class CActionMoveStraight : public CAction
{
private:
	//アクション中かどうかのフラグ true...アクション中
	bool m_inAction = false;

	//基準位置
	Point m_basePos;


	//速度
	float m_vel = 0.0f;

	float m_velY = 0.0f;

	//カウンター
	float m_counter = 0.0f;

	//移動はしないと思うがまっすぐ移動で消す処理を書く
	int deleteCount = 0;

public:
	/**
	*@desc	コンストラクタ
	*@param	基準位置
	*@param	半径
	*@param	速度
	*/
	CActionMoveStraight(Point basePos, float vel);

	CActionMoveStraight(Point basePos, float velX,float velY);

	/**
	*@desc	アクション開始
	*/
	void start() override;

	/*
	*@desc	更新処理
	*@param	アクションを行う対象のキャラクター
	*/
	void update(CCharacter* pChara)override;

	/*
	*@desc	アクション終了
	*/
	void stop() override;
};

//====================================================
//弾発射アクション
//====================================================
class CActionShotBullet : public CAction
{
protected:
	int m_bulletType;

	//発射間隔
	float m_interval = 0.0f;

	//発射カウンター
	float m_shotCount= 0.0f;

	//アニメーション中かどうか
	bool m_inAction = false;

public:

	CActionShotBullet(int type, float interval)
		:m_bulletType(type), m_interval(interval) {}

	/**
	*	@descアクション
	*	@tips 発射ボタンが押された
	*/
	void start() override
	{
		m_inAction = true;
	}

	/**
	*	@desc 更新処理
	*	@param アクションする対象のキャラクター
	*	@tips 上キーが押されたらこの関数を呼び出す
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc アクション終了
	*	@tips 着地した際にこの関数を呼び出す
	*/
	void stop() override
	{
		//アクション中フラグを下ろす
		this->m_inAction = false;
	}

	/**
	*@desc	アクションの再起動
	*@param	再起動するキャラクター
	*@tips	キャラクターのY成分のリセットも行なう
	*/
	void restart(CCharacter* pChara)override {}
};

//=============================================
//上にあがって落ちるアクション(重力)
//=============================================
class CActionCurve : public CAction
{
private:
	//アクション中かどうかのフラグ true...アクション中
	bool m_inAction = false;

	//基準位置
	Point m_basePos;

	//速度
	float m_vel = 0;

	float m_velY = 3;
	//カウンター
	float m_counter = 0.0f;

public:
	/**
	*@desc	コンストラクタ
	*@param	基準位置
	*@param	半径
	*@param	速度
	*/
	CActionCurve(Point basePos, float vel);

	CActionCurve(Point basePos, float velX, float velY);


	/**
	*@desc	アクション開始
	*/
	void start() override;

	/*
	*@desc	更新処理
	*@param	アクションを行う対象のキャラクター
	*/
	void update(CCharacter* pChara)override;

	/*
	*@desc	アクション終了
	*/
	void stop() override;


};

//指定の間アニメーションする
class CActionRoll : public CAction
{
private:
	//アニメーション間隔
	int m_interval = 300;
	//発射カウンター
	int m_counter = 300;
	//アクション開始フラグ
	bool m_isStart = false;

public:
	/*
	*コンストラクタ
	*間隔
	*カウンター
	*/
	CActionRoll(){}

	void start() override;

	void update(CCharacter* pChara)override;

	void stop() override;

};

//=======================================================
//落ちるアクション
//=======================================================
class CActionDown : public CAction
{
private:
	//発射カウンター
	int m_counter = 60;
	//アクション開始フラグ
	bool m_isStart = false;

public:
	/*
	*コンストラクタ
	*間隔
	*カウンター
	*/
	CActionDown() {}

	void start() override;

	void update(CCharacter* pChara)override;

	void stop() override;

};




//=============================================================
//敵生成ブロック用アクション
//=============================================================
class CActionCreateCharacter : public CAction
{
	//{ENEMY_TYPE}出現させる敵のタイプ
	int m_type;

	//アクション中かどうかのフラグ true...アクション中
	bool m_inAction = false;

	//アクション開始フラグ true...アクション開始
	bool m_isStart = false;

	int count = 0;

public:
	/**
	*@desc	コンストラクタ
	*@param	出現させる敵のタイプ
	*/
	CActionCreateCharacter(int type);

	/**
	*@desc	アクション開始
	*/
	void start() override;

	/*
	*@desc	更新処理
	*@param	アクションを行う対象のキャラクター
	*/
	void update(CCharacter* pChara) override;

	/**
	*@desc	アクション終了
	*/
	void stop() override;
};

class CActionEnemyDamage : public CAction
{
protected:
	//ジャンプ加速度
	float m_accele = 0.0f;
	//ジャンプブースト
	int m_boost = 0;

	//バックステップ距離
	float m_backstep = 0.0f;

	//現在のジャンプブースト
	int m_currentBoost = 0;

	//ジャンプ中かどうかのフラグ	true...ジャンプ中
	bool m_isJumping = false;

	//ジャンプ開始フラグ
	bool m_isJumpStart = false;


public:

	CActionEnemyDamage(float accele, int boost, float backstep) :
		m_accele(accele), m_boost(boost), m_backstep(backstep) {}

	/**
	*	@descジャンプ
	*	@param 加速度
	*	@param ジャンプブースト
	*	@tips ジャンプボタンが押された際に値の設定とともに呼び出す
	*/
	void start() override
	{
		//ジャンプ開始
		this->m_isJumpStart = true;
	}

	/**
	*	@desc 更新処理
	*	@param ジャンプする対象のキャラクター
	*	@tips 上キーが押されたらこの関数を呼び出す
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc ジャンプ終了
	*	@tips 着地した際にこの関数を呼び出す
	*/
	void stop() override
	{
		//ジャンプ中フラグを下ろす
		this->m_isJumping = false;
	}

	/**
	*@desc	アクションの再起動
	*@param	再起動するキャラクター
	*@tips	キャラクターのY成分のリセットも行なう
	*/
	void restart(CCharacter* pChara)override;
};


//====================================================
//敵弾発射アクション
//====================================================
class CActionShotEnemyBullet : public CAction
{
protected:
	int m_bulletType = 0;

	//発射間隔
	float m_interval = 0.0f;

	//発射カウンター
	float m_shotCount = 0.0f;

	//アニメーション中かどうか
	bool m_inAction = false;

public:

	CActionShotEnemyBullet(int type, float interval)
		:m_bulletType(type), m_interval(interval) {}

	/**
	*	@descアクション
	*	@tips 発射ボタンが押された
	*/
	void start() override
	{}

	/**
	*	@desc 更新処理
	*	@param アクションする対象のキャラクター
	*	@tips 上キーが押されたらこの関数を呼び出す
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc アクション終了
	*	@tips 着地した際にこの関数を呼び出す
	*/
	void stop() override
	{
		//アクション中フラグを下ろす
		this->m_inAction = false;
	}

	/**
	*@desc	アクションの再起動
	*@param	再起動するキャラクター
	*@tips	キャラクターのY成分のリセットも行なう
	*/
	void restart(CCharacter* pChara)override {}
};

//====================================================
//敵円状弾発射アクション
//====================================================
class CActionShotEnemySphereBullet : public CAction
{
protected:
	int m_bulletType;

	//発射間隔
	float m_interval = 0.0f;

	//発射カウンター
	float m_shotCount = 0.0f;

	//アニメーション中かどうか
	bool m_inAction = false;



public:

	CActionShotEnemySphereBullet(int type, float interval)
		:m_bulletType(type), m_interval(interval) {}

	/**
	*	@descアクション
	*	@tips 発射ボタンが押された
	*/
	void start() override
	{
		m_inAction = true;
	}

	/**
	*	@desc 更新処理
	*	@param アクションする対象のキャラクター
	*	@tips 上キーが押されたらこの関数を呼び出す
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc アクション終了
	*	@tips 着地した際にこの関数を呼び出す
	*/
	void stop() override
	{
		//アクション中フラグを下ろす
		this->m_inAction = false;
	}

	/**
	*@desc	アクションの再起動
	*@param	再起動するキャラクター
	*@tips	キャラクターのY成分のリセットも行なう
	*/
	void restart(CCharacter* pChara)override {}
};

//=============================================
//トロくないやつのアクション
//=============================================
class CActionTRoi : public CAction
{
private:
	//アクション中かどうかのフラグ true...アクション中
	bool m_inAction = false;

	
	//速度
	float m_vel = 0.0f;

	CCharacter* m_pPlayer ;

	int counter = 0;

	int m_intervalTime = 0;

	//プレイヤのポジション
	CVec2 pos;

	//アクションステップ
	int step = 0;

	float nowHeight = 0.0f;

	bool up = false;

	float upheight = 0.0f;
public:
	/**
	*@desc	コンストラクタ
	*@param	基準位置
	*@param	半径
	*@param	速度
	*/
	CActionTRoi(float vel, int interval)
		:m_vel(vel), m_intervalTime(interval){}

	/**
	*@desc	アクション開始
	*/
	void start() override
	{}

	/*
	*@desc	更新処理
	*@param	アクションを行う対象のキャラクター
	*/
	void update(CCharacter* pChara)override;

	/*
	*@desc	アクション終了
	*/
	void stop() override
	{}
};