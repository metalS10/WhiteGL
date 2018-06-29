#include "Sound.h"

CSound::CSound(char* sound, const int bpm, const int channels,bool musicBool)
{
	// SDL������
	SDL_Init(SDL_INIT_AUDIO);
	//���g���A�t�H�[�}�b�g�A�`�����l���A�o�b�t�@�T�C�Y(�傫���ƒx���Ŏ���)
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, channels, 1024);
	// �ȃt�@�C�������[�h
	m_soundName = sound;
	m_bpm = bpm;
	Mix_AllocateChannels(5);
	m_musicBool = musicBool;
}
CSound::CSound(char* sound, const int bpm, const int channels, const int volume, bool musicBool)
{
	// SDL������
	SDL_Init(SDL_INIT_AUDIO);
	//���g���A�t�H�[�}�b�g�A�`�����l���A�o�b�t�@�T�C�Y(�傫���ƒx���Ŏ���)
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, channels, 1024);
	// �ȃt�@�C�������[�h
	m_soundName = sound;
	m_bpm = bpm;
	Mix_AllocateChannels(5);
	m_musicBool = musicBool;
	m_volume = volume;
}


CSound::CSound(char* sound, const int overlapMax)
{
	// SDL������
	SDL_Init(SDL_INIT_AUDIO);
	//���g���A�t�H�[�}�b�g�A�`�����l���A�o�b�t�@�T�C�Y(�傫���ƒx���Ŏ���)
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 512);
	// �ȃt�@�C�������[�h
	m_soundName = sound;
	Mix_AllocateChannels(overlapMax);
	overlapChunkMax = overlapMax;
}
CSound::CSound(char* sound, const int overlapMax, const int volume)
{
	// SDL������
	SDL_Init(SDL_INIT_AUDIO);
	//���g���A�t�H�[�}�b�g�A�`�����l���A�o�b�t�@�T�C�Y(�傫���ƒx���Ŏ���)
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 512);
	// �ȃt�@�C�������[�h
	m_soundName = sound;
	Mix_AllocateChannels(overlapMax);
	overlapChunkMax = overlapMax;
	m_volume = volume;
}


CSound::~CSound()
{
	Mix_FreeMusic(m_music);		// ���[�h�����Ȃ��J��
	Mix_FreeChunk(m_chunk);		// ���[�h�������ʉ�1���J��
	Mix_CloseAudio();			// SDL_Mixer�N���[�Y
	SDL_Quit();					// SDL�g�p�I��
}

void CSound::Load()
{
	//bpm�����݂��Ă���΋Ȕ���
	if (this->m_musicBool)
		LoadMusic();
	//�Ȃ���Ό��ʉ�����
	else
		LoadChunk();
}

void CSound::LoadMusic()
{
	m_music = Mix_LoadMUS(m_soundName);
}

void CSound::LoadChunk()
{
	if (!Mix_LoadWAV(m_soundName))
	{
		std::cerr<<"error,���y�t�@�C���̓ǂݍ��݂Ɏ��s"<<std::endl;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	m_chunk = Mix_LoadWAV(m_soundName);

	setChunkVolume(m_volume);

}

void CSound::Play()
{
	if (m_musicBool)
		playMusic();
	else
		playChunk();
}

void CSound::playMusic()
{
	//Mix_AllocateChannels(-1);
	Mix_PlayMusic(m_music, -1);                // �Ȃ̍Đ��X�^�[�g(�������[�v)

	setMusicVolume(m_volume);
}

void CSound::playChunk()
{
	Mix_PlayChannel(overlapChunkCount, m_chunk, 0);            // ���ʉ�1�Đ�
	//std::cerr << Mix_GetError()<< std::endl;
	overlapChunkCount++;
	if (overlapChunkCount >= overlapChunkMax)
		overlapChunkCount = 0;

}

void CSound::setMusicVolume(int value)
{
	Mix_VolumeMusic(value);
}

void CSound::setChunkVolume(int value)
{
	Mix_VolumeChunk(m_chunk, value);
}

void CSound::fadeOut(int ms)
{
	int i = Mix_FadeOutMusic(ms);
}

void CSound::stop(int channel)
{
	Mix_HaltChannel(channel);
}
void CSound::stop()
{
	Mix_HaltMusic();
}

void CSound::setBpm(int bpm)
{
	m_bpm = bpm;
}
int CSound::getBpm()
{
	return m_bpm;
}

