
#include "PlayerCharacter.h"
#include "../../AllController/AllController.h"

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

	this->m_texID = NULL;

	this->init();


}

//�f�X�g���N�^
CPlayerCharacter::~CPlayerCharacter() {
	SAFE_DELETE(m_pSounds);
	this->deletePoly();
	SAFE_DELETE(m_playerEffect[0])
	SAFE_DELETE(m_playerEffect[1])
	SAFE_DELETE(m_playerEffect[2])
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

	//�U�����ǂݍ���
	this->m_pSounds = new std::vector<CSound*>();
	this->m_pSounds->push_back(new CSound(SOUND_DRUM_AVOIDANCE_MISS	, 16,100));
	this->m_pSounds->push_back(new CSound(SOUND_DRUM_AVOIDANCE		, 16,100));
	this->m_pSounds->push_back(new CSound(SOUND_DRUM_ATTACK_MISS	, 16,100));
	this->m_pSounds->push_back(new CSound(SOUND_DRUM_ATTACK			, 16,100));
	this->m_pSounds->push_back(new CSound(SOUND_QUARTER_BEATS		, 16,80));

	//�|���S����ݒ�
	this->setupPoly(CVec4(0.0f, 0.0f, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::MAIN);

	//PlayerEffect
	m_playerEffect[0] = new rendInfo::CPolygonRendInfo();
	m_playerEffect[1] = new rendInfo::CPolygonRendInfo();
	m_playerEffect[2] = new rendInfo::CPolygonRendInfo();
	m_playerEffect[0]->setupPoly(CVec4(0.0f, 0.0f, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 40.0f), rendInfo::LAYER::MAIN);
	m_playerEffect[1]->setupPoly(CVec4(0.0f, 0.0f, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 60.0f), rendInfo::LAYER::MAIN);
	m_playerEffect[2]->setupPoly(CVec4(0.0f, 0.0f, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 80.0f), rendInfo::LAYER::MAIN);


	for (CSound* sound : (*m_pSounds))
	{
		sound->LoadChunk();
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

	//�|���S���̔��q�A�N�V����
	this->polygonBeatsAction();

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
			inputArrow.x = -1;
			this->m_pMove->m_accele.x = -0.7f;
			this->Allfalse();
		}

		else if (input->getOnKey(Input::Key::DPAD_RIGHT) == true)
		{
			inputArrow.x =1;
			this->m_pMove->m_accele.x = 0.7f;
			this->Allfalse();
		}
		else
		{
			inputArrow.x = 0;
		}
		if (input->getOnKey(Input::Key::DPAD_UP) == true)
		{

			//���݂̕����L�[���͏��
			inputArrow.y = 1;
			/*
			//�n�ʂɂ��Ă���
			if (this->m_isGround)
			{
				//�W�����v���J�n������
				(*this->m_pActions)[(int)ACTION::JUMP]->start();
				this->Allfalse();
			}
			*/
		}
		else if (input->getOnKey(Input::Key::DPAD_DOWN) == true)
		{

			//���݂̕����L�[���͏��
			inputArrow.y = -1;
		}
		else
		{
			//���݂̕����L�[���͏��
			inputArrow.y = 0;
		}
		if (input->getOnKey(Input::Key::Z) == true)
		{
			if (m_denkiPoint >= 5.0f)
			{
				//�e����(playerFactory��getActions�ɂ�����)
				(*this->m_pActions)[(int)ACTION::ATTACK]->start();
				//�A�j���[�V�����̏�����
				//(*this->m_pAnimations)[(int)STATE::ATTACK]->start();
				this->Allfalse();
				m_isAttack1 = true;
			}

		}
		if (input->getOnKey(Input::Key::X) == true)
		{

			//����J�n
			(*this->m_pActions)[(int)ACTION::AVOIDANCE]->start();

			//(*this->m_pAnimations)[(int)STATE::AVOIDANCE]->start();
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

	//����A�N�V�����X�V����
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
	//(*this->m_pAnimations)[m_state]->update();

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
	
	//�_���[�W���ɐF��ς���
	if (m_isDamage)
	{
		setPolyColor(CVec4(100.0f, 0.0f, 0.0f, 100.0f));
	}
	else if (musicNotesMiss > 0)
	{
		//beats�̃~�X�̓s���N
		setPolyColor(CVec4(100.0f, 50.0f, 50.0f, 100.0f));
	}
	else if (m_isAvoidance)
	{
		//��𐬌����̉���s���͉��F
		setPolyColor(CVec4(100.0f, 100.0f, 0.0f, 100.0f));
	}
	else
	{
		//�����Ȃ���Ζ߂�
		setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 100.0f));
	}
	//��]���
	if (playerRolling)
	{
		playerAngle -= m_CharaLaunchVector.x*50.0f;
		if (playerAngle >= 600 || playerAngle <= -600)
		{
			playerAngle = 0;
			playerRolling = false;
		}
		setPolyAngle(playerAngle);
	}
	//Player�̃G�t�F�N�g����
	this->playerEffect();

	//�ʒu�f�[�^�𔽉f
	//rendTex->setPosition(this->m_pMove->m_pos,5);
	//���_���W�̍X�V
	setPolyPos(CVec2(m_pMove->m_pos.x, m_pMove->m_pos.y));

	//�`�b�v�f�[�^�𔽉f
	//game.setTextureRect((*this->m_pAnimations)[1]->getCurrentChip());

}
void CPlayerCharacter::playerEffect()
{
	//�����Ă���G�t�F�N�g�\��
	if (m_state == (int)STATE::WALK)
	{
		playerEffectCount[0]++;
		playerEffectCount[1]++;
		playerEffectCount[2]++;
		if (playerEffectCount[0] >= 2)
		{
			playerEffectCount[0] = 0;
			m_playerEffect[0]->setPolyPos(CVec2(m_pMove->m_pos.x, m_pMove->m_pos.y));
			m_playerEffect[0]->setPolyScale(getPolyScale());
			m_playerEffect[0]->setPolyAngle(getPolyAngle());
			CVec4 playerColor = getPolyColor();
			playerColor.w = 80.0f;
			m_playerEffect[0]->setPolyColor(playerColor);
		}
		if (playerEffectCount[1] >= 4)
		{
			playerEffectCount[1] = 0;
			m_playerEffect[1]->setPolyPos(CVec2(m_pMove->m_pos.x, m_pMove->m_pos.y));
			m_playerEffect[1]->setPolyScale(getPolyScale());
			m_playerEffect[1]->setPolyAngle(getPolyAngle());
			CVec4 playerColor = getPolyColor();
			playerColor.w = 60.0f;
			m_playerEffect[1]->setPolyColor(playerColor);
		}
		if (playerEffectCount[2] >= 6)
		{
			playerEffectCount[2] = 0;
			m_playerEffect[2]->setPolyPos(CVec2(m_pMove->m_pos.x, m_pMove->m_pos.y));
			m_playerEffect[2]->setPolyScale(getPolyScale());
			m_playerEffect[2]->setPolyAngle(getPolyAngle());
			CVec4 playerColor = getPolyColor();
			playerColor.w = 40.0f;
			m_playerEffect[2]->setPolyColor(playerColor);
		}
	}
	//�����Ă��Ȃ���΃G�t�F�N�g��\��
	else
	{
		//�O��̏������u�����Ă����ԁv�Ȃ�
		if (m_state != (int)STATE::WALK)
		{
			m_playerEffect[0]->setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 0.0f));
			m_playerEffect[1]->setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 0.0f));
			m_playerEffect[2]->setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 0.0f));
		}
	}
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

//���q�Ԋu�Z�b�g
void CPlayerCharacter::setBeat(int beat)
{
	m_beatInterval = beat;
	m_beatInterval -= BEAT_INTERVAL;
}

//�W���X�g���
void CPlayerCharacter::DodgeInterval()
{
	m_beatCounter++;

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

void CPlayerCharacter::quarterUpdate()
{
	if (m_beatInterval == 0)
	{
		setBeat(m_beatCounter);
	}
	//����s��������Ȃ����
	if (!m_isAvoidance)
	{
		//�d�͂�߂�
		(*this->m_pPhysicals)[0]->setGravity(-1.5f);
	}
	m_beatCounter = 0;
	//player�̃J�E���^�[
	musicNotesCounter = BEAT_INTERVAL;
	DPHeal(0.5f);
}