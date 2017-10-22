/**
*	main.cpp
*		2017/09/29	Mats
*/
#include "GameEngine.h"

#include "FPS.h"
/**
*GLFW����̃G���[�񍐂���������
*
*@param	error	�G���[�ԍ�
*@para,	desc	�G���[���e
*/
void ErrorCallback(int error, const char* desc)
{
	std::cerr << "ERROR : " << desc << std::endl;
}
/**
*	@file main.cpp
*/
//�G���g���[�|�C���g
int main()
{
	glfwSetErrorCallback(ErrorCallback);


	CGameEngine& game = CGameEngine();
	

	/*
	// ���j�^�Ƃ̓���
	glfwSwapInterval(1);

	// �`��͈͂̎w��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, g_windowWidth, 0.0f, g_windowHeight, -1.0f, 1.0f);

	//�e�N�X�`���̃��[�h
	glGenTextures(1, &g_texID);
	setupTexture(g_texID, PASS"Sparrow.bmp", 200, 200);
	*/
	// ���j�^�Ƃ̓���
	//glfwSwapInterval(1);

	// �`��͈͂̎w��
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	GLFWwindow* window = game.init(WINDOW_SIZE,"WhiteV_GL");
	if (window == NULL)
		return false;
	game.setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 0, CVec4(0.0f, 200.0f, 100.0f, 300.0f), CVec4(0.0f, 200.0f, 0.0f, 200.0f), CVec4(100.0f,100.0f,100.0f,100.0f));


	game.setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 1, CVec4(200.0f, 400.0f, 100.0f, 300.0f), CVec4(100.0f, 200.0f, 100.0f, 200.0f), CVec4(100.0f, 100.0f, 100.0f, 100.0f));

	game.setupTexture(PASS"player.bmp", TEX_TYPE::BMP, 2, CVec4(400.0f, 464.0f, 100.0f, 164.0f), CVec4(0.0f, 64.0f, 128.0f, 192.0f), CVec4(100.0f, 100.0f, 100.0f, 100.0f));

	game.setupTexture(PASS"kuribo.png", TEX_TYPE::PNG, 3, CVec4(0.0f, 100.0f, 300.0f, 400.0f), CVec4(0.0f, 64.0f, 0.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 100.0f));

	game.setupTexture(PASS"player.png", TEX_TYPE::PNG, 4, CVec4(100.0f, 200.0f, 300.0f, 400.0f), CVec4(0.0f, 64.0f, 0.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 100.0f));

	game.setupTexture("", TEX_TYPE::QUAD, MAX_TEXTURE_NUMBER-1, CVec4(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT), CVec4(0.0f, 64.0f, 0.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 0.0f));


	


	
	game.setChipAnim(new CNotAnimation());
	game.setChipAnim(new CNotAnimation());
	game.setChipAnim(new CNotAnimation());
	game.setChipAnim(new CNotAnimation());
	game.setChipAnim(new CListAnimation(20,true));


	game.setChipData(0,CVec4(0.0f, 200.0f, 0.0f, 200.0f));
	game.setChipData(1,CVec4(100.0f, 200.0f, 100.0f, 200.0f));
	game.setChipData(2,CVec4(0.0f, 64.0f, 128.0f, 192.0f));
	game.setChipData(3,CVec4(0.0f, 64.0f, 0.0f, 64.0f));

	game.setChipData(4, CVec4(0.0f, 64.0f, 0.0f, 64.0f));
	game.setChipData(4, CVec4(64.0f, 128.0f, 0.0f, 64.0f));
	game.setChipData(4, CVec4(128.0f, 192.0f, 0.0f, 64.0f));
	game.setChipData(4, CVec4(192.0f, 256.0f, 0.0f, 64.0f));


	FPS* fps = new FPS(60);

	GLFWEW::Window& FwewWindow = GLFWEW::Window::Instance();

	double prevTime = glfwGetTime();

	/**
	*memo
	*���C�����[�v
	*���t���[�����s�����
	*glfwWindowShouldClose�̓E�B���h�E�����ׂ����ǂ����𒲂ׂ�֐�
	*	�����œn���ꂽ�E�B���h�E�ɑ΂���OS������I���v�������Ă��Ȃ����0,���Ă����0�ȊO��Ԃ�
	*GLFW�ō쐬�����E�B���h�E��1�����Ȃ�I������͂��̊֐������邾���ŏ\��
	*/
	while (!glfwWindowShouldClose(window))
	{
		const double curTime = glfwGetTime();
		const double delta = curTime - prevTime;
		prevTime = curTime;
		FwewWindow.UpdateGamePad();
		const GamePad gamepad = game.GetGamePad();
		switch (gamepad.buttons)
		{
			case GamePad::A:
				game.inputKeyA();
				break;
			case GamePad::B:
				game.inputKeyS();
				break;
			case GamePad::Y:
				break;
			default:
				break;
		}
		game.update();
		fps->GetFPS();//FPS�𓾂�
		if (fps->draw) {//�b��60�t���[���̃^�C�~���O�ŕ`��
			game.update60();

		}
		glfwSwapBuffers(window);
	}


	return 0;
}
