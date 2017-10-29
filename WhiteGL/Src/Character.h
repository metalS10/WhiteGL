#pragma once
//===============================================
//�ǉ��̃C���N���[�h�͂�������
//===============================================
#include "Animation.h"
#include "Physical.h"
//#include "ActionController.h"
#include "Collision.h"
#include "CollisionArea.h"
//#include "Map.h"

//===============================================
//�L�����N�^�[�^�C�v
//===============================================
enum class CHARACTER_TYPE : int
{
	NONE = -1,	//�Ȃ�
	PLAYER = 0,		//�v���C���[
	ENEMY = 1,		//�G
	ATTACK = 2,		//�U��
	GIMMICK = 3,		//�M�~�b�N
	ENEMYBULLET = 4,		//�G�̍U��

};

//===============================================
//	�L�����N�^�[�N���X
//		���ׂẴL�����N�^�[�̐��`�ƂȂ钊�ۃN���X
//===============================================
class CCharacter
{
public:
	//�R���X�g���N�^
	CCharacter();

	//�f�X�g���N�^
	virtual ~CCharacter();

	//����������
	virtual bool init();

	//�X�V����
	virtual void update();

	void setTexture(const char* pass) { texPass = pass; }

	//�A�j���[�V�����f�[�^�Q
	std::vector<CAnimation*>* m_pAnimations = NULL;

	//�ړ��f�[�^
	CMove* m_pMove = NULL;

	//�K�p�����镨�����Z�Q
	std::vector<CPhysical*>*m_pPhysicals = NULL;

	//�s����A�N�V�����Q
	//std::vector<CAction*>* m_pActions = NULL;

	//���̃f�[�^(�Փ˔���f�[�^�̌��ƂȂ�f�[�^)
	CBody* m_pBody = NULL;

	//�Փ˔����ԌQ
	std::vector<CCollisionArea*>* m_pCollisionAreas = NULL;

	/**
	*@desc	DP���񕜂���֐�
	*@param	�񕜒l
	*/
	void DPHeal(float dp_value);

	/*
	*	-1����Ȃ��Ȃ�Ύ����폜�������Ă΂��
	*	�����폜�����鎞��(s)
	*/
	int m_DeleteTime = -1;


	//���(�h����ɂ���ă^�C�v���ω�����)
	int m_state = 0;

	//�L���t���O
	bool m_activeFlag = false;

	//�^�O
	int m_tag = 0;

	//�L�����N�^�[�^�C�v
	CHARACTER_TYPE m_charaType = CHARACTER_TYPE::NONE;

	//�G�^�C�v
	//ENEMY_TYPE m_eneType = ENEMY_TYPE::NONE;


	//�L�����N�^�[�̕����̃x�N�g��(�e�̌����x�N�g��)
	CVec2 m_CharaLaunchVector;
	//�ړ����x�x�N�g��
	CVec2 m_moveVector;

	bool m_isAction = false;

	//�n�ʂɂ��Ă���̒x���̂��߂̃����o�ϐ�(Enemy)
	int Groundcount = 0;

	//������
	bool m_isAvoidance = false;

	//�W���X�g���
	int m_DodgeTime = 0;

	//�X�e�[�W�؂�ւ��^�C�~���O
	bool m_nextStage = false;

	//�X�e�[�W�N���A
	bool m_stageClear = false;
	//�Q�[���I�[�o�[
	bool m_gameOver = false;

	const char* texPass = "";

	//�U�����̓G
	CCharacter* m_pNowEnemy = NULL;

	//=================================================
	//	�����o�ϐ�(�X�e�[�^�X��)
	//=================================================

	//���O
	std::string m_name = "None";

	//�ő�̗�
	int m_maxHitPoint = -1;
	//�̗�
	int m_hitPoint = -1;

	//�_���[�W�Ԋu(Player)
	float DamageTime = 60;

	//���d�_���[�W�h�~�p
	int InvisibleFrame = 0;

	//�_���[�W�̓���Ȃ���
	bool m_isInvisible = false;

	//�v���C���[�݂̂ɕK�v
	float m_denkiPoint = 0;

	//�U���L�����̍U����
	int m_attackPoint = 0;

	//�m�b�N�o�b�N�̋���
	CVec2 m_Nockback = CVec2(-this->m_CharaLaunchVector.x * 5, 5);


protected:

	//�ړ�����
	virtual void moveFunc() = 0;

	//�A�j���[�V��������
	virtual void animationFunc() = 0;
	/*
	//��ʔ͈͒[���菈��
	virtual void endOfScreen() = 0;
	*/

	//�Փ˔��菈��
	virtual void collision() = 0;

	//��ԃ`�F�b�N
	virtual void checkState() = 0;

	//���f����
	virtual void applyFunc() = 0;

public:
	/**
	*	@desc �L�����N�^�[�P�̂Ƃ̏Փ˔��菈��
	*	@param �L�����N�^�[�̃A�h���X
	*	@return true...�Փ˂���
	*/
	virtual bool collision(CCharacter* pChara) = 0;

	/**
	*@desc	�}�b�v�Ƃ̏Փ˔��菈��
	*@return	true...�Փ˂���
	*/
	//virtual bool collisionMap() = 0;

	/**
	*@desc	���̈�ƏՓ˂����ۂ̃C�x���g�R�[���o�b�N
	*@param	�}�b�v�`�b�vID
	*		��ʒ[���̍ۂ�0
	*/
	virtual void collisionBottomCallback(int event) {}

	virtual void collisionTopCallback(int event) {}

	virtual void collisionRightCallback(int event) {}

	virtual void collisionLeftCallback(int event) {}


	/**
	*@desc	�Փ˔����̏���
	*@param	�Փ˂��Ă����L�����N�^�[
	*/
	virtual void hits(CCharacter* pChara) = 0;

	//�����Ă��邩����ł��邩�̃t���O
	//true...�����Ă���@false...����ł���
	bool m_isAlive = false;

	bool m_isDamage = false;

	bool m_isAttack1 = false;
	bool m_isAttack2 = false;
	bool m_isAttack3 = false;

	//�n�ʂɒ��n���Ă��邩�ǂ���
	bool m_isGround = false;

	//================================================================
	//
	//�����܂łɃ����o�Ɋւ���R�[�h��ǉ�
	//
	//================================================================
};

//========================================================
//�L�����N�^�[�̏W����
//	�V���O���g���������đ��̃t�@�C���ň�����悤�ɂ��Ă���
//========================================================
class CCharacterAggregate
{
private:
	//================================================================
	//�V���O���g���ݒ�͂�������
	//================================================================
	//���L�C���X�^���X
	static CCharacterAggregate* m_pSharedAggre;

public:

	//�R���X�g���N�^
	CCharacterAggregate();

	//�f�X�g���N�^
	~CCharacterAggregate();

	//���L�C���X�^���X�̎擾
	static CCharacterAggregate* getInstance();
	//���L�C���X�^���X�̔j��
	static void removeInstance();

	//================================================================
	//�V���O���g���ݒ�͂����܂�
	//================================================================

private:
	//�L�����N�^�̏W�܂�
	std::vector<CCharacter*>* m_pCharacters = NULL;

public:
	/**
	*@desc	�L�����N�^�[�̏W�܂�̎Q�Ƃ�ݒ�
	*@param	�ݒ肷��L�����N�^�[�̏W�܂�̃A�h���X
	*/
	void set(std::vector<CCharacter*>* pCharacters);

	/**
	*@desc	�L�����N�^�[�̏W�܂�̎Q�Ƃ�ݒ�
	*@param	�ݒ肷��L�����N�^�[�̏W�܂�̃A�h���X
	*/
	std::vector<CCharacter*>* get();

	/**
	*@desc	�L�����N�^�[��̂��擾
	*@param	�Y���ԍ�
	*@return �L�����N�^�[
	*/
	CCharacter* getAt(int index);

	/**
	*@desc	�^�O����肵�ăL�����N�^�[��̂��擾
	*@param	�^�O
	*@return �L�����N�^�[
	*		 ���݂��Ȃ����NULL��Ԃ�
	*/
	CCharacter* getAtTag(int tag);

	/**
	*@desc	�L�����N�^�[�̒ǉ�
	*@param	�ǉ�����L�����N�^�[
	*/
	void add(CCharacter* pChara);

	/**
	*@desc	�L�����N�^�[�̏W�܂�̎��t�����Ă��鐔���擾
	*@return ���t�����Ă��鐔
	*/
	int getSize();

};

/**
*desc	�L�����N�^�[�̍H��
*/
class CCharacterPartsFactory
{
public:

	//�f�X�g���N�^
	virtual ~CCharacterPartsFactory() {}

	//�A�j���[�V�����擾
	virtual std::vector<CAnimation*>* getAnimations() = 0;

	//�s���擾
	virtual CMove* getMove() = 0;

	//�d�͎擾
	virtual std::vector<CPhysical*>* getPhysicals() = 0;

	//�A�N�V�����擾
	//virtual std::vector<CAction*>* getActions() = 0;

	//���̎擾
	virtual CBody* getBody() = 0;
};



