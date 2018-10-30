/**
*	main.cpp
*		2017/09/29	Mats
*/
#include "GLFWEW/GLFWEW.h"
#include "AllController/AllController.h"
#include "Factory/PlayerFactory/PlayerFactory.h"
#include "Data/FPS.h"
#include "Data/LaunchTrigger/LaunchTrigger.h"
#include "Scene/TitleScene/TitleScene.h"
using namespace MS;
CScene* scene;

/**
*GLFWからのエラー報告を処理する
*
*@param	error	エラー番号
*@para,	desc	エラー内容
*/
void ErrorCallback(int error, const char* desc)
{
	std::cerr << "ERROR : " << desc << std::endl;
}


//入力を感知する
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
	else
	{
		input->setOnKey(Input::Key::GameEnd, false);
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
//エントリーポイント
int main(int argc, char *argv[])
{
	glfwSetErrorCallback(ErrorCallback);
	

	
	CGameEngine& game = CMS::getInstance()->getGame();
	GLFWwindow* window = CMS::getInstance()->getWindow();
	
	if (window == NULL)
		return false;

	
	FPS* fps = new FPS(60);

	GLFWEW::Window& FwewWindow = GLFWEW::Window::Instance();



	//シーンを生成
	CMS::getInstance()->setScene(new CTitle());

	//現在のシーンに反映
	scene = CMS::getInstance()->getScene();

	Input::CGameInput* input = MS::CMS::getInstance()->getInput();



	/**
	*memo
	*メインループ
	*毎フレーム実行される
	*glfwWindowShouldCloseはウィンドウを閉じるべきかどうかを調べる関数
	*	引数で渡されたウィンドウに対してOS等から終了要求が来ていなければ0,着ていれば0以外を返す
	*GLFWで作成したウィンドウが1つだけなら終了判定はこの関数を見るだけで十分
	*/
	while (!glfwWindowShouldClose(window) &&  game.gameNow == true)
	{
		if (scene != CMS::getInstance()->getScene())
		{
			SAFE_DELETE(scene);
			scene = CMS::getInstance()->getScene();
		}

		FwewWindow.UpdateGamePad();
		
		
		//描画用Update
		scene->rendUpdate();//
		
		//入力感知
		InputFunc(game, input);
		game.update();//


		fps->update();//FPSを得る
		if (fps->getDraw()) {//秒間60フレーム
			game.update60();
			scene->sceneUpdate();
			if (game.m_hitStop == 0)
			{
				//シーンの更新
				scene->update();
			}
		}


		glfwSwapBuffers(window);
	}

	
	SAFE_DELETE(fps);
	SAFE_DELETE(scene);

	// SDL_Mixerクローズ
	Mix_CloseAudio();			
	//SDLの使用終了
	SDL_Quit();	
	return 0;
}


