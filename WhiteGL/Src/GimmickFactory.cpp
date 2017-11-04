#include "GimmickFactory.h"

//==================================================
//�v���C���[�H��
//==================================================


std::vector<CAnimation*>* CGimmickPartsFactory::getAnimations()
{
	//�A�j���[�V�����f�[�^�Q�̐���
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//�A�j���[�V�����f�[�^�Q�̍쐬
	return new std::vector<CAnimation*>;

}

CMove* CGimmickPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CGimmickPartsFactory::getPhysicals()
{
	//�K�p�����镨�����Z�쐬
	return new std::vector<CPhysical*>;
}
std::vector<CAction*>* CGimmickPartsFactory::getActions()
{
	//�s����A�N�V�����Q���쐬
	return new std::vector<CAction*>;
}

CBody* CGimmickPartsFactory::getBody()
{
	return new CBody();
}


CCharacter* CGimmickFactory::create(float posX, float posY)
{
	CGimmickCharacter* pChara = this->createGimmick();

	//==============================================
	//�C���X�^���X�ɒl��ݒ肵�Ă���
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara);

	this->settingBody(pChara);

	this->settingCollisionAreas(pChara);

	//������
	this->settingInitialize(pChara);

	return pChara;
}

//========================================
//
//�����u���b�N�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CDamageBlockLeftFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CDamageBlockLeftFactory::settingTexture(CGimmickCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_DAMAGEBLOCK);
}

//�A�j���[�V�����̐ݒ�
void CDamageBlockLeftFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
}

//�������Z�̐ݒ�
void CDamageBlockLeftFactory::settingPhysicals(CGimmickCharacter* pChara)
{
	
}

//�A�N�V�����̐ݒ�
void CDamageBlockLeftFactory::settingActions(CGimmickCharacter* pChara)
{

}

//���̂̐ݒ�
void CDamageBlockLeftFactory::settingBody(CGimmickCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CDamageBlockLeftFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterLeft();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionLeftCallback);

	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//��̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(pCharacterTerritory);



	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//�������ݒ�
void CDamageBlockLeftFactory::settingInitialize(CGimmickCharacter* pChara)
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


//========================================
//
//�㞙�u���b�N�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CDamageBlockTopFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CDamageBlockTopFactory::settingTexture(CGimmickCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_DAMAGEBLOCK);
}

//�A�j���[�V�����̐ݒ�
void CDamageBlockTopFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));
}

//�������Z�̐ݒ�
void CDamageBlockTopFactory::settingPhysicals(CGimmickCharacter* pChara)
{
	
}

//�A�N�V�����̐ݒ�
void CDamageBlockTopFactory::settingActions(CGimmickCharacter* pChara)
{

}

//���̂̐ݒ�
void CDamageBlockTopFactory::settingBody(CGimmickCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CDamageBlockTopFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterTop();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionTopCallback);

	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//�C�x���g�g���K�[���ĂԂ��
	pCharacterArea->addTerritory(pCharacterTerritory);



	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//�������ݒ�
void CDamageBlockTopFactory::settingInitialize(CGimmickCharacter* pChara)
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


//========================================
//
//�E���u���b�N�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CDamageBlockRightFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CDamageBlockRightFactory::settingTexture(CGimmickCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_DAMAGEBLOCK);
}

//�A�j���[�V�����̐ݒ�
void CDamageBlockRightFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(64, 0, 32, 32));
}

//�������Z�̐ݒ�
void CDamageBlockRightFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CDamageBlockRightFactory::settingActions(CGimmickCharacter* pChara)
{

}

//���̂̐ݒ�
void CDamageBlockRightFactory::settingBody(CGimmickCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CDamageBlockRightFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterRight();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionRightCallback);

	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//��̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//�C�x���g�g���K�[�Ăяo�����
	pCharacterArea->addTerritory(pCharacterTerritory);



	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//�������ݒ�
void CDamageBlockRightFactory::settingInitialize(CGimmickCharacter* pChara)
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


//========================================
//
//�����u���b�N�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CDamageBlockBottomFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CDamageBlockBottomFactory::settingTexture(CGimmickCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_DAMAGEBLOCK);
}

//�A�j���[�V�����̐ݒ�
void CDamageBlockBottomFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 32, 32));
}

//�������Z�̐ݒ�
void CDamageBlockBottomFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CDamageBlockBottomFactory::settingActions(CGimmickCharacter* pChara)
{

}

//���̂̐ݒ�
void CDamageBlockBottomFactory::settingBody(CGimmickCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CDamageBlockBottomFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterBottom();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionBottomCallback);

	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//��̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//�C�x���g�g���K�[���ĂԂ��
	pCharacterArea->addTerritory(pCharacterTerritory);

	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//�������ݒ�
void CDamageBlockBottomFactory::settingInitialize(CGimmickCharacter* pChara)
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



//========================================
//
//��]�u���b�N�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CRollBlockFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CRollBlockFactory::settingTexture(CGimmickCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_ROLLBLOCK);
}

//�A�j���[�V�����̐ݒ�
void CRollBlockFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());
	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));

	//���A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));
	(*pChara->m_pAnimations)[1]->addChipData(new CChip(0, 0, 32, 32));
	(*pChara->m_pAnimations)[1]->addChipData(new CChip(32, 0, 32, 32));
	(*pChara->m_pAnimations)[1]->addChipData(new CChip(64, 0, 32, 32));
	(*pChara->m_pAnimations)[1]->addChipData(new CChip(96, 0, 32, 32));
}

//�������Z�̐ݒ�
void CRollBlockFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CRollBlockFactory::settingActions(CGimmickCharacter* pChara)
{
	pChara->m_pActions->push_back(new CActionRoll());
}

//���̂̐ݒ�
void CRollBlockFactory::settingBody(CGimmickCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CRollBlockFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterBottom();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//��̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//�C�x���g�g���K�[���ĂԂ��
	pCharacterArea->addTerritory(pCharacterTerritory);
	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//�������ݒ�
void CRollBlockFactory::settingInitialize(CGimmickCharacter* pChara)
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

//========================================
//
//������u���b�N�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CTikuwaBlockFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CTikuwaBlockFactory::settingTexture(CGimmickCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_TIKUWABLOCK);
}

//�A�j���[�V�����̐ݒ�
void CTikuwaBlockFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());
	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
}

//�������Z�̐ݒ�
void CTikuwaBlockFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CTikuwaBlockFactory::settingActions(CGimmickCharacter* pChara)
{
	pChara->m_pActions->push_back(new CActionDown());
}

//���̂̐ݒ�
void CTikuwaBlockFactory::settingBody(CGimmickCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CTikuwaBlockFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterTop();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionTopCallback);
	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//�C�x���g�g���K�[���ĂԂ��
	pCharacterArea->addTerritory(pCharacterTerritory);
	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//�������ݒ�
void CTikuwaBlockFactory::settingInitialize(CGimmickCharacter* pChara)
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

//========================================
//
//�����u���b�N�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CNoteBlockFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CNoteBlockFactory::settingTexture(CGimmickCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_NOTEBLOCK);
}

//�A�j���[�V�����̐ݒ�
void CNoteBlockFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipListAnimation(10,true));
	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(64, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 32, 32));

}

//�������Z�̐ݒ�
void CNoteBlockFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CNoteBlockFactory::settingActions(CGimmickCharacter* pChara)
{

}

//���̂̐ݒ�
void CNoteBlockFactory::settingBody(CGimmickCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(0, 0, 0, 0);
}

//�Փ˔����Ԃ̐ݒ�
void CNoteBlockFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterTop();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionTopCallback);
	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//�C�x���g�g���K�[���ĂԂ��
	pCharacterArea->addTerritory(pCharacterTerritory);
	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//�������ݒ�
void CNoteBlockFactory::settingInitialize(CGimmickCharacter* pChara)
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


//========================================
//
//�͂Ăȃu���b�N�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CHatenaBlockFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CHatenaBlockFactory::settingTexture(CGimmickCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_HATENABLOCK);
}

//�A�j���[�V�����̐ݒ�
void CHatenaBlockFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));
	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(64, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 32, 32));

	pChara->m_pAnimations->push_back(new CChipNotAnimation());

	(*pChara->m_pAnimations)[1]->addChipData(new CChip(128, 0, 32, 32));
}

//�������Z�̐ݒ�
void CHatenaBlockFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CHatenaBlockFactory::settingActions(CGimmickCharacter* pChara)
{
	int enemy = rand() % 4;
	switch (enemy)
	{
	case 0:
		enemy = (int)ENEMY_TYPE::KURIBO;
		break;
	case 1:
		enemy = (int)ENEMY_TYPE::NOKONOKO;
		break;
	case 2:
		enemy = (int)ENEMY_TYPE::PATAPATA;
		break;
	case 3:
		enemy = (int)ENEMY_TYPE::KILLERHODAI;
		break;
	default:
		break;
	}
	pChara->m_pActions->push_back(new CActionCreateCharacter(enemy));
}

//���̂̐ݒ�
void CHatenaBlockFactory::settingBody(CGimmickCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CHatenaBlockFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterBottom();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	//���̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//��̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//�C�x���g�g���K�[���ĂԂ��
	pCharacterArea->addTerritory(pCharacterTerritory);
	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//�������ݒ�
void CHatenaBlockFactory::settingInitialize(CGimmickCharacter* pChara)
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

//========================================
//
//���[�v�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CWorpFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX + 14, posY + 10);

	//���x�̐ݒ�
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CWorpFactory::settingTexture(CGimmickCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_WORP);
}

//�A�j���[�V�����̐ݒ�
void CWorpFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));
	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 54, 54));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(54, 0, 54, 54));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(108, 0, 54, 54));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(162, 0, 54, 54));

}

//�������Z�̐ݒ�
void CWorpFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CWorpFactory::settingActions(CGimmickCharacter* pChara)
{
	
}

//���̂̐ݒ�
void CWorpFactory::settingBody(CGimmickCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CWorpFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	CCollisionTerritory* pCharacterTerritoryB = new CCollisionTerritoryCharacterBottom();
	pCharacterTerritoryB->setEventCallback(&CCharacter::collisionBottomCallback);

	//���̃}�b�v�`�b�v�̈��ݒ�
	CCollisionTerritory* pCharacterTerritoryL = new CCollisionTerritoryCharacterLeft();
	pCharacterTerritoryL->setEventCallback(&CCharacter::collisionBottomCallback);

	//��̃}�b�v�`�b�v�̈��ݒ�
	CCollisionTerritory* pCharacterTerritoryT = new CCollisionTerritoryCharacterTop();
	pCharacterTerritoryT->setEventCallback(&CCharacter::collisionBottomCallback);

	//�E�̃}�b�v�`�b�v�̈��ݒ�
	CCollisionTerritory* pCharacterTerritoryR = new CCollisionTerritoryCharacterRight();
	pCharacterTerritoryR->setEventCallback(&CCharacter::collisionBottomCallback);

	//�C�x���g�g���K�[���ĂԂ��
	pCharacterArea->addTerritory(pCharacterTerritoryB);
	pCharacterArea->addTerritory(pCharacterTerritoryL);
	pCharacterArea->addTerritory(pCharacterTerritoryT);
	pCharacterArea->addTerritory(pCharacterTerritoryR);
	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//�������ݒ�
void CWorpFactory::settingInitialize(CGimmickCharacter* pChara)
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





//=======================================================
//�G�����H��Ǘ�
//=======================================================
//���L�C���X�^���X�{�̂̐錾
CGimmickFactoryManager* CGimmickFactoryManager::m_pSharedMgr = NULL;