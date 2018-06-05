#pragma once

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_mixer.lib")
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>



//音関係を制御するクラス
class CSound
{
private:
	//BPM
	int m_bpm = 0;
	//ファイル名
	char* m_soundName = "";

	//曲
	Mix_Music* m_music = NULL;
	//効果音
	Mix_Chunk* m_chunk = NULL;
	
	//音楽か効果音化を判定する変数
	bool m_musicBool = false;

	//効果音が重なる事ができる最大数
	int overlapChunkMax = 0;
	int overlapChunkCount = 0;

public:
	//Music用コンストラクタ
	CSound(char* sound,const int bpm,bool musicBool);
	//Chunk用コンストラクタ
	CSound(char* sound,const int overlapMax);
	~CSound();

	void Load();
	//音楽の読み込み(ロード)
	void LoadMusic();
	//効果音の読み込み
	void LoadChunk();

	void Play();
	//曲の再生
	void playMusic();
	//効果音
	void playChunk();

	//音楽のフェードアウト
	void fadeOut(int ms);

	//音楽の停止
	void stop(int channel);
	void stop();

	//bpmのgetset
	void setBpm(int bpm);
	int getBpm();
};
