//=================================================
//�ǉ��̃C���N���[�h�͂�������
//=================================================
#include "Map.h"
#include "Constants.h"
#include "Collision.h"
#include "LaunchData.h"
#include "LaunchTrigger.h"

//=================================================
//�}�b�v�N���X
//=================================================

//����������
bool CMap::init(const std::string& tmxFile)
{
	/*
	if (!TMXTiledMap::initWithTMXFile(tmxFile))
		return false;
	*/
	this->load(tmxFile);

	return true;
}

/**
*@desc	�^�C���̂Q�����z���̍��W���擾
*@param	�Ώۈʒu
*/
CVec2 CMap::getTileCoord(CVec2 pos)
{
	//�}�b�v�̌��_�ʒu
	CVec2 pt = this->getPosition();

	//�}�b�v�^�C���T�C�Y
	CSize& tileSize = this->getTileSize();

	//�}�b�v�̔z��T�C�Y
	CSize& mapSize = this->getMapSize();

	float x = (pos.x + pt.x) / tileSize.width;
	float y = ((mapSize.height * tileSize.height) - pos.y) / tileSize.height;

	//���㌴�_�̏ꍇ
	//int y = (pos_.y + this->getPosition().y)/this->getTileSize().height;

	return CVec2(x, y);
}
/**
*@desc	�^�C���ʒu�̎擾
*@param	�Ώۈʒu
*/

CVec2 CMap::getTilePosition(CVec2 pos)
{
	//�}�b�v�̌��_�ʒu
	CVec2 pt = this->getPosition();

	//�}�b�v�^�C���T�C�Y
	CSize& tileSize = this->getTileSize();

	int x = (pos.x + pt.x) / tileSize.width;
	int y = (pos.y + pt.y) / tileSize.height;

	return CVec2(x * tileSize.width, y * tileSize.height);
}


/**
*@desc	�_�ƃ}�b�v�`�b�v�Ƃ̏Փ˔���
*@param	�ΏۈʒuX
*@param	�ΏۈʒuY
*@return	true...�Փ˂���
*/
bool CMap::hitTest(float posX, float posY)
{
	//�Ώۂ̏Փ˔���̓_
	CCollisionPoint cpt(CVec2(posX, posY));

	//�_�ƏՓ˂��Ă���}�b�v�`�b�v�̌��_(�����̓_)���擾
	CVec2 basePoint = this->getTilePosition(CVec2(posX, posY));

	//�}�b�v�`�b�v�̈ʒu(�}�b�v�`�b�v�̒��S�ʒu)
	CVec2 tilePos = CVec2(basePoint.x + 16.0f, basePoint.y + 16.0f);

	//(-16,16,16,-16)
	CCollisionRect crect(CBody(-16, 16, 16, -16), tilePos);

	//collision���g�p���Ĕ���
	return cpt.collision(&crect);
}

/**
*@desc	�^�C���ԍ��̊m�F
*@param	�^�C���ɏՓ˂��Ă���_��x���W
*@param	�^�C���ɏՓ˂��Ă���_��y���W
*@return	���C���[�̃^�C�v
*@return	�^�C���ԍ�(�u���b�N�ԍ��A�}�b�v�`�b�v�ԍ��A�}�b�v�`�b�vID)
*/
BLOCK_TYPE CMap::checkTile(float posX, float posY,LAYER_TYPE layerType)
{
	
	//���C���[���擾
	//cocos2d::TMXLayer* pLayer = this->getLayer(this->m_layerName[(int)layerType]);

	int pLayer = this->getLayer((int)layerType);


	//�^�C���̂Q�����z���̍��W���擾
	CVec2 tileCoord = this->getTileCoord(CVec2(posX, posY));

	//�}�b�v�̔z��T�C�Y
	CSize& mapSize = this->getMapSize();

	///////
	//�^�C���̂Q�����z���̍��W��0�����܂��̓}�b�v�T�C�Y���傫���ꍇ
	if ((0 <= tileCoord.x && tileCoord.x < mapSize.width) == false ||
		(0 <= tileCoord.y && tileCoord.y < mapSize.height) == false)
	{
		return BLOCK_TYPE::NONE;
	}
	
	//�}�b�v�`�b�v�f�[�^�̎擾
	//return (BLOCK_TYPE)pLayer->getTileGIDAt(tileCoord);
	
	return (BLOCK_TYPE)pLayer;
}

/**
*@desc	�^�C���̕ύX
*@param		�ύX����}�b�v�`�b�vID(�^�C���ԍ��A�u���b�N�ԍ��A�}�b�v�`�b�v�ԍ�)
*@param		�^�C���ɏՓ˂��Ă���_��x���W
*@param		�^�C���ɏՓ˂��Ă���_��y���W
*@param		���C���[�^�C�v
*@return	true...����
*/
bool CMap::changeTile(int mapChipID, float posX, float posY,LAYER_TYPE layerType)
{
	
	//���C���[���擾
	//cocos2d::TMXLayer* pLayer = this->getLayer(this->m_layerName[(int)layerType]);

	//�^�C���̂Q�����z���̍��W���擾
	CVec2 tileCoord = this->getTileCoord(CVec2(posX, posY));

	//�}�b�v�̔z��T�C�Y
	CSize& mapSize = this->getMapSize();

	//////
	//�^�C���̂Q�����z���̍��W��0�����܂��̓}�b�v�T�C�Y���傫���ꍇ
	if ((0 <= tileCoord.x && tileCoord.x < mapSize.width) == false ||
		(0 <= tileCoord.y && tileCoord.y < mapSize.height) == false)
	{
		return false;
	}

	//�}�b�v�`�b�v�f�[�^�̔��f
	//pLayer->setTileGID(mapChipID, tileCoord);
	
	return true;
}

//===================================================================
//�}�b�v�Ǘ��N���X
//===================================================================
//���L�C���X�^���X�{��
CMapManager* CMapManager::m_pSharedMapManager = NULL;

//�R���X�g���N�^
CMapManager::CMapManager() {
}
CMapManager::CMapManager(const CMapManager&customMapmgr_) {
}
//���L�C���X�^���X�̎擾
CMapManager* CMapManager::getInstance()
{
	if (CMapManager::m_pSharedMapManager == NULL)
	{
		CMapManager::m_pSharedMapManager = new CMapManager();
	}
	return CMapManager::m_pSharedMapManager;
}

//�f�X�g���N�^
CMapManager::~CMapManager() {
}

//�j��
void CMapManager::removeInstance()
{
	SAFE_DELETE(CMapManager::m_pSharedMapManager);
}

//�}�b�v�̐���
CMap* CMapManager::createMap(const std::string & fileName_)
{
	//���łɐ�������Ă����琶������Ă�����̂�Ԃ�
	if (this->m_pMap != NULL)
	{
		std::cerr << "���łɐ�������Ă��܂�" << std::endl;
		return this->m_pMap;
	}
	//�}�b�v�N���X�̐���
	this->m_pMap = CMap::create(fileName_);

	if (this->m_pMap == NULL)
	{
		std::cerr << "�}�b�v�̐����Ɏ��s���܂���!!" << std::endl;
		return NULL;
	}

	//�����ʒu�̐ݒ�
	game.TMXMapSetPos(0.0f, 0.0f);

	//���t�����Ă��邷�ׂẴ^�C���̃G�C���A�X�̃f�t�H���g���A���`�G�C���A�X�ɐݒ�
	//������h�~
	/*
	for (const auto & child : this->m_pMap->getChildren())
	{
		static_cast<cocos2d::SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
	}
	*/
	return this->m_pMap;
}

//�}�b�v�̎擾
CMap* CMapManager::getMap()
{
	return this->m_pMap;
}

//�}�b�v�̐ݒ�
CMap* CMapManager::setMap(const std::string & fileName_)
{
	//���łɐ�������Ă�����
	if (this->m_pMap != NULL)
	{
		//���݂̃}�b�v�̍폜
		this->m_pMap = NULL;

		//�}�b�v�N���X�̐���
		this->m_pMap = CMap::create(fileName_);

		if (this->m_pMap == NULL)
		{
			std::cerr << "�}�b�v�̐����Ɏ��s���܂���!!" << std::endl;
			return NULL;
		}

		//�����ʒu�̐ݒ�
		game.TMXMapSetPos(0.0f, 0.0f);

		//���t�����Ă��邷�ׂẴ^�C���̃G�C���A�X�̃f�t�H���g���A���`�G�C���A�X�ɐݒ�
		//������h�~
		/*
		for (const auto & child : this->m_pMap->getChildren())
		{
			static_cast<cocos2d::SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
		}
		*/
		return this->m_pMap;
	}
	else
	{
		//�}�b�v�N���X�̐���
		this->m_pMap = CMap::create(fileName_);

		if (this->m_pMap == NULL)
		{
			std::cerr << "�}�b�v�̐����Ɏ��s���܂���!!" << std::endl;
			return NULL;
		}

		//�����ʒu�̐ݒ�
		game.TMXMapSetPos(0.0f, 0.0f);

		//���t�����Ă��邷�ׂẴ^�C���̃G�C���A�X�̃f�t�H���g���A���`�G�C���A�X�ɐݒ�
		//������h�~
		/*
		for (const auto & child : this->m_pMap->getChildren())
		{
			static_cast<cocos2d::SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
		}
		*/
		return this->m_pMap;
	}
	
}


/*
* @desc	�G�o������
*/
void CMap::checkEnemyLaunch(float X,float Y)
{
	//�}�b�v���擾
	CMap* pMap = CMapManager::getInstance()->getMap();

	//���C���[�̈ʒu���擾
	CVec2 pt(X,Y);

	//���C���[��x�ʒu�ɉ�ʂ̉E�T�C�Y���𑫂����Ƃ�
	//�\������Ă����ʂ̉E�[�̈ʒu���擾�ł���
	float checkPosX = -pt.x + WINDOW_RIGHT;
	//�}�b�v�`�b�v�̃T�C�Y���擾(32,32)

	CSize& tileSize = this->getTileSize();

	//�^�C����2�����z���̍��W���擾(x���W�݂̂��`�F�b�N)
	CVec2 tileCoord = pMap->getTileCoord(CVec2(checkPosX, 0.0f));

	//���ݎQ�ƒ��̓G�o�����C���̃`�F�b�N
	if (pMap->m_launchEnemyLine == tileCoord.x)
	{

		//�����珇�Ƀ^�C���T�C�Y�����^�C�����`�F�b�N���Ă���
		for (float y = tileSize.height;y < WINDOW_TOP;y += tileSize.height)
		{
			//�`�F�b�N����^�C���̍��W��ݒ�(x�͌Œ��y���W���`�F�b�N���Ă���)
			CVec2 tilePos(checkPosX, y);

			//����x���W��2�����z����y�ʒu�ɂ��邷�ׂẴ^�C�����擾
			//���̃^�C���̃^�C���^�C�v(=�G�^�C�v)���擾
			ENEMY_TYPE eneType = (ENEMY_TYPE)pMap->checkTile(tilePos.x, tilePos.y, CMap::LAYER_TYPE::LAUNCH_ENEMY);

			//�G�̃^�C�v��NONE����Ȃ�������o��
			if (eneType != ENEMY_TYPE::NONE)
			{
				//�G�o���f�[�^���쐬
				CEnemyLaunchData* pLaunchData = new CEnemyLaunchData(eneType, tilePos);
				

				pLaunchData = new CEnemyLaunchData(
					(ENEMY_TYPE)pLaunchData->m_type,
					tilePos
				);


				CEnemyLaunchTrigger* pTrigger = new CEnemyLaunchTrigger(pLaunchData);

				CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);
			}


		}
		//�G�o�����C���̍X�V
		pMap->m_launchEnemyLine++;
	}
}

/*
* @desc	�G�o������
*/
void CMap::checkGimmickLaunch(float X, float Y)
{
	//�}�b�v���擾
	CMap* pMap = CMapManager::getInstance()->getMap();

	//���C���[�̈ʒu���擾
	CVec2 pt(X, Y);

	//���C���[��x�ʒu�ɉ�ʂ̉E�T�C�Y���𑫂����Ƃ�
	//�\������Ă����ʂ̉E�[�̈ʒu���擾�ł���
	float checkPosX = -pt.x + WINDOW_RIGHT;

	
	//�}�b�v�`�b�v�̃T�C�Y���擾(32,32)
	CSize& tileSize = this->getTileSize();

	//�^�C����2�����z���̍��W���擾(x���W�݂̂��`�F�b�N)
	CVec2 tileCoord = pMap->getTileCoord(CVec2(checkPosX, 0.0f));

	//���ݎQ�ƒ��̓G�o�����C���̃`�F�b�N
	if (pMap->m_launchGimmickLine == tileCoord.x)
	{

		//�����珇�Ƀ^�C���T�C�Y�����^�C�����`�F�b�N���Ă���
		for (float y = tileSize.height * 0.5f;y < WINDOW_TOP;y += tileSize.height)
		{
			//�`�F�b�N����^�C���̍��W��ݒ�(x�͌Œ��y���W���`�F�b�N���Ă���)
			CVec2 tilePos(checkPosX, y);

			//����x���W��2�����z����y�ʒu�ɂ��邷�ׂẴ^�C�����擾
			//���̃^�C���̃^�C���^�C�v(=�G�^�C�v)���擾
			GIMMICK_TYPE gimType = (GIMMICK_TYPE)pMap->checkTile(tilePos.x, tilePos.y, CMap::LAYER_TYPE::LAUNCH_GIMMICK);

			//�G�̃^�C�v��NONE����Ȃ�������o��
			if (gimType != GIMMICK_TYPE::NONE)
			{
				//�G�o���f�[�^���쐬
				CGimmickLaunchData* pLaunchData = new CGimmickLaunchData(gimType, tilePos);


				pLaunchData = new CGimmickLaunchData(
					(GIMMICK_TYPE)pLaunchData->m_type,
					tilePos
				);


				CGimmickLaunchTrigger* pTrigger = new CGimmickLaunchTrigger(pLaunchData);

				CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);
			}


		}
		//�G�o�����C���̍X�V
		pMap->m_launchGimmickLine++;
	}
}


/**
* @desc	�G�o����̓G�o�����C���[�̃^�C���̍폜
* @param �G�o���f�[�^
*/
void CMap::removeLaunchEnemyBlock(CEnemyLaunchData* pLaunchData)
{
	//�}�b�v���擾
	CMap* pMap = CMapManager::getInstance()->getMap();

	//�o�������ꏊ�̓G�o�����C���[�̃}�b�v�`�b�v��ENEMY_TYPE::NONE�ɂ���
	pMap->changeTile(
		(int)ENEMY_TYPE::NONE,
		pLaunchData->m_pos.x,
		pLaunchData->m_pos.y,
		CMap::LAYER_TYPE::LAUNCH_ENEMY
	);
}

/**
* @desc	�G�o����̓G�o�����C���[�̃^�C���̍폜
* @param �G�o���f�[�^
*/
void CMap::removeLaunchGimmickBlock(CGimmickLaunchData* pLaunchData)
{
	//�}�b�v���擾
	CMap* pMap = CMapManager::getInstance()->getMap();

	//�o�������ꏊ�̓G�o�����C���[�̃}�b�v�`�b�v��ENEMY_TYPE::NONE�ɂ���
	pMap->changeTile(
		(int)GIMMICK_TYPE::NONE,
		pLaunchData->m_pos.x,
		pLaunchData->m_pos.y,
		CMap::LAYER_TYPE::LAUNCH_GIMMICK
	);
}