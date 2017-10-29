/**
*	main.cpp
*		2017/09/29	Mats
*/
#include "GameEngine.h"
#include "Character.h"
#include "PlayerFactory.h"
#include "FPS.h"
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
/**
*	@file main.cpp
*/
//エントリーポイント
int main()
{
	glfwSetErrorCallback(ErrorCallback);


	CGameEngine& game = CGameEngine();
	

	/*
	// モニタとの同期
	glfwSwapInterval(1);

	// 描画範囲の指定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, g_windowWidth, 0.0f, g_windowHeight, -1.0f, 1.0f);

	//テクスチャのロード
	glGenTextures(1, &g_texID);
	setupTexture(g_texID, PASS"Sparrow.bmp", 200, 200);
	*/
	// モニタとの同期
	//glfwSwapInterval(1);

	// 描画範囲の指定
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	std::vector<CCharacter*>* m_pCharacters = NULL;
	//キャラクターの集まりの生成
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

	//プレイヤー1のタグを設定
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregateにプレイヤーを追加
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	game.setupTexture(pPlayerChara->texPass, TEX_TYPE::PNG, 5, pPlayerChara->m_pMove->m_pos, (*pPlayerChara->m_pAnimations)[1]->getCurrentChip());

	game.setupTexture("", TEX_TYPE::QUAD, MAX_TEXTURE_NUMBER-1, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH,  WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 0.0f));


	



	
	game.setChipAnim(new CNotAnimation());
	game.setChipAnim(new CNotAnimation());
	game.setChipAnim(new CListAnimation(10,true));
	game.setChipAnim(new CNotAnimation());
	game.setChipAnim(new CListAnimation(20,true));	

	game.setChipData(0,CVec4(0.0f, 200.0f, 0.0f, 200.0f));
	game.setChipData(1,CVec4(100.0f, 200.0f, 100.0f, 200.0f));
	game.setChipData(2,CVec4(0.0f, 64.0f, 128.0f, 192.0f));
	game.setChipData(2, CVec4(64.0f, 128.0f, 128.0f, 192.0f));
	game.setChipData(2, CVec4(128.0f, 192.0f, 128.0f, 192.0f));
	game.setChipData(2, CVec4(192.0f, 256.0f, 128.0f, 192.0f));
	game.setChipData(3,CVec4(0.0f, 64.0f, 0.0f, 64.0f));

	game.setChipData(4, CVec4(0.0f, 64.0f, 0.0f, 64.0f));
	game.setChipData(4, CVec4(64.0f, 128.0f, 0.0f, 64.0f));
	game.setChipData(4, CVec4(128.0f, 192.0f, 0.0f, 64.0f));
	game.setChipData(4, CVec4(192.0f, 256.0f, 0.0f, 64.0f));



	FPS* fps = new FPS(60);

	GLFWEW::Window& FwewWindow = GLFWEW::Window::Instance();

	

	/**
	*memo
	*メインループ
	*毎フレーム実行される
	*glfwWindowShouldCloseはウィンドウを閉じるべきかどうかを調べる関数
	*	引数で渡されたウィンドウに対してOS等から終了要求が来ていなければ0,着ていれば0以外を返す
	*GLFWで作成したウィンドウが1つだけなら終了判定はこの関数を見るだけで十分
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
		fps->GetFPS();//FPSを得る
		if (fps->draw) {//秒間60フレーム
			game.update60();
			CVec2 vel = {};
			if (gamepad.buttons & GamePad::DPAD_RIGHT)
			{
				vel.x = 5;
			}
			else if (gamepad.buttons & GamePad::DPAD_LEFT)
			{
				vel.x = -5;
			}
			if (gamepad.buttons & GamePad::DPAD_UP)
			{
				vel.y = 5;
			}
			else if (gamepad.buttons & GamePad::DPAD_DOWN)
			{
				vel.y = -5;
			}
			if (gamepad.buttons & GamePad::GameEnd)
			{
				return 0;
			}
			game.setVelocity(vel);
			(*m_pCharacters)[0]->update();
		}
		glfwSwapBuffers(window);
	}


	return 0;
}
