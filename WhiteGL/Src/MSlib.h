#pragma once
#include "GameEngine.h"

namespace MS
{
	class CMS
	{
	private:
		CMS();

		~CMS();

		CGameEngine& game = CGameEngine();

		GLFWwindow* window = game.init(WINDOW_SIZE, "WhiteV_GL");

		static CMS* m_pSharedMS;

	public:

		//共有インスタンスの取得
		static CMS* getInstance();

		//共有インスタンスの破棄
		static void removeInstance();

		CGameEngine& getGame();
		GLFWwindow* getWindow();
	};
}