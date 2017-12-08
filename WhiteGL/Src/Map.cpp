//=================================================
//追加のインクルードはここから
//=================================================
#include "Map.h"
#include "Constants.h"
#include "Collision.h"
#include "LaunchData.h"
#include "LaunchTrigger.h"

//=================================================
//マップクラス
//=================================================

//初期化処理
bool CMap::init(const std::string& tmxFile)
{
	/*
	if (!TMXTiledMap::initWithTMXFile(tmxFile))
		return false;
	*/
	this->load(tmxFile);

	return true;
}

/**
*@desc	タイルの２次元配列上の座標を取得
*@param	対象位置
*/
CVec2 CMap::getTileCoord(CVec2 pos)
{
	//マップの原点位置
	CVec2 pt = this->getPosition();

	//マップタイルサイズ
	CSize& tileSize = this->getTileSize();

	//マップの配列サイズ
	CSize& mapSize = this->getMapSize();

	float x = (pos.x + pt.x) / tileSize.width;
	float y = ((mapSize.height * tileSize.height) - pos.y) / tileSize.height;

	//左上原点の場合
	//int y = (pos_.y + this->getPosition().y)/this->getTileSize().height;

	return CVec2(x, y);
}
/**
*@desc	タイル位置の取得
*@param	対象位置
*/

CVec2 CMap::getTilePosition(CVec2 pos)
{
	//マップの原点位置
	CVec2 pt = this->getPosition();

	//マップタイルサイズ
	CSize& tileSize = this->getTileSize();

	int x = (pos.x + pt.x) / tileSize.width;
	int y = (pos.y + pt.y) / tileSize.height;

	return CVec2(x * tileSize.width, y * tileSize.height);
}


/**
*@desc	点とマップチップとの衝突判定
*@param	対象位置X
*@param	対象位置Y
*@return	true...衝突した
*/
bool CMap::hitTest(float posX, float posY)
{
	//対象の衝突判定の点
	CCollisionPoint cpt(CVec2(posX, posY));

	//点と衝突しているマップチップの原点(左下の点)を取得
	CVec2 basePoint = this->getTilePosition(CVec2(posX, posY));

	//マップチップの位置(マップチップの中心位置)
	CVec2 tilePos = CVec2(basePoint.x + 16.0f, basePoint.y + 16.0f);

	//(-16,16,16,-16)
	CCollisionRect crect(CBody(-16, 16, 16, -16), tilePos);

	//collisionを使用して判定
	return cpt.collision(&crect);
}

/**
*@desc	タイル番号の確認
*@param	タイルに衝突している点のx座標
*@param	タイルに衝突している点のy座標
*@return	レイヤーのタイプ
*@return	タイル番号(ブロック番号、マップチップ番号、マップチップID)
*/
BLOCK_TYPE CMap::checkTile(float posX, float posY,LAYER_TYPE layerType)
{
	
	//レイヤーを取得
	//cocos2d::TMXLayer* pLayer = this->getLayer(this->m_layerName[(int)layerType]);

	int pLayer = this->getLayer((int)layerType);


	//タイルの２次元配列上の座標を取得
	CVec2 tileCoord = this->getTileCoord(CVec2(posX, posY));

	//マップの配列サイズ
	CSize& mapSize = this->getMapSize();

	///////
	//タイルの２次元配列上の座標が0未満またはマップサイズより大きい場合
	if ((0 <= tileCoord.x && tileCoord.x < mapSize.width) == false ||
		(0 <= tileCoord.y && tileCoord.y < mapSize.height) == false)
	{
		return BLOCK_TYPE::NONE;
	}
	
	//マップチップデータの取得
	//return (BLOCK_TYPE)pLayer->getTileGIDAt(tileCoord);
	
	return (BLOCK_TYPE)pLayer;
}

/**
*@desc	タイルの変更
*@param		変更するマップチップID(タイル番号、ブロック番号、マップチップ番号)
*@param		タイルに衝突している点のx座標
*@param		タイルに衝突している点のy座標
*@param		レイヤータイプ
*@return	true...成功
*/
bool CMap::changeTile(int mapChipID, float posX, float posY,LAYER_TYPE layerType)
{
	
	//レイヤーを取得
	//cocos2d::TMXLayer* pLayer = this->getLayer(this->m_layerName[(int)layerType]);

	//タイルの２次元配列上の座標を取得
	CVec2 tileCoord = this->getTileCoord(CVec2(posX, posY));

	//マップの配列サイズ
	CSize& mapSize = this->getMapSize();

	//////
	//タイルの２次元配列上の座標が0未満またはマップサイズより大きい場合
	if ((0 <= tileCoord.x && tileCoord.x < mapSize.width) == false ||
		(0 <= tileCoord.y && tileCoord.y < mapSize.height) == false)
	{
		return false;
	}

	//マップチップデータの反映
	//pLayer->setTileGID(mapChipID, tileCoord);
	
	return true;
}

//===================================================================
//マップ管理クラス
//===================================================================
//共有インスタンス本体
CMapManager* CMapManager::m_pSharedMapManager = NULL;

//コンストラクタ
CMapManager::CMapManager() {
}
CMapManager::CMapManager(const CMapManager&customMapmgr_) {
}
//共有インスタンスの取得
CMapManager* CMapManager::getInstance()
{
	if (CMapManager::m_pSharedMapManager == NULL)
	{
		CMapManager::m_pSharedMapManager = new CMapManager();
	}
	return CMapManager::m_pSharedMapManager;
}

//デストラクタ
CMapManager::~CMapManager() {
}

//破棄
void CMapManager::removeInstance()
{
	SAFE_DELETE(CMapManager::m_pSharedMapManager);
}

//マップの生成
CMap* CMapManager::createMap(const std::string & fileName_)
{
	//すでに生成されていたら生成されているものを返す
	if (this->m_pMap != NULL)
	{
		std::cerr << "すでに生成されています" << std::endl;
		return this->m_pMap;
	}
	//マップクラスの生成
	this->m_pMap = CMap::create(fileName_);

	if (this->m_pMap == NULL)
	{
		std::cerr << "マップの生成に失敗しました!!" << std::endl;
		return NULL;
	}

	//初期位置の設定
	game.TMXMapSetPos(0.0f, 0.0f);

	//取り付けられているすべてのタイルのエイリアスのデフォルトをアンチエイリアスに設定
	//ちらつき防止
	/*
	for (const auto & child : this->m_pMap->getChildren())
	{
		static_cast<cocos2d::SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
	}
	*/
	return this->m_pMap;
}

//マップの取得
CMap* CMapManager::getMap()
{
	return this->m_pMap;
}

//マップの設定
CMap* CMapManager::setMap(const std::string & fileName_)
{
	//すでに生成されていたら
	if (this->m_pMap != NULL)
	{
		//現在のマップの削除
		this->m_pMap = NULL;

		//マップクラスの生成
		this->m_pMap = CMap::create(fileName_);

		if (this->m_pMap == NULL)
		{
			std::cerr << "マップの生成に失敗しました!!" << std::endl;
			return NULL;
		}

		//初期位置の設定
		game.TMXMapSetPos(0.0f, 0.0f);

		//取り付けられているすべてのタイルのエイリアスのデフォルトをアンチエイリアスに設定
		//ちらつき防止
		/*
		for (const auto & child : this->m_pMap->getChildren())
		{
			static_cast<cocos2d::SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
		}
		*/
		return this->m_pMap;
	}
	else
	{
		//マップクラスの生成
		this->m_pMap = CMap::create(fileName_);

		if (this->m_pMap == NULL)
		{
			std::cerr << "マップの生成に失敗しました!!" << std::endl;
			return NULL;
		}

		//初期位置の設定
		game.TMXMapSetPos(0.0f, 0.0f);

		//取り付けられているすべてのタイルのエイリアスのデフォルトをアンチエイリアスに設定
		//ちらつき防止
		/*
		for (const auto & child : this->m_pMap->getChildren())
		{
			static_cast<cocos2d::SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
		}
		*/
		return this->m_pMap;
	}
	
}


/*
* @desc	敵出撃判定
*/
void CMap::checkEnemyLaunch(float X,float Y)
{
	//マップを取得
	CMap* pMap = CMapManager::getInstance()->getMap();

	//レイヤーの位置を取得
	CVec2 pt(X,Y);

	//レイヤーのx位置に画面の右サイズ分を足すことで
	//表示されている画面の右端の位置を取得できる
	float checkPosX = -pt.x + WINDOW_RIGHT;
	//マップチップのサイズを取得(32,32)

	CSize& tileSize = this->getTileSize();

	//タイルの2次元配列上の座標を取得(x座標のみをチェック)
	CVec2 tileCoord = pMap->getTileCoord(CVec2(checkPosX, 0.0f));

	//現在参照中の敵出撃ラインのチェック
	if (pMap->m_launchEnemyLine == tileCoord.x)
	{

		//下から順にタイルサイズ分ずつタイルをチェックしていく
		for (float y = tileSize.height;y < WINDOW_TOP;y += tileSize.height)
		{
			//チェックするタイルの座標を設定(xは固定でy座標をチェックしていく)
			CVec2 tilePos(checkPosX, y);

			//そのx座標の2次元配列上のy位置にあるすべてのタイルを取得
			//そのタイルのタイルタイプ(=敵タイプ)を取得
			ENEMY_TYPE eneType = (ENEMY_TYPE)pMap->checkTile(tilePos.x, tilePos.y, CMap::LAYER_TYPE::LAUNCH_ENEMY);

			//敵のタイプがNONEじゃなかったら出撃
			if (eneType != ENEMY_TYPE::NONE)
			{
				//敵出撃データを作成
				CEnemyLaunchData* pLaunchData = new CEnemyLaunchData(eneType, tilePos);
				

				pLaunchData = new CEnemyLaunchData(
					(ENEMY_TYPE)pLaunchData->m_type,
					tilePos
				);


				CEnemyLaunchTrigger* pTrigger = new CEnemyLaunchTrigger(pLaunchData);

				CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);
			}


		}
		//敵出撃ラインの更新
		pMap->m_launchEnemyLine++;
	}
}

/*
* @desc	敵出撃判定
*/
void CMap::checkGimmickLaunch(float X, float Y)
{
	//マップを取得
	CMap* pMap = CMapManager::getInstance()->getMap();

	//レイヤーの位置を取得
	CVec2 pt(X, Y);

	//レイヤーのx位置に画面の右サイズ分を足すことで
	//表示されている画面の右端の位置を取得できる
	float checkPosX = -pt.x + WINDOW_RIGHT;

	
	//マップチップのサイズを取得(32,32)
	CSize& tileSize = this->getTileSize();

	//タイルの2次元配列上の座標を取得(x座標のみをチェック)
	CVec2 tileCoord = pMap->getTileCoord(CVec2(checkPosX, 0.0f));

	//現在参照中の敵出撃ラインのチェック
	if (pMap->m_launchGimmickLine == tileCoord.x)
	{

		//下から順にタイルサイズ分ずつタイルをチェックしていく
		for (float y = tileSize.height * 0.5f;y < WINDOW_TOP;y += tileSize.height)
		{
			//チェックするタイルの座標を設定(xは固定でy座標をチェックしていく)
			CVec2 tilePos(checkPosX, y);

			//そのx座標の2次元配列上のy位置にあるすべてのタイルを取得
			//そのタイルのタイルタイプ(=敵タイプ)を取得
			GIMMICK_TYPE gimType = (GIMMICK_TYPE)pMap->checkTile(tilePos.x, tilePos.y, CMap::LAYER_TYPE::LAUNCH_GIMMICK);

			//敵のタイプがNONEじゃなかったら出撃
			if (gimType != GIMMICK_TYPE::NONE)
			{
				//敵出撃データを作成
				CGimmickLaunchData* pLaunchData = new CGimmickLaunchData(gimType, tilePos);


				pLaunchData = new CGimmickLaunchData(
					(GIMMICK_TYPE)pLaunchData->m_type,
					tilePos
				);


				CGimmickLaunchTrigger* pTrigger = new CGimmickLaunchTrigger(pLaunchData);

				CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);
			}


		}
		//敵出撃ラインの更新
		pMap->m_launchGimmickLine++;
	}
}


/**
* @desc	敵出撃後の敵出撃レイヤーのタイルの削除
* @param 敵出撃データ
*/
void CMap::removeLaunchEnemyBlock(CEnemyLaunchData* pLaunchData)
{
	//マップを取得
	CMap* pMap = CMapManager::getInstance()->getMap();

	//出撃した場所の敵出撃レイヤーのマップチップをENEMY_TYPE::NONEにする
	pMap->changeTile(
		(int)ENEMY_TYPE::NONE,
		pLaunchData->m_pos.x,
		pLaunchData->m_pos.y,
		CMap::LAYER_TYPE::LAUNCH_ENEMY
	);
}

/**
* @desc	敵出撃後の敵出撃レイヤーのタイルの削除
* @param 敵出撃データ
*/
void CMap::removeLaunchGimmickBlock(CGimmickLaunchData* pLaunchData)
{
	//マップを取得
	CMap* pMap = CMapManager::getInstance()->getMap();

	//出撃した場所の敵出撃レイヤーのマップチップをENEMY_TYPE::NONEにする
	pMap->changeTile(
		(int)GIMMICK_TYPE::NONE,
		pLaunchData->m_pos.x,
		pLaunchData->m_pos.y,
		CMap::LAYER_TYPE::LAUNCH_GIMMICK
	);
}