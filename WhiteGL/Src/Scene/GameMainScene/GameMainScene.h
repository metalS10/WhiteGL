#pragma once
#include "../Scene.h"
#include "../../Factory/PlayerFactory/PlayerFactory.h"
#include "../../Data/LaunchTrigger/LaunchTrigger.h"
#include "../../Data/Stage/Stage.h"
#include "../../NotesUI/NotesUI.h"

class CGameMain : public CScene
{
private:
	bool movingstage = false;
	int stageSelectinterval = 0;
	bool m_stageEnd = false;
	bool m_stageClear = false;
	std::vector<CLaunchTrigger*>* m_pLaunchSchedule;
	std::vector<CCharacter*>* m_pCharacters;
	CPlayerCharacter* pPlayerChara;
	int m_EnemyNameInterval = 0;
	CStage* m_stage = NULL;
	CNotesUI* notes = NULL;

	//BG(背景)
	rendInfo::CTexRendInfo* m_backGround1;
	rendInfo::CTexRendInfo* m_backGround2;
	//UIの背景
	rendInfo::CTexRendInfo* m_UIBack;
	rendInfo::CTexRendInfo* m_HPwaku;	//HPUI枠
	rendInfo::CTexRendInfo* m_BPwaku;	//BPUI枠
	rendInfo::CTexRendInfo* m_HP;	//BPUI
	rendInfo::CTexRendInfo* m_BP;	//BPUI
	rendInfo::CTexRendInfo* m_EnemyStatsUI;	//EnemyUI
	rendInfo::CTexRendInfo* m_EnemyHPwaku;	//EnemyHPUI枠
	rendInfo::CTexRendInfo* m_EnemyHP;	//EnemyHPUI
	rendInfo::CTexRendInfo* m_GameEndUI;	//EnemyHPUI
	//画面全体UI
	rendInfo::CPolygonRendInfo* m_cirUI[4];


public:
	CGameMain();
	~CGameMain();
	bool init()override;		//初期化処理
	void update()override;		//遊びの動き更新
	void rendUpdate()override;	//描画更新
	void sceneUpdate()override;	//システムの更新
	void halfUpdate()override;	//2分音符の更新
	void qauarterUpdate()override;	//4分音符の更新
	void eighthUpdate()override;	//8分音符の更新

	//ステージ遷移初期化
	bool stageChangeInit() override;

	//ゲームの主な動きの更新
	void gameMain();
	//横スクロール
	void scroll();
	
	//ステージの終了処理
	void StageEnd(bool clear);
	//TiledMapの読み込み&開く
	void openMap();


	/**
	*	@desc	チェックと取り外し処理 ( 単体 )
	*	@tips	有効フラグが false のインスタンスをレイヤーから取り外す
	*/
	template <typename Ty>
	void checkAndRemove(Ty* pChara) 
	{
		if (pChara->m_activeFlag == false) 
		{
			pChara->removeFromParent();
		}
	}

	/**
	*	@desc	チェックと取り外し処理 ( 複数 )
	*	@tips	有効フラグが false のインスタンスをレイヤーと std::vector から取り外す
	*/
	template <typename Ty>
	void checkAndRemove(std::vector<Ty*>* pCharas) {

		// ローカル変数の型のテンプレート引数の指定として
		// テンプレート引数を指定する場合は typename 指定をつけなければならない
		typename std::vector<Ty*>::iterator itr = pCharas->begin();
		while (itr != pCharas->end()) {

			if ((*itr)->m_activeFlag == false)
			{
				(*itr)->removeFromParent();
				itr = pCharas->erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}

	/**
	*@desc	チェックと解放
	*@tips	有効フラグがfalseのインスタンスを開放しstd::vectorから取り外す
	*/
	template<typename Ty>
	void checkAndDelete(std::vector<Ty*>*pVector)
	{
		//ローカル変数の方のテンプレート引数の指定として
		//テンプレート引数を指定する場合はtypename指定をつけなければならない
		typename std::vector<Ty*>::iterator itr = pVector->begin();
		while (itr != pVector->end())
		{
			if ((*itr)->m_activeFlag == false)
			{
				SAFE_DELETE((*itr));
				itr = pVector->erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
};