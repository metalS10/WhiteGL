#pragma once
/**
*	Constants.h
*		2017/9/30	Mats
*		ﾏｸﾛなどを設定する場
*/

//絶対パス
#define PASS "C:/Users/tatsu/Desktop/WhiteGL/WhiteGL/Resources/"
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
#define MAX_TEXTURE_NUMBER 1000
//弾
#define MAX_BULLET_TEXTURE_NUMBER 1000
//敵
#define MAX_ENEMY_TEXTURE_NUMBER 1000


//テクスチャID
#define PLAYER_ID 5

//プレイヤー
#define IMAGE_PLAYER PASS"player.png"

#define IMAGE_NORMALATTACK PASS"Attack/attack_sword.png"
#define IMAGE_GETSUGATENSHO PASS"Attack/getsugatenshou.png"
#define IMAGE_ENEMY PASS""
#define IMAGE_NOKONOKO PASS""
#define IMAGE_PATAPATA PASS""
#define IMAGE_KILLER PASS""
#define IMAGE_TROI PASS""

#define IMAGE_DAMAGEBLOCK PASS""
#define IMAGE_ROLLBLOCK PASS""
#define IMAGE_TIKUWABLOCK PASS""
#define IMAGE_NOTEBLOCK PASS""
#define IMAGE_HATENABLOCK PASS""
#define IMAGE_WORP PASS""

#define IMAGE_NORMAL_FIRE PASS""
#define IMAGE_FIREBALL PASS""
#define IMAGE_FIREBALL PASS""
#define IMAGE_FIREBALL PASS""

#define TAG_PLAYER_1 1001

#define M_PI       3.14159265358979323846f   // pi

