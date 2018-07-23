#include "LaunchTrigger.h"
#include "../../Character/Character.h"
#include "../../Factory/EnemyFactory/EnemyFactory.h"
#include "../../Factory/GimmickFactory/GimmickFactory.h"


//===================================================================
//
//�G�o���g���K�[
//	�G�o���f�[�^���g���K�[�ɂ��ēG�o���Ƃ����C�x���g�����s������
//
//===================================================================
//�f�X�g���N�^
CEnemyLaunchTrigger::~CEnemyLaunchTrigger()
{
	SAFE_DELETE(this->m_pLaunchData);
}

/**
*@desc	�C�x���g�����s�ł��邩�ǂ���
*@return true...���s�\
*/
bool CEnemyLaunchTrigger::isTrigger()
{
	if (this->m_pLaunchData == NULL)
	{
		return false;
	}
	return true;
}
/**
*@desc	�ݒ肳��Ă���G�o���f�[�^�����ƂɓG�𐶐�����
*/
CCharacter* CEnemyLaunchTrigger::action()
{
	//�G�𐶐�
	CCharacter* pEnemyChara = CEnemyFactoryManager::getInstance()->create(
		this->m_pLaunchData->m_type,
		this->m_pLaunchData->m_pos.x,
		this->m_pLaunchData->m_pos.y);

	//���˂��I��������ǂ����̃t���O�𗧂Ă�
	this->m_activeFlag = false;

	
	//�G�o���f�[�^��Ԃ�
	//�o���f�[�^�����݂�����
	if (m_pLaunchData != NULL)
	{
		//�G�̉摜������
		CMapManager::getInstance()->getMap()->removeLaunchEnemyBlock(this->m_pLaunchData);
	}

	return pEnemyChara;
}

//===================================================================
//
//�e�o���g���K�[
//	�e�o���f�[�^���g���K�[�ɂ��ēG�o���Ƃ����C�x���g�����s������
//
//===================================================================
//�f�X�g���N�^
CAttackLaunchTrigger::~CAttackLaunchTrigger()
{
	SAFE_DELETE(this->m_pLaunchData);
}

/**
*@desc	�C�x���g�����s�ł��邩�ǂ���
*@return true...���s�\
*/
bool CAttackLaunchTrigger::isTrigger()
{
	if (this->m_pLaunchData == NULL)
	{
		return false;
	}
	return true;
}
/**
*@desc	�ݒ肳��Ă���G�o���f�[�^�����ƂɓG�𐶐�����
*/
CCharacter* CAttackLaunchTrigger::action()
{
	//�G�𐶐�
	CCharacter* pAttackChara = CAttackFactoryManager::getInstance()->create(
		this->m_pLaunchData->m_attacktype,
		this->m_pLaunchData->m_pos.x,
		this->m_pLaunchData->m_pos.y,
		this->m_pLaunchData->m_vec
	);

	//���˂��I��������ǂ����̃t���O�𗧂Ă�
	this->m_activeFlag = false;

	return pAttackChara;
}

//===================================================================
//
//�M�~�b�N�o���g���K�[
//	�M�~�b�N�o���f�[�^���g���K�[�ɂ��ăM�~�b�N�o���Ƃ����C�x���g�����s������
//
//===================================================================
//�f�X�g���N�^
CGimmickLaunchTrigger::~CGimmickLaunchTrigger()
{
	SAFE_DELETE(this->m_pLaunchData);
}

/**
*@desc	�C�x���g�����s�ł��邩�ǂ���
*@return true...���s�\
*/
bool CGimmickLaunchTrigger::isTrigger()
{
	if (this->m_pLaunchData == NULL)
	{
		return false;
	}
	return true;
}
/**
*@desc	�ݒ肳��Ă���G�o���f�[�^�����ƂɓG�𐶐�����
*/
CCharacter* CGimmickLaunchTrigger::action()
{
	//�G�𐶐�
	CCharacter* pGimmickChara = CGimmickFactoryManager::getInstance()->create(
		this->m_pLaunchData->m_type,
		this->m_pLaunchData->m_pos.x,
		this->m_pLaunchData->m_pos.y
	);

	//���˂��I��������ǂ����̃t���O�𗧂Ă�
	this->m_activeFlag = false;


	//�G�o���f�[�^��Ԃ�
	//�o���f�[�^�����݂�����
	if (m_pLaunchData != NULL)
	{
		//�G�̉摜������
		CMapManager::getInstance()->getMap()->removeLaunchGimmickBlock(this->m_pLaunchData);
	}

	return pGimmickChara;
}



//=============================================================
//
//�o���X�P�W���[���[
//	Singleton
//
//=============================================================
//���L�C���X�^���X�{��
CLaunchScheduler* CLaunchScheduler::m_pSharedScheduler = NULL;

//�R���X�g���N�^
CLaunchScheduler::CLaunchScheduler(){}

//���L�C���X�^���X�̎擾
CLaunchScheduler* CLaunchScheduler::getInstance()
{
	if (CLaunchScheduler::m_pSharedScheduler == NULL)
	{
		CLaunchScheduler::m_pSharedScheduler = new CLaunchScheduler();
	}
	return CLaunchScheduler::m_pSharedScheduler;
}

//���L�C���X�^���X�̔j��
void CLaunchScheduler::removeInstance()
{
	SAFE_DELETE(CLaunchScheduler::m_pSharedScheduler);
}

//�f�X�g���N�^
CLaunchScheduler::~CLaunchScheduler()
{
	SAFE_DELETE(this->m_pLauncher);
}

/**
*@desc	���ˑ�̐���
*@param	���ˑ�ɐݒ肷��o������o���X�P�W���[���̃A�h���X
*/
void CLaunchScheduler::createLauncher(std::vector<CLaunchTrigger*>* pLaunchSchedule)
{
	if (this->m_pLauncher == NULL)
	{
		//���ˑ�𐶐����o���X�P�W���[���𔭎ˑ�ɐݒ�
		this->m_pLauncher = new CLauncher(pLaunchSchedule);
	}
}

/**
*@desc	�L�����N�^�[�̏o��
*@param	���t���郌�C���[
*/
void CLaunchScheduler::launchCharacters(CGameEngine& game)
{
	//�X�P�W���[���[�Ɏ��t�����Ă���N���ł���g���K�[�S�Ă��N������
	std::shared_ptr<CLauncher::CLaunchTriggerIterator>itr = this->m_pLauncher->iterator();

	//���̋N���\�ȏo���g���K�[�����邩�ǂ������`�F�b�N
	while (itr->hasNext() == true)
	{
		//�N���\�ȏo���g���K�[���擾���ďo���g���K�[�C�e���[�^�[�����֐i�߂�
		CLaunchTrigger* pTrigger = itr->next();

		//�o���g���K�[���N��
		CCharacter* pChara = pTrigger->action();

		//NULL�`�F�b�N
		if (pChara != NULL)
		{
			//�L�����N�^�[���L�����N�^�[�̏W�܂�Ɏ��t����
			CCharacterAggregate::getInstance()->add(pChara);

			//�L�����N�^�[�����C�����C���[�Ɏ��t����
			//pLayer->addChild(pChara);
			if (pChara->m_charaType == CHARACTER_TYPE::ATTACK)
			{
				game.setupPoly(CVec4(pChara->m_pMove->m_pos.x, pChara->m_pMove->m_pos.y, 32.0f, 32.0f), CVec4(0.0f, 0.0f, 0.0f, 100.0f), 0, POLY_TYPE::QUAD, TAG_PLAYER_ATTACK);
			}
			else
			{
				game.setupTexture(pChara->texPass, TEX_TYPE::PNG, pChara->m_texID, pChara->m_pMove->m_pos, (*pChara->m_pAnimations)[0]->getCurrentChip());
			}
			game.render();

		}
	}
}


//===================================================================
//
//�e�o���g���K�[
//	�e�o���f�[�^���g���K�[�ɂ��ēG�o���Ƃ����C�x���g�����s������
//
//===================================================================
//�f�X�g���N�^
CEnemyBulletLaunchTrigger::~CEnemyBulletLaunchTrigger()
{
	SAFE_DELETE(this->m_pLaunchData);
}

/**
*@desc	�C�x���g�����s�ł��邩�ǂ���
*@return true...���s�\
*/
bool CEnemyBulletLaunchTrigger::isTrigger()
{
	if (this->m_pLaunchData == NULL)
	{
		return false;
	}
	return true;
}
/**
*@desc	�ݒ肳��Ă���G�o���f�[�^�����ƂɓG�𐶐�����
*/
CCharacter* CEnemyBulletLaunchTrigger::action()
{
	//�G�𐶐�
	CCharacter* pBulletChara = CEnemyBulletFactoryManager::getInstance()->create(
		this->m_pLaunchData->m_bullettype,
		this->m_pLaunchData->m_pos.x,
		this->m_pLaunchData->m_pos.y,
		this->m_pLaunchData->m_vec
	);

	//���˂��I��������ǂ����̃t���O�𗧂Ă�
	this->m_activeFlag = false;

	return pBulletChara;
}