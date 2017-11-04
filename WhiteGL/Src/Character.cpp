#include "Character.h"
#include "PlayerCharacter.h"

//�R���X�g���N�^
CCharacter::CCharacter()
{
}

//�f�X�g���N�^
CCharacter::~CCharacter()
{
	SAFE_DELETE(this->m_pBody);
	
	for (CAction* pAction : (*m_pActions))
	{
		SAFE_DELETE(pAction);
	}
	SAFE_DELETE(this->m_pActions);
	
	for (CPhysical* pPhysical : (*m_pPhysicals))
	{
		SAFE_DELETE(pPhysical);
	}
	SAFE_DELETE(this->m_pPhysicals);
	SAFE_DELETE(this->m_pMove);
	for (CAnimation* pAnimation : (*m_pAnimations))
	{
		SAFE_DELETE(pAnimation);
	}
	SAFE_DELETE(this->m_pAnimations);
}

//����������
bool CCharacter::init()
{
	/*
	if (cocos2d::Sprite::init() == false)
	{
		CCLOG("Character�̏������Ɏ��s");
		return false;
	}

	//update()�����o�֐��Ăяo��
	this->scheduleUpdate();
	*/
	return true;
}

//�X�V����
void CCharacter::update()
{
	//�ړ�����
	this->moveFunc();
	
	//�A�j���[�V��������
	this->animationFunc();

	/*
	//��ʔ͈͊O���菈��
	this->endOfScreen();

	//�����Ճ`�b�v�Ƃ̏Փ˔���
	this->collisionMap();
	*/
	//�Փ˔��菈��
	this->collision();

	//��ԃ`�F�b�N
	this->checkState();

	//���f����
	this->applyFunc();

	
}

void CCharacter::setScale(CVec2 scale)
{
	this->m_scale = scale;
}
void CCharacter::setScale(float scaleX,float scaleY)
{
	this->m_scale.x = scaleX;
	this->m_scale.y = scaleY;
}
void CCharacter::setColor(CVec4 color)
{
	this->m_color = color;
}
void CCharacter::setColor(float r, float g, float b, float a)
{
	this->m_color.x = r;
	this->m_color.y = g;
	this->m_color.z = b;
	this->m_color.w = a;
}
void CCharacter::setColor(float opacity)
{
	this->m_color.w = opacity;
}


/**
*@desc	DP�񕜏���
*@param	�񕜒l
*/
void CCharacter::DPHeal(float dp_value)
{
	this->m_denkiPoint += dp_value;
	if (this->m_denkiPoint >= 100)
	{
		this->m_denkiPoint = 100;
	}
}


//==================================================
//�L�����N�^�[�̏W����
//	�V���O���g���������đ��̃t�@�C���ň�����悤�ɂ��Ă���
//==================================================
//���L�C���X�^���X�{��
CCharacterAggregate* CCharacterAggregate::m_pSharedAggre = NULL;

//�R���X�g���N�^
CCharacterAggregate::CCharacterAggregate()
{

}

//�f�X�g���N�^
CCharacterAggregate::~CCharacterAggregate()
{

}

//���L�C���X�^���X�̎擾
CCharacterAggregate* CCharacterAggregate::getInstance()
{
	if (CCharacterAggregate::m_pSharedAggre == NULL)
	{
		CCharacterAggregate::m_pSharedAggre = new CCharacterAggregate();
	}
	return CCharacterAggregate::m_pSharedAggre;
}

//���L�C���X�^���X�̔j��
void CCharacterAggregate::removeInstance()
{
	SAFE_DELETE(CCharacterAggregate::m_pSharedAggre);
}

/**
*@desc	�L�����N�^�[�̏W�܂�̎Q�Ƃ�ݒ�
*@param	�ݒ肷��L�����N�^�[�̏W�܂�̃A�h���X
*/
void CCharacterAggregate::set(std::vector<CCharacter*>* pCharacters)
{
	//���łɐݒ肳��Ă�����ݒ肵�Ȃ��悤�ɂ��Ă���
	if (this->m_pCharacters != NULL)
		return;

	this->m_pCharacters = pCharacters;
}

/**
*@desc	�L�����N�^�[�̏W�܂���擾
*@return �L�����N�^�[�̏W�܂�
*/
std::vector<CCharacter*>* CCharacterAggregate::get()
{
	return this->m_pCharacters;
}

/**
*@desc	�L�����N�^�[��̂��擾
*@param	�Y���ԍ�
*@return �L�����N�^�[
*/
CCharacter* CCharacterAggregate::getAt(int index)
{
	//�ő吔�ȏ�Ȃ�NULL��Ԃ��悤�ɐݒ肵�Ă���
	if (this->m_pCharacters->size() <= index)
		return NULL;

	return(*this->m_pCharacters)[index];
}

/**
*@desc	�^�O����肵�ăL�����N�^�[��̂��擾
*@param	�^�O
*@return �L�����N�^�[
*		���݂��Ȃ����NULL��Ԃ�
*/
CCharacter* CCharacterAggregate::getAtTag(int tag)
{
	for (CCharacter* pChara : (*this -> m_pCharacters))
	{
		if (pChara->m_tag == tag)
		{
			return pChara;
		}
	}
}

/**
*@desc	�L�����N�^�[�̒ǉ�
*@param	�ǉ�����L�����N�^�[
*/
void CCharacterAggregate::add(CCharacter* pChara)
{
	this->m_pCharacters->push_back(pChara);
}

/**
*@desc	�L�����N�^�[�̏W�܂�̎��t�����Ă��鐔���擾
*@return ���t�����Ă��鐔
*/
int CCharacterAggregate::getSize()
{
	return (int)this->m_pCharacters->size();
}

