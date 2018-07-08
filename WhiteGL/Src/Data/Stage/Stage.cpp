#include "Stage.h"

//初期化処理
void CStage1_1::init(CGameEngine& game)
{

	//ステージに定められたマップを開く
	CMapManager::getInstance()->setMap(MAP_DATA_1);
	//背景アクションタイプ設定
	backgroundType = 0;


	//背景ポリゴン軍の初期化
	m_trianglesLeft = std::vector<float>();
	m_trianglesRight = std::vector<float>();

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
			game.setupPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(100.0f, r, r, 100.0f), i * 2.0f,POLY_TYPE::TRIANGLE);	//背景に反映


			m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//このポリゴンのx軸座標左を設定
			m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//このポリゴンのx軸座標右を設定
			game.setupPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, 100.0f, 100.0f), (i + 0.5f) * 2.0f, POLY_TYPE::TRIANGLE);
		}
	}
}

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
	SAFE_DELETE(bgm);
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

//初期化処理
void CStage1_2::init(CGameEngine& game)
{
	//ステージに定められたマップを開く
	CMapManager::getInstance()->setMap(MAP_DATA_2);
	
	//背景アクションタイプ設定
	backgroundType = 1;

	//背景ポリゴン軍の初期化
	m_trianglesLeft = std::vector<float>();
	m_trianglesRight = std::vector<float>();

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
			game.setupPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(r, r, r, 100.0f), i * 2.0f, POLY_TYPE::TRIANGLE);	//背景に反映


			m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//このポリゴンのx軸座標左を設定
			m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//このポリゴンのx軸座標右を設定
			game.setupPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, r, 100.0f), (i + 0.5f) * 2.0f, POLY_TYPE::TRIANGLE);
		}
	}
}

CVec4 CStage1_2::getChangePositionColor(bool Top)
{
	float r = rand() % 100;
	return CVec4(r, r, r, 100.0f);
}

//次のステージを返す。クリアならNULL。
CStage* CStage1_2::changeStage()
{
	//次のステージを返す
	return NULL;
}

//ステージ指定のBGMを返す。
CSound* CStage1_2::getBGM()
{
	//このステージのBGMを設定
	bgm = new CSound(SOUND_BGM2, 212,1, 15, true);
	//設定したものを渡す
	return bgm;
}