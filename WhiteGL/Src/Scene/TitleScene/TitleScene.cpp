#include "TitleScene.h"

#include "../GameMainScene/GameMainScene.h"

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

	//描画情報の初期化
	m_game.renderInit();

	gluLookAt(
		-cameraPosX, -cameraPosY, 0.0f,
		-cameraPosX, -cameraPosY, -10.0f,
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
			m_game.setupPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(r, r, 100.0f, 100.0f), i * 2.0f, POLY_TYPE::TRIANGLE, LAYER::MAIN);	//背景に反映


			//m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//このポリゴンのx軸座標左を設定
			//m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//このポリゴンのx軸座標右を設定
			m_game.setupPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, 100.0f, 100.0f), (i + 0.5f) * 2.0f, POLY_TYPE::TRIANGLE,LAYER::MAIN);
		}
	}
	//タイトルのロゴ
	m_game.setupTexture(TITLE_TEXT, TEX_TYPE::PNG, TAG_TITLE_TEXT1, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.8f), CVec4(0.0f, 0.0f, 300.0f, 80.0f), LAYER::UI);
	//タイトルのStartボタン
	m_game.setupTexture(TITLE_TEXT, TEX_TYPE::PNG, TAG_TITLE_TEXT2, CVec2(WINDOW_RIGHT*0.3f, WINDOW_TOP*0.4f), CVec4(0.0f, 80.0f, 300.0f, 80.0f), LAYER::UI);
	//タイトルのEndボタン
	m_game.setupTexture(TITLE_TEXT, TEX_TYPE::PNG, TAG_TITLE_TEXT3, CVec2(WINDOW_RIGHT*0.7f, WINDOW_TOP*0.4f), CVec4(0.0f, 160.0f, 300.0f, 80.0f), LAYER::UI);


	BGM = new CSound(SOUND_BGM_TITLE, 180,1,20,true);
	if (CScene::init() == false)
	{
		printf("シーン初期化に失敗");
		return false;
	}
	//タイトルのバックグラウンド
	m_game.setupTexture(TITLE_BG, TEX_TYPE::PNG, 0, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT),LAYER::BG);
	//m_game.setScale(CVec2(1,1), 0);

	//ボタンの色を変えておく
	selectingButton(m_select);


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
		if (m_select == 0)
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
		if (!m_pushButton)
		{
			m_select++;
			if (m_select > 1)
			{
				m_select = 0;
			}
			m_pushButton = true;
			//ボタンの色を変える
			selectingButton(m_select);
		}
	}
	else if (input->getOnKey(Input::Key::DPAD_LEFT) == true)
	{
		if (!m_pushButton)
		{
			m_select--;
			if (m_select < 0)
			{
				m_select = 1;
			}
			m_pushButton = true;
			//ボタンの色を変える
			selectingButton(m_select);
		}
	}
	else
	{
		if (m_pushButton)
		{
			m_pushButton = false;
		}
	}
	
}

void CTitle::qauarterUpdate()
{
	m_game.setTexScaleAtTag(CVec2(0.9f, 0.9f), TAG_TITLE_TEXT1);
	//printf("a");
	//Startボタン
	if (m_select == 0)
	{
		m_game.setTexScaleAtTag(CVec2(0.9f, 0.9f), TAG_TITLE_TEXT2);
	}
	//Endボタン
	else if (m_select == 1)
	{
		m_game.setTexScaleAtTag(CVec2(0.9f, 0.9f), TAG_TITLE_TEXT3);
	}
	m_game.notesAction(0);
}

void CTitle::eighthUpdate()
{
}

void CTitle::selectingButton(const int selecting)
{
	switch (selecting)
	{
	case 0:
		m_game.setTexColorAtTag(CVec4(50.0f, 50.0f,100.0f,100.0f), TAG_TITLE_TEXT2);
		m_game.setTexColorAtTag(CVec4(100.0f, 100.0f, 100.0f, 100.0f), TAG_TITLE_TEXT3);
		break;
	case 1:
		m_game.setTexColorAtTag(CVec4(50.0f, 50.0f, 100.0f, 100.0f), TAG_TITLE_TEXT3);
		m_game.setTexColorAtTag(CVec4(100.0f, 100.0f, 100.0f, 100.0f), TAG_TITLE_TEXT2);
		break;
	default:
		printf("ステージ選択中ボタンfunctionに追加されていません\n");
		break;
	}
}
