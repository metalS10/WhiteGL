#include "GameMainScene.h"

CGameMain::CGameMain()
{

	this->init();
}

CGameMain::~CGameMain()
{

}

bool CGameMain::init()
{
	CMapManager::getInstance()->setMap(MAP_DATA_1);

	//出撃スケジュールの生成
	m_pLaunchSchedule = new std::vector<CLaunchTrigger*>();

	//これで削除していないとステージを二度遊んだ時にバグが出る(最強の敵)
	//CLaunchScheduler::getInstance()->removeInstance();

	//出撃スケジュールを出撃スケジューラーに取り付ける
	CLaunchScheduler::getInstance()->createLauncher(m_pLaunchSchedule);

	//キャラクターの集まりの生成
	m_pCharacters = new std::vector<CCharacter*>();
	CCharacterAggregate::getInstance()->set(m_pCharacters);


	pPlayerChara = (CPlayerCharacter*)CPlayerFactoryManager::getInstance()->create(320.0f, 200.0f);

	//プレイヤー1のタグを設定
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregateにプレイヤーを追加
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	m_game.setupTexture(pPlayerChara->texPass, TEX_TYPE::PNG, pPlayerChara->m_texID, pPlayerChara->m_pMove->m_pos, (*pPlayerChara->m_pAnimations)[0]->getCurrentChip());

	pPlayerChara->input = input;

	return true;
}

void CGameMain::update()
{
	//ゲーム全体を制御する場所
	gameMain();


	CLaunchScheduler::getInstance()->launchCharacters(m_game);


	//出撃の完了したトリガーをすべて取り外す
	checkAndDelete(m_pLaunchSchedule);
	checkAndRemove(m_pCharacters);
	for (CCharacter* pChara : (*m_pCharacters))
	{
		pChara->update();
		m_game.setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip(), pChara->m_texID);
		m_game.setScale(pChara->m_scale, pChara->m_texID);
		m_game.setPosition(pChara->m_pMove->m_pos, pChara->m_texID);
	}
	//背景のポジションセット
	m_game.setPosition(CVec2(WINDOW_RIGHT * 0.5 + cameraPosX, WINDOW_TOP * 0.5), MAX_TEXTURE_NUMBER - 1);

	scroll();

	

}

//ゲーム全体の動き
void CGameMain::gameMain()
{
	if (pPlayerChara->m_nextStage)
	{
		//openMap(MAP_DATA_2, m_pCharacters);
		if (!movingstage)
		{
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, false) == true)
			{
				movingstage = true;
				openMap(MAP_DATA_2);
				gluLookAt(
					-cameraPosX, 0.0f, 0.0f,
					-cameraPosX, 0.0f, -10.0f,
					0.0f, 1.0f, 0.0f
				);
				cameraPosX = 0.0f;
				pPlayerChara->setPosition(CVec2(320.0f, 200.0f), PLAYER_ID);
			}
		}
		if (movingstage == true)
		{
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true))
			{
				movingstage = false;
				pPlayerChara->m_nextStage = false;
			}
		}
	}

	if (pPlayerChara->m_stageClear)
	{
		//this->StageEnd(pPlayerChara->m_stageClear);
	}
	if (pPlayerChara->m_gameOver)
	{
		//this->StageEnd(pPlayerChara->m_stageClear);
	}

	
}


/*
*@desc	画面スクロール
*@tips	今回は強制スクロールではなくキャラクターの移動による画面のスクロールとなる
*/
void CGameMain::scroll()
{
	CMap* map = CMapManager::getInstance()->getMap();

	//マップの位置を取得
	CVec2 pt = map->getp();

	//プレイヤーキャラクターの取得
	CCharacter* pPlayerChara = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);

	//プレイヤーの位置が前の値を超えたら
	if (pt.x > WINDOW_RIGHT*0.7f - pPlayerChara->m_pMove->m_pos.x)
	{
		//原点位置を超えた分に設定する
		pt.x = WINDOW_RIGHT*0.7f - pPlayerChara->m_pMove->m_pos.x;

		//超えた分を設定する
		map->setp(pt);

		cameraMoveX = pPlayerChara->m_pMove->m_vel.x;

		//スクロールが行われたときに敵の出撃判定を行う
		map->checkEnemyLaunch(pt.x, pt.y);

		//ギミックの出撃判定も行う
		map->checkGimmickLaunch(pt.x, pt.y);

	}
	//プレイヤーの位置が後ろの値超えたら
	else if (pt.x < WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x)
	{
		//原点位置を超えた分に設定する
		pt.x = WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x;

		//超えた分を設定する
		map->setp(pt);

		cameraMoveX = pPlayerChara->m_pMove->m_vel.x;




	}
	else
	{
		cameraMoveX = 0.0f;

	}
	cameraPosX += cameraMoveX;
	gluLookAt(
		cameraMoveX, 0.0f, 0.0f,
		cameraMoveX, 0.0f, -10.0f,
		0.0f, 1.0f, 0.0f
	);
}



void CGameMain::StageEnd(bool clear)
{
	stageSelectinterval++;
	if (!m_stageEnd)
	{
		//StageEndgridをアクション
		//this->nodegrid->runAction(ReverseTime::create(PageTurn3D::create(0.5, Size(200, 100))));
		if (clear)
		{
			//StageClearを表示
			//this->m_StageClearSprite->runAction(Show::create());

		}
		else
		{
			//Stagefailedを表示
			//this->m_StageFaildSprite->runAction(Show::create());
		}
		//ステージが終了
		m_stageEnd = true;
		stageSelectinterval = 0;
	}
	if (stageSelectinterval >= 60 && stageSelectinterval <= 61)
	{
		//フェードイン開始
		//m_blackBord->runAction(FadeIn::create(2));
		if (!movingstage)
		{
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, false) == true)
			{
				movingstage = true;
				//openMap(MAP_DATA_2, m_pCharacters);
				gluLookAt(
					-cameraPosX, 0.0f, 0.0f,
					-cameraPosX, 0.0f, -10.0f,
					0.0f, 1.0f, 0.0f
				);
				cameraPosX = 0.0f;
				//pPlayerChara->setPosition(CVec2(320.0f, 200.0f), PLAYER_ID);
			}
		}
		if (movingstage == true)
		{
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true))
			{
				movingstage = false;
				//pPlayerChara->m_nextStage = false;
			}
		}
	}
	//時間が経ったら
	if (stageSelectinterval >= 200)
	{


		//ステージセレクト画面に戻る
		//this->runAction(CallFunc::create(this, callfunc_selector(CGameMain::ReturnGameSelect)));
	}


}

void CGameMain::openMap(std::string mapData)
{

	for (CCharacter* pChara : (*m_pCharacters))
	{
		if (pChara->m_tag != TAG_PLAYER_1)
		{
			pChara->m_activeFlag = false;
		}
	}

	m_game.allTextureDeletenotPlayer();

	CMapManager::getInstance()->setMap(mapData);

}