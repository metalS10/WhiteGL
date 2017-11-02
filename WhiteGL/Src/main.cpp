/**
*	main.cpp
*		2017/09/29	Mats
*/
#include "GameEngine.h"
#include "PlayerFactory.h"
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

	std::vector<CCharacter*>* m_pCharacters = NULL;
	//�L�����N�^�[�̏W�܂�̐���
	m_pCharacters = new std::vector<CCharacter*>();
	CCharacterAggregate::getInstance()->set(m_pCharacters);

	GLFWwindow* window = game.init(WINDOW_SIZE,"WhiteV_GL");
	if (window == NULL)
		return false;
	game.setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 0, CVec2(100.0f, 100.0f), CVec4(0.0f, 0.0f, 200.0f, 200.0f));

	game.setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 1, CVec2(300.0f, 100.0f), CVec4(100.0f, 100.0f, 100.0f, 100.0f));

	game.setupTexture(PASS"player.bmp", TEX_TYPE::BMP, 2, CVec2(400.0f, 100.0f), CVec4(0.0f, 128.0f, 64.0f, 64.0f));

	game.setupTexture(PASS"kuribo.png", TEX_TYPE::PNG, 3, CVec2(32.0f, 232.0f), CVec4(0.0f, 0.0f, 64.0f, 64.0f));

	game.setupTexture(PASS"player.png", TEX_TYPE::PNG, 4, CVec2(200.0f, 232.0f), CVec4(0.0f, 0.0f, 64.0f, 64.0f));



	CPlayerCharacter* pPlayerChara = (CPlayerCharacter*)CPlayerFactoryManager::getInstance()->create(320.0f, 200.0f);

	//�v���C���[1�̃^�O��ݒ�
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregate�Ƀv���C���[��ǉ�
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	game.setupTexture(pPlayerChara->texPass, TEX_TYPE::PNG, 5, pPlayerChara->m_pMove->m_pos, (*pPlayerChara->m_pAnimations)[1]->getCurrentChip());

	game.setupTexture("", TEX_TYPE::QUAD, MAX_TEXTURE_NUMBER-1, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH,  WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 0.0f));


	
	


	
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

	int i = m_pCharacters->size();
	std::cerr << i << std::endl;


	FPS* fps = new FPS(60);

	GLFWEW::Window& FwewWindow = GLFWEW::Window::Instance();

	Input::CGameInput* input = new Input::CGameInput();

	pPlayerChara->input = input;

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
		FwewWindow.UpdateGamePad();
		const GamePad gamepad = game.GetGamePad();
		switch (gamepad.buttonDown)
		{
			case GamePad::A:
				game.inputKeyA();
				break;
			case GamePad::B:
				game.inputKeyS();
				break;
			case GamePad::X:
				game.inputKeyX();
				break;
			case GamePad::Z:
				game.inputKeyZ();
				break;
			
			default:
				break;
		}

		game.update();
		fps->GetFPS();//FPS�𓾂�
		if (fps->draw) {//�b��60�t���[��
			game.update60();
			pPlayerChara->m_pMove->m_accele.y = 0;
			if (gamepad.buttons & GamePad::DPAD_RIGHT)
			{
				input->setOnKey(Input::Key::DPAD_LEFT, false);
				input->setOnKey(Input::Key::DPAD_RIGHT,true);
				//pPlayerChara->m_pMove->m_accele.x = 0.7f;
			}
			else if (gamepad.buttons & GamePad::DPAD_LEFT)
			{
				input->setOnKey(Input::Key::DPAD_RIGHT, false);
				input->setOnKey(Input::Key::DPAD_LEFT, true);
				//pPlayerChara->m_pMove->m_accele.x = -0.7f;
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

				//pPlayerChara->m_pMove->m_accele.y = 1;
			}
			else if (gamepad.buttons & GamePad::DPAD_DOWN)
			{
				input->setOnKey(Input::Key::DPAD_UP, false);
				input->setOnKey(Input::Key::DPAD_DOWN, true);

				//pPlayerChara->m_pMove->m_accele.y = -1;
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
			if (gamepad.buttons & GamePad::SPACE)
			{
				input->setOnKey(Input::Key::SPACE, true);
			}
			else
			{
				input->setOnKey(Input::Key::SPACE, false);
			}

			if (gamepad.buttons & GamePad::GameEnd)
			{
				input->setOnKey(Input::Key::GameEnd, true);
				return 0;
			}
			for (CCharacter* pChara: (*m_pCharacters))
			{
				pChara->update();
				game.setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
				game.setScale(pChara->m_scale,pChara->m_texID);
				game.setPosition(pChara->m_pMove->m_pos, pChara->m_texID);

			}

		}
		glfwSwapBuffers(window);
	}


	return 0;
}
