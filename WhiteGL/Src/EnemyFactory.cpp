#include "EnemyFactory.h"
#include "EnemyBulletCharacter.h"

//�����R�[�h��UTF-8�ɂ���(�G�̖��O)
#pragma execution_character_set("utf-8")

//==================================================
//�v���C���[�H��
//==================================================


std::vector<CAnimation*>* CEnemyPartsFactory::getAnimations()
{
	//�A�j���[�V�����f�[�^�Q�̐���
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//�A�j���[�V�����f�[�^�Q�̍쐬
	return new std::vector<CAnimation*>;

}

CMove* CEnemyPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CEnemyPartsFactory::getPhysicals()
{
	//�K�p�����镨�����Z�쐬
	return new std::vector<CPhysical*>;
}


std::vector<CAction*>* CEnemyPartsFactory::getActions()
{
	//�s����A�N�V�����Q���쐬
	return new std::vector<CAction*>;
}

CBody* CEnemyPartsFactory::getBody()
{
	return new CBody();
}

int CEnemyPartsFactory::getState()
{
	return int();
}


CCharacter* CEnemyFactory::create(float posX, float posY)
{
	CEnemyCharacter* pChara = this->createEnemy();

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

	this->settingState(pChara);

	return pChara;
}

//========================================
//
//�N���{�[�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CKuriboFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//�ړ����x�̐ݒ�
	pChara->m_moveVector.set(-1.0f, 0.0f);
	pChara->m_CharaLaunchVector.set(-1.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CKuriboFactory::settingTexture(CEnemyCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_ENEMY);
}

//�A�j���[�V�����̐ݒ�
void CKuriboFactory::settingAnimations(CEnemyCharacter* pChara)
{

	CAnimation* pAnimation = new CChipListAnimation(10, true);
	pAnimation->addChipData(new CChip(37 * 0, 0, 37, 54));
	pAnimation->addChipData(new CChip(37 * 1, 0, 37, 54));
	pAnimation->addChipData(new CChip(37 * 2, 0, 37, 54));
	pAnimation->addChipData(new CChip(37 * 3, 0, 37, 54));
	pChara->m_pAnimations->push_back(pAnimation);

}

//�������Z�̐ݒ�
void CKuriboFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//�d�͉��Z�̐ݒ�
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//�A�N�V�����̐ݒ�
void CKuriboFactory::settingActions(CEnemyCharacter* pChara)
{
	
	//�G���S�A�N�V������0�ԂŐݒ�(���ԂɋC��t����)
	pChara->m_pActions->push_back(new CActionEnemyDead(2.0f, 6.0f));

	//�G�_���[�W�A�N�V�����ݒ�
	pChara->m_pActions->push_back(new CActionEnemyDamage(5, 1, 3));

	//�e���˃A�N�V������ݒ�
	pChara->m_pActions->push_back(new CActionShotEnemyBullet((int)BULLET_TYPE::NORMAL, 60));
	
}

//���̂̐ݒ�
void CKuriboFactory::settingBody(CEnemyCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-18.5, 27, 18.5, -27);
}

//�Փ˔����Ԃ̐ݒ�
void CKuriboFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//��ʒ[�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//��ʒ[�̏Փ˔����Ԃɗ̈��ݒ�
	//��ʉ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//��ʍ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//��ʒ[�̏Փˋ�Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�
	
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	


	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//�������ݒ�
void CKuriboFactory::settingInitialize(CEnemyCharacter* pChara)
{
	//��Ԃ̐ݒ�
	pChara->m_state = 0;

	//�U���͂̐ݒ�
	pChara->m_attackPoint = 1;

	//�L���t���O�𗧂Ă�
	pChara->m_activeFlag = true;

	pChara->m_eneType = ENEMY_TYPE::KURIBO;

	//�����Ă���t���O�𗧂Ă�
	pChara->m_isAlive = true;

	//�����Ă���t���O�𗧂Ă�
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//�`�b�v�f�[�^�𔽉f
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

//�̗͂̐ݒ�
void CKuriboFactory::settingState(CEnemyCharacter* pChara)
{
	//���O�̐ݒ�
	pChara->m_name = "YMD";		//sorce�u�R�c�E�B���X�v

	pChara->m_maxHitPoint = 3;

	pChara->m_hitPoint = 3;


}

//========================================
//
//�΂̃m�R�m�R�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CGreenNokoNokoFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//���x�̐ݒ�
	pChara->m_moveVector.set(-1.0f, 0.0f);

}

//�e�N�X�`���̐ݒ�
void CGreenNokoNokoFactory::settingTexture(CEnemyCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_NOKONOKO);

	//�������ɐݒ�
	pChara->setScale(-1.0f, 1.0f);
}

//�A�j���[�V�����̐ݒ�
void CGreenNokoNokoFactory::settingAnimations(CEnemyCharacter* pChara)
{
	//(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 54));
	//���s�A�j���[�V����
	CAnimation* pAnimation = new CChipListAnimation(10, true);
	pAnimation->addChipData(new CChip(0, 0, 32, 54));
	pAnimation->addChipData(new CChip(32, 0, 32, 54));
	pChara->m_pAnimations->push_back(pAnimation);

}

//�������Z�̐ݒ�
void CGreenNokoNokoFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//�d�͉��Z�̐ݒ�
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//�A�N�V�����̐ݒ�
void CGreenNokoNokoFactory::settingActions(CEnemyCharacter* pChara)
{
	
	//�G���S�A�N�V������0�ԂŐݒ�
	pChara->m_pActions->push_back(new CActionEnemyDead(2.0f, 6.0f));

	//�G�_���[�W�A�N�V�����ݒ�
	pChara->m_pActions->push_back(new CActionEnemyDamage(5, 1, 3));
	

}

//���̂̐ݒ�
void CGreenNokoNokoFactory::settingBody(CEnemyCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 27, 16, -27);
}

//�Փ˔����Ԃ̐ݒ�
void CGreenNokoNokoFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//��ʒ[�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//��ʒ[�̏Փ˔����Ԃɗ̈��ݒ�
	//��ʉ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//��ʍ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//��ʒ[�̏Փˋ�Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�
	
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	

	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//�������ݒ�
void CGreenNokoNokoFactory::settingInitialize(CEnemyCharacter* pChara)
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

//�̗͂̐ݒ�
void CGreenNokoNokoFactory::settingState(CEnemyCharacter* pChara)
{
	//���O�̐ݒ�
	pChara->m_name = "�m�R�m�R";
	pChara->m_maxHitPoint = 5;

	pChara->m_hitPoint = 5;
}

//========================================
//
//�΂̃p�^�p�^�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CGreenPataPataFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//�ړ����x�̐ݒ�
	pChara->m_moveVector.set(-1.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CGreenPataPataFactory::settingTexture(CEnemyCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_PATAPATA);

	//�e�N�X�`���̃f�t�H���g�̌������������ɐݒ�
	pChara->setScale(-1.0f, 1.0f);

}

//�A�j���[�V�����̐ݒ�
void CGreenPataPataFactory::settingAnimations(CEnemyCharacter* pChara)
{
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));

	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 56, 56));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(56, 0, 56, 56));

}

//�������Z�̐ݒ�
void CGreenPataPataFactory::settingPhysicals(CEnemyCharacter* pChara)
{

}

//�A�N�V�����̐ݒ�
void CGreenPataPataFactory::settingActions(CEnemyCharacter* pChara)
{
	
	//�G���S�A�N�V������0�ԂŐݒ�
	pChara->m_pActions->push_back(new CActionEnemyDeadAndCreateEnemy((int)ENEMY_TYPE::NOKONOKO));

	//�㉺�^���A�N�V�����̎��t��
	//��_�������ʒu�ɐݒ肷��
	pChara->m_pActions->push_back(new CActionUpAndDownMove(pChara->m_pMove->m_pos, 100, 0.02f));

	//�e���˃A�N�V������ݒ�
	pChara->m_pActions->push_back(new CActionShotEnemyBullet((int)BULLET_TYPE::CUSTOM, 60));
	
}

//���̂̐ݒ�
void CGreenPataPataFactory::settingBody(CEnemyCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-28, 28, 28, -28);
}

//�Փ˔����Ԃ̐ݒ�
void CGreenPataPataFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{

}

//�������ݒ�
void CGreenPataPataFactory::settingInitialize(CEnemyCharacter* pChara)
{
	//��Ԃ̐ݒ�
	pChara->m_state = 0;

	//�L���t���O�𗧂Ă�
	pChara->m_activeFlag = true;

	//�����Ă���t���O�𗧂Ă�
	pChara->m_isAlive = true;

	pChara->m_eneType = ENEMY_TYPE::PATAPATA;

	//�����Ă���t���O�𗧂Ă�
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//�`�b�v�f�[�^�𔽉f
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

//�̗͂̐ݒ�
void CGreenPataPataFactory::settingState(CEnemyCharacter* pChara)
{
	//���O�̐ݒ�
	pChara->m_name = "�p�^�p�^";

	pChara->m_maxHitPoint = 5;

	pChara->m_hitPoint = 5;
}

//========================================
//
//�L���[�C��̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CKillerHoudaiFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//���x�̐ݒ�
	pChara->m_moveVector.set(0.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CKillerHoudaiFactory::settingTexture(CEnemyCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_KILLER);

	//�������ɐݒ�
	pChara->setScale(-1.0f, 1.0f);
}

//�A�j���[�V�����̐ݒ�
void CKillerHoudaiFactory::settingAnimations(CEnemyCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());

	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));

}

//�������Z�̐ݒ�
void CKillerHoudaiFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//�d�͉��Z�̐ݒ�
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//�A�N�V�����̐ݒ�
void CKillerHoudaiFactory::settingActions(CEnemyCharacter* pChara)
{
	pChara->m_pActions->push_back(new CActionCreateEnemy((int)ENEMY_TYPE::KILLER));
}

//���̂̐ݒ�
void CKillerHoudaiFactory::settingBody(CEnemyCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CKillerHoudaiFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//��ʒ[�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//��ʒ[�̏Փ˔����Ԃɗ̈��ݒ�
	//��ʉ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//��ʍ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//��ʒ[�̏Փˋ�Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�
	
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	

	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//�������ݒ�
void CKillerHoudaiFactory::settingInitialize(CEnemyCharacter* pChara)
{
	//��Ԃ̐ݒ�
	pChara->m_state = 0;

	//�L���t���O�𗧂Ă�
	pChara->m_activeFlag = true;

	//�����Ă���t���O�𗧂Ă�
	pChara->m_isAlive = true;

	//�����Ă���t���O�𗧂Ă�
	//pChara->setPosition(pChara->m_pMove->m_pos);

	pChara->m_eneType = ENEMY_TYPE::KILLERHODAI;

	//�`�b�v�f�[�^�𔽉f
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

//�̗͂̐ݒ�
void CKillerHoudaiFactory::settingState(CEnemyCharacter* pChara)
{
	//���O�̐ݒ�
	pChara->m_name = "�L���[�C��";

	pChara->m_hitPoint = 1;
}

//========================================
//
//�L���[�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CKillerFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//���x�̐ݒ�
	pChara->m_moveVector.set(-2.0f, 0.0f);
}

//�e�N�X�`���̐ݒ�
void CKillerFactory::settingTexture(CEnemyCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_KILLER);

	//�������ɐݒ�
	pChara->setScale(-1.0f, 1.0f);
}

//�A�j���[�V�����̐ݒ�
void CKillerFactory::settingAnimations(CEnemyCharacter* pChara)
{
	//�����A�j���[�V�����̐ݒ�
	pChara->m_pAnimations->push_back(new CChipNotAnimation());

	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));

}

//�������Z�̐ݒ�
void CKillerFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//�d�͉��Z�̐ݒ�
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//�A�N�V�����̐ݒ�
void CKillerFactory::settingActions(CEnemyCharacter* pChara)
{

	pChara->m_pActions->push_back(new CActionEnemyDead(1.0f, -6.0f));
}

//���̂̐ݒ�
void CKillerFactory::settingBody(CEnemyCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//�Փ˔����Ԃ̐ݒ�
void CKillerFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//��ʒ[�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//��ʒ[�̏Փ˔����Ԃɗ̈��ݒ�
	//��ʉ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//��ʍ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//��ʒ[�̏Փˋ�Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�
	
	
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	

	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//�������ݒ�
void CKillerFactory::settingInitialize(CEnemyCharacter* pChara)
{
	//��Ԃ̐ݒ�
	pChara->m_state = 0;

	//�L���t���O�𗧂Ă�
	pChara->m_activeFlag = true;

	//�����Ă���t���O�𗧂Ă�
	pChara->m_isAlive = true;

	pChara->m_eneType = ENEMY_TYPE::KILLER;

	//�����Ă���t���O�𗧂Ă�
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//�`�b�v�f�[�^�𔽉f
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

//�̗͂̐ݒ�
void CKillerFactory::settingState(CEnemyCharacter* pChara)
{
	//���O�̐ݒ�
	pChara->m_name = "�L���[";

	pChara->m_maxHitPoint = 1;

	pChara->m_hitPoint = 1;
}

//========================================
//
//�g�����Ȃ��ؔn�̐����H��
//
//========================================
//�ړ��f�[�^�̐ݒ�
void CTRoiFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//�����ʒu�̐ݒ�
	pChara->m_pMove->m_pos.set(posX, posY);

	//���x�̐ݒ�
	pChara->m_moveVector.set(-1.0f, 0.0f);

}

//�e�N�X�`���̐ݒ�
void CTRoiFactory::settingTexture(CEnemyCharacter* pChara)
{
	//�e�N�X�`���̐ݒ�
	pChara->setTexture(IMAGE_TROI);

	//�������ɐݒ�
	pChara->setScale(-1.0f, 1.0f);
}

//�A�j���[�V�����̐ݒ�
void CTRoiFactory::settingAnimations(CEnemyCharacter* pChara)
{
	//(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 54));
	//���s�A�j���[�V����
	CAnimation* pAnimation = new CChipNotAnimation();
	pAnimation->addChipData(new CChip(0, 0, 200, 160));
	pChara->m_pAnimations->push_back(pAnimation);

}

//�������Z�̐ݒ�
void CTRoiFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//�d�͉��Z�̐ݒ�
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//�A�N�V�����̐ݒ�
void CTRoiFactory::settingActions(CEnemyCharacter* pChara)
{
	
	//�G���S�A�N�V������0�ԂŐݒ�(���ԂɋC��t����)
	pChara->m_pActions->push_back(new CActionEnemyDead(2.0f, 6.0f));

	//�G�_���[�W�A�N�V�����ݒ�
	pChara->m_pActions->push_back(new CActionEnemyDamage(5, 1, 3));

	//�e���˃A�N�V������ݒ�
	pChara->m_pActions->push_back(new CActionShotEnemySphereBullet((int)BULLET_TYPE::NORMAL, 120));

	//TRoi��p�A�N�V������ݒ�
	pChara->m_pActions->push_back(new CActionTRoi(3, false, 300));

}

//���̂̐ݒ�
void CTRoiFactory::settingBody(CEnemyCharacter* pChara)
{
	//���̃f�[�^�̐ݒ�
	pChara->m_pBody->set(-100, 80, 100, -80);
}

//�Փ˔����Ԃ̐ݒ�
void CTRoiFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//��ʒ[�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//��ʒ[�̏Փ˔����Ԃɗ̈��ݒ�
	//��ʉ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//��ʍ��[�̗̈��ݒ�
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//��ʒ[�̏Փˋ�Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//�}�b�v�`�b�v�Փˋ�Ԃɗ̈��ݒ�

	
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//�E�̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//���̃}�b�v�`�b�v�̈��ݒ�
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	

	//��ʒ[�̏Փ˔����Ԃ����t����
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//�������ݒ�
void CTRoiFactory::settingInitialize(CEnemyCharacter* pChara)
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

//�̗͂̐ݒ�
void CTRoiFactory::settingState(CEnemyCharacter* pChara)
{
	//���O�̐ݒ�
	pChara->m_name = "�g�����Ȃ��ؔn";
	pChara->m_maxHitPoint = 10;

	pChara->m_hitPoint = pChara->m_maxHitPoint;

	pChara->m_eneType = ENEMY_TYPE::TROI;
}

//=======================================================
//�G�����H��Ǘ�
//=======================================================
//���L�C���X�^���X�{�̂̐錾
CEnemyFactoryManager* CEnemyFactoryManager::m_pSharedMgr = NULL;