#pragma once

//============================================
//追加のインクルードはここから
//============================================
#include "Constants.h"
#include "Collision.h"
#include <vector>

//============================================
//前方宣言
//============================================
class CCharacter;

//============================================
//領域タイプ
//============================================
enum class TERRITORY_TYPE : int
{
	LEFT,
	TOP,
	RIGHT,
	BOTTOM
};

//============================================
//衝突基準点
//============================================
class CCollisionBasePoint
{
public:
	//領域タイプ
	TERRITORY_TYPE m_type;
	//基準点
	CVec2 m_pt;

	//コンストラクタ
	CCollisionBasePoint(TERRITORY_TYPE type, CVec2 pt)
		:m_type(type), m_pt(pt){}
};

//============================================
//衝突判定領域
//============================================
class CCollisionTerritory
{
public:
	//イベントコールバック
	//void(CCHaracter::*型名)(int event)のtypedef
	//typedefをクラス内に記述することで
	//クラスにだけ有効なtypedefとなる
	typedef void (CCharacter::*EventCallback)(int event);

protected:
	//イベントコールバック
	EventCallback m_pEventCallback = NULL;

public:
	/**
	*@desc	イベントコールバックの設定
	*@param	設定するイベントコールバック
	*@tips	領域を生成し、生成した領域に
	*		イベントコールバック(メンバ関数ポインタ)を設定することで
	*		その領域のイベントが発生したときに
	*		登録したメンバ関数ポインタが呼び出される
	*/
	void setEventCallback(EventCallback pEventCallback)
	{
		this->m_pEventCallback = pEventCallback;
	}

	/**
	*@desc	イベントコールバックの呼び出し
	*@param	呼び出すインスタンス
	*@param	イベント
	*		マップチップの際はマップチップIDをイベントとして渡すが
	*		画面端などはイベントは存在していないので
	*		デフォルト値として0を設定しておく
	*@tips	領域のイベントの発生時にこのメンバ関数を呼び出すことで
	*		登録したメンバ関数ポインタが呼び出される
	*/
	void callEventCallback(CCharacter* pChara, int event = 0);

public:
	//デストラクタ
	virtual ~CCollisionTerritory(){}

	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt) = 0;

	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara,CCharacter* pSelf, CVec2 basePt) = 0;

public:
	//領域タイプ
	TERRITORY_TYPE m_type;

	//コンストラクタ
	CCollisionTerritory(TERRITORY_TYPE type) : m_type(type){}
};


//============================================
//下にある画面端領域との衝突判定
//============================================
class CCollisionTerritoryEndOfScreenBottom : public CCollisionTerritory
{
public:
	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;

	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara,CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	コンストラクタ
	*		領域タイプの設定を初期化子で TERRITORY_TYPE::BOTTOMに
	*		設定しておく
	*/
	CCollisionTerritoryEndOfScreenBottom():CCollisionTerritory(TERRITORY_TYPE::BOTTOM){}
};

//============================================
//左にある画面端領域との衝突判定
//============================================
class CCollisionTerritoryEndOfScreenLeft : public CCollisionTerritory
{
public:
	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;

	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	コンストラクタ
	*		領域タイプの設定を初期化子で TERRITORY_TYPE::BOTTOMに
	*		設定しておく
	*/
	CCollisionTerritoryEndOfScreenLeft() :CCollisionTerritory(TERRITORY_TYPE::LEFT) {}
};


//============================================
//下にいるキャラクターとの衝突判定
//============================================
class CCollisionTerritoryCharacterBottom : public CCollisionTerritory
{
public:
	/**
	*@desc	コンストラクタ
	*		領域タイプの設定を初期化子で TERRITORY_TYPE::BOTTOMに
	*		設定しておく
	*/
	CCollisionTerritoryCharacterBottom() : CCollisionTerritory(TERRITORY_TYPE::BOTTOM) {}


	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt) override {}

	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt)override;
};

//============================================
//左にいるキャラクターとの衝突判定
//============================================
class CCollisionTerritoryCharacterLeft : public CCollisionTerritory
{
public:
	/**
	*@desc	コンストラクタ
	*		領域タイプの設定を初期化子で TERRITORY_TYPE::LEFTに
	*		設定しておく
	*/
	CCollisionTerritoryCharacterLeft() : CCollisionTerritory(TERRITORY_TYPE::LEFT) {}


	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt) override {}

	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt)override;
};


//============================================
//上にいるキャラクターとの衝突判定
//============================================
class CCollisionTerritoryCharacterTop : public CCollisionTerritory
{
public:
	/**
	*@desc	コンストラクタ
	*		領域タイプの設定を初期化子で TERRITORY_TYPE::LEFTに
	*		設定しておく
	*/
	CCollisionTerritoryCharacterTop() : CCollisionTerritory(TERRITORY_TYPE::TOP) {}


	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override{}

	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override;
};

//============================================
//右にいるキャラクターとの衝突判定
//============================================
class CCollisionTerritoryCharacterRight : public CCollisionTerritory
{
public:
	/**
	*@desc	コンストラクタ
	*		領域タイプの設定を初期化子で TERRITORY_TYPE::LEFTに
	*		設定しておく
	*/
	CCollisionTerritoryCharacterRight() : CCollisionTerritory(TERRITORY_TYPE::RIGHT) {}


	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override{}

	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override;
};




//============================================
//衝突判定空間
//============================================
class CCollisionArea
{
protected:
	//衝突基準点群
	std::vector<CCollisionBasePoint*>* m_pBasePoints = NULL;

	//衝突判定領域群
	std::vector<CCollisionTerritory*>* m_pTerritories = NULL;
public:
	//コンストラクタ
	CCollisionArea()
	{
		//衝突基準点群の生成
		this->m_pBasePoints = new std::vector<CCollisionBasePoint*>();

		//衝突判定領域群の生成
		this->m_pTerritories = new std::vector<CCollisionTerritory*>();
	}

	//デストラクタ
	virtual ~CCollisionArea()
	{
		//衝突判定領域の解放
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			SAFE_DELETE(pBasePt);
		}
		SAFE_DELETE(this->m_pBasePoints);

		//衝突判定領域の解放
		for (CCollisionTerritory* pTerritory : (*this->m_pTerritories))
		{
			SAFE_DELETE(pTerritory);
		}
		SAFE_DELETE(this->m_pTerritories);
	}


	virtual void addBasePoint(CCollisionBasePoint* pBasePoint)
	{
		this->m_pBasePoints->push_back(pBasePoint);
	}

	/**
	*@desc	衝突判定領域の追加
	*@param	衝突判定領域
	*/
	virtual void addTerritory(CCollisionTerritory* pTerritory)
	{
		this->m_pTerritories->push_back(pTerritory);
	}

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクター
	*@tips	毎フレーム呼び出す
	*/
	virtual void collision(CCharacter* pChara) = 0;

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクター
	*@param	衝突された自分
	*@tips	毎フレーム呼び出す
	*/
	virtual void collision(CCharacter* pChara,CCharacter* pSelf) = 0;
};

//===========================================
//画面端との衝突判定空間
//===========================================
class CCollisionAreaEndOfScreen : public CCollisionArea
{
public:
	//デフォルト
	CCollisionAreaEndOfScreen(){}

	//引数付きコンストラクタ
	CCollisionAreaEndOfScreen(CBody* pBody)
	{
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(0.0f,pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(0.0f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right,0.0f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left,0.0f)));
	}
	//デストラクタ
	~CCollisionAreaEndOfScreen(){}

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクター
	*/
	void collision(CCharacter* pChara);

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクター
	*@param	衝突された自分
	*/
	void collision(CCharacter* pChara,CCharacter* pSelf) override {}

};

//============================================
//画面上にあるすべてのマップチップとの衝突判定空間
//つまりマップとの衝突判定空間
//============================================
class CCollisionAreaMap : public CCollisionArea
{
public:

	//デフォルト
	CCollisionAreaMap() {}
	//引数つきコンストラクタ
	CCollisionAreaMap(CBody* pBody)
	{
		//マップチップと当たるプレイヤーの当たる基準点
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(pBody->m_left*0.5f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(pBody->m_right*0.5f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(pBody->m_left*0.5f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(pBody->m_right*0.5f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right, pBody->m_top*0.5f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right, pBody->m_bottom*0.5f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left, pBody->m_top*0.5f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left, pBody->m_bottom*0.5f)));
	}
	//デストラクタ
	~CCollisionAreaMap(){}

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクタ―
	*/
	void collision(CCharacter* pChara);

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクター
	*@param	衝突された自分
	*/
	void collision(CCharacter* pChara,CCharacter* pSelf) override {}
};



//============================================
//下にある画面端領域との衝突判定
//============================================
class CCollisionTerritoryOutOfScreenBottom : public CCollisionTerritory
{
public:
	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;

	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	コンストラクタ
	*		領域タイプの設定を初期化子で TERRITORY_TYPE::BOTTOMに
	*		設定しておく
	*/
	CCollisionTerritoryOutOfScreenBottom() :CCollisionTerritory(TERRITORY_TYPE::BOTTOM) {}
};

//============================================
//上にある画面端領域との衝突判定
//============================================
class CCollisionTerritoryOutOfScreenTop : public CCollisionTerritory
{
public:
	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;


	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	コンストラクタ
	*		設定しておく
	*/
	CCollisionTerritoryOutOfScreenTop() :CCollisionTerritory(TERRITORY_TYPE::TOP) {}
};

//============================================
//左にある画面端領域との衝突判定
//============================================
class CCollisionTerritoryOutOfScreenLeft : public CCollisionTerritory
{
public:
	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;


	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	コンストラクタ
	*		設定しておく
	*/
	CCollisionTerritoryOutOfScreenLeft() :CCollisionTerritory(TERRITORY_TYPE::LEFT) {}
};

//============================================
//右にある画面端領域との衝突判定
//============================================
class CCollisionTerritoryOutOfScreenRight : public CCollisionTerritory
{
public:
	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;


	/**
	*@desc	衝突判定
	*@param	衝突対象
	*@param	衝突された自分
	*@param	基準点
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	コンストラクタ
	*		設定しておく
	*/
	CCollisionTerritoryOutOfScreenRight() :CCollisionTerritory(TERRITORY_TYPE::RIGHT) {}
};

class CCollisionAreaOutOfScreen : public CCollisionArea
{
public:
	//デフォルト
	CCollisionAreaOutOfScreen() {}

	//引数付きコンストラクタ
	CCollisionAreaOutOfScreen(CBody* pBody)
	{
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(0.0f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(0.0f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right, 0.0f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left, 0.0f)));
	}
	//デストラクタ
	~CCollisionAreaOutOfScreen() {}

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクター
	*/
	void collision(CCharacter* pChara);

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクター
	*@param	衝突された自分
	*/
	void collision(CCharacter* pChara,CCharacter* pSelf) override {}
};


//============================================
//キャラクターとの衝突判定空間
//============================================
class CCollisionAreaCharacter : public CCollisionArea
{
public:

	//デフォルト
	CCollisionAreaCharacter() {}
	//引数つきコンストラクタ
	CCollisionAreaCharacter(CBody* pBody)
	{
		//マップチップと当たるプレイヤーの当たる基準点
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(pBody->m_left*0.5f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(pBody->m_right*0.5f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(pBody->m_left*0.25f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(pBody->m_right*0.25f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(pBody->m_left*0.5f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(pBody->m_right*0.5f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right, pBody->m_top*0.5f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right, pBody->m_bottom*0.5f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left, pBody->m_top*0.5f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left, pBody->m_bottom*0.5f)));
	}
	//デストラクタ
	~CCollisionAreaCharacter() {}

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクタ―
	*/
	void collision(CCharacter* pChara) override {}

	/**
	*@desc	衝突判定
	*@param	衝突対象のキャラクター
	*@param	衝突された自分
	*/
	void collision(CCharacter* pChara, CCharacter* pSelf) override;
};
