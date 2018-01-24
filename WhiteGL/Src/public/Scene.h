#pragma once
//シーンの親となるクラス
class CScene
{
protected:

	float cameraMoveX = 0.0f;
	float cameraPosX = 0.0f;
public:
	CScene() { init(); };
	

	//デストラクタ
	virtual ~CScene() {};
	//初期化処理
	virtual bool init() {return true; };
	//更新処理
	virtual void update() {};
};
