#pragma once
#include "../Character.h"
#include "../AttackCharacter/AttackCharacter.h"

//==================================================
//�v���C���[�L�����N�^�[
//	����͍X�V�����������ōs���Ă���̂�
//	���͏����������ōs��
//	���͂ɂ��ړ������Ƃ����J�e�S���ň���
//==================================================
class CPlayerCharacter : public CCharacter
{
public:
	//�R���X�g���N�^
	CPlayerCharacter();

	//�f�X�g���N�^
	~CPlayerCharacter();

	//����������
	bool init() override;

	//CREATE_FUNC(CPlayerCharacter);


	//==================================================================
	//
	//	�萔�Ɋւ���R�[�h�̒ǉ��͂�������
	//
	//==================================================================

	//�v���C���[�̏��
	enum class STATE : int
	{
		STAND		=	0,
		JUMPING		=	0,
		WALK		=	1,
		DAMAGE		=	2,
		FALING		=	3,
		ATTACK		=	4,
		AVOIDANCE	=	5,
		DASH		=	6,
		SUPERJUMP	=	7,
		SUPERFALING	=	8,
	};

	//�v���C���[���s����A�N�V����
	enum class ACTION :int
	{
		JUMP			=	0,
		ATTACK			=	1,
		AVOIDANCE		=	2,
		DAMAGE			=	3
	};

	

	//==================================================================
	//
	//	�����o�Ɋւ���R�[�h�̒ǉ��͂�������
	//
	//==================================================================

	//�X�V����
	void update()override;

	/**
	*	@desc���͏���
	*	@tips �ړ������ŌĂяo��
	*/
	void inputFunc();

	//�ړ�����
	void moveFunc() override;

	//�A�j���[�V��������
	void animationFunc() override;
	
	/*
	//��ʔ͈͒[���菈��
	void endOfScreen() override;
	*/
	//���f����
	void applyFunc() override;
	
	void collision() override;

	//��ԃ`�F�b�N
	void checkState() override;

	/**
	*	@desc�L�����N�^�[�P�̂Ƃ̏Փ˔��菈��
	*	@param	�L�����N�^�[�̃A�h���X
	*	@return true...�Փ˂���
	*/
	bool collision(CCharacter* pChara)override;
	
	//���d�_���[�W�h�~
	void DamageInterval();

	//�W���X�g���(���炷����
	void DodgeInterval();
	\
	//4�������X�V
	void quarterUpdate() override;

	/**
	*@desc	���̈�ƏՓ˂����ۂ̃C�x���g�R�[���o�b�N
	*@param	�}�b�v�`�b�vID
	*		��ʒ[���̍ۂ�0
	*/
	void collisionBottomCallback(int event)override
	{
		//�W�����v���~������
		(*this->m_pActions)[(int)ACTION::JUMP]->stop();
	}
	void collisionTopCallback(int event)override {}
	void collisionRightCallback(int event)override {}
	void collisionLeftCallback(int event)override {}


	/**
	*@desc	�}�b�v�Ƃ̏Փ˔���
	*@return	true...�Փ˂���
	*/
	//bool collisionMap() override;

	/**
	*@desc	�Փ˔����̏���
	*@param	�Փ˂��Ă����L�����N�^�[
	*/
	virtual void hits(CCharacter* pChara)override;
	/*
	//�Q�[���p�b�h���͏������擾
	CInputInterface* pGamepadInput = CInputManager::getInstance()->
		get(ControllerType::Gamepad)->get(0);

	//�L�[�{�[�h���͏������擾
	CInputInterface* pKeybordInput = CInputManager::getInstance()->
		get(ControllerType::Keybord)->get(0);

	*/



	void Allfalse();
	//���q�Ԋu�ݒ�
	void setBeat(int beat);
};