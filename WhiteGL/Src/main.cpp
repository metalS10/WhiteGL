/**
*	main.cpp
*		2017/09/29	Mats
*/
#include "MSlib.h"
#include "PlayerFactory.h"
#include "FPS.h"
#include "LaunchTrigger.h"


using namespace MS;
float cameraMoveX = 0.0f;
float cameraPosX = 0.0f;
bool movingstage = false;

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
*	@desc	チェックと取り外し処理 ( 単体 )
*	@tips	有効フラグが false のインスタンスをレイヤーから取り外す
*/
template <typename Ty>
void checkAndRemove(Ty* pChara) {

	if (pChara->m_activeFlag == false) {
		pChara->removeFromParent();
	}
}

/**
*	@desc	チェックと取り外し処理 ( 複数 )
*	@tips	有効フラグが false のインスタンスをレイヤーと std::vector から取り外す
*/
template <typename Ty>
void checkAndRemove(std::vector<Ty*>* pCharas) {

	// ローカル変数の型のテンプレート引数の指定として
	// テンプレート引数を指定する場合は typename 指定をつけなければならない
	typename std::vector<Ty*>::iterator itr = pCharas->begin();
	while (itr != pCharas->end()) {

		if ((*itr)->m_activeFlag == false)
		{

			(*itr)->removeFromParent();
			itr = pCharas->erase(itr);

		}
		else
		{
			itr++;
		}
	}
}

/**
*@desc	チェックと解放
*@tips	有効フラグがfalseのインスタンスを開放しstd::vectorから取り外す
*/
template<typename Ty>
void checkAndDelete(std::vector<Ty*>*pVector)
{
	//ローカル変数の方のテンプレート引数の指定として
	//テンプレート引数を指定する場合はtypename指定をつけなければならない
	typename std::vector<Ty*>::iterator itr = pVector->begin();
	while (itr != pVector->end())
	{
		if ((*itr)->m_activeFlag == false)
		{
			SAFE_DELETE((*itr));
			itr = pVector->erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void openMap(std::string mapData ,std::vector<CCharacter*>* charasters)
{
	CGameEngine& game = CMS::getInstance()->getGame();

	for (CCharacter* pChara : (*charasters))
	{
		if (pChara->m_tag != TAG_PLAYER_1)
		{
			pChara->m_activeFlag = false;
		}
	}

	game.allTextureDeletenotPlayer();
	
	CMapManager::getInstance()->setMap(mapData);

}

/*
*@desc	画面スクロール
*@tips	今回は強制スクロールではなくキャラクターの移動による画面のスクロールとなる
*/
void scroll()
{
	CMap* map = CMapManager::getInstance()->getMap();

	//マップの位置を取得
	CVec2 pt = map->getp();

	//プレイヤーキャラクターの取得
	CCharacter* pPlayerChara = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);

	//プレイヤーの位置が前の値を超えたら
	if (pt.x > WINDOW_RIGHT*0.7f - pPlayerChara->m_pMove->m_pos.x)
	{
		//原点位置を超えた分に設定する
		pt.x = WINDOW_RIGHT*0.7f - pPlayerChara->m_pMove->m_pos.x;

		//超えた分を設定する
		map->setp(pt);

		cameraMoveX = pPlayerChara->m_pMove->m_vel.x;

		//スクロールが行われたときに敵の出撃判定を行う
		map->checkEnemyLaunch(pt.x, pt.y);

		//ギミックの出撃判定も行う
		map->checkGimmickLaunch(pt.x, pt.y);

	}
	//プレイヤーの位置が後ろの値超えたら
	else if (pt.x < WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x)
	{
		//原点位置を超えた分に設定する
		pt.x = WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x;

		//超えた分を設定する
		map->setp(pt);

		cameraMoveX = pPlayerChara->m_pMove->m_vel.x;




	}
	else
	{
		cameraMoveX = 0.0f;
		
	}
	cameraPosX += cameraMoveX;
	gluLookAt(
		cameraMoveX, 0.0f, 0.0f,
		cameraMoveX, 0.0f, -10.0f,
		0.0f, 1.0f, 0.0f
	);
}


/**
*	@file main.cpp
*/
//エントリーポイント
int main()
{
	glfwSetErrorCallback(ErrorCallback);
	
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

	
	CGameEngine& game = CMS::getInstance()->getGame();
	GLFWwindow* window = CMS::getInstance()->getWindow();
	//出撃スケジュールの生成
	std::vector<CLaunchTrigger*>* m_pLaunchSchedule = new std::vector<CLaunchTrigger*>();

	//これで削除していないとステージを二度遊んだ時にバグが出る(最強の敵)
	//CLaunchScheduler::getInstance()->removeInstance();

	//出撃スケジュールを出撃スケジューラーに取り付ける
	CLaunchScheduler::getInstance()->createLauncher(m_pLaunchSchedule);

	//キャラクターの集まりの生成
	std::vector<CCharacter*>* m_pCharacters = new std::vector<CCharacter*>();
	CCharacterAggregate::getInstance()->set(m_pCharacters);
	if (window == NULL)
		return false;

	//画像描画テスト
	/*
	game.setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 0, CVec2(100.0f, 100.0f), CVec4(0.0f, 0.0f, 200.0f, 200.0f));

	game.setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 1, CVec2(300.0f, 100.0f), CVec4(100.0f, 100.0f, 100.0f, 100.0f));

	game.setupTexture(PASS"player.bmp", TEX_TYPE::BMP, 2, CVec2(400.0f, 100.0f), CVec4(0.0f, 128.0f, 64.0f, 64.0f));

	game.setupTexture(PASS"kuribo.png", TEX_TYPE::PNG, 3, CVec2(32.0f, 232.0f), CVec4(0.0f, 0.0f, 64.0f, 64.0f));

	game.setupTexture(PASS"player.png", TEX_TYPE::PNG, 4, CVec2(200.0f, 232.0f), CVec4(0.0f, 0.0f, 64.0f, 64.0f));
	*/


	CPlayerCharacter* pPlayerChara = (CPlayerCharacter*)CPlayerFactoryManager::getInstance()->create(320.0f, 200.0f);

	//プレイヤー1のタグを設定
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregateにプレイヤーを追加
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	game.setupTexture(pPlayerChara->texPass, TEX_TYPE::PNG, pPlayerChara->m_texID, pPlayerChara->m_pMove->m_pos, (*pPlayerChara->m_pAnimations)[0]->getCurrentChip());

	game.setupTexture("", TEX_TYPE::QUAD, MAX_TEXTURE_NUMBER-1, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH,  WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 0.0f));


	
	
	
	CMapManager::getInstance()->setMap(MAP_DATA_1);


	//アニメーションテスト
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

	Input::CGameInput* input = new Input::CGameInput();

	pPlayerChara->input = input;



	/**
	*memo
	*メインループ
	*毎フレーム実行される
	*glfwWindowShouldCloseはウィンドウを閉じるべきかどうかを調べる関数
	*	引数で渡されたウィンドウに対してOS等から終了要求が来ていなければ0,着ていれば0以外を返す
	*GLFWで作成したウィンドウが1つだけなら終了判定はこの関数を見るだけで十分
	*/
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		FwewWindow.UpdateGamePad();
		const GamePad gamepad = game.GetGamePad();
		
		

		game.update();
		fps->GetFPS();//FPSを得る
		if (fps->draw) {//秒間60フレーム
			game.update60();

			
			

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
			if (pPlayerChara->m_nextStage)
			{
				//openMap(MAP_DATA_2, m_pCharacters);
				if (!movingstage)
				{
					if (game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, false) == true)
					{
						movingstage = true;
						openMap(MAP_DATA_2, m_pCharacters);
						gluLookAt(
							-cameraPosX, 0.0f, 0.0f,
							-cameraPosX, 0.0f, -10.0f,
							0.0f, 1.0f, 0.0f
						);
						cameraPosX = 0.0f;
						pPlayerChara->setPosition(CVec2(320.0f, 200.0f), PLAYER_ID);
					}
				}
				if (movingstage == true)
				{
					if (game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true))
					{
						movingstage = false;
						pPlayerChara->m_nextStage = false;
					}
				}
			}
			CLaunchScheduler::getInstance()->launchCharacters(game);
			

			//出撃の完了したトリガーをすべて取り外す
			checkAndDelete(m_pLaunchSchedule);
			checkAndRemove(m_pCharacters);
			for (CCharacter* pChara : (*m_pCharacters))
			{
				pChara->update();
				game.setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip(), pChara->m_texID);
				game.setScale(pChara->m_scale, pChara->m_texID);
				game.setPosition(pChara->m_pMove->m_pos, pChara->m_texID);
			}
			game.setPosition(CVec2(WINDOW_RIGHT * 0.5 + cameraPosX,WINDOW_TOP * 0.5), MAX_TEXTURE_NUMBER - 1);

			
			scroll();
		}


		glfwSwapBuffers(window);
	}


	return 0;
}



