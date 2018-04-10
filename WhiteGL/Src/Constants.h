#pragma once
/**
*	Constants.h
*		2017/9/30	Mats
*		ﾏｸﾛなどを設定する場
*/

//絶対パス
#define PASS "Resources/"
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
//レイヤー最大数(使わない場合は0)
#define MAX_LAYER_NUMBER 3
//テクスチャIDの設定---------------------------------------------------------------
//弾
#define START_BULLET_TEXTURE_NUMBER 1000
//敵
#define START_ENEMY_TEXTURE_NUMBER START_BULLET_TEXTURE_NUMBER + 1000
//敵攻撃
#define START_ENEMY_BULLET_TEXTURE_NUMBER START_ENEMY_TEXTURE_NUMBER+1000
//ギミック
#define START_GIMMICK_TEXTURE_NUMBER START_ENEMY_BULLET_TEXTURE_NUMBER + 1000
//マップ描画
#define START_MAP_TEXTURE_NUMBER 500
//--------------------------------------------------------------------------------

//テクスチャID
#define PLAYER_ID				3	//Player
#define UI_BACK_ID				4	//UIBack
#define OUTLINE_HP_ID			5	//HPWaku
#define OUTLINE_DP_ID			6	//DPWaku
#define BAR_HP_ID				7	//HPBar
#define BAR_DP_ID				8	//DPBar
#define ENEMY_STATS_ID			9	//ENEMYStats
#define OUTLLINE_ENEMYHP_ID		10	//EHPBarWaku
#define BAR_ENEMYHP_ID			11	//EHPBar

#define UI_ID PLAYER_ID UI_BACK_ID OUTLINE_HP_ID OUTLINE_DP_ID BAR_HP_ID BAR_DP_ID ENEMY_STATS_ID OUTLLINE_ENEMYHP_ID BAR_ENEMYHP_ID



//プレイヤー
#define IMAGE_PLAYER PASS"player.png"

//攻撃
#define IMAGE_NORMALATTACK PASS"Attack/attack_sword.png"
#define IMAGE_GETSUGATENSHO PASS"Attack/getsugatenshou.png"

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

//マップ
#define MAP_PASS PASS"mapData/"
#define MAP_DATA_1 PASS"mapData/1_MapData.tmx"
#define MAP_DATA_2 PASS"mapData/MapData2.tmx"

//背景
#define TITLE_BG PASS"Images/BG/title.png"
#define MAIN_BG PASS"Images/BG/black0087.png"
#define MAIN_MOVEBG PASS"Images/BG/p1.png"

//タグ
#define TAG_PLAYER_1 1001

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