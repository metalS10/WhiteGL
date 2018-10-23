#pragma once

#include <Windows.h>
#include <string>
#include "GL\glut.h"

using namespace std;

#define CPUMax 30000
#define CPUMin 10000

#pragma warning(disable : 4996)

//FPS�Ǘ��N���X
class FPS {
public:
	//���[�v�J�E���^,���݂̃t���[��,�X���[�v�l,���݂̃t���[���X�L�b�v��,��b�����̃t���[���X�L�b�v��,��b�����̃��[�v�J�E���^,���݂�FPS�l
	int LoopCount, Frame, sleep, Skip, FrameSkip, Fps, LoopMax, CurrentFps;
	bool draw;
	DWORD Time, Oldtime;//���݂̎���,�O��̎���
	float FrameTime, FrameTimeO;
	FPS(int);
	void SetFPS(int);
	void update();
	bool getDraw();
private:
	//�f�[�^�\�L�p
	string dataStr;
	char buf[255];
};
//�R���X�g���N�^
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
	FrameTime = 1000.0f / fps - 0.000001f;//1�t���[���̎���
	FrameTimeO = 1000.0f / fps + 0.000001f;
}
void FPS::SetFPS(int fps) {
	Fps = fps;
	FrameTime = 1000.0f / fps - 0.000001f;//1�t���[���̎���
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
	if (Time - Oldtime>1000 - FrameTime) {//��b�����̏���
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

//�`��\�^�C�~���O���ǂ���
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