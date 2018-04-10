#pragma once
#include "public/Scene.h"
#include "PlayerFactory.h"
#include "LaunchTrigger.h"
#include "TitleScene.h"

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
	
	
public:
	CGameMain();
	~CGameMain();
	bool init()override;
	void update()override;
	void rendUpdate()override;
	void sceneUpdate()override;


	void gameMain();
	void scroll();

	void StageEnd(bool clear);
	void openMap(std::string mapData);


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