#pragma once
#pragma comment(lib, "winmm.lib")

#include <Windows.h>
#include <string>
#include <mmsystem.h>
#include "GL\glut.h"

using namespace std;

#define CPUMax 30000
#define CPUMin 10000

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
	void GetFPS();
private:
	string str;
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
void FPS::GetFPS()
{
	draw = false;
	LoopCount++;
	Time = timeGetTime();
	if (Time - Oldtime>Frame*FrameTime) {
		Frame++;
		if (Time - Oldtime<Frame*FrameTimeO) {//�`��^�C�~���O�ɊԂɍ������ꍇ
			str = "LOOP_MAX:[";str += _ltoa(LoopMax, buf, 10);str += "] FPS:[";str += _ltoa(CurrentFps - FrameSkip, buf, 10);
			str += "] FRAME:[";str += _ltoa(Frame, buf, 10);str += "] FRAMESKIP:[";str += _ltoa(FrameSkip, buf, 10);
			str += "] SLEEP:[";str += _ltoa(sleep, buf, 10);str += "]";
			//glutSetWindowTitle(str.c_str());
			draw = true;
			Sleep(sleep);
		}
		else {//�`��^�C�~���O�ɊԂɍ���Ȃ������ꍇ�F�t���[���X�L�b�v
			if (sleep>1)sleep--;//�E�F�C�g�����炷
			Skip++;
		}
	}
	if (Time - Oldtime>1000 - FrameTime) {//��b�����̏���
		LoopMax = LoopCount;
		if (LoopMax>CPUMax) { if (sleep<15)sleep++; }//�\���ɗ]�͂�����ꍇ�E�F�C�g�𑝂₷
		if (LoopMax<CPUMin) { if (sleep>1)sleep--; }//�]�T�������ꍇ�E�F�C�g�����炷
		CurrentFps = Frame;
		FrameSkip = Skip;
		Skip = 0;
		LoopCount = 0;
		Frame = 0;
		Oldtime = Time;
	}
}