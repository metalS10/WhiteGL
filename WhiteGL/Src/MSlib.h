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

		//���L�C���X�^���X�̎擾
		static CMS* getInstance();

		//���L�C���X�^���X�̔j��
		static void removeInstance();

		CGameEngine& getGame();
		GLFWwindow* getWindow();
	};
}