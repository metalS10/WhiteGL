/**
*	main.cpp
*		2017/09/29	Mats
*/
#include "AllController/AllController.h"
#include "Factory/PlayerFactory/PlayerFactory.h"
#include "Data/FPS.h"
#include "Data/LaunchTrigger/LaunchTrigger.h"
#include "Scene/TitleScene/TitleScene.h"

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


//���͂����m����
void InputFunc(CGameEngine game,Input::CGameInput* input)
{
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
}


/**
*	@file main.cpp
*/
//�G���g���[�|�C���g
int main(int argc, char *argv[])
{
	glfwSetErrorCallback(ErrorCallback);
	

	
	CGameEngine& game = CMS::getInstance()->getGame();
	GLFWwindow* window = CMS::getInstance()->getWindow();
	
	if (window == NULL)
		return false;

	
	//�u���b�N�{�[�h
	game.setupTexture("", TEX_TYPE::QUAD, BLACKBORD_ID, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH,  WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 0.0f));

	

	
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
	while (!glfwWindowShouldClose(window) &&  game.gameNow == true)
	{
		if (scene != CMS::getInstance()->getScene())
		{
			SAFE_DELETE(scene);
			scene = CMS::getInstance()->getScene();
		}

		FwewWindow.UpdateGamePad();
		
		
		//�`��pUpdate
		scene->rendUpdate();
		
		//���͊��m
		InputFunc(game, input);

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


