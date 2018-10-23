#pragma once
/**
*	Constants.h
*		2017/9/30	Mats
*		ﾏｸﾛなどを設定する場
*/

//パス
#define PATH "Resources/"
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif
//削除
#define SAFE_DELETE(p_)if(p_){delete p_;p_ = NULL;}
//画面サイズ
#define WINDOW_SIZE 1280,720
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_RIGHT WINDOW_WIDTH
#define WINDOW_LEFT 0
#define WINDOW_TOP WINDOW_HEIGHT
#define WINDOW_BOTTOM 0

//テクスチャ最大数
#define MAX_TEXTURE_NUMBER 15000
#define MAX_POLYGON_NUMBER 500
//MapChipのレイヤー最大数
#define MAX_LAYER_NUMBER 3
//背景ポリゴンの最大数
#define MAX_BACKGROUND_NUMBER 140

//テクスチャIDの設定---------------------------------------------------------------
//弾
#define START_BULLET_TEXTURE_NUMBER 2000
//敵
#define START_ENEMY_TEXTURE_NUMBER START_BULLET_TEXTURE_NUMBER + 1000
//敵攻撃
#define START_ENEMY_BULLET_TEXTURE_NUMBER START_ENEMY_TEXTURE_NUMBER + 1000
//ギミック
#define START_GIMMICK_TEXTURE_NUMBER START_ENEMY_BULLET_TEXTURE_NUMBER + 1000
//音に合わせるやつ
#define START_NOTES_TEXTURE_NUMBER START_GIMMICK_TEXTURE_NUMBER + 1000
//マップ描画
#define START_MAP_TEXTURE_NUMBER 500
//--------------------------------------------------------------------------------


//拍子セーフ間隔
#define BEAT_INTERVAL 5;
//背景用拍子のサイズ変更値
#define BEAT_BIGSIZE	30.0f;

/*=========================================
*	テクスチャTAG基テクスチャID
*=========================================*/
#define TAG_BG					0	//BackGround
#define TAG_SCROLLBG			1	//ScrollBackGround
//#define TAG_PLAYER			3	//Player
#define TAG_UI_BACK				4	//UIBack
#define TAG_OUTLINE_HP			5	//HPWaku
#define TAG_OUTLINE_DP			6	//DPWaku
#define TAG_BAR_HP				7	//HPBar
#define TAG_BAR_DP				8	//DPBar
#define TAG_ENEMY_STATS			9	//ENEMYStats
#define TAG_OUTLLINE_ENEMYHP	10	//EHPBarWaku
#define TAG_BAR_ENEMYHP		11	//EHPBar
#define TAG_BLACKBORD			MAX_TEXTURE_NUMBER - 1
#define TAG_NOTES				MAX_TEXTURE_NUMBER - 2
//GameMain
#define TAG_PLAYER_1 101			//プレイヤーキャラクター
#define TAG_PLAYER_EFFECT_1 102	//プレイヤーキャラクターの残像
#define TAG_PLAYER_EFFECT_2 103	//プレイヤーキャラクターの残像
#define TAG_PLAYER_EFFECT_3 104	//プレイヤーキャラクターの残像
#define TAG_BEATSACTION1 105		//画面端のユーザーインターフェース
#define TAG_BEATSACTION2 106		//画面端のユーザーインターフェース
#define TAG_BEATSACTION3 107		//画面端のユーザーインターフェース
#define TAG_BEATSACTION4 108		//画面端のユーザーインターフェース
#define TAG_PLAYER_ATTACK 109		//プレイヤーキャラクターの攻撃
//Title
#define TAG_TITLE_TEXT1 101		//タイトルの文字画像
#define TAG_TITLE_TEXT2 102		//タイトルの文字画像
#define TAG_TITLE_TEXT3 103		//タイトルの文字画像




//プレイヤー
#define IMAGE_PLAYER PATH"player.png"

//攻撃
#define IMAGE_NORMALATTACK PATH"Images/Attack/attack_sword.png"
#define IMAGE_GETSUGATENSHO PATH"Images/Attack/getsugatenshou.png"

//敵
#define IMAGE_ENEMY PATH"Images/Enemy/Enemy.png"
#define IMAGE_NOKONOKO PATH""
#define IMAGE_PATAPATA PATH""
#define IMAGE_KILLER PATH""
#define IMAGE_TROI PATH"Images/Enemy/enemy_Troi.png"

//ギミック
#define IMAGE_DAMAGEBLOCK PATH"Images/damageBlock.png"
#define IMAGE_ROLLBLOCK PATH""
#define IMAGE_TIKUWABLOCK PATH""
#define IMAGE_NOTEBLOCK PATH""
#define IMAGE_HATENABLOCK PATH""
#define IMAGE_WORP PATH"Images/Gimmick/worp.png"

//弾
#define IMAGE_NORMAL_FIRE PATH"Images/normalBullet.png"
#define IMAGE_FIREBALL PATH""

//UI
#define IMAGE_GAMEUI	PATH"Images/UI/WhiteUI.png"
#define IMAGE_STAGEEND	PATH"Images/UI/StageEnd.png"
#define IMAGE_NOTES_UI	PATH"Images/UI/NotesUI.png"

//マップ
#define MAP_PASS PATH"mapData/"
#define MAP_DATA_1 PATH"mapData/1_MapData.tmx"
#define MAP_DATA_2 PATH"mapData/MapData2.tmx"

//背景
#define TITLE_BG PATH"Images/BG/GameBG.png"
#define MAIN_BG PATH"Images/BG/MainBG.png"
#define MAIN_MOVEBG PATH"Images/BG/p1.png"

//Text
#define TITLE_TEXT	PATH"Images/UI/TitleText.png"

//sound
#define SOUND_BGM_TITLE				PATH"sound/gleam.ogg"
#define SOUND_BGM					PATH"sound/cyber_dungeon_001.ogg"
#define SOUND_BGM2					PATH"sound/BraveBattle.ogg"
#define SOUND_DRUM_AVOIDANCE_MISS	PATH"sound/Drum/se_maoudamashii_instruments_drum1_hat.ogg"
#define SOUND_DRUM_AVOIDANCE		PATH"sound/Drum/se_maoudamashii_instruments_drum2_hat.ogg"
#define SOUND_DRUM_ATTACK_MISS		PATH"sound/Drum/se_maoudamashii_instruments_drum1_bassdrum1.ogg"
#define SOUND_DRUM_ATTACK			PATH"sound/Drum/se_maoudamashii_instruments_drum2_bassdrum.ogg"
#define SOUND_QUARTER_BEATS			PATH"sound/Drum/se_maoudamashii_instruments_drum1_hat.ogg"





//Math
#define M_PI       3.14159265358979323846f   // pi
//etc
#define CC_DLL     __declspec(dllimport)

typedef enum TMXTileFlags_ {
    kTMXTileHorizontalFlag  = 0x80000000,
    kTMXTileVerticalFlag    = 0x40000000,
    kTMXTileDiagonalFlag    = 0x20000000,
    kTMXFlipedAll           = (kTMXTileHorizontalFlag|kTMXTileVerticalFlag|kTMXTileDiagonalFlag),
    kTMXFlippedMask         = ~(kTMXFlipedAll)
} TMXTileFlags;