#include "Stage.h"



//===========================================================
//親
//===========================================================
//背景スクロール用の関数
//左へスクロール中
void CStage::scrollBackGroundTrianglesLeft(float posX)
{
	for (int i = 0; i < m_trianglesLeft.size(); i++)
	{
		//ポリゴンの左が画面右端に来たら
		if (m_trianglesLeft[i] >= posX)
		{
			float pos = m_trianglesLeft[i];

			//左を画面左端+ポリゴン間隔に再設置
			m_trianglesLeft[i] = pos - WINDOW_RIGHT - m_polyRange;
			//右を画面左端へ
			m_trianglesRight[i] = pos - WINDOW_RIGHT;
			//色を再設定
			int r = rand() % 100;
			int l = i;
			while (l >= 0)
			{
				l -= 2;
				if (l <= -1)
				{
					m_bgPoly[i]->setTrianglesPolyPos(m_trianglesLeft[i], getChangePositionColor(false));	//背景に反映
					break;
				}
				else if (l <= 0)
				{
					m_bgPoly[i]->setTrianglesPolyPos(m_trianglesLeft[i], getChangePositionColor(true));	//背景に反映
					break;
				}
			}
		}
	}
}
//右へスクロール中
void CStage::scrollBackGroundTrianglesRight(float posX)
{
	for (int i = 0; i < m_trianglesRight.size(); i++)
	{
		float pos = m_trianglesRight[i];

		//ポリゴンの右が画面左端に来たら
		if (m_trianglesRight[i] <= posX)
		{
			//左を画面右端へ
			m_trianglesLeft[i] = pos + WINDOW_RIGHT;
			//右を画面右端+ポリゴン間隔へ
			m_trianglesRight[i] = pos + WINDOW_RIGHT + m_polyRange;
			//色を再設定
			int r = rand() % 100;
			int l = i;
			while (l >= 0)
			{
				l -= 2;
				if (l <= -1)
				{
					m_bgPoly[i]->setTrianglesPolyPos(m_trianglesLeft[i], getChangePositionColor(false));	//背景に反映
					break;
				}
				else if (l <= 0)
				{
					m_bgPoly[i]->setTrianglesPolyPos(m_trianglesLeft[i], getChangePositionColor(true));	//背景に反映
					break;
				}
			}
		}
	}
}

//背景ポリゴンのアクション
/**
*	mode
*0.Random
*1.Up
*2.doubleUp
*/
void CStage::actionBackground(int mode)
{
	for (rendInfo::CTriPolygonRendInfo* bgPoly : m_bgPoly)
	{
		switch (mode)
		{
		case 0:
			bgPoly->notesRandomFadeInit();
			break;
		case 1:
			bgPoly->notesUpFadeInit(mode - 1);
			break;
		case 2:
			bgPoly->notesUpFadeInit(mode - 1);
			break;
		default:
			break;

			//renderer->setRotate(CVec3(1.0f, 0.0f, 0.0f), 1.0f);
		}
	}
}




//===========================================================
//1-1
//===========================================================
//初期化処理
void CStage1_1::init()
{

	//ステージに定められたマップを開く
	CMapManager::getInstance()->setMap(MAP_DATA_1);
	//背景アクションタイプ設定
	backgroundType = 0;


	//背景ポリゴン軍の初期化
	m_trianglesLeft = std::vector<float>();
	m_trianglesRight = std::vector<float>();

	m_bgPoly.clear();

	//背景の設定
	//高さ
	for (int i = 0; i <= 5; i++)
	{
		//幅
		for (int j = 0; j <= 10; j++)
		{

			float r = rand() % 100;
			m_polyRange = 128.0f;		//間隔幅
			float range = m_polyRange - 64.0f;	//大きさ

			m_trianglesLeft.push_back(m_polyRange*j);	//このポリゴンのx軸座標左を設定
			m_trianglesRight.push_back((m_polyRange*j) + m_polyRange);	//このポリゴンのx軸座標右を設定
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly.back()->setupTrianglesPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(100.0f, r, r, 100.0f), i * 2.0f,rendInfo::LAYER::BG);	//背景に反映


			m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//このポリゴンのx軸座標左を設定
			m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//このポリゴンのx軸座標右を設定
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly[m_bgPoly.size() - 1]->setupTrianglesPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, 100.0f, 100.0f), (i + 0.5f) * 2.0f, rendInfo::LAYER::BG);
		}
	}
}

//スクロール更新の際の背景色情報
CVec4 CStage1_1::getChangePositionColor(bool Top)
{
	float r = rand() % 100;
	if (Top)
		return CVec4(100.0f, r, r, 100.0f);
	else
		return CVec4(r, r, 100.0f, 100.0f);
}

//次のステージを返す。クリアならNULL。
CStage* CStage1_1::changeStage()
{
	CMapManager::removeInstance();
	for(rendInfo::CTriPolygonRendInfo* triPoly:m_bgPoly)
	{
		SAFE_DELETE(triPoly);
	}
	//次のステージを返す
	return new CStage1_2();
}

//ステージ指定のBGMを返す。
CSound* CStage1_1::getBGM()
{
	//このステージのBGMを設定
	bgm = new CSound(SOUND_BGM, 140,1, 20, true);
	//設定したものを渡す
	return bgm;
}
void CStage1_1::update()
{
	for (rendInfo::CTriPolygonRendInfo* bgPoly : m_bgPoly)
	{
		bgPoly->notesFadeBackground();
	}
}


//===========================================================
//1-2
//===========================================================
//初期化処理
void CStage1_2::init()
{
	//ステージに定められたマップを開く
	CMapManager::getInstance()->setMap(MAP_DATA_2);
	
	//背景アクションタイプ設定
	backgroundType = 1;

	//背景ポリゴン軍の初期化
	m_trianglesLeft = std::vector<float>();
	m_trianglesRight = std::vector<float>();

	m_bgPoly.clear();

	//背景の設定
	//高さ
	for (int i = 0; i <= 5; i++)
	{
		//幅
		for (int j = 0; j <= 10; j++)
		{

			float r = rand() % 100;
			m_polyRange = 128.0f;		//間隔幅
			float range = m_polyRange - 64.0f;	//大きさ

			m_trianglesLeft.push_back(m_polyRange*j);	//このポリゴンのx軸座標左を設定
			m_trianglesRight.push_back((m_polyRange*j) + m_polyRange);	//このポリゴンのx軸座標右を設定
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly[m_bgPoly.size() - 1]->setupTrianglesPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(r, r, r, 100.0f), i * 2.0f, rendInfo::LAYER::BG);	//背景に反映


			m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//このポリゴンのx軸座標左を設定
			m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//このポリゴンのx軸座標右を設定
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly[m_bgPoly.size() - 1]->setupTrianglesPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, r, 100.0f), (i + 0.5f) * 2.0f, rendInfo::LAYER::BG);
		}
	}
}

//スクロール更新の際の背景色情報
CVec4 CStage1_2::getChangePositionColor(bool Top)
{
	float r = rand() % 100;
	return CVec4(r, r, r, 100.0f);
}

//次のステージを返す。クリアならNULL。
CStage* CStage1_2::changeStage()
{
	CMapManager::removeInstance();
	for (rendInfo::CTriPolygonRendInfo* triPoly : m_bgPoly)
	{
		SAFE_DELETE(triPoly);
	}
	//次のステージを返す
	return NULL;
}

//ステージ指定のBGMを返す。
CSound* CStage1_2::getBGM()
{
	//このステージのBGMを設定
	bgm = new CSound(SOUND_BGM2, 180,1, 15, true);
	//設定したものを渡す
	return bgm;
}
void CStage1_2::update()
{
	for (rendInfo::CTriPolygonRendInfo* bgPoly : m_bgPoly)
	{
		bgPoly->notesFadeBackground();
	}
}