//=======================================================
//�ǉ��̃C���N���[�h�͂�������
//=======================================================
#include "GimmickCharacter.h"
#include "../../Data/Map/Map.h"

//=======================================================
//�M�~�b�N�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CGimmickCharacter::CGimmickCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::GIMMICK;

	this->m_texID = MS::CMS::getInstance()->getTexID((int)ID_TYPE::GIMMICK);

	if (m_texID >= START_GIMMICK_TEXTURE_NUMBER + 1000)
	{
		m_texID = START_GIMMICK_TEXTURE_NUMBER;
	}

	MS::CMS::getInstance()->setTexID(m_texID + 1, (int)ID_TYPE::GIMMICK);
}
//�f�X�g���N�^
CGimmickCharacter::~CGimmickCharacter()
{
}

//����������
bool CGimmickCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�M�~�b�N�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}

/**
* @desc ����������
* @param �����ʒuX
* @param �����ʒuY
*/
bool CGimmickCharacter::init(float posX, float posY)
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�M�~�b�N�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}

	return true;
}

/**
* @desc �ړ�����
*/
void CGimmickCharacter::moveFunc()
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
void CGimmickCharacter::animationFunc()
{
	//�A�j���[�V����
	(*this->m_pAnimations)[m_state]->update();
}

/**
*@desc	��ԂƂ̏Փ˔��菈��
*/
void CGimmickCharacter::collision()
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
void CGimmickCharacter::checkState()
{
	
}

/**
* @desc ���f����
*/
void CGimmickCharacter::applyFunc()
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
bool CGimmickCharacter::collision(CCharacter* pChara)
{
	return true;
}

/**
*@desc	�Փ˔����̏���
*@param	�Փ˂��Ă����L�����N�^�[
*/
void CGimmickCharacter::hits(CCharacter* pChara)
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


//=======================================================
//���M�~�b�N�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CRollGimmickCharacter::CRollGimmickCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CRollGimmickCharacter::~CRollGimmickCharacter()
{

}
//����������
bool CRollGimmickCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�M�~�b�N�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}

//=======================================================
//������M�~�b�N�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CTikuwaGimmickCharacter::CTikuwaGimmickCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CTikuwaGimmickCharacter::~CTikuwaGimmickCharacter()
{

}
//����������
bool CTikuwaGimmickCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�M�~�b�N�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}


//=======================================================
//�����M�~�b�N�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CNoteGimmickCharacter::CNoteGimmickCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CNoteGimmickCharacter::~CNoteGimmickCharacter()
{

}
//����������
bool CNoteGimmickCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�M�~�b�N�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}


//=======================================================
//�͂Ăȃu���b�N�M�~�b�N�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CHatenaGimmickCharacter::CHatenaGimmickCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CHatenaGimmickCharacter::~CHatenaGimmickCharacter()
{

}
//����������
bool CHatenaGimmickCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�M�~�b�N�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}

//=======================================================
//�͂Ăȃu���b�N�M�~�b�N�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CWorpGimmickCharacter::CWorpGimmickCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CWorpGimmickCharacter::~CWorpGimmickCharacter()
{

}
//����������
bool CWorpGimmickCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�M�~�b�N�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}