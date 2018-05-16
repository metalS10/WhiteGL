#pragma once
//=====================================================
//�ǉ��̃C���N���[�h�͂�������
//=====================================================
#include "../Constants.h"
#include "../Vec2.h"

//=====================================================
//�O���錾�Ɋւ���R�[�h�͂������珑��
//=====================================================
class CCharacter;
typedef CVec2 Point;
//=====================================================
//�A�N�V�����N���X
//=====================================================
class CAction
{
public:
	virtual ~CAction(){}
	//�A�N�V�������J�n����ۂɌĂяo��
	virtual void start() = 0;
	//�A�N�V�����̍X�V����
	virtual void update(CCharacter* pChara) = 0;
	//�A�N�V�������I������ۂɌĂяo��
	virtual void stop() = 0;

	/**
	*@desc	�A�N�V�����̍ċN��
	*@param	�ċN������L�����N�^�[
	*@tips	�W���I�ȃA�N�V�����̍ċN��
	*		�����ł̓L�����N�^�[�͎g�p���Ȃ�
	*/
	virtual void restart(CCharacter* pChara)
	{
		//�A�N�V�����̒�~
		this->stop();

		//�A�N�V�����̊J�n
		this->start();
	}
};

//====================================================
//�W�����v
//	�W�����v�Ɋւ��鏈�����s�����������Ƃ��Ĉړ��f�[�^�ɑ΂��ĕύX��������
//		tips:
//			cocos2dx��Action�N���X�ɂ��W�����v�͑��݂��邪
//			Action�N���X�Ɉˑ����Ă���̂ŏd�͂▀�C��}�b�v�`�b�v�Ȃǂ̉e�����l�����
//			���߂̂����͕������čl�����ق����������₷��
//====================================================
class CActionJump : public CAction
{
protected:
	//�W�����v�����x
	float m_accele = 0.0f;
	//�W�����v�u�[�X�g
	float m_boost = 0.0f;

	//���݂̃W�����v�u�[�X�g
	float m_currentBoost = 0.0f;

	//�W�����v�����ǂ����̃t���O	true...�W�����v��
	bool m_isJumping = false;

	//�W�����v�J�n�t���O
	bool m_isJumpStart = false;

public:

	CActionJump(float accele, float boost):
		m_accele(accele),m_boost(boost){}

	/**
	*	@desc�W�����v
	*	@param �����x
	*	@param �W�����v�u�[�X�g
	*	@tips �W�����v�{�^���������ꂽ�ۂɒl�̐ݒ�ƂƂ��ɌĂяo��
	*/
	void start() override
	{
		//�W�����v�J�n
		this->m_isJumpStart = true;
	}

	/**
	*	@desc �X�V����
	*	@param �W�����v����Ώۂ̃L�����N�^�[
	*	@tips ��L�[�������ꂽ�炱�̊֐����Ăяo��
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc �W�����v�I��
	*	@tips ���n�����ۂɂ��̊֐����Ăяo��
	*/
	void stop() override
	{
		//�W�����v���t���O�����낷
		this->m_isJumping = false;
	}

	/**
	*@desc	�A�N�V�����̍ċN��
	*@param	�ċN������L�����N�^�[
	*@tips	�L�����N�^�[��Y�����̃��Z�b�g���s�Ȃ�
	*/
	void restart(CCharacter* pChara)override;
};

//===========================================================
//����A�N�V����
//===========================================================
class CActionAvoidance : public CAction
{
protected:
	//��������x
	float m_accele = 0.0f;


	//�W�����v�����ǂ����̃t���O	true...�W�����v��
	bool m_isAvoidance = false;
	
	//�W�����v�J�n�t���O
	bool m_isAvoidanceStart = false;

	//�J�E���^�[
	//����s���C���^�[�o��
	int m_intarval = 0;
	//�������\�C���^�[�o��
	int m_avoidanceIntarval = 0;
	int m_counter = 0;

public:

	CActionAvoidance(float accele ,int avoidanceIntarval, int intarval) :
		m_accele(accele),m_avoidanceIntarval(avoidanceIntarval), m_intarval(intarval) {}

	/**
	*	@desc�W�����v
	*	@param �����x
	*	@param �W�����v�u�[�X�g
	*	@tips �W�����v�{�^���������ꂽ�ۂɒl�̐ݒ�ƂƂ��ɌĂяo��
	*/
	void start() override
	{
		//�W�����v�J�n
		this->m_isAvoidanceStart = true;
	}

	/**
	*	@desc �X�V����
	*	@param �W�����v����Ώۂ̃L�����N�^�[
	*	@tips ��L�[�������ꂽ�炱�̊֐����Ăяo��
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc �W�����v�I��
	*	@tips ���n�����ۂɂ��̊֐����Ăяo��
	*/
	void stop() override
	{
		//�W�����v���t���O�����낷
		this->m_isAvoidance = false;
	}

	/**
	*@desc	�A�N�V�����̍ċN��
	*@param	�ċN������L�����N�^�[
	*@tips	�L�����N�^�[��Y�����̃��Z�b�g���s�Ȃ�
	*/
	void restart(CCharacter* pChara)override;
};



//====================================================
//�G���S�A�N�V����
//====================================================
class CActionEnemyDead : public CAction
{
protected:
	//���ړ����x
	float m_velX = 0.0f;

	//���˂鑬�x
	float m_leapVelY = 0.0f;

	//�A�N�V���������ǂ����̃t���Otrue...�A�N�V������
	bool m_inAction = false;

	//�A�N�V�����J�n�t���Otrue...�A�N�V�����J�n
	bool m_isStart = false;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	���ړ����x
	*@param	���˂鑬�x
	*/
	CActionEnemyDead(float velX, float leapVelY);

	/**
	*@desc	�A�N�V�����J�n
	*/
	void start() override;

	/**
	*@desc	�X�V����
	*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
	*/
	void update(CCharacter* pChara) override;

	/**
	*@desc	�A�N�V�����I��
	*/
	void stop() override;

	
};

//=============================================
//�㉺�ړ��A�N�V����
//=============================================
class CActionUpAndDownMove : public CAction
{
private:
	//�A�N�V���������ǂ����̃t���O true...�A�N�V������
	bool m_inAction = false;

	//��ʒu
	Point m_basePos;

	//���a
	float m_radius = 0.0f;

	//���x
	float m_vel = 0.0f;

	//�J�E���^�[
	float m_counter = 0.0f;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	��ʒu
	*@param	���a
	*@param	���x
	*/
	CActionUpAndDownMove(Point basePos, float radius, float vel);

	/**
	*@desc	�A�N�V�����J�n
	*/
	void start() override;

	/*
	*@desc	�X�V����
	*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
	*/
	void update(CCharacter* pChara)override;

	/*
	*@desc	�A�N�V�����I��
	*/
	void stop() override;
};

//======================================================
//�G���S�A�N�V������Ɏ��S�ʒu����G���o��������
//======================================================
class CActionEnemyDeadAndCreateEnemy : public CAction
{
	//{ENEMY_TYPE}�o��������G�̃^�C�v
	int m_type;

	//�A�N�V���������ǂ����̃t���O true...�A�N�V������
	bool m_inAction = false;

	//�A�N�V�����J�n�t���O true...�A�N�V�����J�n
	bool m_isStart = false;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	�o��������G�̃^�C�v
	*/
	CActionEnemyDeadAndCreateEnemy(int type);

	/**
	*@desc	�A�N�V�����J�n
	*/
	void start() override;

	/*
	*@desc	�X�V����
	*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
	*/
	void update(CCharacter* pChara) override;

	/**
	*@desc	�A�N�V�����I��
	*/
	void stop() override;
};

//======================================================
//�G�����A�N�V����
//======================================================
class CActionCreateEnemy : public CAction
{
	//{ENEMY_TYPE}�o��������G�̃^�C�v
	int m_type;

	int m_ShotCount = 0;

	//�A�N�V���������ǂ����̃t���O true...�A�N�V������
	bool m_inAction = false;

	//�A�N�V�����J�n�t���O true...�A�N�V�����J�n
	bool m_isStart = false;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	�o��������G�̃^�C�v
	*/
	CActionCreateEnemy(int type);

	/**
	*@desc	�A�N�V�����J�n
	*/
	void start() override;

	/*
	*@desc	�X�V����
	*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
	*/
	void update(CCharacter* pChara) override;

	/**
	*@desc	�A�N�V�����I��
	*/
	void stop() override;
};

//=============================================
//�܂������ړ��A�N�V����
//=============================================
class CActionMoveStraight : public CAction
{
private:
	//�A�N�V���������ǂ����̃t���O true...�A�N�V������
	bool m_inAction = false;

	//��ʒu
	Point m_basePos;


	//���x
	float m_vel = 0.0f;

	float m_velY = 0.0f;

	//�J�E���^�[
	float m_counter = 0.0f;

	//�ړ��͂��Ȃ��Ǝv�����܂������ړ��ŏ�������������
	int deleteCount = 0;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	��ʒu
	*@param	���a
	*@param	���x
	*/
	CActionMoveStraight(Point basePos, float vel);

	CActionMoveStraight(Point basePos, float velX,float velY);

	/**
	*@desc	�A�N�V�����J�n
	*/
	void start() override;

	/*
	*@desc	�X�V����
	*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
	*/
	void update(CCharacter* pChara)override;

	/*
	*@desc	�A�N�V�����I��
	*/
	void stop() override;
};

//====================================================
//�e���˃A�N�V����
//====================================================
class CActionShotBullet : public CAction
{
protected:
	int m_bulletType;

	//���ˊԊu
	float m_interval = 0.0f;

	//���˃J�E���^�[
	float m_shotCount= 0.0f;

	//�A�j���[�V���������ǂ���
	bool m_inAction = false;

public:

	CActionShotBullet(int type, float interval)
		:m_bulletType(type), m_interval(interval) {}

	/**
	*	@desc�A�N�V����
	*	@tips ���˃{�^���������ꂽ
	*/
	void start() override
	{
		m_inAction = true;
	}

	/**
	*	@desc �X�V����
	*	@param �A�N�V��������Ώۂ̃L�����N�^�[
	*	@tips ��L�[�������ꂽ�炱�̊֐����Ăяo��
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc �A�N�V�����I��
	*	@tips ���n�����ۂɂ��̊֐����Ăяo��
	*/
	void stop() override
	{
		//�A�N�V�������t���O�����낷
		this->m_inAction = false;
	}

	/**
	*@desc	�A�N�V�����̍ċN��
	*@param	�ċN������L�����N�^�[
	*@tips	�L�����N�^�[��Y�����̃��Z�b�g���s�Ȃ�
	*/
	void restart(CCharacter* pChara)override {}
};

//=============================================
//��ɂ������ė�����A�N�V����(�d��)
//=============================================
class CActionCurve : public CAction
{
private:
	//�A�N�V���������ǂ����̃t���O true...�A�N�V������
	bool m_inAction = false;

	//��ʒu
	Point m_basePos;

	//���x
	float m_vel = 0;

	float m_velY = 3;
	//�J�E���^�[
	float m_counter = 0.0f;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	��ʒu
	*@param	���a
	*@param	���x
	*/
	CActionCurve(Point basePos, float vel);

	CActionCurve(Point basePos, float velX, float velY);


	/**
	*@desc	�A�N�V�����J�n
	*/
	void start() override;

	/*
	*@desc	�X�V����
	*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
	*/
	void update(CCharacter* pChara)override;

	/*
	*@desc	�A�N�V�����I��
	*/
	void stop() override;


};

//�w��̊ԃA�j���[�V��������
class CActionRoll : public CAction
{
private:
	//�A�j���[�V�����Ԋu
	int m_interval = 300;
	//���˃J�E���^�[
	int m_counter = 300;
	//�A�N�V�����J�n�t���O
	bool m_isStart = false;

public:
	/*
	*�R���X�g���N�^
	*�Ԋu
	*�J�E���^�[
	*/
	CActionRoll(){}

	void start() override;

	void update(CCharacter* pChara)override;

	void stop() override;

};

//=======================================================
//������A�N�V����
//=======================================================
class CActionDown : public CAction
{
private:
	//���˃J�E���^�[
	int m_counter = 60;
	//�A�N�V�����J�n�t���O
	bool m_isStart = false;

public:
	/*
	*�R���X�g���N�^
	*�Ԋu
	*�J�E���^�[
	*/
	CActionDown() {}

	void start() override;

	void update(CCharacter* pChara)override;

	void stop() override;

};




//=============================================================
//�G�����u���b�N�p�A�N�V����
//=============================================================
class CActionCreateCharacter : public CAction
{
	//{ENEMY_TYPE}�o��������G�̃^�C�v
	int m_type;

	//�A�N�V���������ǂ����̃t���O true...�A�N�V������
	bool m_inAction = false;

	//�A�N�V�����J�n�t���O true...�A�N�V�����J�n
	bool m_isStart = false;

	int count = 0;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	�o��������G�̃^�C�v
	*/
	CActionCreateCharacter(int type);

	/**
	*@desc	�A�N�V�����J�n
	*/
	void start() override;

	/*
	*@desc	�X�V����
	*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
	*/
	void update(CCharacter* pChara) override;

	/**
	*@desc	�A�N�V�����I��
	*/
	void stop() override;
};

class CActionEnemyDamage : public CAction
{
protected:
	//�W�����v�����x
	float m_accele = 0.0f;
	//�W�����v�u�[�X�g
	int m_boost = 0;

	//�o�b�N�X�e�b�v����
	float m_backstep = 0.0f;

	//���݂̃W�����v�u�[�X�g
	int m_currentBoost = 0;

	//�W�����v�����ǂ����̃t���O	true...�W�����v��
	bool m_isJumping = false;

	//�W�����v�J�n�t���O
	bool m_isJumpStart = false;


public:

	CActionEnemyDamage(float accele, int boost, float backstep) :
		m_accele(accele), m_boost(boost), m_backstep(backstep) {}

	/**
	*	@desc�W�����v
	*	@param �����x
	*	@param �W�����v�u�[�X�g
	*	@tips �W�����v�{�^���������ꂽ�ۂɒl�̐ݒ�ƂƂ��ɌĂяo��
	*/
	void start() override
	{
		//�W�����v�J�n
		this->m_isJumpStart = true;
	}

	/**
	*	@desc �X�V����
	*	@param �W�����v����Ώۂ̃L�����N�^�[
	*	@tips ��L�[�������ꂽ�炱�̊֐����Ăяo��
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc �W�����v�I��
	*	@tips ���n�����ۂɂ��̊֐����Ăяo��
	*/
	void stop() override
	{
		//�W�����v���t���O�����낷
		this->m_isJumping = false;
	}

	/**
	*@desc	�A�N�V�����̍ċN��
	*@param	�ċN������L�����N�^�[
	*@tips	�L�����N�^�[��Y�����̃��Z�b�g���s�Ȃ�
	*/
	void restart(CCharacter* pChara)override;
};


//====================================================
//�G�e���˃A�N�V����
//====================================================
class CActionShotEnemyBullet : public CAction
{
protected:
	int m_bulletType = 0;

	//���ˊԊu
	float m_interval = 0.0f;

	//���˃J�E���^�[
	float m_shotCount = 0.0f;

	//�A�j���[�V���������ǂ���
	bool m_inAction = false;

public:

	CActionShotEnemyBullet(int type, float interval)
		:m_bulletType(type), m_interval(interval) {}

	/**
	*	@desc�A�N�V����
	*	@tips ���˃{�^���������ꂽ
	*/
	void start() override
	{}

	/**
	*	@desc �X�V����
	*	@param �A�N�V��������Ώۂ̃L�����N�^�[
	*	@tips ��L�[�������ꂽ�炱�̊֐����Ăяo��
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc �A�N�V�����I��
	*	@tips ���n�����ۂɂ��̊֐����Ăяo��
	*/
	void stop() override
	{
		//�A�N�V�������t���O�����낷
		this->m_inAction = false;
	}

	/**
	*@desc	�A�N�V�����̍ċN��
	*@param	�ċN������L�����N�^�[
	*@tips	�L�����N�^�[��Y�����̃��Z�b�g���s�Ȃ�
	*/
	void restart(CCharacter* pChara)override {}
};

//====================================================
//�G�~��e���˃A�N�V����
//====================================================
class CActionShotEnemySphereBullet : public CAction
{
protected:
	int m_bulletType;

	//���ˊԊu
	float m_interval = 0.0f;

	//���˃J�E���^�[
	float m_shotCount = 0.0f;

	//�A�j���[�V���������ǂ���
	bool m_inAction = false;



public:

	CActionShotEnemySphereBullet(int type, float interval)
		:m_bulletType(type), m_interval(interval) {}

	/**
	*	@desc�A�N�V����
	*	@tips ���˃{�^���������ꂽ
	*/
	void start() override
	{
		m_inAction = true;
	}

	/**
	*	@desc �X�V����
	*	@param �A�N�V��������Ώۂ̃L�����N�^�[
	*	@tips ��L�[�������ꂽ�炱�̊֐����Ăяo��
	*/
	void update(CCharacter* pChara);

	/**
	*	@desc �A�N�V�����I��
	*	@tips ���n�����ۂɂ��̊֐����Ăяo��
	*/
	void stop() override
	{
		//�A�N�V�������t���O�����낷
		this->m_inAction = false;
	}

	/**
	*@desc	�A�N�V�����̍ċN��
	*@param	�ċN������L�����N�^�[
	*@tips	�L�����N�^�[��Y�����̃��Z�b�g���s�Ȃ�
	*/
	void restart(CCharacter* pChara)override {}
};

//=============================================
//�g�����Ȃ���̃A�N�V����
//=============================================
class CActionTRoi : public CAction
{
private:
	//�A�N�V���������ǂ����̃t���O true...�A�N�V������
	bool m_inAction = false;

	
	//���x
	float m_vel = 0.0f;

	CCharacter* m_pPlayer ;

	int counter = 0;

	int m_intervalTime = 0;

	//�v���C���̃|�W�V����
	CVec2 pos;

	//�A�N�V�����X�e�b�v
	int step = 0;

	float nowHeight = 0.0f;

	bool up = false;

	float upheight = 0.0f;
public:
	/**
	*@desc	�R���X�g���N�^
	*@param	��ʒu
	*@param	���a
	*@param	���x
	*/
	CActionTRoi(float vel, int interval)
		:m_vel(vel), m_intervalTime(interval){}

	/**
	*@desc	�A�N�V�����J�n
	*/
	void start() override
	{}

	/*
	*@desc	�X�V����
	*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
	*/
	void update(CCharacter* pChara)override;

	/*
	*@desc	�A�N�V�����I��
	*/
	void stop() override
	{}
};