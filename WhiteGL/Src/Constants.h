#pragma once
/**
*	Constants.h
*		2017/9/30	Mats
*		ﾏｸﾛなどを設定する場
*/

#define NULL 0
//削除
#define SAFE_DELETE(p_)if(p_){delete p_;p_ = NULL;}
//画面サイズ
#define WINDOW_SIZE 1280,720
#define WIDTH 1280
#define HEIGHT 720
//テクスチャ最大数
#define MAX_TEXTURE_NUMBER 5

//絶対パス
#define PASS "C:/Users/tatsu/Desktop/WhiteGL/WhiteGL/Resources/"