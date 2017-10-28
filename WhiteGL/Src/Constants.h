#pragma once
/**
*	Constants.h
*		2017/9/30	Mats
*		ﾏｸﾛなどを設定する場
*/

//絶対パス
#define PASS "C:/Users/tatsu/Desktop/WhiteGL/WhiteGL/Resources/"
#define NULL 0
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
#define MAX_TEXTURE_NUMBER 6

//プレイヤー
#define IMAGE_PLAYER PASS"player.png"

#define TAG_PLAYER_1 1001
