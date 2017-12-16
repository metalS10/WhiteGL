#pragma once
/**
*	Constants.h
*		2017/9/30	Mats
*		ﾏｸﾛなどを設定する場
*/

//絶対パス
#define PASS "../WhiteGL/Resources/"
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
//弾
#define MAX_BULLET_TEXTURE_NUMBER 1000
//敵
#define MAX_ENEMY_TEXTURE_NUMBER 1000
//マップ描画
#define START_MAP_TEXTURE_NUMBER 500


//テクスチャID
#define PLAYER_ID 5

//プレイヤー
#define IMAGE_PLAYER PASS"player.png"

//攻撃
#define IMAGE_NORMALATTACK PASS"Attack/attack_sword.png"
#define IMAGE_GETSUGATENSHO PASS"Attack/getsugatenshou.png"

//敵
#define IMAGE_ENEMY PASS""
#define IMAGE_NOKONOKO PASS""
#define IMAGE_PATAPATA PASS""
#define IMAGE_KILLER PASS""
#define IMAGE_TROI PASS""

//ギミック
#define IMAGE_DAMAGEBLOCK PASS""
#define IMAGE_ROLLBLOCK PASS""
#define IMAGE_TIKUWABLOCK PASS""
#define IMAGE_NOTEBLOCK PASS""
#define IMAGE_HATENABLOCK PASS""
#define IMAGE_WORP PASS""

//弾
#define IMAGE_NORMAL_FIRE PASS""
#define IMAGE_FIREBALL PASS""

//マップ
#define MAP_PASS PASS"mapData/"
#define MAP_DATA_1 PASS"mapData/1_MapData.tmx"
#define MAP_DATA_2 PASS"mapData/2_MapData.tmx"
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