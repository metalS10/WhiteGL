#include "TitleScene.h"

#include "../GameMainScene/GameMainScene.h"

CTitle::CTitle()
{
	this->init();
}

CTitle::~CTitle()
{
	for (rendInfo::CTriPolygonRendInfo* bgPoly : m_bgPoly)
	{
		SAFE_DELETE(bgPoly);
	}
	SAFE_DELETE(m_titleText);
	SAFE_DELETE(m_startButton);
	SAFE_DELETE(m_endButton);
	SAFE_DELETE(m_titleBG);
	SAFE_DELETE(m_blackBoad);
}

bool CTitle::init()
{
	//描画情報の初期化
	m_game.renderInit();

	gluLookAt(
		-cameraPosX, -cameraPosY, 0.0f,
		-cameraPosX, -cameraPosY, -10.0f,
		0.0f, 1.0f, 0.0f
	);
	//m_bgPoly = std::vector<rendInfo::CTriPolygonRendInfo>();

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
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly[m_bgPoly.size() - 1]->setupTrianglesPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(r, r, 100.0f, 100.0f), i * 2.0f, rendInfo::LAYER::MAIN);	//背景に反映
			
			//m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//このポリゴンのx軸座標左を設定
			//m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//このポリゴンのx軸座標右を設定
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly[m_bgPoly.size() - 1]->setupTrianglesPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, 100.0f, 100.0f), (i + 0.5f) * 2.0f, rendInfo::LAYER::MAIN);
			
		}
	}
	//タイトルのロゴ
	m_titleText = new rendInfo::CTexRendInfo();
	m_titleText->setImage(TITLE_TEXT, rendInfo::TEX_TYPE::PNG, TAG_TITLE_TEXT1, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.8f), CVec4(0.0f, 0.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);
	//タイトルのStartボタン
	m_startButton = new rendInfo::CTexRendInfo();
	m_startButton->setImage(TITLE_TEXT, rendInfo::TEX_TYPE::PNG, TAG_TITLE_TEXT2, CVec2(WINDOW_RIGHT*0.3f, WINDOW_TOP*0.4f), CVec4(0.0f, 80.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);
	//タイトルのEndボタン
	m_endButton = new rendInfo::CTexRendInfo();
	m_endButton->setImage(TITLE_TEXT, rendInfo::TEX_TYPE::PNG, TAG_TITLE_TEXT3, CVec2(WINDOW_RIGHT*0.7f, WINDOW_TOP*0.4f), CVec4(0.0f, 160.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);
	
	//音に合わせるアクションフラグを立てる
	m_titleText->setTexActionBeats(true);
	m_startButton->setTexActionBeats(true);
	m_endButton->setTexActionBeats(true);


	BGM = new CSound(SOUND_BGM_TITLE, 180,1,20,true);
	if (CScene::init() == false)
	{
		printf("シーン初期化に失敗");
		return false;
	}
	//タイトルのバックグラウンド
	m_titleBG = new rendInfo::CTexRendInfo();
	m_titleBG->setImage(TITLE_BG, rendInfo::TEX_TYPE::PNG, 0, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT),rendInfo::LAYER::BG);
	//m_game.setScale(CVec2(1,1), 0);

	//ボタンの色を変えておく
	selectingButton(m_select);


	//ブラックボード
	m_blackBoad = new rendInfo::CTexRendInfo();
	m_blackBoad->setImage("", rendInfo::TEX_TYPE::QUAD, TAG_BLACKBORD, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 100.0f), rendInfo::LAYER::BB);

	m_blackBoad->setActionFade(true, 10.0f);


	return true;
}

void CTitle::rendUpdate()
{
	CScene::rendUpdate();
}

void CTitle::update()
{
	//フェードアウト更新
	m_blackBoad->textureActionFade();

	CScene::update();
	if (input->getOnKey(Input::Key::START) == true && !m_pushStart)
	{
		//スタートボタンを押した合図
		m_pushStart = true;
		//gameStart
		if (m_select == 0)
		{
			BGM->fadeOut(1000);

			//ゲームスタートする合図
			m_start = true;

		}
		//gameEnd
		else
		{
			BGM->fadeOut(1000);

			//必要ないが一応ゲーム終了する合図
			m_start = false;

		}
		m_blackBoad->setActionFade(false, 10.0f);

	}
	//ボタンを押した後なら
	else if (m_pushStart)
	{
		selectEnter(m_start);
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

	for (rendInfo::CTriPolygonRendInfo* bgPoly : m_bgPoly)
	{
		bgPoly->notesFadeBackground();
	}
	m_titleText->textureNotesAction();
	m_startButton->textureNotesAction();
	m_endButton->textureNotesAction();
}

void CTitle::selectEnter(bool start)
{
	if (m_blackBoad->endTextureFade())
	{
		if (start)
		{
			//ゲームメインシーンを生成
			MS::CMS::getInstance()->setScene(new CGameMain());
		}
		else
		{
			//ゲームを終了する
			m_game.GameEnd();
		}
	}
}

void CTitle::qauarterUpdate()
{
	m_titleText->setTextureScale(CVec2(0.9f, 0.9f));
	//printf("a");
	//Startボタン
	if (m_select == 0)
	{
		m_startButton->setTextureScale(CVec2(0.9f, 0.9f));
	}
	//Endボタン
	else if (m_select == 1)
	{
		m_endButton->setTextureScale(CVec2(0.9f, 0.9f));
	}
	for (rendInfo::CTriPolygonRendInfo* bgPoly : m_bgPoly)
	{
		bgPoly->notesRandomFadeInit();
	}
}

void CTitle::eighthUpdate()
{
}

void CTitle::selectingButton(const int selecting)
{
	switch (selecting)
	{
	case 0:
		m_startButton->setupTextureColor(CVec4(50.0f, 50.0f,100.0f,100.0f));
		m_endButton->setupTextureColor(CVec4(100.0f, 100.0f, 100.0f, 100.0f));
		break;
	case 1:
		m_endButton->setupTextureColor(CVec4(50.0f, 50.0f, 100.0f, 100.0f));
		m_startButton->setupTextureColor(CVec4(100.0f, 100.0f, 100.0f, 100.0f));
		break;
	default:
		printf("ステージ選択中ボタンfunctionに追加されていません\n");
		break;
	}
}
