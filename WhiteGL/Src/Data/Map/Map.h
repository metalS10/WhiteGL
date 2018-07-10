#pragma once
#include <stdio.h>
#include "../../Constants.h"
#include "../../interpreter/CCTMXTiledMap.h"
#include "../../Vec2.h"
#include <vector>
#include "../../AllController/AllController.h"

//=====================================================
//�O���錾
//=====================================================
class CEnemyLaunchData;
class CGimmickLaunchData;

//=========================================================
//�u���b�N(�}�b�v�`�b�v�̂���)���
//�V������ނ��ł����炱���ɑ��₵�Ă���
//=========================================================
enum class BLOCK_TYPE : int {
	NONE		= 0, //�����Ȃ�
};

//=========================================================
//�G�̎��
//�u���b�N�ԍ��Ɉˑ�
//=========================================================
enum class ENEMY_TYPE : int
{
	NONE		=	0,			//�����Ȃ�
	KURIBO		=	102,		//�N���{�[
	NOKONOKO	=	108,		//�m�R�m�R
	PATAPATA	=	109,		//�p�^�p�^
	KILLERHODAI	=	124,		//�L���[�C��
	KILLER		=	1000,		//�L���[
	TROI		=	110,		//�g�����Ȃ��ؔn
};

//=========================================================
//�M�~�b�N�̎��
//�u���b�N�ԍ��Ɉˑ�
//=========================================================
enum class GIMMICK_TYPE : int
{
	NONE	=	0,		//�����Ȃ�
	TIKUWA	=	132,	//��������
	ROLL	=	135,	//�����
	TOGE_L	=	136,	//�������̂Ƃ�
	TOGE_T	=	137,	//������̂Ƃ�
	TOGE_R	=	138,	//�E�����̂Ƃ�
	TOGE_B	=	139,	//�������̂Ƃ�
	NOTE	=	140,	//���˂���
	HATENA	=	141,	//�n�e�i�u���b�N
	WORP	=	142,	//���[�v
};


//=========================================================
//�}�b�v�N���X
//=========================================================
class CMap :public TMXTiledMap
{


public:
	//=====================================================
	//���C���[�^�C�v
	//=====================================================
	enum  class LAYER_TYPE :int
	{
		NORMAL = 0,//�ʏ�}�b�v
		LAUNCH_ENEMY = 1,//�G�o���p�}�b�v
		LAUNCH_GIMMICK = 2,//�M�~�b�N�o���p�}�b�v
	};

	//=====================================================
	//�}�b�v�^�C�v�ɂ�郌�C���[�̖��O
	//=====================================================
	std::vector<std::string>m_layerName
	{
		"normal",
		"launchenemy",
		"launchgimmick",
	};
public:

	//�R���X�g���N�^
	CMap(){}

	//����
	static CMap* create(const std::string&tmxFile)
	{
		CMap* pMap = new(std::nothrow)CMap();
		if (pMap->init(tmxFile))
		{
			//pMap->autorelease();
			return pMap;
		}
		SAFE_DELETE(pMap);
		return NULL;
	}

	bool init(const std::string& tmxFile);


	/**
	*@desc	�^�C����1�����z���̍��W���擾
	*@param	��������_�Ƃ����z���̍��W�ʒu
	*/
	CVec2 getTileCoord(CVec2 pos);

	/**
	*@desc	�^�C����1�����z���̍��W���擾
	*@param	���������_�Ƃ����Ώۂ̍��W�ʒu
	*/
	CVec2 getTilePosition(CVec2 pos);

	/**
	*@desc	�_�ƃ}�b�v�`�b�v�Ƃ̏Փ˔���
	*@param	�ΏۈʒuX
	*@param	�ΏۈʒuY
	*/
	bool hitTest(float posX, float posY);

	/**
	* @desc	�^�C���ԍ��̊m�F
	* @param	�^�C���ɏՓ˂��Ă���_��x�ʒu
	* @param	�^�C���ɏՓ˂��Ă���_��y�ʒu
	* @return	���C���[�^�C�v
	* @return	�^�C���ԍ�(�u���b�N�ԍ�,�}�b�v�`�b�v�ԍ�,�}�b�v�`�b�vID)
	*/
	BLOCK_TYPE checkTile(float posX, float posY, LAYER_TYPE layerType = LAYER_TYPE::NORMAL);

	/**
	*@desc	�^�C���̕ύX
	*@param	�ύX����}�b�v�`�b�vID(�^�C���ԍ��A�u���b�N�ԍ��A�}�b�v�`�b�v�ԍ�)
	*@param	�^�C���ɏՓ˂��Ă���_��x���W
	*@param	�^�C���ɏՓ˂��Ă���_��y���W
	*@param ���C���[�^�C�v
	*@return	true...����
	*/
	bool changeTile(int mapChipID, float posX, float posY,LAYER_TYPE layerType = LAYER_TYPE::NORMAL);

	/*
	*	@desc	�G�o������
	*	@return �G�̃^�C�v
	*/
	void checkEnemyLaunch(float X,float Y);

	/*
	*	@desc	�M�~�b�N�o������
	*	@return �G�̃^�C�v
	*/
	void checkGimmickLaunch(float X, float Y);

	//�G�o�����C��(�}�b�v2�����z���̃^�C����x�ʒu)
	//20�͉�ʂ̒[ + 1����
	int m_launchEnemyLine = 40;
	int m_launchGimmickLine = 40;


	/**
	* @desc	�G�o����̓G�o�����C���[�̃^�C���̍폜
	* @param �G�o���f�[�^
	*/
	void removeLaunchEnemyBlock(CEnemyLaunchData* pLaunchData);

	/**
	* @desc	�M�~�b�N�o����̃M�~�b�N�o�����C���[�̃^�C���̍폜
	* @param �M�~�b�N�o���f�[�^
	*/
	void removeLaunchGimmickBlock(CGimmickLaunchData* pLaunchData);


};

//========================================================================
//�}�b�v�Ǘ��N���X
//========================================================================
class CMapManager
{
private:
	//=============================================================================
	//�V���O���g���ݒ�
	//=============================================================================

	//�R���X�g���N�^
	CMapManager();
	CMapManager(const CMapManager & customMapMgr);

	//���L�C���X�^���X
	static CMapManager* m_pSharedMapManager;

public:
	//���L�C���X�^���X�̎擾
	static CMapManager* getInstance();

	//�j��
	static void removeInstance();
	//�f�X�g���N�^
	~CMapManager();

private:
	//�}�b�v
	CMap* m_pMap = NULL;

public:
	//�}�b�v�̐���
	CMap* createMap(const std::string & fileName);

	//�}�b�v�̎擾
	CMap* getMap();

	//�}�b�v�̐ݒ�
	CMap* setMap(const std::string & fileName);

	CGameEngine& game = MS::CMS::getInstance()->getGame();

	
};