
#include "EnemyCharacter.h"
#include "../../Data/Map/Map.h"

//=======================================================
//�G�L�����N�^�[�̃����o�֐��̃R�[�h�̒ǉ��͂�������
//=======================================================
//�R���X�g���N�^
CEnemyCharacter::CEnemyCharacter()
{
	//�L�����N�^�[�^�C�v��G�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::ENEMY;
	this->m_texID = MS::CMS::getInstance()->getTexID((int)ID_TYPE::ENEMY);

	if (m_texID >= START_ENEMY_TEXTURE_NUMBER + 1000)
	{
		m_texID = START_ENEMY_TEXTURE_NUMBER;
	}

	MS::CMS::getInstance()->setTexID(m_texID + 1, (int)ID_TYPE::ENEMY);
}
//�f�X�g���N�^
CEnemyCharacter::~CEnemyCharacter()
{
}

//����������
bool CEnemyCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�G�l�~�\�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}

	return true;
}

/**
* @desc ����������
* @param �����ʒuX
* @param �����ʒuY
*/
bool CEnemyCharacter::init(float posX, float posY)
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		std::cerr << "�G�l�~�\�L�����N�^�[�������Ɏ��s" << std::endl;
		return false;
	}

	return true;
}

/**
* @desc �ړ�����
*/
void CEnemyCharacter::moveFunc()
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

	//���d�_���[�W�h�~
	this->DamageInterval();

	if (this->m_eneType == ENEMY_TYPE::TROI && !Troi)
	{
		//this->runAction(cocos2d::TintTo::create(0.01f, 0, 0, 0));
		Troi = true;
	}
	if (this->m_enemyDeadOneFrame == 1)
	{
		pPlayerChara->m_pNowEnemy = NULL;
	}
}

//�A�j���[�V��������
void CEnemyCharacter::animationFunc()
{
	//�A�j���[�V����
	(*this->m_pAnimations)[m_state]->update();
}

/**
*@desc	��ԂƂ̏Փ˔��菈��
*/
void CEnemyCharacter::collision()
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
void CEnemyCharacter::checkState()
{
	if (!this->m_isDamage)
	{
		//�����̔���
		if (this->m_pMove->m_vel.x != 0)
		{
			if (this->m_pMove->m_vel.x > 0)
			{
				//�E�����ɐݒ�
				this->setScale(1.0f, 1.0f);
				if(this->m_moveVector.x >= 0)
					this->m_CharaLaunchVector.set(1.0f,0.0f);
				else
					this->m_CharaLaunchVector.set(-1.0f, 0.0f);
			}
			else
			{
				//�������ɐݒ�
				this->setScale(-1.0f, 1.0f);
				if (this->m_moveVector.x >= 0)
					this->m_CharaLaunchVector.set(1.0f, 0.0f);
				else
					this->m_CharaLaunchVector.set(-1.0f, 0.0f);
			}
		}
	}

	//y�ړ����x��0�Ȃ�
	if (this->m_pMove->m_vel.y == 0.0f)
	{
		Groundcount++;
		if (Groundcount == 2)
		{
			if (!this->m_isGround)
			{
				this->m_pMove->m_vel.set(this->m_moveVector);
				this->m_isDamage = false;
			}
			//�n�ʂɂ��Ă���
			this->m_isGround = true;
			Groundcount = 0;
		}
	}
	else if (this->m_pMove->m_vel.y > 0.0f)
	{
		//�n�ʂɂ��Ă��Ȃ�
		this->m_isGround = false;
		Groundcount = 0;
	}
	else if (this->m_pMove->m_vel.y < 0.0f)
	{
		//�n�ʂɂ��Ă��Ȃ�
		this->m_isGround = false;
		Groundcount = 0;
	}
}

/**
* @desc ���f����
*/
void CEnemyCharacter::applyFunc()
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
bool CEnemyCharacter::collision(CCharacter* pChara)
{
	return true;
}

/**
*@desc	�Փ˔����̏���
*@param	�Փ˂��Ă����L�����N�^�[
*/
void CEnemyCharacter::hits(CCharacter* pChara)
{
	//����ł������΂�
	if (this->m_isAlive == false)
		return;


	if (pChara->m_charaType == CHARACTER_TYPE::PLAYER)
	{

		this->hitsPlayerCharacter(pChara);
	}
	if(pChara->m_charaType == CHARACTER_TYPE::ATTACK)
	{
		this->hitsBulletCharacter(pChara);
	}
}

void CEnemyCharacter::hitsPlayerCharacter( CCharacter* pChara )
{
	//�v���C���[�̑����̈ʒu
	float playerFeetPosY = pChara->m_pMove->m_pos.y + pChara->m_pBody->m_bottom;

	//�G�̒��S�ʒu
	float enePosY = this->m_pMove->m_pos.y;

	//�G���ォ�ǂ���
	float posY = playerFeetPosY - enePosY;

	if (posY > 0.0f)
	{
		/*
		//�ゾ����
		std::cerr << u8"����" << std::endl;

		//�G�̎��S�t���O�𗧂Ă�
		//�܂萶���Ă��邩����ł��邩�̃t���O��false������
		this->m_isAlive = false;

		//�G�L�����N�^�[�̃A�N�V�����ɓK���S�A�N�V���������t����
		//this->m_pActions->push_back(new CActionEnemyDead(2.0f, 6.0f));
		//��
		(*this->m_pActions)[0]->start();


		//==============================================================
		//�߂荞�񂾕��߂�
		//==============================================================
		//�߂荞�񂾕��̌v�Z
		float boundary = (this->m_pMove->m_pos.y + this->m_pBody->m_top) - playerFeetPosY;

		//�ŏI�I�ɖ߂��l
		pChara->m_pMove->m_pos.y -= boundary;

		//==============================================================
		//�W�����v�A�N�V�����̍ċN��
		//==============================================================
		//�W�����v�A�N�V�����̍ċN��
		(*pChara->m_pActions)[0]->restart(pChara);
		*/
		
	}
	else
	{
		if(this->m_isAlive)
			pChara->hits(this);
	}
}

void CEnemyCharacter::hitsBulletCharacter(CCharacter* pChara)
{
	//�v���C���[���Q�b�g
	pPlayerChara = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);

	//�v���C���[�̍��̓G�Ɏ��g���Z�b�g
	pPlayerChara->m_pNowEnemy = this;

	if (this->InvisibleFrame <= 0)
	{
		//�_���[�W�̃t���O��true�ɂ���
		this->m_isDamage = true;
		//�̗͂����炷
		this->m_hitPoint -= pChara->m_attackPoint;

		//�L���[�Ƀ_���[�W�A�N�V�����͂Ȃ��̂�
		if (this->m_eneType != ENEMY_TYPE::TROI)
		{
			//�_���[�W�A�N�V����
			(*this->m_pActions)[1]->restart(this);
		}
		else if (this->m_eneType == ENEMY_TYPE::TROI && !pPlayerChara->m_stageClear)
		{
			/*
			//�Ԃ��_��
			cocos2d::Sequence* sequence = cocos2d::Sequence::create(cocos2d::TintTo::create(0.05f, 255, 0, 0), cocos2d::TintTo::create(0.1f, 0, 0, 0),NULL);
			this->runAction(sequence);
			*/
			//���d�_���[�W�h�~
			this->InvisibleFrame = 10;

		}
		//�G�̗͉̑���
		//CCLOG("%i", m_hitPoint);


	//HP��0�ȉ��Ȃ玀
		if (this->m_hitPoint <= 0)
		{
			//�_���[�W�̃t���O��true�ɂ���
			this->m_isDamage = true;

			if (this->m_eneType == ENEMY_TYPE::TROI)
			{
				this->m_pMove->m_vel = CVec2(0, 0);

				/*
				//�����Ȃ�A������A�E��
				cocos2d::Sequence* sequence = cocos2d::Sequence::create(cocos2d::TintTo::create(0.5f, 255,0,0),cocos2d::FadeOut::create(0.3),cocos2d::CallFunc::create(this,callfunc_selector(CEnemyCharacter::isDeath)), NULL);
				this->runAction(sequence);
				*/
				this->isDeath();
				//�X�e�[�W�N���A��true
				pPlayerChara->m_stageClear = true;

				this->InvisibleFrame = 60;
			}
			else
			{
				//�G�̎��S�t���O�𗧂Ă�
				//�܂萶���Ă��邩����ł��邩�̃t���O��false������
				this->m_isAlive = false;
				(*this->m_pActions)[0]->start();
			}
			this->m_enemyDeadOneFrame++;

		}
		CGameEngine& game = MS::CMS::getInstance()->getGame();
		game.HitStop(3.0f);
		CScene* scene = MS::CMS::getInstance()->getScene();
		scene->SetCameraShake(10.0f,5,2);
	}

	//�e������
	//pChara->m_activeFlag = false;

}

void CEnemyCharacter::isDeath()
{
	this->m_isAlive = false;
}


//���d�_���[�W�h�~�p
void CEnemyCharacter::DamageInterval()
{
	if (this->InvisibleFrame <= 0)
	{
		this->InvisibleFrame = 0;
		//�C���r�W�u��false
		this->m_isInvisible = false;
	}
	//�ȉ�����Ȃ����
	else if (!this->InvisibleFrame <= 0)
	{
		this->InvisibleFrame--;
	}
}
