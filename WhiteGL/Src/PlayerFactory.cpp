#include "PlayerFactory.h"
//#include "Model/Character/AttackCharacter/AttackCharacter.h"

//==================================================
//�v���C���[�H��
//==================================================


std::vector<CAnimation*>* CPlayerPartsFactory::getAnimations()
{
	//�A�j���[�V�����f�[�^�Q�̐���
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//�����A�j���[�V�����̐ݒ�
	//m_pAnimations->push_back(new CChipListAnimation(10,true));
	m_pAnimations->push_back(new CNotAnimation());

	//���s�A�j���[�V�����̐ݒ�
	m_pAnimations->push_back(new CListAnimation(10, true));
	//�_���[�W���󂯂����̃A�j���[�V�����̐ݒ�
	m_pAnimations->push_back(new CNotAnimation());
	//�����Ă��鎞�̃A�j���[�V�����̐ݒ�
	m_pAnimations->push_back(new CNotAnimation());
	//�U���A�j���[�V����
	m_pAnimations->push_back(new CListAnimation(10,false));
	m_pAnimations->push_back(new CListAnimation(10, false));
	//������
	m_pAnimations->push_back(new CNotAnimation());
	//�_�b�V���A�j���[�V�����̐ݒ�
	m_pAnimations->push_back(new CListAnimation(10, true));
	//��𒆃W�����v�A�j���[�V�����̐ݒ�
	m_pAnimations->push_back(new CNotAnimation());
	//��𗎂��Ă��鎞�̃A�j���[�V�����̐ݒ�
	m_pAnimations->push_back(new CNotAnimation());

	return m_pAnimations;
}

CMove* CPlayerPartsFactory::getMove()
{
	return new CMove();
}

std::vector<CPhysical*>* CPlayerPartsFactory::getPhysicals()
{
	std::vector<CPhysical*>* m_pPhysicals;

	//�K�������镨�����Z�쐬
	m_pPhysicals = new std::vector<CPhysical*>();
	//�d�͉��Z�̐ݒ�
	m_pPhysicals->push_back(new CPhysicalGravity());
	//���C���Z�̐ݒ�
	//maxspeed
	m_pPhysicals->push_back(new CPhysicalFriction(10));

	return m_pPhysicals;
}
/*
std::vector<CAction*>* CPlayerPartsFactory::getActions()
{
	std::vector<CAction*>* m_pActions;

	//�s����A�N�V�����R���쐬
	m_pActions = new std::vector<CAction*>();
	//�W�����v�A�N�V������ݒ�
	m_pActions->push_back(new CActionJump(4.0f, 3));
	//�e���˃A�N�V������ݒ�
	m_pActions->push_back(new CActionShotBullet((int)ATTACK_TYPE::NORMAL, 20));

	m_pActions->push_back(new CActionShotBullet((int)ATTACK_TYPE::NOR, 20));

	m_pActions->push_back(new CActionShotBullet((int)ATTACK_TYPE::FIREBALL, 20));
	//SuperJump
	m_pActions->push_back(new CActionJump(12.0f, 1));

	return m_pActions;
}
*/
CBody* CPlayerPartsFactory::getBody()
{
	return new CBody();
}



CCharacter* CPlayerFactory::create(float posX,float posY)
{
	CPlayerCharacter* pChara = this->createPlayer();

	//==============================================
	//�C���X�^���X�ɒl��ݒ肵�Ă���
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara);

	this->settingBody(pChara);

	//������
	this->settingInitialize(pChara);

	return pChara;
}


//============================
//��{�v���C���[�H��
//============================

void CBasePlayerFactory::settingMove(CPlayerCharacter* pPlayerCharacter, float posX, float posY)
{
	pPlayerCharacter->m_pMove->m_pos.set(posX, posY);
}

void CBasePlayerFactory::settingTexture(CPlayerCharacter* pPlayerCharacter)
{
	pPlayerCharacter->setTexture(IMAGE_PLAYER);
}

void CBasePlayerFactory::settingAnimations(CPlayerCharacter* pPlayerCharacter)
{
	//�����A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(0, 0, 64, 64));
	/*
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(64, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(64 * 2, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(64 * 3, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(64 * 4, 0, 64, 64));
	*/


	//���s�A�j���[�V�����ɐݒ肷��1���ڂ̃`�b�v�f�[�^�̍쐬
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::WALK]->addChipData(new CChip(64, 0, 64, 64));
	//���s�A�j���[�V�����ɐݒ肷��2���ڂ̃`�b�v�f�[�^�̍쐬
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::WALK]->addChipData(new CChip(128, 0, 64, 64));


	//�_���[�W���󂯂��Ƃ��̃A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::DAMAGE]->addChipData(new CChip(192, 0, 64, 64));

	//�����Ă���Ƃ��̃A�j���[�V�����ɐݒ肷�邽�߂̃`�b�v�f�[�^�̐ݒ�
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::FALING]->addChipData(new CChip(256, 0, 64, 64));

	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::ATTACK]->addChipData(new CChip(192, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::ATTACK]->addChipData(new CChip(256, 0, 64, 64));

	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::NOR]->addChipData(new CChip(192, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::NOR]->addChipData(new CChip(256, 0, 64, 64));
	
	//��𒆂̃`�b�v�f�[�^
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::AVOIDANCE]->addChipData(new CChip(0, 64, 64, 64));

	//�_�b�V���A�j���[�V�����ɐݒ肷��1���ڂ̃`�b�v�f�[�^�̍쐬
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::DASH]->addChipData(new CChip(64, 64, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::DASH]->addChipData(new CChip(128, 64, 64, 64));

	//��𒆃W�����v
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::SUPERJUMP]->addChipData(new CChip(0, 64, 64, 64));

	//��𒆗�����`�b�v�f�[�^
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::SUPERFALING]->addChipData(new CChip(192, 64, 64, 64));


}

void CBasePlayerFactory::settingPhysicals(CPlayerCharacter* pPlayerCharacter)
{

}


void CBasePlayerFactory::settingActions(CPlayerCharacter* pPlayerCharacter)
{

}

void CBasePlayerFactory::settingBody(CPlayerCharacter* pPlayerCharacter)
{
	pPlayerCharacter->m_pBody->set(-32, 32, 32, -32);
}

void CBasePlayerFactory::settingInitialize(CPlayerCharacter* pPlayerCharacter)
{
	//��Ԃ̐ݒ�
	pPlayerCharacter->m_state = (int)CPlayerCharacter::STATE::FALING;

	//�L���t���O�𗧂Ă�
	pPlayerCharacter->m_activeFlag = true;

	/*
	*�v�Z�f�[�^�̂܂܂ŋN�������1�t���[���Y������������̂�
	*���������̍Ō�ɒl��Sprite�ɔ��f����
	*/
	pPlayerCharacter->applyFunc();

	//=================================================
	//�Փ˔����Ԃ̐���
	//=================================================
	pPlayerCharacter->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//=================================================
	//��ʒ[�Փˋ�Ԃ̐���
	//=================================================
	//Body�𑗂�
	CCollisionArea* pEndOfScreeArea = new CCollisionAreaEndOfScreen(pPlayerCharacter->m_pBody);

	//��ʒ[�̏Փ˔����Ԃɗ̈��ݒ�
	//��ʉ��[�̗̈��ݒ�
	CCollisionTerritory* pEndOfScreenBttomTerritory = new CCollisionTerritoryEndOfScreenBottom();

	//��ʉ��[�ƏՓ˂����ۂ̃C�x���g��ݒ�
	pEndOfScreenBttomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);


	//��ʉ��[�̗̈��ݒ�
	pEndOfScreeArea->addTerritory(pEndOfScreenBttomTerritory);

	CCollisionTerritory* pEndOfScreenLeftTerritory = new CCollisionTerritoryEndOfScreenLeft();

	//��ʉ��[�̗̈��ݒ�
	pEndOfScreeArea->addTerritory(pEndOfScreenLeftTerritory);


	//��ʒ[�̏Փˋ�ԂɏՓ˂��s�����̊�_��ݒ�		CollisionArea.h
	//pEndOfScreeArea->addBasePoint(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, cocos2d::Point(0, -32)));


	//��ʒ[�̏Փˋ�Ԃ����t����
	pPlayerCharacter->m_pCollisionAreas->push_back(pEndOfScreeArea);

	//==================================================
	//�}�b�v�Փˋ�Ԃ̐���
	//==================================================
	//Body�𑗂�
	CCollisionArea* pMapArea = new CCollisionAreaMap(pPlayerCharacter->m_pBody);



	
	/*		CollisionArea.h
	//��_�̐ݒ�
	//���̃}�b�v�`�b�v�Փˋ�ԂɏՓ˂��s�����̊�_��ݒ�(���ɗ����Ȃ��悤��x��������Ƃ��炷)
	pMapArea->addBasePoint(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, cocos2d::Point(16, -32)));
	//���̃}�b�v�`�b�v�Փˋ�ԂɏՓ˂��s�����̊�_��ݒ�(���ɗ����Ȃ��悤��x��������Ƃ��炷)
	pMapArea->addBasePoint(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, cocos2d::Point(-16, -32)));
	*/
	//��ʒ[�̏Փˋ�Ԃ����t����
	pPlayerCharacter->m_pCollisionAreas->push_back(pMapArea);

	
}


//���L�C���X�^���X
CPlayerFactoryManager* CPlayerFactoryManager::m_pSharedInstance = NULL;

//�R���X�g���N�^
CPlayerFactoryManager::CPlayerFactoryManager()
{
	//��{�I�ȃv���C���[�H��̐����Ǝ��t��
	this->m_factories.push_back(new CBasePlayerFactory());
}

//�f�X�g���N�^
CPlayerFactoryManager::~CPlayerFactoryManager()
{
	for (CPlayerFactory* pFactory : this->m_factories)
	{
		SAFE_DELETE(pFactory);
	}
}

//���L�C���X�^���X�̎擾
CPlayerFactoryManager* CPlayerFactoryManager::getInstance()
{
	if (CPlayerFactoryManager::m_pSharedInstance == NULL)
	{
		CPlayerFactoryManager::m_pSharedInstance = new CPlayerFactoryManager();
	}
	return CPlayerFactoryManager::m_pSharedInstance;
}

//���L�C���X�^���X�̔j��
void CPlayerFactoryManager::removeInstance()
{
	SAFE_DELETE(CPlayerFactoryManager::m_pSharedInstance);
}

/**
*@desc	�v���C���[�̐���
*@param	�����ʒux
*@param	�����ʒuy
*@return �v���C���[
*/
CCharacter* CPlayerFactoryManager::create(float x, float y)
{
	return this->m_factories[0]->create(x, y);
}

