#include "Stage.h"

//初期化処理
void CStage1_1::init()
{
	//ステージに定められたマップを開く
	CMapManager::getInstance()->setMap(MAP_DATA_1);
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
void CStage1_2::init()
{
	//ステージに定められたマップを開く
	CMapManager::getInstance()->setMap(MAP_DATA_2);
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
	bgm = new CSound(SOUND_BGM2, 212,1, 20, true);
	//設定したものを渡す
	return bgm;
}