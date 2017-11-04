//=======================================================
//�ǉ��̃C���N���[�h�͂�������
//=======================================================
#include "AttackCharacter.h"
#include "Map.h"

//=======================================================
//�e�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CAttackCharacter::CAttackCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::ATTACK;


}
//�f�X�g���N�^
CAttackCharacter::~CAttackCharacter()
{
	//CCLOG("unko");
}

//����������
bool CAttackCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr<<"�U���̏������Ɏ��s"<<std::endl;
		return false;
	}
	return true;
}

/**
* @desc ����������
* @param �����ʒuX
* @param �����ʒuY
*/
bool CAttackCharacter::init(float posX, float posY)
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�U���������Ɏ��s"<<std::endl;
		return false;
	}

	return true;
}

/**
* @desc �ړ�����
*/
void CAttackCharacter::moveFunc()
{
	//���t�����Ă���A�N�V�����̍X�V
	
	for (CAction* pAction : (*m_pActions))
	{
		pAction->update(this);
	}
	

	//�����v�Z
	for (CPhysical* pPhysical : (*m_pPhysicals))
	{
		pPhysical->update(this->m_pMove);
	}

	//�ړ��v�Z
	this->m_pMove->moveBy();
}



//�A�j���[�V��������
void CAttackCharacter::animationFunc()
{
	//�A�j���[�V����
	(*this->m_pAnimations)[m_state]->update();
}
/**
* @desc	��ʔ��菈��
* @tips	�܂��폜�̏������쐬���Ă��Ȃ��̂ŉ�ʉ��Ŏ~�߂鏈���̂ݎ������Ă���
*/
/*
void CEnemyCharacter::endOfScreen()
{
cocos2d::Vec2* pPos = &this->m_pMove->m_pos;
cocos2d::Vec2* pVel = &this->m_pMove->m_vel;
cocos2d::Vec2* pAccele = &this->m_pMove->m_accele;

//��ʉ��Ŏ~�߂�悤�ɂ���
if (pVel->y < 0.0f&&pPos->y + this->m_pBody->m_bottom < WINDOW_BOTTOM)
{
//�ݒ� �C���l
float boundary = (pPos->y + this->m_pBody->m_bottom) - WINDOW_BOTTOM;
pPos->y -= boundary;

//���x�Ɖ����x��0�ɂ���
pVel->y = 0.0f;
pAccele->y = 0.0f;
}
}
*/

/**
*@desc	��ԂƂ̏Փ˔��菈��
*/
void CAttackCharacter::collision()
{
	//��ԂƂ̏Փ˔�����s��
	for (CCollisionArea* pArea : (*this->m_pCollisionAreas))
	{
		pArea->collision(this);
	}
	//���ׂẴL�����N�^�[�Ƃ̏Փ˔���
	std::vector<CCharacter*>* pCharacters = CCharacterAggregate::getInstance()->get();
	for (CCharacter* pChara : (*pCharacters))
	{
		//�L�����N�^�[1�̂Ƃ̏Փ˔���
		this->collision(pChara);
	}
}

/**
* @desc ��ԃ`�F�b�N
* @tips �l���`�F�b�N���Č��݂̏�Ԃ�ύX����
*/
void CAttackCharacter::checkState()
{
	//�����̔���
	if (this->m_pMove->m_vel.x != 0)
	{
		if (this->m_pMove->m_vel.x > 0)
		{
			//�E�����ɐݒ�
			this->setScale(1.0f, 1.0f);
		}
		else
		{
			//�������ɐݒ�
			this->setScale(-1.0f, 1.0f);
		}
	}
}

/**
* @desc ���f����
*/
void CAttackCharacter::applyFunc()
{
	//�ʒu�f�[�^�𔽉f
	//this->setPosition(this->m_pMove->m_pos);

	//�`�b�v�f�[�^�𔽉f
	//this->setTextureRect((*this->m_pAnimations)[m_state]->getCurrentChip());
}

/**
* @desc �L�����N�^�[1�̂Ƃ̏Փ˔��菈��
* @param �L�����N�^�[�̃A�h���X
* @return true...�Փ˂���
*/
bool CAttackCharacter::collision(CCharacter* pChara)
{
	//�G��������
	if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
	{
		//���g�̏Փ˔����`
		CCollisionRect myRect(*this->m_pBody, this->m_pMove->m_pos);

		//�G�̏Փ˔����`
		CCollisionRect eneRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//�Փ˔���
		if (myRect.collision(&eneRect) == true)
		{
			//�Փ˂�����̔���


			//�Փ˔����̏���
			pChara->hits(this);

			return true;
		}
	}
	return false;
}

/**
*@desc	�Փ˔����̏���
*@param	�Փ˂��Ă����L�����N�^�[
*/
void CAttackCharacter::hits(CCharacter* pChara)
{

}


//�R���X�g���N�^
CFireBallAttackCharacter::CFireBallAttackCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::ATTACK;
}
//�f�X�g���N�^
CFireBallAttackCharacter::~CFireBallAttackCharacter()
{
}

//����������
bool CFireBallAttackCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�e�̏������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}

/**
* @desc ����������
* @param �����ʒuX
* @param �����ʒuY
*/
bool CFireBallAttackCharacter::init(float posX, float posY)
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�v���C���[�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}

	return true;
}