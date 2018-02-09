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
	if (CScene::init() == false)
	{
		printf("シーン初期化に失敗");
		return false;
	}
	CMapManager::getInstance()->setMap(MAP_DATA_1);

	//出撃スケジュールの生成
	m_pLaunchSchedule = new std::vector<CLaunchTrigger*>();

	//これで削除していないとステージを二度遊んだ時にバグが出る(最強の敵)
	CLaunchScheduler::getInstance()->removeInstance();

	//出撃スケジュールを出撃スケジューラーに取り付ける
	CLaunchScheduler::getInstance()->createLauncher(m_pLaunchSchedule);

	//キャラクターの集まりの生成
	SAFE_DELETE(m_pCharacters);
	m_pCharacters = new std::vector<CCharacter*>();
	CCharacterAggregate::removeInstance();
	CCharacterAggregate::getInstance()->set(m_pCharacters);


	pPlayerChara = (CPlayerCharacter*)CPlayerFactoryManager::getInstance()->create(320.0f, 200.0f);

	//プレイヤー1のタグを設定
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregateにプレイヤーを追加
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	m_game.setupTexture(pPlayerChara->texPass, TEX_TYPE::PNG, pPlayerChara->m_texID, pPlayerChara->m_pMove->m_pos, (*pPlayerChara->m_pAnimations)[0]->getCurrentChip());

	//UIのバック
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, 2, CVec2(WINDOW_RIGHT*0.125f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f));

	//HPの枠
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, 3, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 20.0f, 210.0f, 14.0f));
	//DPの枠
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, 4, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f));

	//HP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, 5 , CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 0.0f, 200.0f, 10.0f));
	//DP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, 6, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 10.0f, 200.0f, 10.0f));
	//EnemyStats
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, 7, CVec2(WINDOW_RIGHT*0.355f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f));
	//EnemyHPwaku
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, 8, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f));
	//EnemyHP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, 9, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 0.0f, 200.0f, 10.0f));


	pPlayerChara->input = input;

	return true;
}

//描画用Update
void CGameMain::RendUpdate()
{
	//ステージ終了していなければ
	if (!m_stageEnd)
	{
		for (CCharacter* pChara : (*m_pCharacters))
		{
			m_game.setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip(), pChara->m_texID);
			m_game.setScale(pChara->m_scale, pChara->m_texID);
			m_game.setPosition(pChara->m_pMove->m_pos, pChara->m_texID);
		}
	}


	m_game.setPosition(CVec2(WINDOW_RIGHT*0.125f + cameraPosX, WINDOW_TOP*0.94f), 2);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.962f), 3);
	//HP
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.92f), 4);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.962f), 5);
	//DP
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.92f), 6);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.355f + cameraPosX, WINDOW_TOP*0.94f), 7);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f), 8);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f), 9);
}

void CGameMain::update()
{
	//ゲーム全体を制御する場所
	gameMain();

	CLaunchScheduler::getInstance()->launchCharacters(m_game);



	//出撃の完了したトリガーをすべて取り外す
	checkAndDelete(m_pLaunchSchedule);
	checkAndRemove(m_pCharacters);
	//ステージ終了していなければ
	if (!m_stageEnd)
	{
		for (CCharacter* pChara : (*m_pCharacters))
		{
			pChara->update();
			
		}
		if (pPlayerChara->m_isDamage)
			m_game.setTextureRect(CVec4(0.0f, 0.0f, pPlayerChara->m_hitPoint, 10.0), 4);

		m_game.setTextureRect(CVec4(0.0f, 10.0f, pPlayerChara->m_denkiPoint, 10.0), 6);
	}
	//背景のポジションセット
	m_game.setPosition(CVec2(WINDOW_RIGHT * 0.5 + cameraPosX, WINDOW_TOP * 0.5), MAX_TEXTURE_NUMBER - 1);

	scroll();


}

//ゲーム全体の動き
void CGameMain::gameMain()
{
	//次のステージへ
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
		this->StageEnd(pPlayerChara->m_stageClear);
	}
	if (pPlayerChara->m_gameOver)
	{
		this->StageEnd(pPlayerChara->m_stageClear);
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
			m_game.setupTexture(IMAGE_STAGEEND, TEX_TYPE::PNG, 10, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 1280.0f, 200.0f));


		}
		else
		{
			//Stagefailedを表示
			//this->m_StageFaildSprite->runAction(Show::create());
			m_game.setupTexture(IMAGE_STAGEEND, TEX_TYPE::PNG, 10, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 200.0f, 1280.0f, 200.0f));

		}
		//ステージが終了
		m_stageEnd = true;
		stageSelectinterval = 0;
	}
	if (stageSelectinterval >= 60)
	{
		//フェードイン開始
		if (!movingstage)
		{
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, false) == true)
			{
				movingstage = true;
				gluLookAt(
					-cameraPosX, 0.0f, 0.0f,
					-cameraPosX, 0.0f, -10.0f,
					0.0f, 1.0f, 0.0f
				);
				cameraPosX = 0.0f;
			}
		}
		//フェードイン終了
		if (movingstage == true)
		{
			stageSelectinterval = 0;
			//タイトルシーンを生成
			MS::CMS::getInstance()->setScene(new CTitle());		//ステージセレクト画面に戻る
		}
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