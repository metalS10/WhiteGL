#include "ActionController.h"
#include "../Character.h"
#include "../LaunchData.h"
#include "../LaunchTrigger.h"



/*
*	@desc �X�V����(�W�����v�ړ��v�Z)
*	@param �W�����v����Ώۂ̃L�����N�^�[
*	@tips ��L�[�������ꂽ�炱�̊֐����Ăяo��
*/
void CActionJump::update(CCharacter* pChara)
{
	if (this->m_isJumping == true)
	{
		//�W�����v��

		//�W�����v�u�[�X�g�����炵�Ă���
		this->m_currentBoost--;

		//�W�����v�u�[�X�g��0��菬�����ꍇ
		if ((this->m_isJumpStart == false) || (this->m_currentBoost < 0))
		{
			//�����x��0�ɂ���
			pChara->m_pMove->m_accele.y = 0.0f;

			pChara->m_isGround = false;
		}
	}
	else if (this->m_isJumpStart == true)
	{
		//�W�����v�J�n

		//y���̉����x�ɒl��ݒ�
		pChara->m_pMove->m_accele.y = this->m_accele;
		//���t���[���A�����x��K�p�����邩��ݒ�
		this->m_currentBoost = this->m_boost;
		//�W�����v�t���O��true�ɂ���
		this->m_isJumping = true;
	}
	this->m_isJumpStart = false;
}

/**
*@desc	�A�N�V�����̍ċN��
*@param	�ċN������L�����N�^�[
*@tips	�L�����N�^�[��Y�����̃��Z�b�g���s��
*/
void CActionJump::restart(CCharacter* pChara)
{
	//Y�����̑��x�h�ߑ��x�̃��Z�b�g
	pChara->m_pMove->m_vel.y = 0.0f;
	pChara->m_pMove->m_accele.y = 0.0f;

	//�A�N�V�����̒�~
	this->stop();

	//�A�N�V�����̊J�n
	this->start();
}


/*
*	@desc �X�V����(����ړ��v�Z)
*	@param �������Ώۂ̃L�����N�^�[
*	@tips ����L�[�������ꂽ�炱�̊֐����Ăяo��
*/
void CActionAvoidance::update(CCharacter* pChara)
{
	if (this->m_isAvoidanceStart == true && m_isAvoidance == false)
	{

		//�ő呬�x�̕ύX
		(*pChara->m_pPhysicals)[1]->SetMaxSpeed(m_accele, 5.0f);
		//x���̈ړ����x�ɒl��ݒ�
		pChara->m_pMove->m_vel.x = this->m_accele * pChara->m_CharaLaunchVector.x;
		pChara->m_pMove->m_vel.y = 0;
		pChara->m_isAvoidance = true;
		//����t���O��true�ɂ���
		this->m_isAvoidance = true;
	}
	else if(m_isAvoidance)
	{
		//�J�E���^�[���C���^�[�o���ɓ��B������
		m_counter++;
		//����s���̃C���^�[�o��
		if (m_counter >= m_avoidanceIntarval)
		{
			pChara->m_pMove->m_vel.x = 0;
			pChara->m_isAvoidance = false;
			(*pChara->m_pPhysicals)[1]->SetMaxSpeed(10.0f, 0.5f);
			//�������\�C���^�[�o��
			if (m_counter >= m_intarval)
			{

				m_counter = 0;
				//�A�N�V������~
				m_isAvoidance = false;
			}
		}
		else
		{
			//���ɉ���s����
			pChara->m_pMove->m_vel.x = this->m_accele * pChara->m_CharaLaunchVector.x;
			pChara->m_pMove->m_vel.y = 0;

		}
	}
	this->m_isAvoidanceStart = false;
}

/**
*@desc	�A�N�V�����̍ċN��
*@param	�ċN������L�����N�^�[
*@tips	�L�����N�^�[��Y�����̃��Z�b�g���s��
*/
void CActionAvoidance::restart(CCharacter* pChara)
{
	//Y�����̑��x�h�ߑ��x�̃��Z�b�g
	pChara->m_pMove->m_vel.x = 0.0f;
	pChara->m_pMove->m_accele.x = 0.0f;

	//�A�N�V�����̒�~
	this->stop();

	//�A�N�V�����̊J�n
	this->start();
}



//=====================================================
//�G���S�A�N�V����
//=====================================================
/**
*@desc	�R���X�g���N�^
*@param	���ړ����x
*@param	���˂鑬�x
*/
CActionEnemyDead::CActionEnemyDead(float velX,float leapVelY)
	:m_velX(velX), m_leapVelY(leapVelY)
{
	//�R���X�g���N�^
	//this->start();
}

/**
*@desc	�A�N�V�����J�n
*/
void CActionEnemyDead::start()
{
	//�A�N�V�����J�n
	this->m_isStart = true;
}

/**
*@desc	�X�V����
*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
*/
void CActionEnemyDead::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//�A�N�V������

		//��ʂ̊O�ɏo����
		if (pChara->m_pMove->m_pos.y + pChara->m_pBody->m_top < WINDOW_BOTTOM)
		{
			//�A�N�V�������~
			this->stop();

			//�L���t���O��������
			pChara->m_activeFlag = false;
		}
	}
	else if (this->m_isStart == true)
	{
		//�A�N�V�����̊J�n

		//�A�N�V�������̃t���O�𗧂Ă�
		this->m_inAction = true;

		//���˂鑬�x�Ɖ��ړ����x��ݒ肷��
		pChara->m_pMove->m_vel.set(this->m_velX * - pChara->m_moveVector.x, this->m_leapVelY);

		//�A�N�V�����J�n�t���O�͉�����
		this->m_isStart = false;
	}
}

/**
*@desc	�A�N�V�����I��
*/
void CActionEnemyDead::stop()
{
	//�A�N�V�������t���O�����낷
	this->m_inAction = false;
}

//========================================================
//�㉺�ړ��A�N�V����
//========================================================
/**
*@desc	�R���X�g���N�^
*@param	��ʒu
*@param	���a
*@param	���x
*/
CActionUpAndDownMove::CActionUpAndDownMove(Point basePos, float radius, float vel)
	:m_basePos(basePos), m_radius(radius), m_vel(vel)
{
	this->start();
}

/**
*@desc	�A�N�V�����J�n
*/
void CActionUpAndDownMove::start()
{
	this->m_inAction = true;
}

/*
*@desc	�X�V����
*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
*/
void CActionUpAndDownMove::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//X�ʒu�͊�_�̂܂�
		pChara->m_pMove->m_pos.x = this->m_basePos.x;
		//Y�ʒu��sin�J�[�u�^��
		pChara->m_pMove->m_pos.y = sinf(this->m_counter)* this->m_radius + this->m_basePos.y;

		//�J�E���^�[�𑬓x���X�V
		this->m_counter += this->m_vel;
	}
}

/**
*@desc	�A�N�V�����I��
*/
void CActionUpAndDownMove::stop()
{
	this->m_inAction = false;
}

//===================================================
//�G���S�A�N�V������Ɏ��S�ʒu����G���o��������
//===================================================
/**
*@desc	�R���X�g���N�^
*@param	�o��������G�̃^�C�v
*/
CActionEnemyDeadAndCreateEnemy::CActionEnemyDeadAndCreateEnemy(int type)
	:m_type(type){}

/**
*@desc	�A�N�V�����J�n
*/
void CActionEnemyDeadAndCreateEnemy::start()
{
	this->m_inAction = true;
}

/*
*@desc	�X�V����
*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
*/
void CActionEnemyDeadAndCreateEnemy::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//�L���t���O�����낷
		pChara->m_activeFlag = false;

		//��\���ɂ���
		pChara->setColor(0);


		//==============================
		//�����ł͏o���̏����o���g���K�[�Ƃ���
		//�o���X�P�W���[���Ɏ��t���邾��
		//==============================
		
		
		//�G�o���f�[�^(�o���̏��)�̐���
		CEnemyLaunchData* pLaunchData = new CEnemyLaunchData(
			(ENEMY_TYPE)this->m_type,
			pChara->m_pMove->m_pos
		);

		//�o���g���K�[�𐶐����A�G�o���f�[�^��ݒ�
		CEnemyLaunchTrigger* pTrigger = new CEnemyLaunchTrigger(pLaunchData);

		//�o���g���K�[���o���X�P�W���[���Ƃ��Ēǉ�����
		CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);


		//�A�N�V�������Ƀt���O�����낷
		this->m_inAction = false;
		
	}
}

/**
*@desc	�A�N�V�����I��
*/
void CActionEnemyDeadAndCreateEnemy::stop()
{
	this->m_inAction = false;
}

//===================================================
//�G�����A�N�V����
//===================================================
/**
*@desc	�R���X�g���N�^
*@param	�o��������G�̃^�C�v
*/
CActionCreateEnemy::CActionCreateEnemy(int type)
	:m_type(type) {}

/**
*@desc	�A�N�V�����J�n
*/
void CActionCreateEnemy::start()
{
	this->m_inAction = true;
}

/*
*@desc	�X�V����
*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
*/
void CActionCreateEnemy::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//==============================
		//�����ł͏o���̏����o���g���K�[�Ƃ���
		//�o���X�P�W���[���Ɏ��t���邾��
		//==============================

		this->m_ShotCount++;

		if (this->m_ShotCount == 60)
		{
			//�G�o���f�[�^(�o���̏��)�̐���
			CEnemyLaunchData* pLaunchData = new CEnemyLaunchData(
				(ENEMY_TYPE)this->m_type,
				pChara->m_pMove->m_pos
			);

			//�o���g���K�[�𐶐����A�G�o���f�[�^��ݒ�
			CEnemyLaunchTrigger* pTrigger = new CEnemyLaunchTrigger(pLaunchData);

			//�o���g���K�[���o���X�P�W���[���Ƃ��Ēǉ�����
			CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);

			this->m_ShotCount = 0;
		}
	}
}

/**
*@desc	�A�N�V�����I��
*/
void CActionCreateEnemy::stop()
{
	this->m_inAction = false;
}


//========================================================
//�܂������ړ��A�N�V����
//========================================================
/**
*@desc	�R���X�g���N�^
*@param	��ʒu
*@param	���x
*/
CActionMoveStraight::CActionMoveStraight(Point basePos, float vel)
	:m_basePos(basePos), m_vel(vel)
{
	this->start();
}

CActionMoveStraight::CActionMoveStraight(Point basePos, float velX,float velY)
	: m_basePos(basePos), m_vel(velX),m_velY(velY)
{
	this->start();
}

/**
*@desc	�A�N�V�����J�n
*/
void CActionMoveStraight::start()
{
	this->m_inAction = true;
}

/*
*@desc	�X�V����
*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
*/
void CActionMoveStraight::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		
		//�ʒu�͊�_�̂܂�
		pChara->m_pMove->m_pos.y = this->m_basePos.y;
		pChara->m_pMove->m_pos.x = this->m_basePos.x;

		//X�ʒu�͂܂������ړ�
		pChara->m_pMove->m_vel.set(this->m_vel, this->m_velY);


	}
	this->m_inAction = false;

	//�U�����肪�����ŏ����邽�߂̃R�[�h
	if (pChara->m_DeleteTime != -1)
	{
		
		deleteCount++;
		if (deleteCount >= pChara->m_DeleteTime)
		{
			pChara->m_activeFlag = false;
			deleteCount = 0;
		}
	}

}

/**
*@desc	�A�N�V�����I��
*/
void CActionMoveStraight::stop()
{
	this->m_inAction = false;
}


/**
*�e���˃A�N�V����
*/
void CActionShotBullet::update(CCharacter* pChara)
{
	if (this->m_inAction== true)
	{
		//�A�N�V������true�ɂȂ��
		
		/**
		*�e�𔭎�
		*/
		//�Ԋu���u���Ă��ԁv�Ȃ�
		if (this->m_shotCount == 0)
		{
			//�܂������e��ł�
			//CCharacter* bulletChara = (CBulletCharacter*)CBulletFactoryManager::getInstance()->create(BULLET_TYPE::NORMAL, pChara->m_pMove->m_pos.x, pChara->m_pMove->m_pos.y, pChara->m_shotLaunchVector);

			//CCharacterAggregate�Ƀv���C���[��ǉ�
			//�G�o���f�[�^���쐬
			//CBulletLaunchData* pLaunchData = new CBulletLaunchData(BULLET_TYPE::NORMAL, pChara->m_pMove->m_pos, pChara->m_shotLaunchVector);


			CAttackLaunchData* pLaunchData = new CAttackLaunchData(
				(ATTACK_TYPE)this->m_bulletType,
				pChara->m_pMove->m_pos,
				pChara->m_CharaLaunchVector
			);


			CAttackLaunchTrigger* pTrigger = new CAttackLaunchTrigger(pLaunchData);

			CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);

			this->m_shotCount = this->m_interval;

		}
		//�łĂȂ��Ȃ�
		else
		{
			//�Ԋu�������Ă���(0�ɂȂ�܂�)
			this->m_shotCount--;

			if (this->m_shotCount == 0)
			{
				pChara->m_isAttack1 = false;
				this->m_inAction = false;
			}
		}


	}
}

//========================================================
//��ɂ������ė�����A�N�V����(�d��)
//========================================================
/**
*@desc	�R���X�g���N�^
*@param	��ʒu
*@param	���x
*/
CActionCurve::CActionCurve(Point basePos, float vel)
	:m_basePos(basePos), m_vel(vel)
{
	this->start();
}
CActionCurve::CActionCurve(Point basePos, float velX,float velY)
	: m_basePos(basePos), m_vel(velX),m_velY(velY)
{
	this->start();
}

/**
*@desc	�A�N�V�����J�n
*/
void CActionCurve::start()
{
	this->m_inAction = true;
}

/*
*@desc	�X�V����
*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
*/
void CActionCurve::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{

		//�ʒu�͊�_�̂܂�
		pChara->m_pMove->m_pos.y = this->m_basePos.y;
		pChara->m_pMove->m_pos.x = this->m_basePos.x;

		//�|�[���ƈړ�
		pChara->m_pMove->m_vel.set(this->m_vel, this->m_velY);


	}
	this->m_inAction = false;

}

/**
*@desc	�A�N�V�����I��
*/
void CActionCurve::stop()
{
	this->m_inAction = false;
}


/**
*@desc	�A�N�V�����J�n
*/
void CActionRoll::start()
{
	this->m_isStart = true;
}

/*
*@desc	�X�V����
*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
*/
void CActionRoll::update(CCharacter* pChara)
{
	if (this->m_counter > 0 && this->m_isStart == true)
	{
		this->m_counter--;

		//true�ɂ��邱�Ƃ�hits��collisionArea��ݒ肷�镔����return����
		pChara->m_isAction = true;
		//1�ɂ��邱�ƂŃA�j���[�V��������
		pChara->m_state = 1;

		if (this->m_counter <= 0)
		{
			pChara->m_isAction = false;
			pChara->m_state = 0;
			this->stop();
		}
		

	}

}

/**
*@desc	�A�N�V�����I��
*/
void CActionRoll::stop()
{
	this->m_isStart = false;
	this->m_counter = this->m_interval;
}


//=======================================================
//������A�N�V����
//=======================================================
/**
*@desc	�A�N�V�����J�n
*/
void CActionDown::start()
{
	this->m_isStart = true;
}

/*
*@desc	�X�V����
*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
*/
void CActionDown::update(CCharacter* pChara)
{
	if (this->m_isStart == true)
	{
		this->m_counter--;

		if (this->m_counter <= 0)
		{
			//�d�͂����t����
			pChara->m_pPhysicals->push_back(new CPhysicalGravity());
			this->stop();
		}


	}

}

/**
*@desc	�A�N�V�����I��
*/
void CActionDown::stop()
{
	this->m_isStart = false;
}


//===============================================================
//�G�����u���b�N�p�A�N�V����
//===============================================================
/**
*@desc	�R���X�g���N�^
*@param	�o��������G�̃^�C�v
*/
CActionCreateCharacter::CActionCreateCharacter(int type)
	:m_type(type) {}

/**
*@desc	�A�N�V�����J�n
*/
void CActionCreateCharacter::start()
{
	this->m_inAction = true;
}

/*
*@desc	�X�V����
*@param	�A�N�V�������s���Ώۂ̃L�����N�^�[
*/
void CActionCreateCharacter::update(CCharacter* pChara)
{
	if (this->m_inAction == true && this->count == 0)
	{

		//�G�o���f�[�^(�o���̏��)�̐���
		CEnemyLaunchData* pLaunchData = new CEnemyLaunchData(
			(ENEMY_TYPE)this->m_type,
			pChara->m_pMove->m_pos
		);

		pChara->m_state = 1;

		pLaunchData->m_pos.y += pChara->m_pBody->m_top * 2;

		//�o���g���K�[�𐶐����A�G�o���f�[�^��ݒ�
		CEnemyLaunchTrigger* pTrigger = new CEnemyLaunchTrigger(pLaunchData);

		//�o���g���K�[���o���X�P�W���[���Ƃ��Ēǉ�����
		CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);

		this->count++;
	}
}

/**
*@desc	�A�N�V�����I��
*/
void CActionCreateCharacter::stop()
{
	this->m_inAction = false;
}


/*
*	@desc �X�V����(�W�����v�ړ��v�Z)
*	@param �W�����v����Ώۂ̃L�����N�^�[
*	@tips ��L�[�������ꂽ�炱�̊֐����Ăяo��
*/
void CActionEnemyDamage::update(CCharacter* pChara)
{
	if (this->m_isJumping == true)
	{
		//�W�����v��
		
		//�W�����v�u�[�X�g�����炵�Ă���
		this->m_currentBoost--;

		//�W�����v�u�[�X�g��0��菬�����ꍇ
		if ((this->m_isJumpStart == false) || (this->m_currentBoost < 0))
		{
			//�����x��0�ɂ���
			pChara->m_pMove->m_accele.y = 0.0f;
			pChara->m_pMove->m_accele.x = 0.0f;
		}
	}
	else if (this->m_isJumpStart == true)
	{
		//�W�����v�J�n

		//y���̉����x�ɒl��ݒ�
		pChara->m_pMove->m_vel.y = this->m_accele;

		//�����ɍ��킹�ăm�b�N�o�b�N��x��ς���

		//���ړ����x��ݒ肷��
		pChara->m_pMove->m_vel.x = this->m_backstep * -pChara->m_moveVector.x;
		
		//���t���[���A�����x��K�p�����邩��ݒ�
		//this->m_currentBoost = this->m_boost;
		//�W�����v�t���O��true�ɂ���
		this->m_isJumping = true;

		/*
		//�_�ŃA�j���[�V����(����,��)-----------------------
		cocos2d::Blink* blink = cocos2d::Blink::create(1, 20);
		pChara->runAction(blink);
		//-------------------------------------------------
		*/
		//�C���r�W�u������
		pChara->InvisibleFrame = 60;

		pChara->m_isInvisible = true;

	}
	this->m_isJumpStart = false;
}

/**
*@desc	�A�N�V�����̍ċN��
*@param	�ċN������L�����N�^�[
*@tips	�L�����N�^�[��Y�����̃��Z�b�g���s��
*/
void CActionEnemyDamage::restart(CCharacter* pChara)
{
	//Y�����̑��x�h�ߑ��x�̃��Z�b�g
	pChara->m_pMove->m_vel.y = 0.0f;
	pChara->m_pMove->m_accele.y = 0.0f;

	//�A�N�V�����̒�~
	this->stop();

	//�A�N�V�����̊J�n
	this->start();
}


/**
*�e���˃A�N�V����
*/
void CActionShotEnemyBullet::update(CCharacter* pChara)
{
	if (pChara->m_isAlive)
	{
		/**
		*�e�𔭎�
		*/
		//�Ԋu���u���Ă��ԁv�Ȃ�
		if (this->m_shotCount == 0)
		{
			//�܂������e��ł�
			//CCharacter* bulletChara = (CBulletCharacter*)CBulletFactoryManager::getInstance()->create(BULLET_TYPE::NORMAL, pChara->m_pMove->m_pos.x, pChara->m_pMove->m_pos.y, pChara->m_shotLaunchVector);

			//CCharacterAggregate�Ƀv���C���[��ǉ�
			//�G�o���f�[�^���쐬
			//CBulletLaunchData* pLaunchData = new CBulletLaunchData(BULLET_TYPE::NORMAL, pChara->m_pMove->m_pos, pChara->m_shotLaunchVector);
			CVec2 vec = CVec2(pChara->m_moveVector.x * 3, pChara->m_moveVector.y);

			CEnemyBulletLaunchData* pLaunchData = new CEnemyBulletLaunchData(
				(BULLET_TYPE)this->m_bulletType,
				pChara->m_pMove->m_pos,
				vec
			);


			CEnemyBulletLaunchTrigger* pTrigger = new CEnemyBulletLaunchTrigger(pLaunchData);

			CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);

			this->m_shotCount = this->m_interval;

		}
		//�łĂȂ��Ȃ�
		else
		{
			//�Ԋu�������Ă���(0�ɂȂ�܂�)
			this->m_shotCount--;

			if (this->m_shotCount == 0)
			{
				pChara->m_isAttack1 = false;

			}
		}
	}
}


/**
*�~��e���˃A�N�V����
*/
void CActionShotEnemySphereBullet::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//�A�N�V������true�ɂȂ��

		/**
		*�e�𔭎�
		*/
		if (this->m_interval <= 0)
		{
			for (int i = 0;i <= 17;i++)
			{
				//�p�x
				float angle = i * 20.0f - 10.0f;

				//�p�x���ɂQ�����x�N�g�����擾
				float velX = cos(angle * M_PI / 180.0f) * 6.0f;
				float velY = sin(angle * M_PI / 180.0f) * 6.0f;


				CEnemyBulletLaunchData* pLaunchData = new CEnemyBulletLaunchData(
					(BULLET_TYPE)this->m_bulletType,
					pChara->m_pMove->m_pos,
					CVec2(velX, velY)
				);
				CEnemyBulletLaunchTrigger* pTrigger = new CEnemyBulletLaunchTrigger(pLaunchData);

				CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);
			}


			this->m_interval = 60;
		}
		else
		{
			m_interval--;
			if (this->m_interval <= 0)
			{
				this->m_interval = 0;
				this->stop();
			}
		}

	}


}

/**
*�{�X�A�N�V����
*/
void CActionTRoi::update(CCharacter* pChara)
{
	if (pChara->m_isAlive)
	{
		switch (step)
		{
		case 0:
			if (this->counter <= 0)
			{
				m_pPlayer = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
				if (pChara->m_pMove->m_pos.x < m_pPlayer->m_pMove->m_pos.x - 10)
				{
					(*pChara->m_pActions)[2]->start();
					pChara->setScale(1.0f, 1.0f);
					pChara->m_moveVector = CVec2(20, 0);
					pChara->m_pMove->m_vel = pChara->m_moveVector;

				}
				else if (pChara->m_pMove->m_pos.x > m_pPlayer->m_pMove->m_pos.x + 10)
				{
					(*pChara->m_pActions)[2]->start();
					pChara->setScale(-1.0f, 1.0f);
					pChara->m_moveVector = CVec2(-20, 0);
					pChara->m_pMove->m_vel = pChara->m_moveVector;
				}
				this->counter = this->m_intervalTime;

				step++;
			}
			break;

		//���
		case 1:
			if (pChara->m_pMove->m_pos.x < m_pPlayer->m_pMove->m_pos.x - 300 && pChara->m_pMove->m_vel.x < 0)
			{
				(*pChara->m_pPhysicals)[0]->setGravity(0.0f);
				pChara->setScale(1.0f, 1.0f);

				pChara->m_moveVector = CVec2(0, 0);
				step++;

			}
			else if (pChara->m_pMove->m_pos.x > m_pPlayer->m_pMove->m_pos.x + 300 && pChara->m_pMove->m_vel.x > 0)
			{
				(*pChara->m_pPhysicals)[0]->setGravity(0.0f);
				pChara->setScale(-1.0f, 1.0f);

				pChara->m_moveVector = CVec2(0, 0);
				step++;

			}


			pChara->m_pMove->m_vel = pChara->m_moveVector;
			break;

		case 2:
			//�󒆒�~
			if (pChara->m_pMove->m_pos.y >= 300.0f)
			{
				(*pChara->m_pActions)[2]->start();
				this->nowHeight = pChara->m_pMove->m_pos.y;
				step++;
			}
			else
			{
				pChara->m_pMove->m_pos.y += 1;
			}
			break;
		//����
		case 3:
			if (up)
			{
				upheight += 0.1f;
				if (upheight >= 1)
				{
					up = false;
				}
			}
			else
			{
				upheight -= 0.1f;
				if (upheight <=  -1)
				{
					up = true;
				}
			}
			pChara->m_pMove->m_pos.y += upheight;
			this->counter--;
			if (this->counter <= 0)
			{
				step = 0;
				(*pChara->m_pPhysicals)[0]->setGravity(0.0f);

			}

			break;
		default:
			break;
		}

	}
}
