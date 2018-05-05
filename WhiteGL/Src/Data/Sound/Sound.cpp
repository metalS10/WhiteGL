#include "Sound.h"

CSound::CSound(char* sound, const int bpm)
{
	// SDL初期化
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	// 曲ファイルをロード
	m_soundName = sound;
	m_bpm = bpm;
	Mix_AllocateChannels(10);
}
CSound::CSound(char* sound)
{
	// SDL初期化
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	// 曲ファイルをロード
	m_soundName = sound;
	Mix_AllocateChannels(10);
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
	if (this->m_bpm)
		LoadMusic();
	//なければ効果音判定
	else
		LoadChunk();
}

void CSound::LoadMusic()
{
	m_music = Mix_LoadMUS(m_soundName);
	m_musicBool = true;
}

void CSound::LoadChunk()
{
	if (!Mix_LoadWAV(m_soundName))
	{
		std::cerr<<"error,音楽ファイルの読み込みに失敗"<<std::endl;
	}
	m_chunk = Mix_LoadWAV(m_soundName);
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
	Mix_PlayMusic(m_music, -1);                // 曲の再生スタート(無限ループ)
}

void CSound::playChunk()
{
	Mix_PlayChannel(-1, m_chunk, 0);            // 効果音1再生
}

void CSound::fadeOut(int ms)
{
	Mix_FadeOutMusic(ms);
}

void CSound::stop()
{
	Mix_HaltMusic();
}
/*lib使用なし試用
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#pragma comment(lib,"winmm.lib")
#include <windows.h>
#include <mmsystem.h>

#include <GL/freeglut.h>
#include <stdio.h>
#include "../../Constants.h"

#define WIDTH 320
#define HEIGHT 240

LPCWSTR Sound;

class GLFONT
{
public:
	HFONT Hfont;
	HDC Hdc;
	GLFONT(wchar_t *fontname, int size);
	void DrawStringW(int x, int y, wchar_t *format, ...);
};
//コンストラクタ フォント作成
GLFONT::GLFONT(wchar_t *fontname, int size)
{
	Hfont = CreateFontW(
		size,      //フォント高さ
		0,       //文字幅
		0,       //テキストの角度
		0,       //ベースラインとｘ軸との角度
		FW_REGULAR,     //フォントの太さ
		FALSE,      //イタリック体
		FALSE,      //アンダーライン
		FALSE,      //打ち消し線
		SHIFTJIS_CHARSET,   //文字セット
		OUT_DEFAULT_PRECIS,   //出力精度
		CLIP_DEFAULT_PRECIS,  //クリッピング精度
		ANTIALIASED_QUALITY,  //出力品質
		FIXED_PITCH | FF_MODERN, //ピッチとファミリー
		fontname);     //書体名

	Hdc = wglGetCurrentDC();
	SelectObject(Hdc, Hfont);
}
//ワイド文字列の描画
void GLFONT::DrawStringW(int x, int y, wchar_t *format, ...)
{
	wchar_t buf[256];
	va_list ap;
	int Length = 0;
	int list = 0;

	//ポインタがNULLの場合は終了
	if (format == NULL)
		return;

	//文字列変換
	va_start(ap, format);
	vswprintf_s(buf, format, ap);
	va_end(ap);

	Length = wcslen(buf);
	list = glGenLists(Length);
	for (int i = 0; i<Length; i++) {
		wglUseFontBitmapsW(Hdc, buf[i], 1, list + (DWORD)i);
	}

	glDisable(GL_LIGHTING);
	glRasterPos2i(x, y);
	//ディスプレイリストで描画
	for (int i = 0; i<Length; i++)
	{
		glCallList(list + i);
	}
	glEnable(GL_LIGHTING);
	//ディスプレイリスト破棄
	glDeleteLists(list, Length);
	list = 0;
	Length = 0;
}

GLFONT *font;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	font->DrawStringW(10, 120, L".wavファイル再生テスト");
	glutSwapBuffers();
}
void idle(void)
{
	glutPostRedisplay();
}
void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	font = new GLFONT(L"ＭＳ明朝", 24);

	DWORD dwReadSize;
	HANDLE FileHandle = CreateFile(SOUND_BGM, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHandle == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, L"ファイルが開けません", L"ERROR!!", MB_OK);
	}
	DWORD dwFileSize = GetFileSize(FileHandle, NULL);
	Sound = (LPCWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwFileSize);
	ReadFile(FileHandle, (LPVOID)Sound, dwFileSize, &dwReadSize, NULL);
	CloseHandle(FileHandle);
	PlaySound(Sound, NULL, SND_MEMORY | SND_ASYNC | SND_LOOP);
}
void Release() {
	PlaySound(NULL, NULL, 0);
	HeapFree(GetProcessHeap(), 0, (LPVOID)Sound);
	MessageBox(NULL, L"解放して終了します。", L"END", MB_OK);
	PostQuitMessage(0);
}
int main(int argc, char *argv[])
{
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("wavを再生");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);//メインループから戻ってくる設定
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	Init();
	glutMainLoop();
	Release();
	return 0;
}
*/