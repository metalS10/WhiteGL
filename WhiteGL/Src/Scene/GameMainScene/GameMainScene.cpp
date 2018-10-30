#include "GameMainScene.h"
#include "../TitleScene/TitleScene.h"

CGameMain::CGameMain()
{

	this->init();
}

CGameMain::~CGameMain()
{


	SAFE_DELETE(notes);
	SAFE_DELETE(m_pCharacters);
	SAFE_DELETE(m_stage);
	CMapManager::removeInstance();
	SAFE_DELETE(m_backGround1);
	SAFE_DELETE(m_backGround2);
	SAFE_DELETE(m_UIBack);
	SAFE_DELETE(m_HPwaku);	//HPUI枠
	SAFE_DELETE(m_BPwaku);	//BPUI枠
	SAFE_DELETE(m_HP);	//BPUI
	SAFE_DELETE(m_BP);	//BPUI
	SAFE_DELETE(m_EnemyStatsUI);	//EnemyUI
	SAFE_DELETE(m_EnemyHPwaku);	//EnemyHPUI枠
	SAFE_DELETE(m_EnemyHP);	//EnemyHPUI
	SAFE_DELETE(m_GameEndUI);	//EnemyHPUI
	SAFE_DELETE(m_cirUI[0]);
	SAFE_DELETE(m_cirUI[1]);
	SAFE_DELETE(m_cirUI[2]);
	SAFE_DELETE(m_cirUI[3]);

	SAFE_DELETE(pPlayerChara);
	SAFE_DELETE(m_blackBoad);


}

bool CGameMain::init()
{
	

	//描画情報の初期化
	m_game.renderInit();

	//ステージ1を開く
	m_stage = new CStage1_1();
	BGM = m_stage->getBGM();

	//ブラックボード
	m_blackBoad = new rendInfo::CTexRendInfo();
	m_blackBoad->setImage("", rendInfo::TEX_TYPE::QUAD, TAG_BLACKBORD, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 100.0f), rendInfo::LAYER::BB);

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

	//一度削除していないとステージを二度遊んだ時にバグが出る
	CLaunchScheduler::getInstance()->removeInstance();

	//出撃スケジュールを出撃スケジューラーに取り付ける
	CLaunchScheduler::getInstance()->createLauncher(m_pLaunchSchedule);

	//キャラクターの集まりの生成
	SAFE_DELETE(m_pCharacters);
	m_pCharacters = new std::vector<CCharacter*>();
	CCharacterAggregate::removeInstance();
	CCharacterAggregate::getInstance()->set(m_pCharacters);

	m_backGround1 = new rendInfo::CTexRendInfo();
	m_backGround2 = new rendInfo::CTexRendInfo();
	//背景
	m_backGround1->setImage(MAIN_BG, rendInfo::TEX_TYPE::PNG, TAG_BG, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, WINDOW_RIGHT, WINDOW_TOP), rendInfo::LAYER::BG);
	m_backGround2->setImage(MAIN_MOVEBG, rendInfo::TEX_TYPE::PNG, TAG_SCROLLBG, CVec2(WINDOW_RIGHT * 3, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 6400.0f, 720.0f), rendInfo::LAYER::BG);
	
	//画面全体UI
	m_cirUI[0] = new rendInfo::CPolygonRendInfo();
	m_cirUI[1] = new rendInfo::CPolygonRendInfo();
	m_cirUI[2] = new rendInfo::CPolygonRendInfo();
	m_cirUI[3] = new rendInfo::CPolygonRendInfo();
	m_cirUI[0]->setupPoly(CVec4(WINDOW_RIGHT * 0.01f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01f, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f),rendInfo::LAYER::UI);
	m_cirUI[1]->setupPoly(CVec4(WINDOW_RIGHT * 0.99f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01f, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[2]->setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.01f, WINDOW_RIGHT * 0.985f, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[3]->setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.99f, WINDOW_RIGHT * 0.985f, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	

	pPlayerChara = (CPlayerCharacter*)CPlayerFactoryManager::getInstance()->create(320.0f, 200.0f);


	//プレイヤー1のタグを設定
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregateにプレイヤーを追加
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	notes = new CNotesUI();


	
	
	m_UIBack = new rendInfo::CTexRendInfo();
	m_HPwaku = new rendInfo::CTexRendInfo();
	m_BPwaku = new rendInfo::CTexRendInfo();
	m_HP = new rendInfo::CTexRendInfo();
	m_BP = new rendInfo::CTexRendInfo();
	m_EnemyStatsUI = new rendInfo::CTexRendInfo();
	m_EnemyHPwaku = new rendInfo::CTexRendInfo();
	m_EnemyHP = new rendInfo::CTexRendInfo();

	//UIの背景
	m_UIBack->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_UI_BACK, CVec2(WINDOW_RIGHT*0.120f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);

	//HPの枠
	m_HPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLINE_HP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);
	//DPの枠
	m_BPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLINE_DP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);

	//HP
	m_HP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_HP , CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);
	//DP
	m_BP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_DP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 10.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);
	//EnemyStats
	m_EnemyStatsUI->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_ENEMY_STATS, CVec2(WINDOW_RIGHT*0.355f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);
	//EnemyHPwaku
	m_EnemyHPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLLINE_ENEMYHP, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);
	//EnemyHP
	m_EnemyHP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_ENEMYHP, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);




	pPlayerChara->input = input;
	//フェードアウト
	m_blackBoad->setActionFade(true, 10.0f);


	return true;
}
bool CGameMain::stageChangeInit()
{
	//初期化
	pPlayerChara->m_beatInterval = 0;
	pPlayerChara->m_beatCounter = 0;

	cameraMoveX = 0.0f;
	cameraMoveY = 0.0f;
	return true;
}

//描画用Update
void CGameMain::rendUpdate()
{

	CScene::rendUpdate();
		
	//カメラ追従UI系
	m_UIBack->setTexPosition(CVec2(WINDOW_RIGHT*0.120f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY));
	m_HPwaku->setTexPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY));
	m_BPwaku->setTexPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));
	m_EnemyStatsUI->setTexPosition(CVec2(WINDOW_RIGHT*0.355f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY));
	m_EnemyHP->setTexPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));
	m_EnemyHPwaku->setTexPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));
	m_backGround1->setTexPosition(CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f + cameraPosY));
	notes->setTexPosition(CVec2(WINDOW_RIGHT-50.0f + cameraPosX, WINDOW_BOTTOM+50.0f + cameraPosY));
	m_cirUI[0]->setPolyPosX(WINDOW_RIGHT * 0.01f +cameraPosX);
	m_cirUI[1]->setPolyPosX(WINDOW_RIGHT * 0.99f +cameraPosX);
	m_cirUI[2]->setPolyPosX(WINDOW_RIGHT * 0.5f	+cameraPosX);
	m_cirUI[3]->setPolyPosX(WINDOW_RIGHT * 0.5f	+cameraPosX);
	
	//HPをHPCarに反映
	m_HP->SetProgressBarWH(CVec4(0.0f, 0.0f, pPlayerChara->m_hitPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY));
	//DPも同様
	m_BP->SetProgressBarWH(CVec4(0.0f, 10.0f, pPlayerChara->m_denkiPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

	if (!m_stageEnd)
	{

		CCharacter* pPlayerChara = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);

		if (pPlayerChara != NULL)
		{

			//プレイヤーに敵がセットされていれば
			if (pPlayerChara->m_pNowEnemy != NULL)
			{
				//ENEMYHPBarにはセットした敵のHPを設定
				float EnemyHP = 100.0f * pPlayerChara->m_pNowEnemy->m_hitPoint / pPlayerChara->m_pNowEnemy->m_maxHitPoint;
				m_EnemyHP->SetProgressBarWH(CVec4(0.0f, 0.0f, EnemyHP, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

				//敵の名前をラベルにセット
				//text->setString(pPlayerChara->m_pNowEnemy->m_name);

				//敵の名前を消すインターバルを初期化する
				m_EnemyNameInterval = 0;
			}
			//敵がセットされていなければ
			else
			{
				//空にする
				m_EnemyHP->SetProgressBarWH(CVec4(0.0f, 0.0f, 0.0f, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));


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
		m_EnemyHP->SetProgressBarWH(CVec4(0.0f, 0.0f, 0.0f, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

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

	//シーンの親更新
	CScene::update();
	//カメラの設定
	cameraPosX += cameraMoveX;
	cameraPosY += cameraMoveY;

	gluLookAt(
		cameraMoveX, cameraMoveY, 0.0f,
		cameraMoveX, cameraMoveY, -10.0f,
		0.0f, 1.0f, 0.0f
	);

	scroll();
	this->cameraShake();
	notes->update();
	//背景用
	m_stage->update();

	//画面全体UIアクション更新
	m_cirUI[0]->polygonBeatsAction();
	m_cirUI[1]->polygonBeatsAction();
	m_cirUI[2]->polygonBeatsAction();
	m_cirUI[3]->polygonBeatsAction();

	
}

//ヒットストップが存在するので注意
void CGameMain::update()
{
	m_blackBoad->textureActionFade();

	//ゲームエンドボタンを押したら
	if (input->getOnKey(Input::Key::GameEnd) == true)
	{
		gluLookAt(
			-cameraPosX, 0.0f, 0.0f,
			-cameraPosX, 0.0f, -10.0f,
			0.0f, 1.0f, 0.0f
		);
		cameraPosX = 0.0f;
		stageSelectinterval = 0;
		m_stageEnd = false;
		//タイトルシーンを生成
		MS::CMS::getInstance()->setScene(new CTitle());		//ステージセレクト画面に戻る
	}
	//printf("%d\n",pPlayerChara->musicNotesCounter );
	//ゲーム全体を制御する場所
	gameMain();

	CLaunchScheduler::getInstance()->launchCharacters();
	
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
	m_blackBoad->setTexPosition(CVec2(WINDOW_RIGHT * 0.5f + cameraPosX, WINDOW_TOP * 0.5f + cameraPosY));

}

//ゲーム全体の動き(ステージ移動)
void CGameMain::gameMain()
{
	//次のステージへ
	if (pPlayerChara->m_nextStage)
	{

		if (!movingstage)
		{
			//フェードアウト
			if (ActionStage(m_blackBoad, 1.0f, false) == true)
			{
				//フェードアウトが終了した
				movingstage = true;
				//次のステージへの関数
				openMap();
				gluLookAt(
					-cameraPosX, 0.0f, 0.0f,
					-cameraPosX, 0.0f, -10.0f,
					0.0f, 1.0f, 0.0f
				);
				cameraPosX = 0.0f;

				pPlayerChara->setPosition(CVec2(320.0f, 200.0f));
			}
		}
		//フェードアウトが終了したら
		if (movingstage == true)
		{
			//フェードイン開始
			if (ActionStage(m_blackBoad, 1.0f, true))
			{
				//フェードインが終了
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

		m_stage->scrollBackGroundTrianglesRight(cameraPosX);

	}
	//プレイヤーの位置が後ろの値超えたら
	else if (pt.x < WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x)
	{
		//原点位置を超えた分に設定する
		pt.x = WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x;

		//超えた分を設定する
		map->setp(pt);

		cameraMoveX = pPlayerChara->m_pMove->m_vel.x;

		m_stage->scrollBackGroundTrianglesLeft(cameraPosX + WINDOW_RIGHT);


	}
	else
	{
		cameraMoveX = 0.0f;

	}
	
}



//現在のゲーム終了判定、セレクト画面へ移行
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
			m_GameEndUI = new rendInfo::CTexRendInfo();
			m_GameEndUI->setImage(IMAGE_STAGEEND, rendInfo::TEX_TYPE::PNG, 9995, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 1280.0f, 200.0f));


		}
		else
		{
			//Stagefailedを表示
			//this->m_StageFaildSprite->runAction(Show::create());
			m_GameEndUI = new rendInfo::CTexRendInfo();
			m_GameEndUI->setImage(IMAGE_STAGEEND, rendInfo::TEX_TYPE::PNG, 9995, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 200.0f, 1280.0f, 200.0f));

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
			BGM->fadeOut(300);
			if (ActionStage(m_blackBoad,1.0f, false) == true)
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

void CGameMain::openMap()
{

	for (CCharacter* pChara : (*m_pCharacters))
	{
		if (pChara->m_tag != TAG_PLAYER_1)
		{
			pChara->m_activeFlag = false;
		}
	}
	m_game.changeStageInit();

	//------------------------------------
	//画像の再生成
	//------------------------------------
	//ブラックボード
	m_blackBoad = new rendInfo::CTexRendInfo();
	m_blackBoad->setImage("", rendInfo::TEX_TYPE::QUAD, TAG_BLACKBORD, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 100.0f), rendInfo::LAYER::BB);


	//BGMのフェードアウト
	BGM->fadeOut(300);

	m_stage = m_stage->changeStage();
	BGM = m_stage->getBGM();

	m_backGround1 = new rendInfo::CTexRendInfo();
	m_backGround2 = new rendInfo::CTexRendInfo();
	//背景
	m_backGround1->setImage(MAIN_BG, rendInfo::TEX_TYPE::PNG, TAG_BG, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, WINDOW_RIGHT, WINDOW_TOP), rendInfo::LAYER::BG);
	m_backGround2->setImage(MAIN_MOVEBG, rendInfo::TEX_TYPE::PNG, TAG_SCROLLBG, CVec2(WINDOW_RIGHT * 3, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 6400.0f, 720.0f), rendInfo::LAYER::BG);

	//画面全体UI
	m_cirUI[0] = new rendInfo::CPolygonRendInfo();
	m_cirUI[1] = new rendInfo::CPolygonRendInfo();
	m_cirUI[2] = new rendInfo::CPolygonRendInfo();
	m_cirUI[3] = new rendInfo::CPolygonRendInfo();
	m_cirUI[0]->setupPoly(CVec4(WINDOW_RIGHT * 0.01f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01f, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[1]->setupPoly(CVec4(WINDOW_RIGHT * 0.99f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01f, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[2]->setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.01f, WINDOW_RIGHT * 0.985f, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[3]->setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.99f, WINDOW_RIGHT * 0.985f, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);

	m_UIBack = new rendInfo::CTexRendInfo();
	m_HPwaku = new rendInfo::CTexRendInfo();
	m_BPwaku = new rendInfo::CTexRendInfo();
	m_HP = new rendInfo::CTexRendInfo();
	m_BP = new rendInfo::CTexRendInfo();
	m_EnemyStatsUI = new rendInfo::CTexRendInfo();
	m_EnemyHPwaku = new rendInfo::CTexRendInfo();
	m_EnemyHP = new rendInfo::CTexRendInfo();

	//UIの背景
	m_UIBack->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_UI_BACK, CVec2(WINDOW_RIGHT*0.120f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);

	//HPの枠
	m_HPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLINE_HP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);
	//DPの枠
	m_BPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLINE_DP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);

	//HP
	m_HP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_HP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);
	//DP
	m_BP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_DP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 10.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);
	//EnemyStats
	m_EnemyStatsUI->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_ENEMY_STATS, CVec2(WINDOW_RIGHT*0.355f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);
	//EnemyHPwaku
	m_EnemyHPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLLINE_ENEMYHP, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);
	//EnemyHP
	m_EnemyHP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_ENEMYHP, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);


	if (CScene::init() == false)
	{
		printf("ステージ遷移に失敗");
	}

	m_stage->init();
	if (this->stageChangeInit() == false)
		printf("ステージ遷移用初期化に失敗");
}






void CGameMain::halfUpdate()
{
	m_stage->actionBackground(m_stage->backgroundType);
}

void CGameMain::qauarterUpdate()
{
	(*pPlayerChara->m_pSounds)[(int)SOUND::PLAYER_BEATS]->Play();
	pPlayerChara->polygonBeatsActionInit(0);
	m_cirUI[0]->polygonBeatsActionInit(1);
	m_cirUI[1]->polygonBeatsActionInit(1);
	m_cirUI[2]->polygonBeatsActionInit(1);
	m_cirUI[3]->polygonBeatsActionInit(1);
	//拍子間隔の更新処理
	for (CCharacter* pChara : (*m_pCharacters))
	{
		pChara->quarterUpdate();
	}
	if(notes != NULL)
		notes->quarter();

	pPlayerChara->playerRolling = true;
}

void CGameMain::eighthUpdate()
{

}

