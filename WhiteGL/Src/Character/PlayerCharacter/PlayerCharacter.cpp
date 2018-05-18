//================================================
//�ǉ��̃C���N���[�h�͂�������
//================================================
#include "PlayerCharacter.h"
//#include "Model/Map/Map.h"
//#include "Data/LaunchData/LaunchData.h"
//#include "Data/LaunchTrigger/LaunchTrigger.h"

//================================================
//�v���C���[�L�����N�^�[�̃����o�֐��̃R�[�h�ǉ��͂�������
//================================================

//�R���X�g���N�^
CPlayerCharacter::CPlayerCharacter() {

	//�L�����N�^�[�^�C�v���v���C���[�L�����N�^�[�ɐݒ�
	this->m_charaType = CHARACTER_TYPE::PLAYER;

	this->m_CharaLaunchVector.x = 1.0f;

	this->m_tag = TAG_PLAYER_1;

	this->m_denkiPoint = 100;

	this->m_hitPoint = 100;

	this->m_texID = PLAYER_ID;

	this->init();

}

//�f�X�g���N�^
CPlayerCharacter::~CPlayerCharacter() {
}

//����������
bool CPlayerCharacter::init()
{
	//�L�����N�^�[�N���X�̏�����
	if (CCharacter::init() == false)
	{
		printf("�v���C���[�L�����N�^�[�������Ɏ��s");
		return false;
	}


	return true;
}

void CPlayerCharacter::update()
{
	//x���̉����x�̏�����
	this->m_pMove->m_accele.x = 0.0f;

	//�_���[�W�C���^�[�o������
	this->DamageInterval();

	//�W���X�g����C���^�[�o��
	this->DodgeInterval();

	this->animationFunc();
	//�L�����N�^�[�̍X�V�����Ăяo��
	CCharacter::update();
}

/**
*	@desc���͏���
*	@tip	�ړ������ŌĂяo��
*/
void CPlayerCharacter::inputFunc()
{
	
	//�_���[�W������Ȃ���� && ��𒆂���Ȃ����
	if (!this->m_isDamage && !this-> m_isAvoidance)
	{
		if (input->getOnKey(Input::Key::DPAD_LEFT) == true)
		{

			this->m_pMove->m_accele.x = -0.7f;
			this->Allfalse();
		}

		if (input->getOnKey(Input::Key::DPAD_RIGHT) == true)
		{
			this->m_pMove->m_accele.x = 0.7f;
			this->Allfalse();
		}

		if (input->getOnKey(Input::Key::DPAD_UP) == true)
		{
			//�n�ʂɂ��Ă���
			if (this->m_isGround)
			{
				//�W�����v���J�n������
				(*this->m_pActions)[(int)ACTION::JUMP]->start();
				this->Allfalse();
			}
		}
		if (input->getOnKey(Input::Key::Z) == true)
		{
			//�A�j���[�V�����̏�����
			(*this->m_pAnimations)[(int)STATE::ATTACK]->start();
			//�e����(playerFactory��getActions�ɂ�����)
			(*this->m_pActions)[(int)ACTION::ATTACK]->start();
			this->m_denkiPoint -= 5.0f;
			this->Allfalse();
			m_isAttack1 = true;
		}
		if (input->getOnKey(Input::Key::X) == true)
		{
			//�~�X���Ă��Ȃ�&�����^�C�~���O�Ȃ�Q�[�W��
			if (this->musicNotesCounter > 0 && musicNotesMiss <= 0)
			{
				this->DPHeal(10.0f);
			}
			//�����^�C�~���O�Ȃ�miss����
			else if(!this->musicNotesCounter > 0)
			{
				//Miss!
				musicNotesMiss = 20;
				printf("Miss\n");
			}
			//����J�n
			(*this->m_pActions)[(int)ACTION::AVOIDANCE]->start();

			(*this->m_pAnimations)[(int)STATE::AVOIDANCE]->start();

		}
		if (input->getOnKey(Input::Key::D) == true)
		{

		}
		//�f�o�b�O�p
		if (input->getOnKey(Input::Key::SPACE) == true)
		{
			this->DPHeal(100);
			this->m_hitPoint = 100;
		}
	}
	
	
}

/**
*	@desc �ړ�����
*/
void CPlayerCharacter::moveFunc()
{
	/*
	*���͏���
	*	������͓͂��͂ɂ��ړ��Ƃ����J�e�S���ň���
	*/
	
	this->inputFunc();
	
	//�W�����v�ړ��v�Z
	(*this->m_pActions)[(int)ACTION::JUMP]->update(this);
	

	//�e����update
	(*this->m_pActions)[(int)ACTION::ATTACK]->update(this);


	(*this->m_pActions)[(int)ACTION::AVOIDANCE]->update(this);

	(*this->m_pActions)[(int)ACTION::DAMAGE]->update(this);



	
	//�����v�Z
	for (CPhysical* pPhysical : (*m_pPhysicals))
	{
		pPhysical->update(this->m_pMove);
	}
	
	//�ړ��v�Z
	this->m_pMove->moveBy();
}

//�A�j���[�V��������
void CPlayerCharacter::animationFunc()
{
	//�A�j���[�V����
	(*this->m_pAnimations)[m_state]->update();

}

/**
* @desc	��ʔ͈͊O���菈��
* @tips	���������������̎d���͂��ꂩ��͏��Ȃ����Ă����悤��
*		�S�����悤�B
*		�ǂ̂悤�ɂ���Δėp�I�ɁA�܂葼�̃L�����N�^�[�ł��g���񂵂ł��邩��
*		�l���Ď��s���Ă������B
*/
/*
void CPlayerCharacter::endOfScreen()
{
	//���Ɉړ����Ă���ꍇ�͉�ʍ��Ŏ~�߂�悤�ɂ���
	if (this->m_pMove->m_vel.x < 0.0f&&this->m_pMove->m_pos.x + m_pBody->m_left < WINDOW_LEFT)
	{
		//�ݒ�@�C���l
		float boundary = (this->m_pMove->m_pos.x + this->m_pBody->m_left) - WINDOW_LEFT;
		this->m_pMove->m_pos.x -= boundary;

		//���x�Ɖ����x��0�ɂ��邩�ǂ����̓Q�[���ɂ���ĕς��
		this->m_pMove->m_vel.x = 0.0f;
		this->m_pMove->m_accele.x = 0.0f;
	}
	//�E�Ɉړ����Ă���ꍇ�͉�ʉE�Ŏ~�߂�悤�ɂ���
	if (this->m_pMove->m_vel.x > 0.0f&&this->m_pMove->m_pos.x + m_pBody->m_right > WINDOW_RIGHT)
	{
		//�ݒ�@�C���l
		float boundary = (this->m_pMove->m_pos.x + this->m_pBody->m_right) - WINDOW_RIGHT;
		this->m_pMove->m_pos.x -= boundary;

		//���x�Ɖ����x��0�ɂ��邩�ǂ����̓Q�[���ɂ���ĕς��
		this->m_pMove->m_vel.x = 0.0f;
		this->m_pMove->m_accele.x = 0.0f;
	}
	//��ʉ��Ŏ~�߂�悤�ɂ���
	if (this->m_pMove->m_pos.y + this->m_pBody->m_bottom < WINDOW_BOTTOM)
	{
		//�ݒ�@�C���l
		float boundary = (this->m_pMove->m_pos.y + this->m_pBody->m_bottom) - WINDOW_BOTTOM;
		this->m_pMove->m_pos.y -= boundary;

		//���x�Ɖ����x��0�ɂ���
		this->m_pMove->m_vel.y = 0.0f;
		this->m_pMove->m_accele.y = 0.0f;

		//�W�����v���~������
		(*this->m_pActions)[(int)ACTION::JUMP]->stop();
	}
}
*/

/**
*@desc	��ԂƂ̏Փ˔��菈��
*/
void CPlayerCharacter::collision()
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
*	@desc ��ԃ`�F�b�N
*	@tips �l���`�F�b�N���Č��݂̏�Ԃ�ύX����
*/
void CPlayerCharacter::checkState()
{
	
	//�����̔���
	if (this->m_pMove->m_vel.x != 0)
	{
		if (this->m_pMove->m_vel.x > 0)
		{
			//�E�����ɐݒ�
			this->setScale(1.0f, 1.0f);

			this->m_CharaLaunchVector.set(1.0f, 0.0f);
		}
		else
		{
			//�������ɐݒ�
			this->setScale(-1.0f, 1.0f);

			this->m_CharaLaunchVector.set(-1.0f, 0.0f);
		}
	}
	//y�ړ����x��0�Ȃ�
	if (this->m_pMove->m_vel.y == 0.0f)
	{
		//�n�ʂɂ��Ă���
		this->m_isGround = true;
	}
	//�_���[�W������Ȃ���� && ��𒆂���Ȃ����
	if (!this->m_isDamage && !this->m_isAvoidance)
	{
		//��Ԃ̔���
		if (this->m_isAttack1 == true)
		{
			m_state = (int)STATE::ATTACK;
		}
		else if (this->m_pMove->m_vel.y > 0.0f)
		{
			//y���̑��x���v���X�Ƃ������Ƃ̓W�����v���Ă�����
			m_state = (int)STATE::JUMPING;
		}
		else if (this->m_pMove->m_vel.y < 0.0f)
		{
			//y���̑��x���}�C�i�X�Ƃ������Ƃ͗����Ă�����
			m_state = (int)STATE::FALING;
			//�n�ʂɂ��Ă��Ȃ�
			this->m_isGround = false;
		}
		else if (this->m_pMove->m_vel.x != 0)
		{
			//�����Ă���
			m_state = (int)STATE::WALK;
		}
		else
		{
			//�����Ă���
			m_state = (int)STATE::STAND;
		}
	}
	//��𒆂Ȃ�
	else if (this->m_isAvoidance)
	{
		if (this->m_pMove->m_vel.y > 0.0f)
		{
			//y���̑��x���v���X�Ƃ������Ƃ̓W�����v���Ă�����
			m_state = (int)STATE::SUPERJUMP;
		}
		else if (this->m_pMove->m_vel.y < 0.0f)
		{
			//y���̑��x���}�C�i�X�Ƃ������Ƃ͗����Ă�����
			m_state = (int)STATE::SUPERFALING;
			//�n�ʂɂ��Ă��Ȃ�
			this->m_isGround = false;
		}
		else if (this->m_pMove->m_vel.x != 0)
		{
			//�����Ă���
			m_state = (int)STATE::DASH;
		}
		else
		{
			//��𒆗����Ă�����
			m_state = (int)STATE::AVOIDANCE;
		}
	}
	//�_���[�W���Ȃ�
	else
	{
		//�_���[�W���Œn�ʂɂ��Ă��Ȃ����
		if (this->m_isDamage == true && this->m_pMove->m_vel.y != 0)
		{
			m_state = (int)STATE::DAMAGE;
		}
	}
}

/**
*	@desc���f����
*/
void CPlayerCharacter::applyFunc()
{
	
	//�ʒu�f�[�^�𔽉f
	//rendTex->setPosition(this->m_pMove->m_pos,5);

	//�`�b�v�f�[�^�𔽉f
	//game.setTextureRect((*this->m_pAnimations)[1]->getCurrentChip());
	
}

/**
*	@desc �L�����N�^�[�P�̂Ƃ̏Փ˔��菈��
*	@param �L�����N�^�[�̃A�h���X
*	@return ture....�Փ˂���
*/
bool CPlayerCharacter::collision(CCharacter* pChara)
{
	//�G���M�~�b�N��������
	if (pChara->m_charaType == CHARACTER_TYPE::ENEMY || pChara->m_charaType == CHARACTER_TYPE::GIMMICK)
	{
		//���g�̏Փ˔����`
		CCollisionRect myRect(*this->m_pBody, this->m_pMove->m_pos);

		//�G�̏Փ˔����`
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
void CPlayerCharacter::hits(CCharacter* pChara)
{
	//�G��������
	if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
	{
		//�C���r�W�u����Ԃ���Ȃ��Ȃ� && �����Ԃ���Ȃ��Ȃ�
		if (!this->m_isInvisible && !this->m_isAvoidance && !pChara->m_isInvisible)
		{
			//(*this->m_pActions)[4]->restart(this);

			//x���ړ��̐ݒ�(�����ɓ���)
			this->m_Nockback.x = -this->m_CharaLaunchVector.x * 5;

			//�m�b�N�o�b�N
			this->m_pMove->m_vel = this->m_Nockback;

			//�_���[�W�̃t���O��true�ɂ���
			this->m_isDamage = true;
			
			//�C���r�W�u���̃t���O��true�ɂ���
			this->m_isInvisible = true;

			//�_�ŃA�j���[�V����(����,��)-----------------------
			//cocos2d::Blink* blink = cocos2d::Blink::create(DamageTime / 60, DamageTime / 3);
			//this->runAction(blink);
			//-------------------------------------------------
			//�C���r�W�u������
			this->InvisibleFrame = DamageTime;

			//�����ƃv���C���[�Ƃ̏Փ˔���(�ザ��Ȃ��ꍇ)
			//�̗͂����炷
			this->m_hitPoint -= pChara->m_attackPoint;
		}
		//�W���X�g����\�Ȃ�
		else if (this->m_DodgeTime > 0)
		{
			printf("JustAvoidance!");
		}
	}

	//�G�̍U����������
	if (pChara->m_charaType == CHARACTER_TYPE::ENEMYBULLET)
	{
		//�C���r�W�u����Ԃ���Ȃ��Ȃ� && �����Ԃ���Ȃ��Ȃ�
		if (!this->m_isInvisible && !this->m_isAvoidance)
		{
			//(*this->m_pActions)[4]->restart(this);

			//x���ړ��̐ݒ�(�����ɓ���)
			this->m_Nockback.x = -this->m_CharaLaunchVector.x * 5;

			//�m�b�N�o�b�N
			this->m_pMove->m_vel = this->m_Nockback;

			//�_���[�W�̃t���O��true�ɂ���
			this->m_isDamage = true;

			//�C���r�W�u���̃t���O��true�ɂ���
			this->m_isInvisible = true;

			//�_�ŃA�j���[�V����(����,��)-----------------------
			//cocos2d::Blink* blink = cocos2d::Blink::create(DamageTime / 60, DamageTime / 3);
			//this->runAction(blink);
			//-------------------------------------------------
			//�C���r�W�u������
			this->InvisibleFrame = DamageTime;

			//�����ƃv���C���[�Ƃ̏Փ˔���(�ザ��Ȃ��ꍇ)
			//�̗͂����炷
			this->m_hitPoint -= pChara->m_attackPoint;

			//�G�̒e������
			pChara->m_activeFlag = false;
		}
	}
	if (this->m_hitPoint <= 0)
	{
		this->m_gameOver = true;
	}
}

void CPlayerCharacter::Allfalse()
{
	this->m_isAttack1 = false;
}

//���d�_���[�W�h�~�p(�_���[�W����)
void CPlayerCharacter::DamageInterval()
{
	//�_���[�W�Ԋu
	if (!this->InvisibleFrame <= 0)
	{
		this->InvisibleFrame--;
	}
	//�_���[�W���󂯂���̑��얳������
	if (this->InvisibleFrame <= this->DamageTime * 0.5 && this->m_isDamage)
	{
		this->m_isDamage = false;
	}
	//���G����(�C���r�W�u��)
	else if (this->InvisibleFrame <= 0 && this->m_isInvisible)
	{
		this->m_isInvisible = false;
	}
}

//�W���X�g���
void CPlayerCharacter::DodgeInterval()
{
	//���ɍ��킹��^�C�~���O��������
	if (!this->musicNotesCounter <= 0)
	{
		//���X�ɍ���Ȃ��Ȃ�
		this->musicNotesCounter--;
	}
	//�~�X������
	if(this->musicNotesMiss > 0)
	{
		this->musicNotesMiss--;
	}
}