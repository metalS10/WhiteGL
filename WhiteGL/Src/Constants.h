#pragma once
/**
*	Constants.h
*		2017/9/30	Mats
*		ﾏｸﾛなどを設定する場
*/

//絶対パス
#define PASS "Resources/"
#define LPASS L"Resources/"
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
#define MAX_TEXTURE_NUMBER 10000
#define MAX_POLYGON_NUMBER 500
//MapChipのレイヤー最大数
#define MAX_LAYER_NUMBER 3
//背景ポリゴンの最大数
#define MAX_BACKGROUND_NUMBER 140

//テクスチャIDの設定---------------------------------------------------------------
//弾
#define START_BULLET_TEXTURE_NUMBER 1000
//敵
#define START_ENEMY_TEXTURE_NUMBER START_BULLET_TEXTURE_NUMBER + 1000
//敵攻撃
#define START_ENEMY_BULLET_TEXTURE_NUMBER START_ENEMY_TEXTURE_NUMBER+1000
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

//テクスチャID
#define BG_ID					0	//BackGround
#define SCROLLBG_ID				1	//ScrollBackGround
//#define PLAYER_ID				3	//Player
#define UI_BACK_ID				4	//UIBack
#define OUTLINE_HP_ID			5	//HPWaku
#define OUTLINE_DP_ID			6	//DPWaku
#define BAR_HP_ID				7	//HPBar
#define BAR_DP_ID				8	//DPBar
#define ENEMY_STATS_ID			9	//ENEMYStats
#define OUTLLINE_ENEMYHP_ID		10	//EHPBarWaku
#define BAR_ENEMYHP_ID			11	//EHPBar
#define BLACKBORD_ID			MAX_TEXTURE_NUMBER - 1
#define NOTES_ID				MAX_TEXTURE_NUMBER - 2




//プレイヤー
#define IMAGE_PLAYER PASS"player.png"

//攻撃
#define IMAGE_NORMALATTACK PASS"Images/Attack/attack_sword.png"
#define IMAGE_GETSUGATENSHO PASS"Images/Attack/getsugatenshou.png"

//敵
#define IMAGE_ENEMY PASS"Images/Enemy/Enemy.png"
#define IMAGE_NOKONOKO PASS""
#define IMAGE_PATAPATA PASS""
#define IMAGE_KILLER PASS""
#define IMAGE_TROI PASS"Images/Enemy/enemy_Troi.png"

//ギミック
#define IMAGE_DAMAGEBLOCK PASS"Images/damageBlock.png"
#define IMAGE_ROLLBLOCK PASS""
#define IMAGE_TIKUWABLOCK PASS""
#define IMAGE_NOTEBLOCK PASS""
#define IMAGE_HATENABLOCK PASS""
#define IMAGE_WORP PASS"Images/Gimmick/worp.png"

//弾
#define IMAGE_NORMAL_FIRE PASS"Images/normalBullet.png"
#define IMAGE_FIREBALL PASS""

//UI
#define IMAGE_GAMEUI	PASS"Images/UI/WhiteUI.png"
#define IMAGE_STAGEEND	PASS"Images/UI/StageEnd.png"
#define IMAGE_NOTES_UI	PASS"Images/UI/NotesUI.png"

//マップ
#define MAP_PASS PASS"mapData/"
#define MAP_DATA_1 PASS"mapData/1_MapData.tmx"
#define MAP_DATA_2 PASS"mapData/MapData2.tmx"

//背景
#define TITLE_BG PASS"Images/BG/title.png"
#define MAIN_BG PASS"Images/BG/black0087.png"
#define MAIN_MOVEBG PASS"Images/BG/p1.png"

//sound
#define SOUND_BGM_TITLE				PASS"sound/gleam.ogg"
#define SOUND_BGM					PASS"sound/cyber_dungeon_001.ogg"
#define SOUND_BGM2					PASS"sound/BraveBattle.ogg"
#define SOUND_DRUM_AVOIDANCE_MISS	PASS"sound/Drum/se_maoudamashii_instruments_drum1_hat.ogg"
#define SOUND_DRUM_AVOIDANCE		PASS"sound/Drum/se_maoudamashii_instruments_drum2_hat.ogg"
#define SOUND_DRUM_ATTACK_MISS		PASS"sound/Drum/se_maoudamashii_instruments_drum1_bassdrum1.ogg"
#define SOUND_DRUM_ATTACK			PASS"sound/Drum/se_maoudamashii_instruments_drum2_bassdrum.ogg"
#define SOUND_QUARTER_NOTES			PASS"sound/Drum/se_maoudamashii_instruments_drum1_bassdrum1.ogg"


//タグ
#define TAG_PLAYER_1 1001
#define TAG_PLAYER_EFFECT_1 1002
#define TAG_PLAYER_EFFECT_2 1003
#define TAG_PLAYER_EFFECT_3 1004
#define TAG_BEATSACTION1 1005
#define TAG_BEATSACTION2 1006
#define TAG_BEATSACTION3 1007
#define TAG_BEATSACTION4 1008

#define TAG_TITLE_TEXT1 1001
#define TAG_TITLE_TEXT2 1002
#define TAG_TITLE_TEXT3 1003
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