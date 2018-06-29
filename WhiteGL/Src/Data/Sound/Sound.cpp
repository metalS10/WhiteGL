#include "Sound.h"

CSound::CSound(char* sound, const int bpm, const int channels,bool musicBool)
{
	// SDL初期化
	SDL_Init(SDL_INIT_AUDIO);
	//周波数、フォーマット、チャンネル、バッファサイズ(大きいと遅延で死ぬ)
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, channels, 1024);
	// 曲ファイルをロード
	m_soundName = sound;
	m_bpm = bpm;
	Mix_AllocateChannels(5);
	m_musicBool = musicBool;
}
CSound::CSound(char* sound, const int bpm, const int channels, const int volume, bool musicBool)
{
	// SDL初期化
	SDL_Init(SDL_INIT_AUDIO);
	//周波数、フォーマット、チャンネル、バッファサイズ(大きいと遅延で死ぬ)
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, channels, 1024);
	// 曲ファイルをロード
	m_soundName = sound;
	m_bpm = bpm;
	Mix_AllocateChannels(5);
	m_musicBool = musicBool;
	m_volume = volume;
}


CSound::CSound(char* sound, const int overlapMax)
{
	// SDL初期化
	SDL_Init(SDL_INIT_AUDIO);
	//周波数、フォーマット、チャンネル、バッファサイズ(大きいと遅延で死ぬ)
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 512);
	// 曲ファイルをロード
	m_soundName = sound;
	Mix_AllocateChannels(overlapMax);
	overlapChunkMax = overlapMax;
}
CSound::CSound(char* sound, const int overlapMax, const int volume)
{
	// SDL初期化
	SDL_Init(SDL_INIT_AUDIO);
	//周波数、フォーマット、チャンネル、バッファサイズ(大きいと遅延で死ぬ)
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 512);
	// 曲ファイルをロード
	m_soundName = sound;
	Mix_AllocateChannels(overlapMax);
	overlapChunkMax = overlapMax;
	m_volume = volume;
}


CSound::~CSound()
{
	Mix_FreeMusic(m_music);		// ロードした曲を開放
	Mix_FreeChunk(m_chunk);		// ロードした効果音1を開放
	Mix_CloseAudio();			// SDL_Mixerクローズ
	SDL_Quit();					// SDL使用終了
}

void CSound::Load()
{
	//bpmが存在していれば曲判定
	if (this->m_musicBool)
		LoadMusic();
	//なければ効果音判定
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
		std::cerr<<"error,音楽ファイルの読み込みに失敗"<<std::endl;
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
	Mix_PlayMusic(m_music, -1);                // 曲の再生スタート(無限ループ)

	setMusicVolume(m_volume);
}

void CSound::playChunk()
{
	Mix_PlayChannel(overlapChunkCount, m_chunk, 0);            // 効果音1再生
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

