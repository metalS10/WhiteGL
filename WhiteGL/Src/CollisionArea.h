#pragma once

//============================================
//�ǉ��̃C���N���[�h�͂�������
//============================================
#include "Constants.h"
#include "Collision.h"
#include <vector>

//============================================
//�O���錾
//============================================
class CCharacter;

//============================================
//�̈�^�C�v
//============================================
enum class TERRITORY_TYPE : int
{
	LEFT,
	TOP,
	RIGHT,
	BOTTOM
};

//============================================
//�Փˊ�_
//============================================
class CCollisionBasePoint
{
public:
	//�̈�^�C�v
	TERRITORY_TYPE m_type;
	//��_
	CVec2 m_pt;

	//�R���X�g���N�^
	CCollisionBasePoint(TERRITORY_TYPE type, CVec2 pt)
		:m_type(type), m_pt(pt){}
};

//============================================
//�Փ˔���̈�
//============================================
class CCollisionTerritory
{
public:
	//�C�x���g�R�[���o�b�N
	//void(CCHaracter::*�^��)(int event)��typedef
	//typedef���N���X���ɋL�q���邱�Ƃ�
	//�N���X�ɂ����L����typedef�ƂȂ�
	typedef void (CCharacter::*EventCallback)(int event);

protected:
	//�C�x���g�R�[���o�b�N
	EventCallback m_pEventCallback = NULL;

public:
	/**
	*@desc	�C�x���g�R�[���o�b�N�̐ݒ�
	*@param	�ݒ肷��C�x���g�R�[���o�b�N
	*@tips	�̈�𐶐����A���������̈��
	*		�C�x���g�R�[���o�b�N(�����o�֐��|�C���^)��ݒ肷�邱�Ƃ�
	*		���̗̈�̃C�x���g�����������Ƃ���
	*		�o�^���������o�֐��|�C���^���Ăяo�����
	*/
	void setEventCallback(EventCallback pEventCallback)
	{
		this->m_pEventCallback = pEventCallback;
	}

	/**
	*@desc	�C�x���g�R�[���o�b�N�̌Ăяo��
	*@param	�Ăяo���C���X�^���X
	*@param	�C�x���g
	*		�}�b�v�`�b�v�̍ۂ̓}�b�v�`�b�vID���C�x���g�Ƃ��ēn����
	*		��ʒ[�Ȃǂ̓C�x���g�͑��݂��Ă��Ȃ��̂�
	*		�f�t�H���g�l�Ƃ���0��ݒ肵�Ă���
	*@tips	�̈�̃C�x���g�̔������ɂ��̃����o�֐����Ăяo�����Ƃ�
	*		�o�^���������o�֐��|�C���^���Ăяo�����
	*/
	void callEventCallback(CCharacter* pChara, int event = 0);

public:
	//�f�X�g���N�^
	virtual ~CCollisionTerritory(){}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt) = 0;

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara,CCharacter* pSelf, CVec2 basePt) = 0;

public:
	//�̈�^�C�v
	TERRITORY_TYPE m_type;

	//�R���X�g���N�^
	CCollisionTerritory(TERRITORY_TYPE type) : m_type(type){}
};


//============================================
//���ɂ����ʒ[�̈�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryEndOfScreenBottom : public CCollisionTerritory
{
public:
	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara,CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	�R���X�g���N�^
	*		�̈�^�C�v�̐ݒ���������q�� TERRITORY_TYPE::BOTTOM��
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryEndOfScreenBottom():CCollisionTerritory(TERRITORY_TYPE::BOTTOM){}
};

//============================================
//���ɂ����ʒ[�̈�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryEndOfScreenLeft : public CCollisionTerritory
{
public:
	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	�R���X�g���N�^
	*		�̈�^�C�v�̐ݒ���������q�� TERRITORY_TYPE::BOTTOM��
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryEndOfScreenLeft() :CCollisionTerritory(TERRITORY_TYPE::LEFT) {}
};


//============================================
//���ɂ���L�����N�^�[�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryCharacterBottom : public CCollisionTerritory
{
public:
	/**
	*@desc	�R���X�g���N�^
	*		�̈�^�C�v�̐ݒ���������q�� TERRITORY_TYPE::BOTTOM��
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryCharacterBottom() : CCollisionTerritory(TERRITORY_TYPE::BOTTOM) {}


	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt) override {}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt)override;
};

//============================================
//���ɂ���L�����N�^�[�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryCharacterLeft : public CCollisionTerritory
{
public:
	/**
	*@desc	�R���X�g���N�^
	*		�̈�^�C�v�̐ݒ���������q�� TERRITORY_TYPE::LEFT��
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryCharacterLeft() : CCollisionTerritory(TERRITORY_TYPE::LEFT) {}


	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt) override {}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt)override;
};


//============================================
//��ɂ���L�����N�^�[�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryCharacterTop : public CCollisionTerritory
{
public:
	/**
	*@desc	�R���X�g���N�^
	*		�̈�^�C�v�̐ݒ���������q�� TERRITORY_TYPE::LEFT��
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryCharacterTop() : CCollisionTerritory(TERRITORY_TYPE::TOP) {}


	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override{}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override;
};

//============================================
//�E�ɂ���L�����N�^�[�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryCharacterRight : public CCollisionTerritory
{
public:
	/**
	*@desc	�R���X�g���N�^
	*		�̈�^�C�v�̐ݒ���������q�� TERRITORY_TYPE::LEFT��
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryCharacterRight() : CCollisionTerritory(TERRITORY_TYPE::RIGHT) {}


	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override{}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override;
};




//============================================
//�Փ˔�����
//============================================
class CCollisionArea
{
protected:
	//�Փˊ�_�Q
	std::vector<CCollisionBasePoint*>* m_pBasePoints = NULL;

	//�Փ˔���̈�Q
	std::vector<CCollisionTerritory*>* m_pTerritories = NULL;
public:
	//�R���X�g���N�^
	CCollisionArea()
	{
		//�Փˊ�_�Q�̐���
		this->m_pBasePoints = new std::vector<CCollisionBasePoint*>();

		//�Փ˔���̈�Q�̐���
		this->m_pTerritories = new std::vector<CCollisionTerritory*>();
	}

	//�f�X�g���N�^
	virtual ~CCollisionArea()
	{
		//�Փ˔���̈�̉��
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			SAFE_DELETE(pBasePt);
		}
		SAFE_DELETE(this->m_pBasePoints);

		//�Փ˔���̈�̉��
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
	*@desc	�Փ˔���̈�̒ǉ�
	*@param	�Փ˔���̈�
	*/
	virtual void addTerritory(CCollisionTerritory* pTerritory)
	{
		this->m_pTerritories->push_back(pTerritory);
	}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�[
	*@tips	���t���[���Ăяo��
	*/
	virtual void collision(CCharacter* pChara) = 0;

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�[
	*@param	�Փ˂��ꂽ����
	*@tips	���t���[���Ăяo��
	*/
	virtual void collision(CCharacter* pChara,CCharacter* pSelf) = 0;
};

//===========================================
//��ʒ[�Ƃ̏Փ˔�����
//===========================================
class CCollisionAreaEndOfScreen : public CCollisionArea
{
public:
	//�f�t�H���g
	CCollisionAreaEndOfScreen(){}

	//�����t���R���X�g���N�^
	CCollisionAreaEndOfScreen(CBody* pBody)
	{
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(0.0f,pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(0.0f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right,0.0f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left,0.0f)));
	}
	//�f�X�g���N�^
	~CCollisionAreaEndOfScreen(){}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�[
	*/
	void collision(CCharacter* pChara);

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�[
	*@param	�Փ˂��ꂽ����
	*/
	void collision(CCharacter* pChara,CCharacter* pSelf) override {}

};

//============================================
//��ʏ�ɂ��邷�ׂẴ}�b�v�`�b�v�Ƃ̏Փ˔�����
//�܂�}�b�v�Ƃ̏Փ˔�����
//============================================
class CCollisionAreaMap : public CCollisionArea
{
public:

	//�f�t�H���g
	CCollisionAreaMap() {}
	//�������R���X�g���N�^
	CCollisionAreaMap(CBody* pBody)
	{
		//�}�b�v�`�b�v�Ɠ�����v���C���[�̓������_
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(pBody->m_left*0.5f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(pBody->m_right*0.5f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(pBody->m_left*0.5f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(pBody->m_right*0.5f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right, pBody->m_top*0.5f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right, pBody->m_bottom*0.5f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left, pBody->m_top*0.5f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left, pBody->m_bottom*0.5f)));
	}
	//�f�X�g���N�^
	~CCollisionAreaMap(){}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�\
	*/
	void collision(CCharacter* pChara);

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�[
	*@param	�Փ˂��ꂽ����
	*/
	void collision(CCharacter* pChara,CCharacter* pSelf) override {}
};



//============================================
//���ɂ����ʒ[�̈�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryOutOfScreenBottom : public CCollisionTerritory
{
public:
	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	�R���X�g���N�^
	*		�̈�^�C�v�̐ݒ���������q�� TERRITORY_TYPE::BOTTOM��
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryOutOfScreenBottom() :CCollisionTerritory(TERRITORY_TYPE::BOTTOM) {}
};

//============================================
//��ɂ����ʒ[�̈�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryOutOfScreenTop : public CCollisionTerritory
{
public:
	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;


	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	�R���X�g���N�^
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryOutOfScreenTop() :CCollisionTerritory(TERRITORY_TYPE::TOP) {}
};

//============================================
//���ɂ����ʒ[�̈�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryOutOfScreenLeft : public CCollisionTerritory
{
public:
	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;


	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	�R���X�g���N�^
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryOutOfScreenLeft() :CCollisionTerritory(TERRITORY_TYPE::LEFT) {}
};

//============================================
//�E�ɂ����ʒ[�̈�Ƃ̏Փ˔���
//============================================
class CCollisionTerritoryOutOfScreenRight : public CCollisionTerritory
{
public:
	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CVec2 basePt)override;


	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏ�
	*@param	�Փ˂��ꂽ����
	*@param	��_
	*/
	virtual void collision(CCharacter* pChara, CCharacter* pSelf, CVec2 basePt) override {}

public:
	/**
	*@desc	�R���X�g���N�^
	*		�ݒ肵�Ă���
	*/
	CCollisionTerritoryOutOfScreenRight() :CCollisionTerritory(TERRITORY_TYPE::RIGHT) {}
};

class CCollisionAreaOutOfScreen : public CCollisionArea
{
public:
	//�f�t�H���g
	CCollisionAreaOutOfScreen() {}

	//�����t���R���X�g���N�^
	CCollisionAreaOutOfScreen(CBody* pBody)
	{
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, CVec2(0.0f, pBody->m_bottom)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::TOP, CVec2(0.0f, pBody->m_top)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::RIGHT, CVec2(pBody->m_right, 0.0f)));
		this->m_pBasePoints->push_back(new CCollisionBasePoint(TERRITORY_TYPE::LEFT, CVec2(pBody->m_left, 0.0f)));
	}
	//�f�X�g���N�^
	~CCollisionAreaOutOfScreen() {}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�[
	*/
	void collision(CCharacter* pChara);

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�[
	*@param	�Փ˂��ꂽ����
	*/
	void collision(CCharacter* pChara,CCharacter* pSelf) override {}
};


//============================================
//�L�����N�^�[�Ƃ̏Փ˔�����
//============================================
class CCollisionAreaCharacter : public CCollisionArea
{
public:

	//�f�t�H���g
	CCollisionAreaCharacter() {}
	//�������R���X�g���N�^
	CCollisionAreaCharacter(CBody* pBody)
	{
		//�}�b�v�`�b�v�Ɠ�����v���C���[�̓������_
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
	//�f�X�g���N�^
	~CCollisionAreaCharacter() {}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�\
	*/
	void collision(CCharacter* pChara) override {}

	/**
	*@desc	�Փ˔���
	*@param	�ՓˑΏۂ̃L�����N�^�[
	*@param	�Փ˂��ꂽ����
	*/
	void collision(CCharacter* pChara, CCharacter* pSelf) override;
};
