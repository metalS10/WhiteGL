#pragma once
#include "../Data/Animation/Animation.h"
#include "../Physical.h"
#include "../Data/ActionController/ActionController.h"
#include "../Data/Collision/Collision.h"
#include "../Data/CollisionArea/CollisionArea.h"
#include "../Data/Map/Map.h"
#include "../Data/Notes/Notes.h"
#include "../Data/Sound/Sound.h"
#include "../RendInfo/RendInfo.h"
#include "../gameInput.h"


//===============================================
//キャラクタータイプ
//===============================================
enum class CHARACTER_TYPE : int
{
	NONE = -1,	//なし
	PLAYER = 0,		//プレイヤー
	ENEMY = 1,		//敵
	ATTACK = 2,		//攻撃
	GIMMICK = 3,		//ギミック
	ENEMYBULLET = 4,		//敵の攻撃
	NOTES	=5		//音に乗る

};

//音集
enum class SOUND : int
{
	PLAYER_AVOIDANCE_MISS = 0,
	PLAYER_AVOIDANCE = 1,
	PLAYER_ATTACK_MISS = 2,
	PLAYER_ATTACK = 3,
	PLAYER_BEATS	=	4,
};

//===============================================
//	キャラクタークラス
//		すべてのキャラクターの雛形となる抽象クラス
//===============================================
class CCharacter : public rendInfo::CTexRendInfo,public rendInfo::CPolygonRendInfo
{
public:
	//コンストラクタ
	CCharacter();

	//デストラクタ
	virtual ~CCharacter();

	//初期化処理
	virtual bool init();

	//更新処理
	virtual void update();

	virtual void half();
	virtual void quarter();
	virtual void eighth();


	void setTexture(const char* pass) { texPass = pass; }

	//アニメーションデータ群
	std::vector<CAnimation*>* m_pAnimations = NULL;

	//移動データ
	CMove* m_pMove = NULL;

	//適用させる物理演算群
	std::vector<CPhysical*>* m_pPhysicals = NULL;

	//行えるアクション群
	std::vector<CAction*>* m_pActions = NULL;

	//実体データ(衝突判定データの元となるデータ)
	CBody* m_pBody = NULL;

	//衝突判定空間群
	std::vector<CCollisionArea*>* m_pCollisionAreas = NULL;

	//音に合わせて動くものの群
	std::vector<CNotes*>* m_pNotes = NULL;

	//Characterが出す音
	std::vector<CSound*>* m_pSounds = NULL;

	int m_texID = 0;

	CVec2 m_scale = CVec2(1, 1);

	void setScale(CVec2 scale);
	void setScale(float scaleX,float scaleY);

	Input::CGameInput* input = new Input::CGameInput();

	CVec4 m_color = CVec4(1, 1, 1, 1);

	//現在の方向キー入力情報
	CVec2 inputArrow = CVec2(0, 0);

	void setColor(CVec4 color);
	void setColor(float r, float g, float b, float a);
	void setColor(float opacity);

	void setPosition(CVec2 vec);


	/**
	*@desc	DPを回復する関数
	*@param	回復値
	*/
	void DPHeal(float dp_value);

	/*
	*	-1じゃなくなれば自動削除処理が呼ばれる
	*	自動削除させる時間(s)
	*/
	int m_DeleteTime = -1;


	//状態(派生先によってタイプが変化する)
	int m_state = 0;

	//有効フラグ
	bool m_activeFlag = false;

	//タグ
	int m_tag = 0;

	//キャラクタータイプ
	CHARACTER_TYPE m_charaType = CHARACTER_TYPE::NONE;

	//敵タイプ
	ENEMY_TYPE m_eneType = ENEMY_TYPE::NONE;


	//キャラクターの方向のベクトル(弾の向きベクトル)
	CVec2 m_CharaLaunchVector;
	//移動速度ベクトル
	CVec2 m_moveVector;

	bool m_isAction = false;

	//地面についてからの遅延のためのメンバ変数(Enemy)
	int Groundcount = 0;

	//回避状態
	bool m_isAvoidance = false;

	//ジャスト回避
	int m_DodgeTime = 0;

	//ステージ切り替えタイミング
	bool m_nextStage = false;

	//ステージクリア
	bool m_stageClear = false;
	//ゲームオーバー
	bool m_gameOver = false;

	const char* texPass = "";

	//攻撃中の敵
	CCharacter* m_pNowEnemy = NULL;

	//=================================================
	//	メンバ変数(ステータス編)
	//=================================================

	//名前
	std::string m_name = "None";

	//最大体力
	int m_maxHitPoint = -1;
	//体力
	int m_hitPoint = -1;

	//ダメージ間隔(Player)
	float DamageTime = 60;

	//多重ダメージ防止用
	float InvisibleFrame = 0.0f;

	//ダメージの入らない間
	bool m_isInvisible = false;

	//プレイヤーのみに必要
	float m_denkiPoint = 0;

	//攻撃キャラの攻撃力
	int m_attackPoint = 0;

	//ノックバックの距離
	CVec2 m_Nockback = CVec2(-this->m_CharaLaunchVector.x * 5, 5);

	//タイミングカウンタ―
	int musicNotesCounter = 0;
	int musicNotesMiss = 0;

	//拍子間隔
	int m_beatCounter = 0;
	int m_beatInterval = 0;

protected:

	//移動処理
	virtual void moveFunc() = 0;

	//アニメーション処理
	virtual void animationFunc() = 0;
	/*
	//画面範囲端判定処理
	virtual void endOfScreen() = 0;
	*/

	//衝突判定処理
	virtual void collision() = 0;

	//状態チェック
	virtual void checkState() = 0;

	//反映処理
	virtual void applyFunc() = 0;

public:
	/**
	*	@desc キャラクター１体との衝突判定処理
	*	@param キャラクターのアドレス
	*	@return true...衝突した
	*/
	virtual bool collision(CCharacter* pChara) = 0;

	/**
	*@desc	マップとの衝突判定処理
	*@return	true...衝突した
	*/
	//virtual bool collisionMap() = 0;

	/**
	*@desc	下領域と衝突した際のイベントコールバック
	*@param	マップチップID
	*		画面端下の際は0
	*/
	virtual void collisionBottomCallback(int event) {}

	virtual void collisionTopCallback(int event) {}

	virtual void collisionRightCallback(int event) {}

	virtual void collisionLeftCallback(int event) {}


	/**
	*@desc	衝突判定後の処理
	*@param	衝突してきたキャラクター
	*/
	virtual void hits(CCharacter* pChara) = 0;

	//4分音符のタイミングで行う行動
	virtual void quarterUpdate() {};

	//生きているか死んでいるかのフラグ
	//true...生きている　false...死んでいる
	bool m_isAlive = false;

	bool m_isDamage = false;

	bool m_isAttack1 = false;

	//地面に着地しているかどうか
	bool m_isGround = false;

	void removeFromParent();

	//================================================================
	//
	//ここまでにメンバに関するコードを追加
	//
	//================================================================
};

//========================================================
//キャラクターの集合体
//	シングルトン化させて他のファイルで扱えるようにしておく
//========================================================
class CCharacterAggregate
{
private:
	//================================================================
	//シングルトン設定はここから
	//================================================================
	//共有インスタンス
	static CCharacterAggregate* m_pSharedAggre;

public:

	//コンストラクタ
	CCharacterAggregate();

	//デストラクタ
	~CCharacterAggregate();

	//共有インスタンスの取得
	static CCharacterAggregate* getInstance();
	//共有インスタンスの破棄
	static void removeInstance();

	//================================================================
	//シングルトン設定はここまで
	//================================================================

private:
	//キャラクタの集まり
	std::vector<CCharacter*>* m_pCharacters = NULL;

public:
	/**
	*@desc	キャラクターの集まりの参照を設定
	*@param	設定するキャラクターの集まりのアドレス
	*/
	void set(std::vector<CCharacter*>* pCharacters);

	/**
	*@desc	キャラクターの集まりの参照を設定
	*@param	設定するキャラクターの集まりのアドレス
	*/
	std::vector<CCharacter*>* get();

	/**
	*@desc	キャラクター一体を取得
	*@param	添字番号
	*@return キャラクター
	*/
	CCharacter* getAt(int index);

	/**
	*@desc	タグを特定してキャラクター一体を取得
	*@param	タグ
	*@return キャラクター
	*		 存在しなければNULLを返す
	*/
	CCharacter* getAtTag(int tag);

	/**
	*@desc	キャラクターの追加
	*@param	追加するキャラクター
	*/
	void add(CCharacter* pChara);

	/**
	*@desc	キャラクターの集まりの取り付けられている数を取得
	*@return 取り付けられている数
	*/
	int getSize();

};

/**
*desc	キャラクターの工場
*/
class CCharacterPartsFactory
{
public:

	//デストラクタ
	virtual ~CCharacterPartsFactory() {}

	//アニメーション取得
	virtual std::vector<CAnimation*>* getAnimations() = 0;

	//行動取得
	virtual CMove* getMove() = 0;

	//重力取得
	virtual std::vector<CPhysical*>* getPhysicals() = 0;

	//アクション取得
	virtual std::vector<CAction*>* getActions() = 0;

	//音に合わせて動くアクション取得
	virtual std::vector<CNotes*>* getNotes() = 0;

	//実体取得
	virtual CBody* getBody() = 0;
};



