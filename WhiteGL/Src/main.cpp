/**
*	main.cpp
*		2017/09/29	Mats
*/
#include "MSlib.h"
#include "PlayerFactory.h"
#include "FPS.h"
#include "LaunchTrigger.h"
#include "TitleScene.h"

using namespace MS;
CScene* scene;

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
int main(int argc, char *argv[])
{
	glfwSetErrorCallback(ErrorCallback);
	
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

	
	CGameEngine& game = CMS::getInstance()->getGame();
	GLFWwindow* window = CMS::getInstance()->getWindow();
	
	if (window == NULL)
		return false;

	//�摜�`��e�X�g
	/*
	game.setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 0, CVec2(100.0f, 100.0f), CVec4(0.0f, 0.0f, 200.0f, 200.0f));

	game.setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 1, CVec2(300.0f, 100.0f), CVec4(100.0f, 100.0f, 100.0f, 100.0f));

	game.setupTexture(PASS"player.bmp", TEX_TYPE::BMP, 2, CVec2(400.0f, 100.0f), CVec4(0.0f, 128.0f, 64.0f, 64.0f));

	game.setupTexture(PASS"kuribo.png", TEX_TYPE::PNG, 3, CVec2(32.0f, 232.0f), CVec4(0.0f, 0.0f, 64.0f, 64.0f));

	game.setupTexture(PASS"player.png", TEX_TYPE::PNG, 4, CVec2(200.0f, 232.0f), CVec4(0.0f, 0.0f, 64.0f, 64.0f));
	*/
	//�u���b�N�{�[�h
	game.setupTexture("", TEX_TYPE::QUAD, MAX_TEXTURE_NUMBER-1, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH,  WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 0.0f));

	

	//�A�j���[�V�����e�X�g
	/*
	game.setChipAnim(new CChipNotAnimation());
	game.setChipAnim(new CChipNotAnimation());
	game.setChipAnim(new CChipListAnimation(10,true));
	game.setChipAnim(new CChipNotAnimation());
	game.setChipAnim(new CChipListAnimation(20,true));

	game.setChipData(0,CVec4(0.0f, 0.0f, 200.0f, 200.0f));
	game.setChipData(1,CVec4(100.0f, 100.0f, 100.0f, 100.0f));

	game.setChipData(2, CVec4(0.0f, 128.0f, 64.0f, 64.0f));
	game.setChipData(2, CVec4(64.0f, 128.0f, 64.0f, 64.0f));
	game.setChipData(2, CVec4(128.0f, 128.0f, 64.0f, 64.0f));
	game.setChipData(2, CVec4(192.0f, 128.0f, 64.0f, 64.0f));

	game.setChipData(3,CVec4(0.0f, 0.0f, 64.0f, 64.0f));

	game.setChipData(4, CVec4(0.0f, 0.0f, 64.0f, 64.0f));
	game.setChipData(4, CVec4(64.0f, 0.0f, 64.0f, 64.0f));
	game.setChipData(4, CVec4(128.0f, 0.0f, 64.0f, 64.0f));
	game.setChipData(4, CVec4(192.0f, 0.0f, 64.0f, 64.0f));
	*/
	FPS* fps = new FPS(60);

	GLFWEW::Window& FwewWindow = GLFWEW::Window::Instance();



	//�Q�[�����C���V�[���𐶐�
	CMS::getInstance()->setScene(new CTitle());
	//���݂̃V�[���ɔ��f
	scene = CMS::getInstance()->getScene();

	Input::CGameInput* input = MS::CMS::getInstance()->getInput();


	/**
	*memo
	*���C�����[�v
	*���t���[�����s�����
	*glfwWindowShouldClose�̓E�B���h�E�����ׂ����ǂ����𒲂ׂ�֐�
	*	�����œn���ꂽ�E�B���h�E�ɑ΂���OS������I���v�������Ă��Ȃ����0,���Ă����0�ȊO��Ԃ�
	*GLFW�ō쐬�����E�B���h�E��1�����Ȃ�I������͂��̊֐������邾���ŏ\��
	*/
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		if (scene != CMS::getInstance()->getScene())
		{
			SAFE_DELETE(scene);
			scene = CMS::getInstance()->getScene();
		}

		FwewWindow.UpdateGamePad();
		
		//input
		const GamePad gamepad = game.GetGamePad();
		if (gamepad.buttons & GamePad::DPAD_RIGHT)
		{
			input->setOnKey(Input::Key::DPAD_LEFT, false);
			input->setOnKey(Input::Key::DPAD_RIGHT, true);
			//pPlayerChara->m_pMove->m_accele.x = 0.7f;
		}
		else if (gamepad.buttons & GamePad::DPAD_LEFT)
		{
			input->setOnKey(Input::Key::DPAD_RIGHT, false);
			input->setOnKey(Input::Key::DPAD_LEFT, true);
		}
		else
		{
			input->setOnKey(Input::Key::DPAD_RIGHT, false);
			input->setOnKey(Input::Key::DPAD_LEFT, false);
		}
		if (gamepad.buttons & GamePad::DPAD_UP)
		{
			input->setOnKey(Input::Key::DPAD_UP, true);
			input->setOnKey(Input::Key::DPAD_DOWN, false);

		}
		else if (gamepad.buttons & GamePad::DPAD_DOWN)
		{
			input->setOnKey(Input::Key::DPAD_UP, false);
			input->setOnKey(Input::Key::DPAD_DOWN, true);

		}
		else
		{
			input->setOnKey(Input::Key::DPAD_UP, false);
			input->setOnKey(Input::Key::DPAD_DOWN, false);

		}
		if (gamepad.buttons & GamePad::L_SHIFT)
		{
			input->setOnKey(Input::Key::L_SHIFT, true);
		}
		else
		{
			input->setOnKey(Input::Key::L_SHIFT, false);
		}
		if (gamepad.buttons & GamePad::START)
		{
			input->setOnKey(Input::Key::START, true);
		}
		else
		{
			input->setOnKey(Input::Key::START, false);
		}

		if (gamepad.buttons & GamePad::GameEnd)
		{
			input->setOnKey(Input::Key::GameEnd, true);
		}
		if (gamepad.buttons & GamePad::Z)
		{
			input->setOnKey(Input::Key::Z, true);
		}
		else
		{
			input->setOnKey(Input::Key::Z, false);
		}

		if (gamepad.buttons & GamePad::X)
		{
			input->setOnKey(Input::Key::X, true);
		}
		else
		{
			input->setOnKey(Input::Key::X, false);
		}
		//�`��pUpdate
		scene->rendUpdate();
		


		game.update();
		fps->GetFPS();//FPS�𓾂�
		if (fps->draw) {//�b��60�t���[��
			game.update60();
			scene->sceneUpdate();

			if (game.m_hitStop == 0)
			{
				//�V�[���̍X�V
				scene->update();
			}
		}
		


		glfwSwapBuffers(window);
	}



	SAFE_DELETE(fps);
	SAFE_DELETE(scene);
	return 0;
}


