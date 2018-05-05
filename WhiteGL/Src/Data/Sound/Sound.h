#pragma once

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_mixer.lib")
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>

//���֌W�𐧌䂷��N���X
class CSound
{
private:
	//BPM
	int m_bpm = 0;
	//�t�@�C����
	char* m_soundName = "";

	//��
	Mix_Music* m_music = NULL;
	//���ʉ�
	Mix_Chunk* m_chunk = NULL;

	bool m_musicBool = false;

public:
	//Music�p�R���X�g���N�^
	CSound(char* sound,const int bpm);
	//Chunk�p�R���X�g���N�^
	CSound(char* sound);
	~CSound();

	void Load();
	//���y�̓ǂݍ���(���[�h)
	void LoadMusic();
	//���ʉ��̓ǂݍ���
	void LoadChunk();

	void Play();
	//�Ȃ̍Đ�
	void playMusic();
	//���ʉ�
	void playChunk();

	//���y�̃t�F�[�h�A�E�g
	void fadeOut(int ms);

	//���y�̒�~
	void stop();
};
