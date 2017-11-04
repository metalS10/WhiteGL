#include "EnemyBulletFactory.h"

std::vector<CAnimation*>* CEnemyBulletPartsFactory::getAnimations()
{
	//�A�j���[�V�����f�[�^�Q�̐���
	//std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//�A�j���[�V�����f�[�^�Q�̍쐬
	return new std::vector<CAnimation*>;

}

CMove* CEnemyBulletPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CEnemyBulletPartsFactory::getPhysicals()
{
	//�K�p�����镨�����Z�쐬
	return new std::vector<CPhysical*>;
}

std::vector<CAction*>* CEnemyBulletPartsFactory::getActions()
{
	//�s����A�N�V�����Q���쐬
	return new std::vector<CAction*>;
}

CBody* CEnemyBulletPartsFactory::getBody()
{
	return new CBody();
}


CCharacter* CEnemyBulletFactory::create(float posX, float posY, CVec2 vec)
{
	CEnemyBulletCharacter* pChara = this->createEnemyBullet();

	//==============================================
	//�C���X�^���X�ɒl��ݒ肵�Ă���
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara,vec);

	this->settingBody(pChara);

	this->settingCollisionAreas(pChara);

	//������
	this->settingInitialize(pChara);

	this->settingState(pChara);

	return pChara;
}

//========================================
//
//�m�[�}���e�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CNormalEnemyBulletFactory::settingMove(CEnemyBulletCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//���x�̐ݒ�
	//pChara->m_pMove->m_vel.set(0.0f, 0.0f);

}

//�e�N�X�`���̐ݒ�
void CNormalEnemyBulletFactory::settingTexture(CEnemyBulletCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_NORMAL_FIRE);
}

//�A�j���[�V�����̐ݒ�
void CNormalEnemyBulletFactory::settingAnimations(CEnemyBulletCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 16, 16));
}

//�������Z�̐ݒ�
void CNormalEnemyBulletFactory::settingPhysicals(CEnemyBulletCharacter* pChara)
{
	
}

//�A�N�V�����̐ݒ�
void CNormalEnemyBulletFactory::settingActions(CEnemyBulletCharacter* pChara, CVec2 vec)
{
	//�G���S�A�N�V������0�ԂŐݒ�
	pChara->m_pActions->push_back(new CActionMoveStraight(pChara->m_pMove->m_pos, vec.x,vec.y));

}

//���̂̐ݒ�
void CNormalEnemyBulletFactory::settingBody(CEnemyBulletCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-8, 8, 8, -8);
}

//�Փ˔����Ԃ̐ݒ�
void CNormalEnemyBulletFactory::settingCollisionAreas(CEnemyBulletCharacter* pChara)
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

	/*
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
	*/


	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//�������ݒ�
void CNormalEnemyBulletFactory::settingInitialize(CEnemyBulletCharacter* pChara)
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

void CNormalEnemyBulletFactory::settingState(CEnemyBulletCharacter* pChara)
{
	//���R���ł��鎞��
	pChara->m_DeleteTime = 180;

	//�U����
	pChara->m_attackPoint = 10;
}

//========================================
//
//�m�[�}���e���̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CCustomEnemyBulletFactory::settingMove(CEnemyBulletCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//���x�̐ݒ�
	//pChara->m_pMove->m_vel.set(0.0f, 0.0f);

}

//�e�N�X�`���̐ݒ�
void CCustomEnemyBulletFactory::settingTexture(CEnemyBulletCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_NORMAL_FIRE);
}

//�A�j���[�V�����̐ݒ�
void CCustomEnemyBulletFactory::settingAnimations(CEnemyBulletCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0.0f, 0.0f, 16.0f, 16.0f));
}

//�������Z�̐ݒ�
void CCustomEnemyBulletFactory::settingPhysicals(CEnemyBulletCharacter* pChara)
{
	pChara->m_pPhysicals->push_back(new CPhysicalGravity(-0.15f));
}

//�A�N�V�����̐ݒ�
void CCustomEnemyBulletFactory::settingActions(CEnemyBulletCharacter* pChara, CVec2 vec)
{
	//�G���S�A�N�V������0�ԂŐݒ�
	pChara->m_pActions->push_back(new CActionCurve(pChara->m_pMove->m_pos, vec.x,vec.y));

}

//���̂̐ݒ�
void CCustomEnemyBulletFactory::settingBody(CEnemyBulletCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-8, 8, 8, -8);
}

//�Փ˔����Ԃ̐ݒ�
void CCustomEnemyBulletFactory::settingCollisionAreas(CEnemyBulletCharacter* pChara)
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
	/*
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
	*/


	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//�������ݒ�
void CCustomEnemyBulletFactory::settingInitialize(CEnemyBulletCharacter* pChara)
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

void CCustomEnemyBulletFactory::settingState(CEnemyBulletCharacter* pChara)
{
	//���R���ł��鎞��
	pChara->m_DeleteTime = 180;

	//�U����
	pChara->m_attackPoint = 10;
}



//========================================
//
//�t�@�C�A�{�[���̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CFireBallEnemyBulletFactory::settingMove(CEnemyBulletCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//���x�̐ݒ�
	//pChara->m_pMove->m_vel.set(0.0f, 0.0f);

}

//�e�N�X�`���̐ݒ�
void CFireBallEnemyBulletFactory::settingTexture(CEnemyBulletCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_FIREBALL);
}

//�A�j���[�V�����̐ݒ�
void CFireBallEnemyBulletFactory::settingAnimations(CEnemyBulletCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipListAnimation(5, true));



	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0.0f, 0.0f, 16.0f, 16.0f));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(16.0f, 0.0f, 16.0f, 16.0f));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32.0f, 0.0f, 16.0f, 16.0f));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(48.0f, 0.0f, 16.0f, 16.0f));

}

//�������Z�̐ݒ�
void CFireBallEnemyBulletFactory::settingPhysicals(CEnemyBulletCharacter* pChara)
{
	pChara->m_pPhysicals->push_back(new CPhysicalGravity(-0.15f));
}

//�A�N�V�����̐ݒ�
void CFireBallEnemyBulletFactory::settingActions(CEnemyBulletCharacter* pChara, CVec2 vec)
{
	float velX = 3.0f * vec.x;
	pChara->m_pActions->push_back(new CActionJump(4.0f,3.0f));

	pChara->m_pActions->push_back(new CActionMoveStraight(pChara->m_pMove->m_pos, velX));
}

//���̂̐ݒ�
void CFireBallEnemyBulletFactory::settingBody(CEnemyBulletCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-8, 8, 8, -8);
}

//�Փ˔����Ԃ̐ݒ�
void CFireBallEnemyBulletFactory::settingCollisionAreas(CEnemyBulletCharacter* pChara)
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

	/*
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
	*/


	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//�������ݒ�
void CFireBallEnemyBulletFactory::settingInitialize(CEnemyBulletCharacter* pChara)
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

void CFireBallEnemyBulletFactory::settingState(CEnemyBulletCharacter* pChara)
{
	//���R���ł��鎞��
	pChara->m_DeleteTime = 180;

	//�U����
	pChara->m_attackPoint = 1;
}



//=======================================================
//�G�����H��Ǘ�
//=======================================================
//���L�C���X�^���X�{�̂̐錾
CEnemyBulletFactoryManager* CEnemyBulletFactoryManager::m_pSharedMgr = NULL;