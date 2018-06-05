#include "NotesFactory.h"

//==================================================
//�����킹�H��
//==================================================


std::vector<CAnimation*>* CNotesPartsFactory::getAnimations()
{
	//�A�j���[�V�����f�[�^�Q�̐���
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//�A�j���[�V�����f�[�^�Q�̍쐬
	return new std::vector<CAnimation*>;

}

CMove* CNotesPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CNotesPartsFactory::getPhysicals()
{
	//�K�p�����镨�����Z�쐬
	return new std::vector<CPhysical*>;
}
std::vector<CAction*>* CNotesPartsFactory::getActions()
{
	//�s����A�N�V�����Q���쐬
	return new std::vector<CAction*>;
}

std::vector<CNotes*>* CNotesPartsFactory::getNotes()
{
	//�s���鉹�A�N�V�����Q���쐬
	return new std::vector<CNotes*>;
}

CBody* CNotesPartsFactory::getBody()
{
	return new CBody();
}


CCharacter* CNotesFactory::create(float posX, float posY)
{
	CNotesCharacter* pChara = this->createNotes();

	//==============================================
	//�C���X�^���X�ɒl��ݒ肵�Ă���
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara);

	//this->settingBody(pChara);

	this->settingCollisionAreas(pChara);

	//������
	this->settingInitialize(pChara);

	return pChara;
}


//========================================
//
//���A�j���[�V�����̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CNotesAnimationFactory::settingMove(CNotesCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	//pChara->m_pMove->m_pos.set(posX + 14, posY);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CNotesAnimationFactory::settingTexture(CNotesCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_HATENABLOCK);
}

//�A�j���[�V�����̐ݒ�
void CNotesAnimationFactory::settingAnimations(CNotesCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));
	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(64, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 32, 32));

	pChara->m_pAnimations->push_back(new CChipNotAnimation());
}

//�������Z�̐ݒ�
void CNotesAnimationFactory::settingPhysicals(CNotesCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CNotesAnimationFactory::settingActions(CNotesCharacter* pChara)
{

}

//���A�N�V�����̐ݒ�
void CNotesAnimationFactory::settingNotes(CNotesCharacter* pChara)
{

}



//�Փ˔����Ԃ̐ݒ�
void CNotesAnimationFactory::settingCollisionAreas(CNotesCharacter* pChara)
{
	
}

//�������ݒ�
void CNotesAnimationFactory::settingInitialize(CNotesCharacter* pChara)
{
	//��Ԃ̐ݒ�
	pChara->m_state = 0;
	//�L���t���O�𗧂Ă�
	pChara->m_activeFlag = true;
	//�����Ă���t���O�𗧂Ă�
	pChara->m_isAlive = true;
	//�����Ă���t���O�𗧂Ă�
	//pChara->setPosition(pChara->m_pMove->m_pos);
	//�`�b�v�f�[�^�𔽉f
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}