#pragma once
#include <stdio.h>
#include "../../Constants.h"
#include "../../interpreter/CCTMXTiledMap.h"
#include "../../Vec2.h"
#include <vector>
#include "../../AllController/AllController.h"

//=====================================================
//前方宣言
//=====================================================
class CEnemyLaunchData;
class CGimmickLaunchData;

//=========================================================
//ブロック(マップチップのこと)種類
//新しい種類ができたらここに増やしていく
//=========================================================
enum class BLOCK_TYPE : int {
	NONE		= 0, //何もなし
};

//=========================================================
//敵の種類
//ブロック番号に依存
//=========================================================
enum class ENEMY_TYPE : int
{
	NONE		=	0,			//何もなし
	KURIBO		=	102,		//クリボー
	NOKONOKO	=	108,		//ノコノコ
	PATAPATA	=	109,		//パタパタ
	KILLERHODAI	=	124,		//キラー砲台
	KILLER		=	1000,		//キラー
	TROI		=	110,		//トロくない木馬
};

//=========================================================
//ギミックの種類
//ブロック番号に依存
//=========================================================
enum class GIMMICK_TYPE : int
{
	NONE	=	0,		//何もなし
	TIKUWA	=	132,	//落ちるやつ
	ROLL	=	135,	//回るやつ
	TOGE_L	=	136,	//左向きのとげ
	TOGE_T	=	137,	//上向きのとげ
	TOGE_R	=	138,	//右向きのとげ
	TOGE_B	=	139,	//下向きのとげ
	NOTE	=	140,	//跳ねるやつ
	HATENA	=	141,	//ハテナブロック
	WORP	=	142,	//ワープ
};


//=========================================================
//マップクラス
//=========================================================
class CMap :public TMXTiledMap
{


public:
	//=====================================================
	//レイヤータイプ
	//=====================================================
	enum  class LAYER_TYPE :int
	{
		NORMAL = 0,//通常マップ
		LAUNCH_ENEMY = 1,//敵出現用マップ
		LAUNCH_GIMMICK = 2,//ギミック出現用マップ
	};

	//=====================================================
	//マップタイプによるレイヤーの名前
	//=====================================================
	std::vector<std::string>m_layerName
	{
		"normal",
		"launchenemy",
		"launchgimmick",
	};
public:

	//コンストラクタ
	CMap(){}

	//生成
	static CMap* create(const std::string&tmxFile)
	{
		CMap* pMap = new(std::nothrow)CMap();
		if (pMap->init(tmxFile))
		{
			//pMap->autorelease();
			return pMap;
		}
		SAFE_DELETE(pMap);
		return NULL;
	}

	bool init(const std::string& tmxFile);


	/**
	*@desc	タイルの1次元配列上の座標を取得
	*@param	左上を原点とした配列上の座標位置
	*/
	CVec2 getTileCoord(CVec2 pos);

	/**
	*@desc	タイルの1次元配列上の座標を取得
	*@param	左下を原点とした対象の座標位置
	*/
	CVec2 getTilePosition(CVec2 pos);

	/**
	*@desc	点とマップチップとの衝突判定
	*@param	対象位置X
	*@param	対象位置Y
	*/
	bool hitTest(float posX, float posY);

	/**
	* @desc	タイル番号の確認
	* @param	タイルに衝突している点のx位置
	* @param	タイルに衝突している点のy位置
	* @return	レイヤータイプ
	* @return	タイル番号(ブロック番号,マップチップ番号,マップチップID)
	*/
	BLOCK_TYPE checkTile(float posX, float posY, LAYER_TYPE layerType = LAYER_TYPE::NORMAL);

	/**
	*@desc	タイルの変更
	*@param	変更するマップチップID(タイル番号、ブロック番号、マップチップ番号)
	*@param	タイルに衝突している点のx座標
	*@param	タイルに衝突している点のy座標
	*@param レイヤータイプ
	*@return	true...成功
	*/
	bool changeTile(int mapChipID, float posX, float posY,LAYER_TYPE layerType = LAYER_TYPE::NORMAL);

	/*
	*	@desc	敵出撃判定
	*	@return 敵のタイプ
	*/
	void checkEnemyLaunch(float X,float Y);

	/*
	*	@desc	ギミック出撃判定
	*	@return 敵のタイプ
	*/
	void checkGimmickLaunch(float X, float Y);

	//敵出撃ライン(マップ2次元配列上のタイルのx位置)
	//20は画面の端 + 1つ分の
	int m_launchEnemyLine = 40;
	int m_launchGimmickLine = 40;


	/**
	* @desc	敵出撃後の敵出撃レイヤーのタイルの削除
	* @param 敵出撃データ
	*/
	void removeLaunchEnemyBlock(CEnemyLaunchData* pLaunchData);

	/**
	* @desc	ギミック出撃後のギミック出撃レイヤーのタイルの削除
	* @param ギミック出撃データ
	*/
	void removeLaunchGimmickBlock(CGimmickLaunchData* pLaunchData);


};

//========================================================================
//マップ管理クラス
//========================================================================
class CMapManager
{
private:
	//=============================================================================
	//シングルトン設定
	//=============================================================================

	//コンストラクタ
	CMapManager();
	CMapManager(const CMapManager & customMapMgr);

	//共有インスタンス
	static CMapManager* m_pSharedMapManager;

public:
	//共有インスタンスの取得
	static CMapManager* getInstance();

	//破棄
	static void removeInstance();
	//デストラクタ
	~CMapManager();

private:
	//マップ
	CMap* m_pMap = NULL;

public:
	//マップの生成
	CMap* createMap(const std::string & fileName);

	//マップの取得
	CMap* getMap();

	//マップの設定
	CMap* setMap(const std::string & fileName);

	CGameEngine& game = MS::CMS::getInstance()->getGame();

	
};