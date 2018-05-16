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
	//ステージ1を開く
	m_stage = new CStage1_1();
	BGM = m_stage->getBGM(BGM);
	if (CScene::init() == false)
	{
		printf("シーン初期化に失敗");
		return false;
	}
	//マップを開く(初期化)
	m_stage->init();
	//BGMを開始させる
	m_BGMStart = false;

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

	//背景
	m_game.setupTexture(MAIN_BG, TEX_TYPE::PNG, 0, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, WINDOW_RIGHT, WINDOW_TOP));
	m_game.setupTexture(MAIN_MOVEBG, TEX_TYPE::PNG, 1, CVec2(WINDOW_RIGHT * 3, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 6400.0f, 720.0f));



	pPlayerChara = (CPlayerCharacter*)CPlayerFactoryManager::getInstance()->create(320.0f, 200.0f);

	//プレイヤー1のタグを設定
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregateにプレイヤーを追加
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	m_game.setupTexture(pPlayerChara->texPass, TEX_TYPE::PNG, pPlayerChara->m_texID, pPlayerChara->m_pMove->m_pos, (*pPlayerChara->m_pAnimations)[0]->getCurrentChip());

	//UIのバック
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, UI_BACK_ID, CVec2(WINDOW_RIGHT*0.125f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f));

	//HPの枠
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, OUTLINE_HP_ID, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 20.0f, 210.0f, 14.0f));
	//DPの枠
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, OUTLINE_DP_ID, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f));

	//HP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, BAR_HP_ID , CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 0.0f, 200.0f, 10.0f));
	//DP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, BAR_DP_ID, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 10.0f, 200.0f, 10.0f));
	//EnemyStats
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, ENEMY_STATS_ID, CVec2(WINDOW_RIGHT*0.355f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f));
	//EnemyHPwaku
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, OUTLLINE_ENEMYHP_ID, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f));
	//EnemyHP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, BAR_ENEMYHP_ID, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 0.0f, 200.0f, 10.0f));


	pPlayerChara->input = input;
	return true;
}

//描画用Update
void CGameMain::rendUpdate()
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


	m_game.setPosition(CVec2(WINDOW_RIGHT*0.125f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY), 4);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY), 5);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY), 6);
	//HP
	//m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.962f), 7);
	//DP
	//m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.92f), 8);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.355f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY), 9);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY), 10);
	//m_game.setPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f), 11);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f + cameraPosY), 0);


	if (!m_stageEnd)
	{
		//ダメージを受けたら
		m_game.SetProgressBarWH(BAR_HP_ID, CVec4(0.0f, 0.0f, pPlayerChara->m_hitPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY));
		//プログレスバー専用の動きをさせる
		m_game.SetProgressBarWH(BAR_DP_ID, CVec4(0.0f, 10.0f, pPlayerChara->m_denkiPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

		CCharacter* pPlayerChara = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);

		if (pPlayerChara != NULL)
		{

			//プレイヤーに敵がセットされていれば
			if (pPlayerChara->m_pNowEnemy != NULL)
			{
				//ENEMYHPBarにはセットした敵のHPを設定
				float EnemyHP = 100 * pPlayerChara->m_pNowEnemy->m_hitPoint / pPlayerChara->m_pNowEnemy->m_maxHitPoint;
				m_game.SetProgressBarWH(BAR_ENEMYHP_ID, CVec4(0.0f, 0.0f, EnemyHP, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

				//敵の名前をラベルにセット
				//text->setString(pPlayerChara->m_pNowEnemy->m_name);

				//敵の名前を消すインターバルを初期化する
				m_EnemyNameInterval = 0;
			}
			//敵がセットされていなければ
			else
			{
				//空にする
				m_game.SetProgressBarWH(BAR_ENEMYHP_ID, CVec4(0.0f, 0.0f, 0.0f, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));


				//名前を空にするのはちょっと待つ
				this->m_EnemyNameInterval++;
				if (this->m_EnemyNameInterval >= 120)
				{
					//text->setString("");
					m_EnemyNameInterval = 0;

				}
			}
		}
	}
	else
	{
		//空にする
		m_game.SetProgressBarWH(BAR_ENEMYHP_ID, CVec4(0.0f, 0.0f, 0.0f, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

		//名前を空にするのはちょっと待つ
		this->m_EnemyNameInterval++;
		if (this->m_EnemyNameInterval >= 120)
		{
			//text->setString("");
			m_EnemyNameInterval = 0;

		}
	}
}

void CGameMain::sceneUpdate()
{

	scroll();
	this->cameraShake();

	cameraPosX += cameraMoveX;
	cameraPosY += cameraMoveY;

	gluLookAt(
		cameraMoveX, cameraMoveY, 0.0f,
		cameraMoveX, cameraMoveY, -10.0f,
		0.0f, 1.0f, 0.0f
	);
}

void CGameMain::update()
{
	//シーンの親更新
	CScene::update();

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
	}

	//背景のポジションセット
	m_game.setPosition(CVec2(WINDOW_RIGHT * 0.5 + cameraPosX, WINDOW_TOP * 0.5 + cameraPosY), MAX_TEXTURE_NUMBER - 1);
}

//ゲーム全体の動き
void CGameMain::gameMain()
{
	//次のステージへ
	if (pPlayerChara->m_nextStage)
	{

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
			m_game.setupTexture(IMAGE_STAGEEND, TEX_TYPE::PNG, 9995, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 1280.0f, 200.0f));


		}
		else
		{
			//Stagefailedを表示
			//this->m_StageFaildSprite->runAction(Show::create());
			m_game.setupTexture(IMAGE_STAGEEND, TEX_TYPE::PNG, 9995, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 200.0f, 1280.0f, 200.0f));

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
			//BGMのフェードアウト
			BGM->fadeOut(100);
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, false) == true)
			{
				movingstage = true;
				gluLookAt(
					-cameraPosX, cameraPosY, 0.0f,
					-cameraPosX, cameraPosY, -10.0f,
					0.0f, 1.0f, 0.0f
				);
				cameraPosX = 0.0f;
			}
		}
		//フェードイン終了
		if (movingstage == true)
		{
			stageSelectinterval = 0;
			m_stageEnd = false;
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

	m_stage = m_stage->changeStage();
	m_stage->init();

}

void CGameMain::qauarterUpdate()
{
	//playerのカウンター
	pPlayerChara->musicNotesCounter = m_quarterNotes * 0.5f;
	pPlayerChara->DPHeal(1.0f);
}