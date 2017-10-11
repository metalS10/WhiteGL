
//=============================================
//�ǉ��̃C���N���[�h�͂�������
//=============================================
#include "CollisionArea.h"
#include "Model/Character/Character.h"
#include "Model/Map/Map.h"

/**
*@desc	�C�x���g�R�[���o�b�N�̌Ăяo��
*@param	�Ăяo���C���X�^���X
*		�}�b�v�`�b�v�̍ۂ̓u���b�N�̃^�C�v���C�x���g�Ƃ��ēn����
*		��ʒ[�ȂǂɃC�x���g�͑��݂��Ȃ��̂�
*		�f�t�H���g�l�Ƃ���0��ݒ肵�Ă���
*/
void CCollisionTerritory::callEventCallback(CCharacter* pChara, int event)
{
	//�C�x���g�R�[���o�b�N���ݒ肳��Ă��Ȃ����
	//�܂�NULL�Ȃ�Ăяo�����s��Ȃ�
	if (this->m_pEventCallback != NULL)
	{
		
		
		//�C�x���g�R�[���o�b�N���Ăяo�������o�֐������������
		//�L�����N�^�[����Ăяo�����s��
		(pChara->*m_pEventCallback)(event);

		
	}

}

//=============================================
//���ɂ����ʗ̈�Ƃ̏Փ˔���
//=============================================
void CCollisionTerritoryEndOfScreenBottom::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ������`�F�b�N
	if (pChara->m_pMove -> m_vel.y < 0.0f)
	{
		
		//���ɉ�ʒ[�����邩�ǂ������`�F�b�N
		if ((pChara->m_pMove->m_pos.y + basePt.y) < WINDOW_BOTTOM)
		{
			//�C�x���g�R�[���o�b�N�̌Ăяo��
			this->callEventCallback(pChara);
			//�߂荞�񂾕��̌v�Z
			float boundary = (pChara->m_pMove->m_pos.y +basePt.y) - WINDOW_BOTTOM;

			//�ŏI�I�ɖ߂��l
			pChara->m_pMove->m_pos.y -= boundary;

			//���Z�b�g����l
			pChara->m_pMove->m_vel.y = 0.0f;
			pChara->m_pMove->m_accele.y = 0.0f;

			//�W�����v�̒�~�͂�������폜���R�����g�A�E�g���Ă���
			//���̕������l���Ȃ��Ă͂Ȃ�Ȃ������l����Ƃ܂Ƃ܂�Ȃ��̂�
			//���͍l���Ȃ�
		}
	}
}

//=============================================
//���ɂ����ʗ̈�Ƃ̏Փ˔���
//=============================================
void CCollisionTerritoryEndOfScreenLeft::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ������`�F�b�N
	if (pChara->m_pMove->m_vel.x < 0.0f)
	{
		//���ɉ�ʒ[�����邩�ǂ������`�F�b�N
		if ((pChara->m_pMove->m_pos.x + basePt.x) < WINDOW_LEFT)
		{
			//�C�x���g�R�[���o�b�N�̌Ăяo��
			this->callEventCallback(pChara);

			//�߂荞�񂾕��̌v�Z
			float boundary = (pChara->m_pMove->m_pos.x + basePt.x) - WINDOW_LEFT;

			//�ŏI�I�ɖ߂��l
			pChara->m_pMove->m_pos.x -= boundary;

			//���Z�b�g����l
			pChara->m_pMove->m_vel.x = 0.0f;
			pChara->m_pMove->m_accele.x = 0.0f;

			//�G�Ȃ�E��
			if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
			{
				pChara->m_isAlive = false;
				pChara->m_activeFlag = false;
			}
		}
	}
}

//=============================================
//���̃}�b�v�`�b�v�̈�Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/
void CCollisionTerritoryMapChipBottom::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ���
	if (pChara->m_pMove->m_vel.y < 0.0f)
	{
		//�Փ˂��Ă����_(�L�����N�^�[�̓_)
		cocos2d::Point pt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + basePt.y);

		//�Փ˂��Ă��邩�ǂ���
		if (CMapManager::getInstance()->getMap()->hitTest(pt.x, pt.y))
		{
			//�Փ˂��Ă���

			//�u���b�N�̃^�C�v���擾
			BLOCK_TYPE mapChipID = CMapManager::getInstance()->getMap()->checkTile(pt.x, pt.y);

			if (mapChipID != BLOCK_TYPE::NONE)
			{
				//�C�x���g�R�[���o�b�N�̌Ăяo��
				this->callEventCallback(pChara, (int)mapChipID);
				//�߂��ׂ��ʒu�̌v�Z

				//�^�C���̃T�C�Y(32,32)
				cocos2d::Size tileSize = CMapManager::getInstance()->getMap()->getTileSize();

				//�L�����N�^�[���߂荞��ł���u���b�N�̉��̃u���b�N�̈ʒu = �u���b�N�� * �u���b�N����
				float blockPos = floor((pt.y) / tileSize.height) * tileSize.height;

				//�߂��ׂ��ʒu
				//	�C���ʒu(�L�����N�^�[���߂荞��ł���u���b�N�̏�̈ʒu) =
				//	�L�����N�^�[���߂荞��ł���u���b�N�̉��̃u���b�N�̈ʒu + �u���b�N1�� - �ʒuy
				//�߂荞�񂾕��̌v�Z
				float boundary = pt.y - (blockPos + tileSize.height);

				//�ŏI�I�ɖ߂��l(�߂荞�񂾕���߂�)
				pChara->m_pMove->m_pos.y -= boundary;

				//���Z�b�g����l
				pChara->m_pMove->m_vel.y = 0.0f;
				pChara->m_pMove->m_accele.y = 0.0f;

			}
		}
	}
}


//=============================================
//��̃}�b�v�`�b�v�̈�Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/
void CCollisionTerritoryMapChipTop::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//��Ɉړ����Ă��邩�ǂ���
	if (pChara->m_pMove->m_vel.y > 0.0f)
	{
		//�Փ˂��Ă����_(�L�����N�^�[�̓_)
		cocos2d::Point pt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + basePt.y);

		//�Փ˂��Ă��邩�ǂ���
		if (CMapManager::getInstance()->getMap()->hitTest(pt.x, pt.y))
		{
			//�Փ˂��Ă���

			//�u���b�N�̃^�C�v���擾
			BLOCK_TYPE mapChipID = CMapManager::getInstance()->getMap()->checkTile(pt.x, pt.y);

			if (mapChipID != BLOCK_TYPE::NONE)
			{
				//�C�x���g�R�[���o�b�N�̌Ăяo��
				this->callEventCallback(pChara, (int)mapChipID);

				//�߂��ׂ��ʒu�̌v�Z

				//�^�C���̃T�C�Y(32,32)
				cocos2d::Size tileSize = CMapManager::getInstance()->getMap()->getTileSize();

				//�L�����N�^�[���߂荞��ł���u���b�N�̏�̃u���b�N�̈ʒu = �u���b�N�� * �u���b�N����
				float blockPos = floor((pt.y) / tileSize.height) * tileSize.height;

				//�߂��ׂ��ʒu
				//	�C���ʒu(�L�����N�^�[���߂荞��ł���u���b�N�̏�̈ʒu) =
				//	�L�����N�^�[���߂荞��ł���u���b�N�̏�̃u���b�N�̈ʒu + �u���b�N1�� - �ʒuy
				//�߂荞�񂾕��̌v�Z
				float boundary = pt.y - (blockPos);

				//�ŏI�I�ɖ߂��l(�߂荞�񂾕���߂�)
				pChara->m_pMove->m_pos.y -= boundary;

				//���Z�b�g����l
				pChara->m_pMove->m_vel.y = 0.0f;
				pChara->m_pMove->m_accele.y = 0.0f;

			}
		}
	}
}

//=============================================
//�E�̃}�b�v�`�b�v�̈�Ƃ̏Փ˔���
//=============================================
/**
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/

void CCollisionTerritoryMapChipRight::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//�E�Ɉړ����Ă��邩�ǂ���
	if (pChara->m_pMove->m_vel.x > 0.0f)
	{
		//�Փ˂��Ă����_(�L�����N�^�[�̓_)
		cocos2d::Point pt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + basePt.y);

		//�Փ˂��Ă��邩�ǂ���
		if (CMapManager::getInstance()->getMap()->hitTest(pt.x, pt.y))
		{
			//�Փ˂��Ă���

			//�u���b�N�̃^�C�v���擾
			BLOCK_TYPE mapChipID = CMapManager::getInstance()->getMap()->checkTile(pt.x, pt.y);

			if (mapChipID != BLOCK_TYPE::NONE)
			{
				//�C�x���g�R�[���o�b�N�̌Ăяo��
				this->callEventCallback(pChara, (int)mapChipID);
				//�߂��ׂ��ʒu�̌v�Z

				//�^�C���̃T�C�Y(32,32)
				cocos2d::Size tileSize = CMapManager::getInstance()->getMap()->getTileSize();

				//�L�����N�^�[���߂荞��ł���u���b�N�̏�̃u���b�N�̈ʒu = �u���b�N�� * �u���b�N����
				float blockPos = floor((pt.x) / tileSize.width) * -tileSize.width;

				//�߂��ׂ��ʒu
				//	�C���ʒu(�L�����N�^�[���߂荞��ł���u���b�N�̏�̈ʒu) =
				//	�L�����N�^�[���߂荞��ł���u���b�N�̏�̃u���b�N�̈ʒu + �u���b�N1�� - �ʒuy
				//�߂荞�񂾕��̌v�Z
				float boundary = pt.x + (blockPos);

				//�ŏI�I�ɖ߂��l(�߂荞�񂾕���߂�)
				pChara->m_pMove->m_pos.x -= boundary;

				

				//�L�����N�^�[���G�Ȃ�
				if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
				{
					//������ς���
					pChara->m_moveVector *= -1;

					pChara->m_pMove->m_vel.x *= -1;
				}
				else
				{
					//���Z�b�g����l
					pChara->m_pMove->m_vel.x = 0.0f;
					pChara->m_pMove->m_accele.x = 0.0f;
				}

			}
		}
	}
}


//=============================================
//���̃}�b�v�`�b�v�̈�Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/

void CCollisionTerritoryMapChipLeft::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ���
	if (pChara->m_pMove->m_vel.x < 0.0f)
	{
		//�Փ˂��Ă����_(�L�����N�^�[�̓_)
		cocos2d::Point pt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + basePt.y);

		//�Փ˂��Ă��邩�ǂ���
		if (CMapManager::getInstance()->getMap()->hitTest(pt.x, pt.y))
		{
			//�Փ˂��Ă���

			//�u���b�N�̃^�C�v���擾
			BLOCK_TYPE mapChipID = CMapManager::getInstance()->getMap()->checkTile(pt.x, pt.y);

			if (mapChipID != BLOCK_TYPE::NONE)
			{
				//�C�x���g�R�[���o�b�N�̌Ăяo��
				this->callEventCallback(pChara, (int)mapChipID);

				//�߂��ׂ��ʒu�̌v�Z

				//�^�C���̃T�C�Y(32,32)
				cocos2d::Size tileSize = CMapManager::getInstance()->getMap()->getTileSize();

				//�L�����N�^�[���߂荞��ł���u���b�N�̏�̃u���b�N�̈ʒu = �u���b�N�� * �u���b�N����
				float blockPos = floor((pt.x) / tileSize.width) * tileSize.width;

				//�߂��ׂ��ʒu
				//	�C���ʒu(�L�����N�^�[���߂荞��ł���u���b�N�̏�̈ʒu) =
				//	�L�����N�^�[���߂荞��ł���u���b�N�̏�̃u���b�N�̈ʒu + �u���b�N1�� - �ʒuy
				//�߂荞�񂾕��̌v�Z
				float boundary = pt.x - (blockPos + tileSize.width);

				//�ŏI�I�ɖ߂��l(�߂荞�񂾕���߂�)
				pChara->m_pMove->m_pos.x -= boundary;

				//�L�����N�^�[���G�Ȃ�
				if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
				{
					//������ς���
					pChara->m_moveVector *= -1;

					pChara->m_pMove->m_vel.x *= -1;
				}
				else
				{
					//���Z�b�g����l
					pChara->m_pMove->m_vel.x = 0.0f;
					pChara->m_pMove->m_accele.x = 0.0f;
				}

			}
		}
	}
}


//=============================================
//�L�����N�^�[�̍��Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/
void CCollisionTerritoryCharacterLeft::collision(CCharacter* pChara,CCharacter* pSelf, cocos2d::Point basePt)
{
	//�E�Ɉړ����Ă��邩�ǂ���
	if (pChara->m_pMove->m_vel.x > 0.0f)
	{
		//�Փ˂��Ă����_(�L�����N�^�[�̓_)
		cocos2d::Point Charapt(pChara->m_pMove->m_pos.x + pChara->m_pBody->m_right, pChara->m_pMove->m_pos.y + basePt.y);
		cocos2d::Point Selfpt(pSelf->m_pMove->m_pos.x + basePt.x, pSelf->m_pMove->m_pos.y + basePt.y);

		//�����̏Փ˔����`
		CCollisionPoint selfPt(cocos2d::Point(Selfpt.x, Selfpt.y));
		//�ՓˑΏۂ̏Փ˔����`
		CCollisionRect charaRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//�Փ˔���
		if (selfPt.collision(&charaRect))
		{
			if (pChara->m_charaType != CHARACTER_TYPE::ENEMY)
				this->callEventCallback(pSelf);

			//�߂荞�񂾕��̌v�Z
			float boundary = ((Charapt.x) - (Selfpt.x));
			//�ŏI�I�ɖ߂��l
			pChara->m_pMove->m_pos.x -= boundary;

			pChara->m_pMove->m_accele.x = 0.0f;
			pChara->m_pMove->m_vel.x = 0.0f;

		}
	}
}

//=============================================
//�L�����N�^�[�̉E�Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/
void CCollisionTerritoryCharacterRight::collision(CCharacter* pChara, CCharacter* pSelf, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ���
	if (pChara->m_pMove->m_vel.x < 0.0f)
	{
		//�Փ˂��Ă����_(�L�����N�^�[�̓_)
		cocos2d::Point Charapt(pChara->m_pMove->m_pos.x + pChara->m_pBody->m_left, pChara->m_pMove->m_pos.y + basePt.y);
		cocos2d::Point Selfpt(pSelf->m_pMove->m_pos.x + basePt.x, pSelf->m_pMove->m_pos.y + basePt.y);

		//�����̏Փ˔����`
		CCollisionPoint selfPt(cocos2d::Point(Selfpt.x, Selfpt.y));
		//�ՓˑΏۂ̏Փ˔����`
		CCollisionRect charaRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//�Փ˔���
		if (selfPt.collision(&charaRect))
		{
			if (pChara->m_charaType != CHARACTER_TYPE::ENEMY)
				this->callEventCallback(pSelf);

			//�߂荞�񂾕��̌v�Z
			float boundary = ((Charapt.x) - (Selfpt.x));
			//�ŏI�I�ɖ߂��l
			pChara->m_pMove->m_pos.x -= boundary;


			pChara->m_pMove->m_vel.x = 0.0f;
			pChara->m_pMove->m_accele.x = 0.0f;

		}
	}
}


//=============================================
//�L�����N�^�[�̏�Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/
void CCollisionTerritoryCharacterTop::collision(CCharacter* pChara, CCharacter* pSelf, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ���
	if (pChara->m_pMove->m_vel.y < 0.0f)
	{
		//�Փ˂��Ă����_(�L�����N�^�[�̓_)
		cocos2d::Point Charapt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + pChara->m_pBody->m_bottom);
		cocos2d::Point Selfpt(pSelf->m_pMove->m_pos.x + basePt.x, pSelf->m_pMove->m_pos.y + basePt.y);

		//�����̏Փ˔����`
		CCollisionPoint selfPt(cocos2d::Point(Selfpt.x, Selfpt.y));
		//�ՓˑΏۂ̏Փ˔����`
		CCollisionRect charaRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//�Փ˔���
		if (selfPt.collision(&charaRect))
		{
			if (pChara->m_charaType != CHARACTER_TYPE::ENEMY)
			{
				pChara->collisionBottomCallback(0);
				this->callEventCallback(pSelf);
			}
			//�߂荞�񂾕��̌v�Z
			float boundary = ((Charapt.y) - (Selfpt.y));
			//�ŏI�I�ɖ߂��l
			pChara->m_pMove->m_pos.y -= boundary;

			pChara->m_pMove->m_accele.y = 0.0f;
			pChara->m_pMove->m_vel.y = 0.0f;

		}
	}
}


//=============================================
//�L�����N�^�[�̉��Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/
void CCollisionTerritoryCharacterBottom::collision(CCharacter* pChara, CCharacter* pSelf, cocos2d::Point basePt)
{
	//��Ɉړ����Ă��邩�ǂ���
	if (pChara->m_pMove->m_vel.y > 0.0f)
	{
		//�Փ˂��Ă����_(�L�����N�^�[�̓_)
		cocos2d::Point Charapt(pChara->m_pMove->m_pos.x + basePt.x, pChara->m_pMove->m_pos.y + pChara->m_pBody->m_top);
		cocos2d::Point Selfpt(pSelf->m_pMove->m_pos.x + basePt.x, pSelf->m_pMove->m_pos.y + basePt.y);

		//�����̏Փ˔����`
		CCollisionPoint selfPt(cocos2d::Point(Selfpt.x, Selfpt.y));
		//�ՓˑΏۂ̏Փ˔����`
		CCollisionRect charaRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//�Փ˔���
		if (selfPt.collision(&charaRect))
		{
			if (pChara->m_charaType != CHARACTER_TYPE::ENEMY)
			{
				this->callEventCallback(pSelf);
			}
			//�߂荞�񂾕��̌v�Z
			float boundary = ((Charapt.y) - (Selfpt.y));
			//�ŏI�I�ɖ߂��l
			pChara->m_pMove->m_pos.y -= boundary;

			pChara->m_pMove->m_accele.y = 0.0f;
			pChara->m_pMove->m_vel.y = 0.0f;

		}
	}
}




//=============================================
//��ʒ[�Ƃ̏Փ˔�����
//=============================================
/**
*@desc	�Փ˔���
*@param	�ՓˑΏۂ̃L�����N�^�[
*/
void CCollisionAreaEndOfScreen::collision(CCharacter* pChara)
{
	//�̈敪�J��Ԃ�
	for (CCollisionTerritory* pTerritory : (*this->m_pTerritories))
	{
		//��_���J��Ԃ�
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			//��_�̒��ɓo�^����Ă���Փ˔���̈�^�C�v����v�����炻�̊�_�ŏՓ˔�����s��
			if (pBasePt->m_type == pTerritory->m_type)
			{
				pTerritory->collision(pChara, pBasePt->m_pt);
			}
		}
	}
}

//=============================================
//��ʏ�ɂ��邷�ׂẴ}�b�v�`�b�v�Ƃ̏Փ˔�����
//�܂�}�b�v�Ƃ̏Փ˔�����
//=============================================
/**
*@desc	�Փ˔���
*@param �ՓˑΏۂ̃L�����N�^�[
*/
void CCollisionAreaMap::collision(CCharacter* pChara)
{
	//�̈敪�J��Ԃ�
	for (CCollisionTerritory* pTerritory : (*this->m_pTerritories))
	{
		//��_���J��Ԃ�
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			//��_�̒��ɓo�^����Ă���Փ˔���̈�^�C�v����v�����炻�̊�_�ŏՓ˔�����s��
			if (pBasePt->m_type == pTerritory->m_type)
			{
				pTerritory->collision(pChara, pBasePt->m_pt);
			}
		}
	}
}

//=============================================
//���̃}�b�v�`�b�v�̈�Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/
void CCollisionTerritoryOutOfScreenBottom::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ������`�F�b�N
	if (pChara->m_pMove->m_vel.y < 0.0f)
	{

		//���ɉ�ʒ[�����邩�ǂ������`�F�b�N
		if ((pChara->m_pMove->m_pos.y + basePt.y) < WINDOW_BOTTOM)
		{
			//�C�x���g�R�[���o�b�N�̌Ăяo��
			this->callEventCallback(pChara);

		}
	}
}

//=============================================
//��̃}�b�v�`�b�v�̈�Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/
void CCollisionTerritoryOutOfScreenTop::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ������`�F�b�N
	if (pChara->m_pMove->m_vel.y > 0.0f)
	{

		//���ɉ�ʒ[�����邩�ǂ������`�F�b�N
		if ((pChara->m_pMove->m_pos.y + basePt.y) > WINDOW_TOP)
		{
			//�C�x���g�R�[���o�b�N�̌Ăяo��
			this->callEventCallback(pChara);

		}
	}
}

//=============================================
//�E�̃}�b�v�`�b�v�̈�Ƃ̏Փ˔���
//=============================================
/**
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/

void CCollisionTerritoryOutOfScreenRight::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ������`�F�b�N
	if (pChara->m_pMove->m_vel.x > 0.0f)
	{
		//�E�ɉ�ʒ[�����邩�ǂ������`�F�b�N
		if ((pChara->m_pMove->m_pos.x + basePt.x) > WINDOW_RIGHT*3)
		{
			//�C�x���g�R�[���o�b�N�̌Ăяo��
			this->callEventCallback(pChara);

		}
	}
}


//=============================================
//���̃}�b�v�`�b�v�̈�Ƃ̏Փ˔���
//=============================================
/***
*@desc	�Փ˔���
*@param	�ՓˑΏ�
*/

void CCollisionTerritoryOutOfScreenLeft::collision(CCharacter* pChara, cocos2d::Point basePt)
{
	//���Ɉړ����Ă��邩�ǂ���
	if (pChara->m_pMove->m_vel.x < 0.0f)
	{
		//���ɉ�ʒ[�����邩�ǂ������`�F�b�N
		if ((pChara->m_pMove->m_pos.x + basePt.x) < WINDOW_LEFT)
		{
			//�C�x���g�R�[���o�b�N�̌Ăяo��
			this->callEventCallback(pChara);

		}
	}
}


//=============================================
//��ʏ�ɂ��邷�ׂẴ}�b�v�`�b�v�Ƃ̏Փ˔�����
//�܂�}�b�v�Ƃ̏Փ˔�����
//=============================================
/**
*@desc	�Փ˔���
*@param �ՓˑΏۂ̃L�����N�^�[
*/
void CCollisionAreaOutOfScreen::collision(CCharacter* pChara)
{
	//�̈敪�J��Ԃ�
	for (CCollisionTerritory* pTerritory : (*this->m_pTerritories))
	{
		//��_���J��Ԃ�
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			//��_�̒��ɓo�^����Ă���Փ˔���̈�^�C�v����v�����炻�̊�_�ŏՓ˔�����s��
			if (pBasePt->m_type == pTerritory->m_type)
			{
				pTerritory->collision(pChara, pBasePt->m_pt);
			}
		}
	}
}


//=============================================
//�L�����N�^�[�Ƃ̏Փ˔�����
//=============================================
/**
*@desc	�Փ˔���
*@param	�ՓˑΏۂ̃L�����N�^�[
*/
void CCollisionAreaCharacter::collision(CCharacter* pChara,CCharacter* pSelf)
{
	//�̈敪�J��Ԃ�
	for (CCollisionTerritory* pTerritory : (*this->m_pTerritories))
	{
		//��_���J��Ԃ�
		for (CCollisionBasePoint* pBasePt : (*this->m_pBasePoints))
		{
			//��_�̒��ɓo�^����Ă���Փ˔���̈�^�C�v����v�����炻�̊�_�ŏՓ˔�����s��
			if (pBasePt->m_type == pTerritory->m_type)
			{
				pTerritory->collision(pChara, pSelf, pBasePt->m_pt);
			}
		}
	}
}