#include "NotesCharacter.h"

//=======================================================
//�M�~�b�N�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CNotesCharacter::CNotesCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::NOTES;

	this->m_texID = MS::CMS::getInstance()->getTexID((int)ID_TYPE::NOTES);

	if (m_texID >= START_NOTES_TEXTURE_NUMBER + 1000)
	{
		m_texID = START_NOTES_TEXTURE_NUMBER;
	}

	MS::CMS::getInstance()->setTexID(m_texID + 1, (int)ID_TYPE::NOTES);
}
//�f�X�g���N�^
CNotesCharacter::~CNotesCharacter()
{
}

//����������
bool CNotesCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "���ɍ��킹�ē����L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}

/**
* @desc ����������
* @param �����ʒuX
* @param �����ʒuY
*/
bool CNotesCharacter::init(float posX, float posY)
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "���ɍ��킹�ē����L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}

	return true;
}

/**
* @desc �ړ�����
*/
void CNotesCharacter::moveFunc()
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
void CNotesCharacter::animationFunc()
{
	//�A�j���[�V����
	(*this->m_pAnimations)[m_state]->update();
}

/**
*@desc	��ԂƂ̏Փ˔��菈��
*/
void CNotesCharacter::collision()
{
	//����ł������΂�
	if (this->m_isAlive == false)
		return;

	//��ԂƂ̏Փ˔�����s��
	for (CCollisionArea* pArea : (*this->m_pCollisionAreas))
	{
		pArea->collision(this);
	}
}

/**
* @desc ��ԃ`�F�b�N
* @tips �l���`�F�b�N���Č��݂̏�Ԃ�ύX����
*/
void CNotesCharacter::checkState()
{

}
//4�������X�V
void CNotesCharacter::quarterUpdate()
{

}

/**
* @desc ���f����
*/
void CNotesCharacter::applyFunc()
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
bool CNotesCharacter::collision(CCharacter* pChara)
{
	return true;
}

/**
*@desc	�Փ˔����̏���
*@param	�Փ˂��Ă����L�����N�^�[
*/
void CNotesCharacter::hits(CCharacter* pChara)
{
	//����ł������΂�
	if (this->m_isAlive == false)
		return;
	if (this->m_isAction == true)
		return;


	for (CCollisionArea* pCollisionArea : (*this->m_pCollisionAreas))
	{
		pCollisionArea->collision(pChara, this);
	}
}