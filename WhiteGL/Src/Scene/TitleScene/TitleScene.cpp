#include "TitleScene.h"

CTitle::CTitle()
{
	this->init();
}

CTitle::~CTitle()
{

}

bool CTitle::init()
{

	//全テクスチャ削除
	m_game.allTextureDelete();

	gluLookAt(
		-cameraPosX, 0.0f, 0.0f,
		-cameraPosX, 0.0f, -10.0f,
		0.0f, 1.0f, 0.0f
	);
	//背景の設定
	//高さ
	for (int i = 0; i <= 5; i++)
	{
		//幅
		for (int j = 0; j <= 10; j++)
		{

			float r = rand() % 100;
			float m_polyRange = 128.0f;		//間隔幅
			float range = m_polyRange - 64.0f;	//大きさ

			//m_trianglesLeft.push_back(m_polyRange*j);	//このポリゴンのx軸座標左を設定
			//m_trianglesRight.push_back((m_polyRange*j) + m_polyRange);	//このポリゴンのx軸座標右を設定
			m_game.setupPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(r, r, 0.0f, 100.0f), i * 2.0f, POLY_TYPE::TRIANGLE, LAYER::MAIN);	//背景に反映


			//m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//このポリゴンのx軸座標左を設定
			//m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//このポリゴンのx軸座標右を設定
			m_game.setupPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, 0.0f, 100.0f), (i + 0.5f) * 2.0f, POLY_TYPE::TRIANGLE,LAYER::MAIN);
		}
	}
	//タイトルのロゴ
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, UI_BACK_ID, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.8f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), LAYER::UI, TAG_TITLE_TEXT1);
	//タイトルのStartボタン
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, UI_BACK_ID+1, CVec2(WINDOW_RIGHT*0.3f, WINDOW_TOP*0.4f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), LAYER::UI, TAG_TITLE_TEXT2);
	//タイトルのEndボタン
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, UI_BACK_ID+2, CVec2(WINDOW_RIGHT*0.7f, WINDOW_TOP*0.4f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), LAYER::UI, TAG_TITLE_TEXT3);


	BGM = new CSound(SOUND_BGM_TITLE, 180,1,20,true);
	if (CScene::init() == false)
	{
		printf("シーン初期化に失敗");
		return false;
	}
	//タイトルのバックグラウンド
	m_game.setupTexture(TITLE_BG, TEX_TYPE::PNG, 0, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT),LAYER::BG);
	//m_game.setScale(CVec2(1,1), 0);
	return true;
}

void CTitle::rendUpdate()
{
	CScene::rendUpdate();
}

void CTitle::update()
{
	if (input->getOnKey(Input::Key::START) == true)
	{
		//gameStart
		if (select == 0)
		{
			BGM->fadeOut(1000);
			//ゲームメインシーンを生成
			MS::CMS::getInstance()->setScene(new CGameMain());
		}
		//gameEnd
		else
		{
			BGM->fadeOut(1000);
			m_game.GameEnd();
		}
	}
	//ステージセレクト
	if (input->getOnKey(Input::Key::DPAD_RIGHT) == true)
	{
		if (!pushButton)
		{
			select++;
			if (select > 1)
			{
				select = 0;
			}
			pushButton = true;
		}
	}
	else if (input->getOnKey(Input::Key::DPAD_LEFT) == true)
	{
		if (!pushButton)
		{
			select--;
			if (select < 0)
			{
				select = 1;
			}
			pushButton = true;

		}
	}
	else
	{
		if (pushButton)
		{
			pushButton = false;
		}
	}
	
}

void CTitle::qauarterUpdate()
{
	m_game.setTexScaleAtTag(CVec2(0.9f, 0.9f), TAG_TITLE_TEXT1);
	//printf("a");
	//Startボタン
	if (select == 0)
	{
		m_game.setTexScaleAtTag(CVec2(0.9f, 0.9f), TAG_TITLE_TEXT2);
	}
	//Endボタン
	else if (select == 1)
	{
		m_game.setTexScaleAtTag(CVec2(0.9f, 0.9f), TAG_TITLE_TEXT3);
	}
	m_game.notesAction(0);
}

void CTitle::eighthUpdate()
{
}