#pragma once

#include <Windows.h>
#include <string>
#include "GL\glut.h"

using namespace std;

#define CPUMax 30000
#define CPUMin 10000

#pragma warning(disable : 4996)

//FPS管理クラス
class FPS {
public:
	//ループカウンタ,現在のフレーム,スリープ値,現在のフレームスキップ数,一秒おきのフレームスキップ数,一秒おきのループカウンタ,現在のFPS値
	int LoopCount, Frame, sleep, Skip, FrameSkip, Fps, LoopMax, CurrentFps;
	bool draw;
	DWORD Time, Oldtime;//現在の時間,前回の時間
	float FrameTime, FrameTimeO;
	FPS(int);
	void SetFPS(int);
	void update();
	bool getDraw();
private:
	//データ表記用
	string dataStr;
	char buf[255];
};
//コンストラクタ
FPS::FPS(int fps) {
	draw = false;
	LoopCount = 0;
	Frame = 0;
	sleep = 15;
	Skip = 0;
	Fps = fps;
	FrameSkip = 0;
	LoopMax = 0;
	CurrentFps = 0;
	FrameTime = 1000.0f / fps - 0.000001f;//1フレームの時間
	FrameTimeO = 1000.0f / fps + 0.000001f;
}
void FPS::SetFPS(int fps) {
	Fps = fps;
	FrameTime = 1000.0f / fps - 0.000001f;//1フレームの時間
	FrameTimeO = 1000.0f / fps + 0.000001f;
}
void FPS::update()
{
	
	LoopCount++;
	Time = timeGetTime();
	if (Time - Oldtime>Frame*FrameTime) {
		Frame++;
			//glutSetWindowTitle(str.c_str());
			draw = true;
			//Sleep(sleep);
		
	}
	if (Time - Oldtime>1000 - FrameTime) {//一秒おきの処理
		LoopMax = LoopCount;
		CurrentFps = Frame;
		FrameSkip = Skip;
		Skip = 0;
		LoopCount = 0;
		Frame = 0;
		Oldtime = Time;
	}
	//std::cerr << dataStr << std::endl;
	
}

//描画可能タイミングかどうか
bool FPS::getDraw()
{
	if (draw)
	{
		draw = false;
		return true;
	}
	else
	{
		return false;
	}
}