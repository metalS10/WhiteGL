#pragma once
//==============================================
//追加のインクルードはここから
//==============================================
#include "../Map/Map.h"
#include "../../Factory/AttackFactory/AttackFactory.h"
#include "../../Factory/EnemyBulletFactory/EnemyBulletFactory.h"

//==============================================
//敵出撃データ
//==============================================
class CEnemyLaunchData
{
public:
	//敵のタイプ
	ENEMY_TYPE m_type;
	//出撃位置
	CVec2 m_pos;

	//コンストラクタ
	CEnemyLaunchData(ENEMY_TYPE type, CVec2 pos)
		:m_type(type),m_pos(pos){}
};

//==============================================
//攻撃出撃データ
//==============================================
class CAttackLaunchData
{
public:
	//弾のタイプ
	ATTACK_TYPE m_attacktype;
	//初期位置(出撃位置)
	CVec2 m_pos;

	CVec2 m_vec;

	//コンストラクタ
	CAttackLaunchData(ATTACK_TYPE type, CVec2 pos, CVec2 vec)
		:m_attacktype(type), m_pos(pos),m_vec(vec) {}
};

//==============================================
//敵攻撃出撃データ
//==============================================
class CEnemyBulletLaunchData
{
public:
	//弾のタイプ
	BULLET_TYPE m_bullettype;
	//初期位置(出撃位置)
	CVec2 m_pos;

	CVec2 m_vec;

	//コンストラクタ
	CEnemyBulletLaunchData(BULLET_TYPE type, CVec2 pos, CVec2 vec)
		:m_bullettype(type), m_pos(pos), m_vec(vec) {}
};


//==============================================
//ギミック出撃データ
//==============================================
class CGimmickLaunchData
{
public:
	//敵のタイプ
	GIMMICK_TYPE m_type;
	//出撃位置
	CVec2 m_pos;

	//コンストラクタ
	CGimmickLaunchData(GIMMICK_TYPE type, CVec2 pos)
		:m_type(type), m_pos(pos) {}
};