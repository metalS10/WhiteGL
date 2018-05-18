//=======================================================
//�ǉ��̃C���N���[�h�͂�������
//=======================================================
#include "EnemyBulletCharacter.h"
#include "../../Data/Map/Map.h"

//=======================================================
//�e�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CEnemyBulletCharacter::CEnemyBulletCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::ENEMYBULLET;

	this->m_texID = MS::CMS::getInstance()->getTexID((int)ID_TYPE::ENEMY_ATTACK);

	if (m_texID >= START_ENEMY_BULLET_TEXTURE_NUMBER + 1000)
	{
		m_texID = START_ENEMY_BULLET_TEXTURE_NUMBER;
	}

	MS::CMS::getInstance()->setTexID(m_texID + 1, (int)ID_TYPE::ENEMY_ATTACK);
}
//�f�X�g���N�^
CEnemyBulletCharacter::~CEnemyBulletCharacter()
{
	//CCLOG("unko");
}

//����������
bool CEnemyBulletCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�e�̏������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}

/**
* @desc ����������
* @param �����ʒuX
* @param �����ʒuY
*/
bool CEnemyBulletCharacter::init(float posX, float posY)
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�e�̏������Ɏ��s" << std::endl;
		return false;
	}

	return true;
}

/**
* @desc �ړ�����
*/
void CEnemyBulletCharacter::moveFunc()
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
void CEnemyBulletCharacter::animationFunc()
{
	//�A�j���[�V����
	(*this->m_pAnimations)[m_state]->update();
}
/**
* @desc	��ʔ��菈��
* @tips	�܂��폜�̏������쐬���Ă��Ȃ��̂ŉ�ʉ��Ŏ~�߂鏈���̂ݎ������Ă���
*/
/*
void CEnemyCharacter::endOfScreen()
{
cocos2d::Vec2* pPos = &this->m_pMove->m_pos;
cocos2d::Vec2* pVel = &this->m_pMove->m_vel;
cocos2d::Vec2* pAccele = &this->m_pMove->m_accele;

//��ʉ��Ŏ~�߂�悤�ɂ���
if (pVel->y < 0.0f&&pPos->y + this->m_pBody->m_bottom < WINDOW_BOTTOM)
{
//�ݒ� �C���l
float boundary = (pPos->y + this->m_pBody->m_bottom) - WINDOW_BOTTOM;
pPos->y -= boundary;

//���x�Ɖ����x��0�ɂ���
pVel->y = 0.0f;
pAccele->y = 0.0f;
}
}
*/

/**
*@desc	��ԂƂ̏Փ˔��菈��
*/
void CEnemyBulletCharacter::collision()
{
	//��ԂƂ̏Փ˔�����s��
	for (CCollisionArea* pArea : (*this->m_pCollisionAreas))
	{
		pArea->collision(this);
	}
	//���ׂẴL�����N�^�[�Ƃ̏Փ˔���
	std::vector<CCharacter*>* pCharacters = CCharacterAggregate::getInstance()->get();
	for (CCharacter* pChara : (*pCharacters))
	{
		//�L�����N�^�[1�̂Ƃ̏Փ˔���
		this->collision(pChara);
	}
}

/**
* @desc ��ԃ`�F�b�N
* @tips �l���`�F�b�N���Č��݂̏�Ԃ�ύX����
*/
void CEnemyBulletCharacter::checkState()
{
	//�����̔���
	if (this->m_pMove->m_vel.x != 0)
	{
		if (this->m_pMove->m_vel.x > 0)
		{
			//�E�����ɐݒ�
			this->setScale(1.0f, 1.0f);
		}
		else
		{
			//�������ɐݒ�
			this->setScale(-1.0f, 1.0f);
		}
	}
}

/**
* @desc ���f����
*/
void CEnemyBulletCharacter::applyFunc()
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
bool CEnemyBulletCharacter::collision(CCharacter* pChara)
{
	//�v���C���[��������
	if (pChara->m_charaType == CHARACTER_TYPE::PLAYER)
	{
		//���g�̏Փ˔����`
		CCollisionRect myRect(*this->m_pBody, this->m_pMove->m_pos);

		//�v���C���[�̏Փ˔����`
		CCollisionRect eneRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//�Փ˔���
		if (myRect.collision(&eneRect) == true)
		{
			//�Փ˂�����̔���


			//�Փ˔����̏���
			pChara->hits(this);

			return true;
		}
	}
	return false;
}

/**
*@desc	�Փ˔����̏���
*@param	�Փ˂��Ă����L�����N�^�[
*/
void CEnemyBulletCharacter::hits(CCharacter* pChara)
{
	//����ł������΂�
	if (this->m_isAlive == false)
		return;


	//�e�̎��S�t���O�𗧂Ă�
	//�܂萶���Ă��邩����ł��邩�̃t���O��false������
	this->m_isAlive = false;

	//��������������悤�ɂ���
	this->m_activeFlag = false;

	//�G�L�����N�^�[�̃A�N�V�����ɓK���S�A�N�V���������t����
	//this->m_pActions->push_back(new CActionEnemyDead(2.0f, 6.0f));
	//��
	(*this->m_pActions)[0]->start();



}

//�R���X�g���N�^
CFireBallEnemyBulletCharacter::CFireBallEnemyBulletCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::ENEMYBULLET;
}
//�f�X�g���N�^
CFireBallEnemyBulletCharacter::~CFireBallEnemyBulletCharacter()
{
}

//����������
bool CFireBallEnemyBulletCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�e�̏������Ɏ��s" << std::endl;
		return false;
	}
	return true;
}

/**
* @desc ����������
* @param �����ʒuX
* @param �����ʒuY
*/
bool CFireBallEnemyBulletCharacter::init(float posX, float posY)
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�e�̏������Ɏ��s" << std::endl;
		return false;
	}

	return true;
}