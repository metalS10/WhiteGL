#include "AttackFactory.h"

std::vector<CAnimation*>* CAttackPartsFactory::getAnimations()
{
	//�A�j���[�V�����f�[�^�Q�̐���
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//�A�j���[�V�����f�[�^�Q�̍쐬
	return new std::vector<CAnimation*>;

}

CMove* CAttackPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CAttackPartsFactory::getPhysicals()
{
	//�K�p�����镨�����Z�쐬
	return new std::vector<CPhysical*>;
}

std::vector<CAction*>* CAttackPartsFactory::getActions()
{
	//�s����A�N�V�����Q���쐬
	return new std::vector<CAction*>;
}


CBody* CAttackPartsFactory::getBody()
{
	return new CBody();
}

int CAttackPartsFactory::getState()
{
	return int();
}


CCharacter* CAttackFactory::create(float posX, float posY, CVec2 vec)
{
	CAttackCharacter* pChara = this->createAttack();

	//==============================================
	//�C���X�^���X�ɒl��ݒ肵�Ă���
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara, vec);

	this->settingBody(pChara);

	this->settingCollisionAreas(pChara);

	//������
	this->settingInitialize(pChara);

	this->settingState(pChara);

	return pChara;
}

//========================================
//
//�ʏ�U���̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CNormalAttackFactory::settingMove(CAttackCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//���x�̐ݒ�
	//pChara->m_pMove->m_vel.set(0.0f, 0.0f);

}

//�e�N�X�`���̐ݒ�
void CNormalAttackFactory::settingTexture(CAttackCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_NORMALATTACK);
}

//�A�j���[�V�����̐ݒ�
void CNormalAttackFactory::settingAnimations(CAttackCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipListAnimation(5, false));



	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 48, 16));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(48, 0, 48, 16));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 48, 16));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(144, 0, 48, 16));

}

//�������Z�̐ݒ�
void CNormalAttackFactory::settingPhysicals(CAttackCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�

void CNormalAttackFactory::settingActions(CAttackCharacter* pChara, CVec2 vec)
{
	//�U���̈ړ����x
	float velX = 0 * vec.x;
	//�G���S�A�N�V������0�ԂŐݒ�
	//pos�Ɍ��������˔�����player�̐��n���Ă���
	pChara->m_pActions->push_back(new CActionMoveStraight(pChara->m_pMove->m_pos + (vec * 60.0f), velX));
}


//���̂̐ݒ�
void CNormalAttackFactory::settingBody(CAttackCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-8, 8, 8, -8);
}

//�Փ˔����Ԃ̐ݒ�
void CNormalAttackFactory::settingCollisionAreas(CAttackCharacter* pChara)
{
	//==========================================================
	//��ʒ[�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pOutOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//��ʒ[�̏Փ˔����Ԃɗ̈��ݒ�
	//��ʉ��[�̗̈��ݒ�
	CCollisionTerritory* pOutOfScreenBttomTerritory = new CCollisionTerritoryOutOfScreenBottom();
	pOutOfScreenBttomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenBttomTerritory);


	//��ʏ�[�̗̈��ݒ�
	pOutOfScreenArea->addTerritory(new CCollisionTerritoryOutOfScreenTop());

	//��ʉE�[�̗̈��ݒ�
	CCollisionTerritory* pOutOfScreenRightTerritory = new CCollisionTerritoryOutOfScreenRight();
	pOutOfScreenRightTerritory->setEventCallback(&CCharacter::collisionRightCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenRightTerritory);

	//��ʍ��[�̗̈��ݒ�
	CCollisionTerritory* pOutOfScreenLeftTerritory = new CCollisionTerritoryOutOfScreenLeft();
	pOutOfScreenLeftTerritory->setEventCallback(&CCharacter::collisionLeftCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenLeftTerritory);

	//��ʒ[�̏Փˋ�Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pOutOfScreenArea);

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	
	//���̃}�b�v�`�b�v�̈��ݒ�
	CCollisionTerritory* pMapChipBottomTerritory = new CCollisionTerritoryMapChipBottom();
	pMapChipBottomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	pMapArea->addTerritory(pMapChipBottomTerritory);

	//�E�̃}�b�v�`�b�v�̈��ݒ�
	CCollisionTerritory* pMapChipRightTerritory = new CCollisionTerritoryMapChipRight();
	pMapChipRightTerritory->setEventCallback(&CCharacter::collisionRightCallback);
	pMapArea->addTerritory(pMapChipRightTerritory);

	//���̃}�b�v�`�b�v�̈��ݒ�
	CCollisionTerritory* pMapChipLeftTerritory = new CCollisionTerritoryMapChipLeft();
	pMapChipLeftTerritory->setEventCallback(&CCharacter::collisionLeftCallback);
	pMapArea->addTerritory(pMapChipLeftTerritory);



	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
	
}

//�������ݒ�
void CNormalAttackFactory::settingInitialize(CAttackCharacter* pChara)
{
	//��Ԃ̐ݒ�
	pChara->m_state = 0;

	//�L���t���O�𗧂Ă�
	pChara->m_activeFlag = true;

	//�����Ă���t���O�𗧂Ă�
	pChara->m_isAlive = true;

	//�ʒu��ݒ�
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//�`�b�v�f�[�^�𔽉f
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());

}

void CNormalAttackFactory::settingState(CAttackCharacter* pChara)
{
	//���R���ł��鎞��
	pChara->m_DeleteTime = 20;

	//�U����
	pChara->m_attackPoint = 1;
}


//========================================
//
//nor�U���̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CNorAttackFactory::settingMove(CAttackCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//���x�̐ݒ�
	//pChara->m_pMove->m_vel.set(5.0f, 0.0f);

}

//�e�N�X�`���̐ݒ�
void CNorAttackFactory::settingTexture(CAttackCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_GETSUGATENSHO);
}

//�A�j���[�V�����̐ݒ�
void CNorAttackFactory::settingAnimations(CAttackCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipListAnimation(3, false));



	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(84, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(126, 0, 42, 100));

}

//�������Z�̐ݒ�
void CNorAttackFactory::settingPhysicals(CAttackCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CNorAttackFactory::settingActions(CAttackCharacter* pChara, CVec2 vec)
{
	//�U���̈ړ����x
	float velX = 20 * vec.x;
	//�G���S�A�N�V������0�ԂŐݒ�
	//pos�Ɍ��������˔�����player�̐��n���Ă���
	pChara->m_pActions->push_back(new CActionMoveStraight(pChara->m_pMove->m_pos + (vec * 30.0f), velX));

}


//���̂̐ݒ�
void CNorAttackFactory::settingBody(CAttackCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-21, 50, 21, -50);
}

//�Փ˔����Ԃ̐ݒ�
void CNorAttackFactory::settingCollisionAreas(CAttackCharacter* pChara)
{
	//==========================================================
	//��ʒ[�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pOutOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//��ʒ[�̏Փ˔����Ԃɗ̈��ݒ�
	//��ʉ��[�̗̈��ݒ�
	CCollisionTerritory* pOutOfScreenBttomTerritory = new CCollisionTerritoryOutOfScreenBottom();
	pOutOfScreenBttomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenBttomTerritory);


	//��ʏ�[�̗̈��ݒ�
	pOutOfScreenArea->addTerritory(new CCollisionTerritoryOutOfScreenTop());

	//��ʉE�[�̗̈��ݒ�
	CCollisionTerritory* pOutOfScreenRightTerritory = new CCollisionTerritoryOutOfScreenRight();
	pOutOfScreenRightTerritory->setEventCallback(&CCharacter::collisionRightCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenRightTerritory);

	//��ʍ��[�̗̈��ݒ�
	CCollisionTerritory* pOutOfScreenLeftTerritory = new CCollisionTerritoryOutOfScreenLeft();
	pOutOfScreenLeftTerritory->setEventCallback(&CCharacter::collisionLeftCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenLeftTerritory);

	//��ʒ[�̏Փˋ�Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pOutOfScreenArea);

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	
	//���̃}�b�v�`�b�v�̈��ݒ�
	CCollisionTerritory* pMapChipBottomTerritory = new CCollisionTerritoryMapChipBottom();
	pMapChipBottomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	pMapArea->addTerritory(pMapChipBottomTerritory);

	//�E�̃}�b�v�`�b�v�̈��ݒ�
	CCollisionTerritory* pMapChipRightTerritory = new CCollisionTerritoryMapChipRight();
	pMapChipRightTerritory->setEventCallback(&CCharacter::collisionRightCallback);
	pMapArea->addTerritory(pMapChipRightTerritory);

	//���̃}�b�v�`�b�v�̈��ݒ�
	CCollisionTerritory* pMapChipLeftTerritory = new CCollisionTerritoryMapChipLeft();
	pMapChipLeftTerritory->setEventCallback(&CCharacter::collisionLeftCallback);
	pMapArea->addTerritory(pMapChipLeftTerritory);



	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
	
}

//�������ݒ�
void CNorAttackFactory::settingInitialize(CAttackCharacter* pChara)
{
	//��Ԃ̐ݒ�
	pChara->m_state = 0;

	//�L���t���O�𗧂Ă�
	pChara->m_activeFlag = true;

	//�����Ă���t���O�𗧂Ă�
	pChara->m_isAlive = true;

	//�ʒu��ݒ�
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//�`�b�v�f�[�^�𔽉f
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());

}

void CNorAttackFactory::settingState(CAttackCharacter* pChara)
{
	//���R���ł��鎞��
	pChara->m_DeleteTime = 30;

	//�U����
	pChara->m_attackPoint = 10;
}


//=======================================================
//�U�������H��Ǘ�
//=======================================================
//���L�C���X�^���X�{�̂̐錾
CAttackFactoryManager* CAttackFactoryManager::m_pSharedMgr = NULL;