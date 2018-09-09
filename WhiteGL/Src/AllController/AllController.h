#pragma once
#include "../GameEngine/GameEngine.h"
#include "../gameInput.h"

enum class ID_TYPE : int
{
	ENEMY	=	0,
	ATTACK	=	1,
	ENEMY_ATTACK	=	2,
	GIMMICK	=	3,
	NOTES	=	4,
};

class CScene;
namespace MS
{
	class CMS
	{
	private:
		CMS();

		~CMS();

		CGameEngine& game = CGameEngine();

		GLFWwindow* window = game.init(WINDOW_SIZE, "WhiteBeats");

		static CMS* m_pSharedMS;

		int TexID[(int)ID_TYPE::NOTES + 1] = {START_ENEMY_TEXTURE_NUMBER,START_BULLET_TEXTURE_NUMBER,START_ENEMY_BULLET_TEXTURE_NUMBER,START_GIMMICK_TEXTURE_NUMBER,START_NOTES_TEXTURE_NUMBER };

		Input::CGameInput* input = new Input::CGameInput();
		//Input::CGameInput* input;
		CScene* m_pScene;
	public:

		//共有インスタンスの取得
		static CMS* getInstance();

		//共有インスタンスの破棄
		static void removeInstance();

		CGameEngine& getGame();
		GLFWwindow* getWindow();

		Input::CGameInput* getInput();

		void setTexID(int id ,int idType);
		int getTexID(int idType);

		void setScene(CScene* scene);
		CScene* getScene();
	};
}