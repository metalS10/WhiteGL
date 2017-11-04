#pragma once

#include <stdio.h>
#include <memory>
#include "Constants.h"
#include "LaunchData.h"
#include "Map.h"


//==================================================
//前方宣言
//==================================================
class CCharacter;

//==================================================
//
//出撃トリガー
//
//==================================================
class CLaunchTrigger
{
public:
	//有効フラグ	false...出撃スケジュールから取り外す
	bool m_activeFlag = false;

	//コンストラクタ
	CLaunchTrigger()
	{
		this->m_activeFlag = true;
	}

	//デストラクタ
	virtual ~CLaunchTrigger(){}

	/**
	*@desc	発射し終わったかどうか
	*@return true...発射した　false...発射していない
	*@tips	発射し終わったかどうかは派生クラスによって
	*		フラグが変化する場合が存在する
	*/
	virtual bool isLaunched()
	{
		return this->m_activeFlag;
	}

	/**
	*@desc	設定されているトリガーがイベントを行えるかどうか
	*@param	true...イベントの実行が可能
	*@tips	イベントの実行可能条件は派生クラスによって変化する
	*/
	virtual bool isTrigger() = 0;

	/**
	*@desc	トリガーのイベントの実行
	*		ここでのトリガーイベントはキャラクターの生成
	*/
	virtual CCharacter* action() = 0;
};

//====================================================================
//
//敵出撃トリガー
//	敵出撃データをトリガーとして敵出撃というイベントを実装させる
//
//====================================================================
class CEnemyLaunchTrigger : public CLaunchTrigger
{
private:
	//敵出撃データ
	CEnemyLaunchData* m_pLaunchData = NULL;

public:
	/**
	*@desc	コンストラクタ
	*@param	敵出撃データ
	*@tips	敵出撃データをトリガーとして設定する
	*/
	CEnemyLaunchTrigger(CEnemyLaunchData* pLaunchData)
		:m_pLaunchData(pLaunchData){}

	//デストラクタ
	~CEnemyLaunchTrigger();

	/**
	*@desc	イベントを実行できるかどうか
	*@return	true...実行可能
	*/
	bool isTrigger() override;

	/**
	*@desc	設定されている敵出撃データをもとに敵を生成する
	*		トリガーを元にイベントを実行
	*/
	CCharacter* action() override;
};

//====================================================================
//
//弾出撃トリガー
//	弾出撃データをトリガーとして弾出撃というイベントを実装させる
//
//====================================================================
class CAttackLaunchTrigger : public CLaunchTrigger
{
private:
	//敵出撃データ
	CAttackLaunchData* m_pLaunchData = NULL;

public:
	/**
	*@desc	コンストラクタ
	*@param	敵出撃データ
	*@tips	敵出撃データをトリガーとして設定する
	*/
	CAttackLaunchTrigger(CAttackLaunchData* pLaunchData)
		:m_pLaunchData(pLaunchData) {}

	//デストラクタ
	~CAttackLaunchTrigger();

	/**
	*@desc	イベントを実行できるかどうか
	*@return	true...実行可能
	*/
	bool isTrigger() override;

	/**
	*@desc	設定されている敵出撃データをもとに敵を生成する
	*		トリガーを元にイベントを実行
	*/
	CCharacter* action() override;
};

//====================================================================
//
//ギミック出撃トリガー
//	ギミック出撃データをトリガーとしてギミック出撃というイベントを実装させる
//
//====================================================================
class CGimmickLaunchTrigger : public CLaunchTrigger
{
private:
	//敵出撃データ
	CGimmickLaunchData* m_pLaunchData = NULL;

public:
	/**
	*@desc	コンストラクタ
	*@param	敵出撃データ
	*@tips	敵出撃データをトリガーとして設定する
	*/
	CGimmickLaunchTrigger(CGimmickLaunchData* pLaunchData)
		:m_pLaunchData(pLaunchData) {}

	//デストラクタ
	~CGimmickLaunchTrigger();

	/**
	*@desc	イベントを実行できるかどうか
	*@return	true...実行可能
	*/
	bool isTrigger() override;

	/**
	*@desc	設定されている敵出撃データをもとに敵を生成する
	*		トリガーを元にイベントを実行
	*/
	CCharacter* action() override;
};

//===========================================================
//発射台
//	出撃スケジュールの参照を設定して
//	出撃スケジュールに取り付けられている出撃トリガーの順番通りに
//	イベントを実行していく
//	つまり取り付けられた順番通りに出撃を行っていく
//
//	Aggregate
//
//===========================================================
class CLauncher
{
public:
	//出撃スケジュールの参照(つまりこのクラスで生成や破棄を行わない)
	//1フレームに出撃させるトリガーイベントの集まり
	std::vector<CLaunchTrigger*>* m_pLaunchSchedule = NULL;

	/**
	*@desc	コンストラクタ
	*@param	出撃スケジュールのアドレス
	*/
	CLauncher(std::vector<CLaunchTrigger*>* pLaunchSchedule)
		:m_pLaunchSchedule(pLaunchSchedule){}

	//デストラクタ
	~CLauncher(){}

	/**
	*@desc	出撃トリガーを出撃スケジュールに追加する
	*/
	void add(CLaunchTrigger* pTrigger)
	{
		this->m_pLaunchSchedule->push_back(pTrigger);
	}
	
	/**
	*@desc	出撃スケジュールのサイズの取得
	*/
	int getSize()
	{
		return (int)this->m_pLaunchSchedule->size();
	}

	/**
	*@desc	出撃トリガーの取得
	*@param	添え字番号
	*/
	CLaunchTrigger* getAt(int index)
	{
		//最大要素以上の際はNULLを返す
		if (this->getSize() <= index)
		{
			return NULL;
		}
		return (*this->m_pLaunchSchedule)[index];
	}

	//==============================================================
	//
	//出撃トリガーイテレーター
	//	発射台に取り付けられているトリガーを発射可能か調べて、
	//	発射可能なら1つづつ出撃させるための捜査を行うクラス
	//	Aggregateの中に実装
	//		Iterator
	//
	//==============================================================
	class CLaunchTriggerIterator
	{
	public:
		//発射台
		CLauncher* m_pLauncher = NULL;

		//現在参照中の番号
		int m_triggerCount = 0;

		//コンストラクタ
		CLaunchTriggerIterator(CLauncher* pLauncher)
			:m_pLauncher(pLauncher){}

		/**
		*@desc	出撃トリガーの次があるかどうかを調べる
		*		もしくは出撃トリガーが起動可能かどうかを調べる
		*/
		bool hasNext()
		{
			//トリガーイベントの集まりのサイズを調べる
			if (this->m_pLauncher->getSize() <= this->m_triggerCount)
			{
				return false;
			}

			//出撃トリガーが起動可能かどうかを調べる
			if (this->m_pLauncher->getAt(this->m_triggerCount)->isTrigger() == false)
			{
				//起動可能でない場合は添え字番号を次に進めて
				this->m_triggerCount++;
				//次をチェック
				return this->hasNext();
			}
			return true;
		}

		/**
		*@desc	現在の出撃トリガーを取得し添え字番号を次に進める
		*/
		CLaunchTrigger* next()
		{
			CLaunchTrigger* pTrigger = this->m_pLauncher->getAt(this->m_triggerCount);
			this->m_triggerCount++;
			return pTrigger;
		}
	};

	/**
	*@desc	出撃トリガーイテレーターの生成
	*@param	出撃トリガーイテレーター
	*/
	std::shared_ptr<CLaunchTriggerIterator>iterator()
	{
		return std::shared_ptr<CLaunchTriggerIterator>(new CLaunchTriggerIterator(this));
	}
};

//======================================================
//
//出撃スケジューラー
//	Singleton
//
//======================================================
class CLaunchScheduler
{
	//=========================================================
	//ここからSingleton設定
	//=========================================================

private:
	//共有インスタンス
	static CLaunchScheduler* m_pSharedScheduler;

	//コンストラクタ
	CLaunchScheduler();

public:
	//共有インスタンスの取得
	static CLaunchScheduler* getInstance();

	//共有インスタンスの破棄
	static void removeInstance();

	//デストラクタ
	~CLaunchScheduler();

	//=========================================================
	//ここまでSingleton設定
	//=========================================================

public:
	//発射台
	CLauncher* m_pLauncher = NULL;

	/**
	*@desc	発射台
	*@param	発射台に設定する出撃スケジュールのアドレス
	*/
	void createLauncher(std::vector<CLaunchTrigger*>* pLaunchSchedule);

	/**
	*@desc	キャラクターの出撃
	*@param	取り付けるレイヤー
	*/
	void launchCharacters();
};


//====================================================================
//
//敵の弾出撃トリガー
//	弾出撃データをトリガーとして弾出撃というイベントを実装させる
//
//====================================================================
class CEnemyBulletLaunchTrigger : public CLaunchTrigger
{
private:
	//敵出撃データ
	CEnemyBulletLaunchData* m_pLaunchData = NULL;

public:
	/**
	*@desc	コンストラクタ
	*@param	敵出撃データ
	*@tips	敵出撃データをトリガーとして設定する
	*/
	CEnemyBulletLaunchTrigger(CEnemyBulletLaunchData* pLaunchData)
		:m_pLaunchData(pLaunchData) {}

	//デストラクタ
	~CEnemyBulletLaunchTrigger();

	/**
	*@desc	イベントを実行できるかどうか
	*@return	true...実行可能
	*/
	bool isTrigger() override;

	/**
	*@desc	設定されている敵出撃データをもとに敵を生成する
	*		トリガーを元にイベントを実行
	*/
	CCharacter* action() override;
};