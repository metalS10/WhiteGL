#pragma once
//==============================================
//�ǉ��̃C���N���[�h�͂�������
//==============================================
#include "Model/Map/Map.h"
#include "Model/Character/Factory/AttackFactory/AttackFactory.h"
#include "Model/Character/Factory/BulletFactory/EnemyBulletFactory.h"

//==============================================
//�G�o���f�[�^
//==============================================
class CEnemyLaunchData
{
public:
	//�G�̃^�C�v
	ENEMY_TYPE m_type;
	//�o���ʒu
	cocos2d::Point m_pos;

	//�R���X�g���N�^
	CEnemyLaunchData(ENEMY_TYPE type, cocos2d::Point pos)
		:m_type(type),m_pos(pos){}
};

//==============================================
//�U���o���f�[�^
//==============================================
class CAttackLaunchData
{
public:
	//�e�̃^�C�v
	ATTACK_TYPE m_attacktype;
	//�����ʒu(�o���ʒu)
	cocos2d::Point m_pos;

	cocos2d::Vec2 m_vec;

	//�R���X�g���N�^
	CAttackLaunchData(ATTACK_TYPE type, cocos2d::Point pos,cocos2d::Vec2 vec)
		:m_attacktype(type), m_pos(pos),m_vec(vec) {}
};

//==============================================
//�G�U���o���f�[�^
//==============================================
class CEnemyBulletLaunchData
{
public:
	//�e�̃^�C�v
	BULLET_TYPE m_bullettype;
	//�����ʒu(�o���ʒu)
	cocos2d::Point m_pos;

	cocos2d::Vec2 m_vec;

	//�R���X�g���N�^
	CEnemyBulletLaunchData(BULLET_TYPE type, cocos2d::Point pos, cocos2d::Vec2 vec)
		:m_bullettype(type), m_pos(pos), m_vec(vec) {}
};


//==============================================
//�M�~�b�N�o���f�[�^
//==============================================
class CGimmickLaunchData
{
public:
	//�G�̃^�C�v
	GIMMICK_TYPE m_type;
	//�o���ʒu
	cocos2d::Point m_pos;

	//�R���X�g���N�^
	CGimmickLaunchData(GIMMICK_TYPE type, cocos2d::Point pos)
		:m_type(type), m_pos(pos) {}
};