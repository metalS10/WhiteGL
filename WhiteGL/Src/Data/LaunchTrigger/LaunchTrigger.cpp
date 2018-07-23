#include "LaunchTrigger.h"
#include "../../Character/Character.h"
#include "../../Factory/EnemyFactory/EnemyFactory.h"
#include "../../Factory/GimmickFactory/GimmickFactory.h"


//===================================================================
//
//敵出撃トリガー
//	敵出撃データをトリガーにして敵出撃というイベントを実行させる
//
//===================================================================
//デストラクタ
CEnemyLaunchTrigger::~CEnemyLaunchTrigger()
{
	SAFE_DELETE(this->m_pLaunchData);
}

/**
*@desc	イベントを実行できるかどうか
*@return true...実行可能
*/
bool CEnemyLaunchTrigger::isTrigger()
{
	if (this->m_pLaunchData == NULL)
	{
		return false;
	}
	return true;
}
/**
*@desc	設定されている敵出撃データをもとに敵を生成する
*/
CCharacter* CEnemyLaunchTrigger::action()
{
	//敵を生成
	CCharacter* pEnemyChara = CEnemyFactoryManager::getInstance()->create(
		this->m_pLaunchData->m_type,
		this->m_pLaunchData->m_pos.x,
		this->m_pLaunchData->m_pos.y);

	//発射し終わったかどうかのフラグを立てる
	this->m_activeFlag = false;

	
	//敵出撃データを返す
	//出撃データが存在したら
	if (m_pLaunchData != NULL)
	{
		//敵の画像を消す
		CMapManager::getInstance()->getMap()->removeLaunchEnemyBlock(this->m_pLaunchData);
	}

	return pEnemyChara;
}

//===================================================================
//
//弾出撃トリガー
//	弾出撃データをトリガーにして敵出撃というイベントを実行させる
//
//===================================================================
//デストラクタ
CAttackLaunchTrigger::~CAttackLaunchTrigger()
{
	SAFE_DELETE(this->m_pLaunchData);
}

/**
*@desc	イベントを実行できるかどうか
*@return true...実行可能
*/
bool CAttackLaunchTrigger::isTrigger()
{
	if (this->m_pLaunchData == NULL)
	{
		return false;
	}
	return true;
}
/**
*@desc	設定されている敵出撃データをもとに敵を生成する
*/
CCharacter* CAttackLaunchTrigger::action()
{
	//敵を生成
	CCharacter* pAttackChara = CAttackFactoryManager::getInstance()->create(
		this->m_pLaunchData->m_attacktype,
		this->m_pLaunchData->m_pos.x,
		this->m_pLaunchData->m_pos.y,
		this->m_pLaunchData->m_vec
	);

	//発射し終わったかどうかのフラグを立てる
	this->m_activeFlag = false;

	return pAttackChara;
}

//===================================================================
//
//ギミック出撃トリガー
//	ギミック出撃データをトリガーにしてギミック出撃というイベントを実行させる
//
//===================================================================
//デストラクタ
CGimmickLaunchTrigger::~CGimmickLaunchTrigger()
{
	SAFE_DELETE(this->m_pLaunchData);
}

/**
*@desc	イベントを実行できるかどうか
*@return true...実行可能
*/
bool CGimmickLaunchTrigger::isTrigger()
{
	if (this->m_pLaunchData == NULL)
	{
		return false;
	}
	return true;
}
/**
*@desc	設定されている敵出撃データをもとに敵を生成する
*/
CCharacter* CGimmickLaunchTrigger::action()
{
	//敵を生成
	CCharacter* pGimmickChara = CGimmickFactoryManager::getInstance()->create(
		this->m_pLaunchData->m_type,
		this->m_pLaunchData->m_pos.x,
		this->m_pLaunchData->m_pos.y
	);

	//発射し終わったかどうかのフラグを立てる
	this->m_activeFlag = false;


	//敵出撃データを返す
	//出撃データが存在したら
	if (m_pLaunchData != NULL)
	{
		//敵の画像を消す
		CMapManager::getInstance()->getMap()->removeLaunchGimmickBlock(this->m_pLaunchData);
	}

	return pGimmickChara;
}



//=============================================================
//
//出撃スケジューラー
//	Singleton
//
//=============================================================
//共有インスタンス本体
CLaunchScheduler* CLaunchScheduler::m_pSharedScheduler = NULL;

//コンストラクタ
CLaunchScheduler::CLaunchScheduler(){}

//共有インスタンスの取得
CLaunchScheduler* CLaunchScheduler::getInstance()
{
	if (CLaunchScheduler::m_pSharedScheduler == NULL)
	{
		CLaunchScheduler::m_pSharedScheduler = new CLaunchScheduler();
	}
	return CLaunchScheduler::m_pSharedScheduler;
}

//共有インスタンスの破棄
void CLaunchScheduler::removeInstance()
{
	SAFE_DELETE(CLaunchScheduler::m_pSharedScheduler);
}

//デストラクタ
CLaunchScheduler::~CLaunchScheduler()
{
	SAFE_DELETE(this->m_pLauncher);
}

/**
*@desc	発射台の生成
*@param	発射台に設定する出撃する出撃スケジュールのアドレス
*/
void CLaunchScheduler::createLauncher(std::vector<CLaunchTrigger*>* pLaunchSchedule)
{
	if (this->m_pLauncher == NULL)
	{
		//発射台を生成し出撃スケジュールを発射台に設定
		this->m_pLauncher = new CLauncher(pLaunchSchedule);
	}
}

/**
*@desc	キャラクターの出撃
*@param	取り付けるレイヤー
*/
void CLaunchScheduler::launchCharacters(CGameEngine& game)
{
	//スケジューラーに取り付けられている起動できるトリガー全てを起動する
	std::shared_ptr<CLauncher::CLaunchTriggerIterator>itr = this->m_pLauncher->iterator();

	//次の起動可能な出撃トリガーがあるかどうかをチェック
	while (itr->hasNext() == true)
	{
		//起動可能な出撃トリガーを取得して出撃トリガーイテレーターを次へ進める
		CLaunchTrigger* pTrigger = itr->next();

		//出撃トリガーを起動
		CCharacter* pChara = pTrigger->action();

		//NULLチェック
		if (pChara != NULL)
		{
			//キャラクターをキャラクターの集まりに取り付ける
			CCharacterAggregate::getInstance()->add(pChara);

			//キャラクターをメインレイヤーに取り付ける
			//pLayer->addChild(pChara);
			if (pChara->m_charaType == CHARACTER_TYPE::ATTACK)
			{
				game.setupPoly(CVec4(pChara->m_pMove->m_pos.x, pChara->m_pMove->m_pos.y, 32.0f, 32.0f), CVec4(0.0f, 0.0f, 0.0f, 100.0f), 0, POLY_TYPE::QUAD, TAG_PLAYER_ATTACK);
			}
			else
			{
				game.setupTexture(pChara->texPass, TEX_TYPE::PNG, pChara->m_texID, pChara->m_pMove->m_pos, (*pChara->m_pAnimations)[0]->getCurrentChip());
			}
			game.render();

		}
	}
}


//===================================================================
//
//弾出撃トリガー
//	弾出撃データをトリガーにして敵出撃というイベントを実行させる
//
//===================================================================
//デストラクタ
CEnemyBulletLaunchTrigger::~CEnemyBulletLaunchTrigger()
{
	SAFE_DELETE(this->m_pLaunchData);
}

/**
*@desc	イベントを実行できるかどうか
*@return true...実行可能
*/
bool CEnemyBulletLaunchTrigger::isTrigger()
{
	if (this->m_pLaunchData == NULL)
	{
		return false;
	}
	return true;
}
/**
*@desc	設定されている敵出撃データをもとに敵を生成する
*/
CCharacter* CEnemyBulletLaunchTrigger::action()
{
	//敵を生成
	CCharacter* pBulletChara = CEnemyBulletFactoryManager::getInstance()->create(
		this->m_pLaunchData->m_bullettype,
		this->m_pLaunchData->m_pos.x,
		this->m_pLaunchData->m_pos.y,
		this->m_pLaunchData->m_vec
	);

	//発射し終わったかどうかのフラグを立てる
	this->m_activeFlag = false;

	return pBulletChara;
}