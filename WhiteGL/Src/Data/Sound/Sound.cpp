#include "Sound.h"

CSound::CSound(char* sound, const int bpm)
{
	// SDL������
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	// �ȃt�@�C�������[�h
	m_soundName = sound;
	m_bpm = bpm;
	Mix_AllocateChannels(10);
}
CSound::CSound(char* sound)
{
	// SDL������
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	// �ȃt�@�C�������[�h
	m_soundName = sound;
	Mix_AllocateChannels(10);
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
	if (this->m_bpm)
		LoadMusic();
	//�Ȃ���Ό��ʉ�����
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
		std::cerr<<"error,���y�t�@�C���̓ǂݍ��݂Ɏ��s"<<std::endl;
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
	Mix_PlayMusic(m_music, -1);                // �Ȃ̍Đ��X�^�[�g(�������[�v)
}

void CSound::playChunk()
{
	Mix_PlayChannel(-1, m_chunk, 0);            // ���ʉ�1�Đ�
}

void CSound::fadeOut(int ms)
{
	Mix_FadeOutMusic(ms);
}

void CSound::stop()
{
	Mix_HaltMusic();
}
/*lib�g�p�Ȃ����p
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
//�R���X�g���N�^ �t�H���g�쐬
GLFONT::GLFONT(wchar_t *fontname, int size)
{
	Hfont = CreateFontW(
		size,      //�t�H���g����
		0,       //������
		0,       //�e�L�X�g�̊p�x
		0,       //�x�[�X���C���Ƃ����Ƃ̊p�x
		FW_REGULAR,     //�t�H���g�̑���
		FALSE,      //�C�^���b�N��
		FALSE,      //�A���_�[���C��
		FALSE,      //�ł�������
		SHIFTJIS_CHARSET,   //�����Z�b�g
		OUT_DEFAULT_PRECIS,   //�o�͐��x
		CLIP_DEFAULT_PRECIS,  //�N���b�s���O���x
		ANTIALIASED_QUALITY,  //�o�͕i��
		FIXED_PITCH | FF_MODERN, //�s�b�`�ƃt�@�~���[
		fontname);     //���̖�

	Hdc = wglGetCurrentDC();
	SelectObject(Hdc, Hfont);
}
//���C�h������̕`��
void GLFONT::DrawStringW(int x, int y, wchar_t *format, ...)
{
	wchar_t buf[256];
	va_list ap;
	int Length = 0;
	int list = 0;

	//�|�C���^��NULL�̏ꍇ�͏I��
	if (format == NULL)
		return;

	//������ϊ�
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
	//�f�B�X�v���C���X�g�ŕ`��
	for (int i = 0; i<Length; i++)
	{
		glCallList(list + i);
	}
	glEnable(GL_LIGHTING);
	//�f�B�X�v���C���X�g�j��
	glDeleteLists(list, Length);
	list = 0;
	Length = 0;
}

GLFONT *font;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	font->DrawStringW(10, 120, L".wav�t�@�C���Đ��e�X�g");
	glutSwapBuffers();
}
void idle(void)
{
	glutPostRedisplay();
}
void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	font = new GLFONT(L"�l�r����", 24);

	DWORD dwReadSize;
	HANDLE FileHandle = CreateFile(SOUND_BGM, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHandle == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, L"�t�@�C�����J���܂���", L"ERROR!!", MB_OK);
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
	MessageBox(NULL, L"������ďI�����܂��B", L"END", MB_OK);
	PostQuitMessage(0);
}
int main(int argc, char *argv[])
{
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("wav���Đ�");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);//���C�����[�v����߂��Ă���ݒ�
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	Init();
	glutMainLoop();
	Release();
	return 0;
}
*/