#include "GameMainScene.h"

CGameMain::CGameMain()
{

	this->init();
}

CGameMain::~CGameMain()
{

}

bool CGameMain::init()
{
	//�X�e�[�W1���J��
	m_stage = new CStage1_1();
	BGM = m_stage->getBGM(BGM);
	if (CScene::init() == false)
	{
		printf("�V�[���������Ɏ��s");
		return false;
	}
	//�}�b�v���J��(������)
	m_stage->init();
	//BGM���J�n������
	m_BGMStart = false;

	//�o���X�P�W���[���̐���
	m_pLaunchSchedule = new std::vector<CLaunchTrigger*>();

	//����ō폜���Ă��Ȃ��ƃX�e�[�W���x�V�񂾎��Ƀo�O���o��(�ŋ��̓G)
	CLaunchScheduler::getInstance()->removeInstance();

	//�o���X�P�W���[�����o���X�P�W���[���[�Ɏ��t����
	CLaunchScheduler::getInstance()->createLauncher(m_pLaunchSchedule);

	//�L�����N�^�[�̏W�܂�̐���
	SAFE_DELETE(m_pCharacters);
	m_pCharacters = new std::vector<CCharacter*>();
	CCharacterAggregate::removeInstance();
	CCharacterAggregate::getInstance()->set(m_pCharacters);

	//�w�i
	m_game.setupTexture(MAIN_BG, TEX_TYPE::PNG, 0, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, WINDOW_RIGHT, WINDOW_TOP));
	m_game.setupTexture(MAIN_MOVEBG, TEX_TYPE::PNG, 1, CVec2(WINDOW_RIGHT * 3, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 6400.0f, 720.0f));



	pPlayerChara = (CPlayerCharacter*)CPlayerFactoryManager::getInstance()->create(320.0f, 200.0f);

	//�v���C���[1�̃^�O��ݒ�
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregate�Ƀv���C���[��ǉ�
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	m_game.setupTexture(pPlayerChara->texPass, TEX_TYPE::PNG, pPlayerChara->m_texID, pPlayerChara->m_pMove->m_pos, (*pPlayerChara->m_pAnimations)[0]->getCurrentChip());

	//UI�̃o�b�N
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, UI_BACK_ID, CVec2(WINDOW_RIGHT*0.125f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f));

	//HP�̘g
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, OUTLINE_HP_ID, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 20.0f, 210.0f, 14.0f));
	//DP�̘g
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, OUTLINE_DP_ID, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f));

	//HP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, BAR_HP_ID , CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 0.0f, 200.0f, 10.0f));
	//DP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, BAR_DP_ID, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 10.0f, 200.0f, 10.0f));
	//EnemyStats
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, ENEMY_STATS_ID, CVec2(WINDOW_RIGHT*0.355f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f));
	//EnemyHPwaku
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, OUTLLINE_ENEMYHP_ID, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f));
	//EnemyHP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, BAR_ENEMYHP_ID, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 0.0f, 200.0f, 10.0f));


	pPlayerChara->input = input;
	return true;
}

//�`��pUpdate
void CGameMain::rendUpdate()
{
	//�X�e�[�W�I�����Ă��Ȃ����
	if (!m_stageEnd)
	{
		for (CCharacter* pChara : (*m_pCharacters))
		{
			m_game.setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip(), pChara->m_texID);
			m_game.setScale(pChara->m_scale, pChara->m_texID);
			m_game.setPosition(pChara->m_pMove->m_pos, pChara->m_texID);
		}
	}


	m_game.setPosition(CVec2(WINDOW_RIGHT*0.125f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY), 4);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY), 5);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY), 6);
	//HP
	//m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.962f), 7);
	//DP
	//m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.92f), 8);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.355f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY), 9);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY), 10);
	//m_game.setPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f), 11);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f + cameraPosY), 0);


	if (!m_stageEnd)
	{
		//�_���[�W���󂯂���
		m_game.SetProgressBarWH(BAR_HP_ID, CVec4(0.0f, 0.0f, pPlayerChara->m_hitPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY));
		//�v���O���X�o�[��p�̓�����������
		m_game.SetProgressBarWH(BAR_DP_ID, CVec4(0.0f, 10.0f, pPlayerChara->m_denkiPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

		CCharacter* pPlayerChara = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);

		if (pPlayerChara != NULL)
		{

			//�v���C���[�ɓG���Z�b�g����Ă����
			if (pPlayerChara->m_pNowEnemy != NULL)
			{
				//ENEMYHPBar�ɂ̓Z�b�g�����G��HP��ݒ�
				float EnemyHP = 100 * pPlayerChara->m_pNowEnemy->m_hitPoint / pPlayerChara->m_pNowEnemy->m_maxHitPoint;
				m_game.SetProgressBarWH(BAR_ENEMYHP_ID, CVec4(0.0f, 0.0f, EnemyHP, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

				//�G�̖��O�����x���ɃZ�b�g
				//text->setString(pPlayerChara->m_pNowEnemy->m_name);

				//�G�̖��O�������C���^�[�o��������������
				m_EnemyNameInterval = 0;
			}
			//�G���Z�b�g����Ă��Ȃ����
			else
			{
				//��ɂ���
				m_game.SetProgressBarWH(BAR_ENEMYHP_ID, CVec4(0.0f, 0.0f, 0.0f, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));


				//���O����ɂ���̂͂�����Ƒ҂�
				this->m_EnemyNameInterval++;
				if (this->m_EnemyNameInterval >= 120)
				{
					//text->setString("");
					m_EnemyNameInterval = 0;

				}
			}
		}
	}
	else
	{
		//��ɂ���
		m_game.SetProgressBarWH(BAR_ENEMYHP_ID, CVec4(0.0f, 0.0f, 0.0f, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

		//���O����ɂ���̂͂�����Ƒ҂�
		this->m_EnemyNameInterval++;
		if (this->m_EnemyNameInterval >= 120)
		{
			//text->setString("");
			m_EnemyNameInterval = 0;

		}
	}
}

void CGameMain::sceneUpdate()
{

	scroll();
	this->cameraShake();

	cameraPosX += cameraMoveX;
	cameraPosY += cameraMoveY;

	gluLookAt(
		cameraMoveX, cameraMoveY, 0.0f,
		cameraMoveX, cameraMoveY, -10.0f,
		0.0f, 1.0f, 0.0f
	);
}

void CGameMain::update()
{
	//�V�[���̐e�X�V
	CScene::update();

	//�Q�[���S�̂𐧌䂷��ꏊ
	gameMain();

	CLaunchScheduler::getInstance()->launchCharacters(m_game);



	//�o���̊��������g���K�[�����ׂĎ��O��
	checkAndDelete(m_pLaunchSchedule);
	checkAndRemove(m_pCharacters);
	//�X�e�[�W�I�����Ă��Ȃ����
	if (!m_stageEnd)
	{
		for (CCharacter* pChara : (*m_pCharacters))
		{
			pChara->update();
		}
	}

	//�w�i�̃|�W�V�����Z�b�g
	m_game.setPosition(CVec2(WINDOW_RIGHT * 0.5 + cameraPosX, WINDOW_TOP * 0.5 + cameraPosY), MAX_TEXTURE_NUMBER - 1);
}

//�Q�[���S�̂̓���
void CGameMain::gameMain()
{
	//���̃X�e�[�W��
	if (pPlayerChara->m_nextStage)
	{

		if (!movingstage)
		{
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, false) == true)
			{
				movingstage = true;
				openMap(MAP_DATA_2);
				gluLookAt(
					-cameraPosX, 0.0f, 0.0f,
					-cameraPosX, 0.0f, -10.0f,
					0.0f, 1.0f, 0.0f
				);
				cameraPosX = 0.0f;

				pPlayerChara->setPosition(CVec2(320.0f, 200.0f), PLAYER_ID);
			}
		}
		if (movingstage == true)
		{
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true))
			{
				movingstage = false;
				pPlayerChara->m_nextStage = false;
			}
		}
	}

	if (pPlayerChara->m_stageClear)
	{
		this->StageEnd(pPlayerChara->m_stageClear);
	}
	if (pPlayerChara->m_gameOver)
	{
		this->StageEnd(pPlayerChara->m_stageClear);
	}

	
}


/*
*@desc	��ʃX�N���[��
*@tips	����͋����X�N���[���ł͂Ȃ��L�����N�^�[�̈ړ��ɂ���ʂ̃X�N���[���ƂȂ�
*/
void CGameMain::scroll()
{
	CMap* map = CMapManager::getInstance()->getMap();

	//�}�b�v�̈ʒu���擾
	CVec2 pt = map->getp();

	//�v���C���[�L�����N�^�[�̎擾
	CCharacter* pPlayerChara = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);

	//�v���C���[�̈ʒu���O�̒l�𒴂�����
	if (pt.x > WINDOW_RIGHT*0.7f - pPlayerChara->m_pMove->m_pos.x)
	{
		//���_�ʒu�𒴂������ɐݒ肷��
		pt.x = WINDOW_RIGHT*0.7f - pPlayerChara->m_pMove->m_pos.x;

		//����������ݒ肷��
		map->setp(pt);

		cameraMoveX = pPlayerChara->m_pMove->m_vel.x;

		//�X�N���[�����s��ꂽ�Ƃ��ɓG�̏o��������s��
		map->checkEnemyLaunch(pt.x, pt.y);

		//�M�~�b�N�̏o��������s��
		map->checkGimmickLaunch(pt.x, pt.y);

	}
	//�v���C���[�̈ʒu�����̒l��������
	else if (pt.x < WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x)
	{
		//���_�ʒu�𒴂������ɐݒ肷��
		pt.x = WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x;

		//����������ݒ肷��
		map->setp(pt);

		cameraMoveX = pPlayerChara->m_pMove->m_vel.x;




	}
	else
	{
		cameraMoveX = 0.0f;

	}
	
}




void CGameMain::StageEnd(bool clear)
{
	stageSelectinterval++;
	if (!m_stageEnd)
	{
		//StageEndgrid���A�N�V����
		//this->nodegrid->runAction(ReverseTime::create(PageTurn3D::create(0.5, Size(200, 100))));
		if (clear)
		{
			//StageClear��\��
			//this->m_StageClearSprite->runAction(Show::create());
			m_game.setupTexture(IMAGE_STAGEEND, TEX_TYPE::PNG, 9995, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 1280.0f, 200.0f));


		}
		else
		{
			//Stagefailed��\��
			//this->m_StageFaildSprite->runAction(Show::create());
			m_game.setupTexture(IMAGE_STAGEEND, TEX_TYPE::PNG, 9995, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 200.0f, 1280.0f, 200.0f));

		}
		//�X�e�[�W���I��
		m_stageEnd = true;
		stageSelectinterval = 0;
	}
	if (stageSelectinterval >= 60)
	{
		//�t�F�[�h�C���J�n
		if (!movingstage)
		{
			//BGM�̃t�F�[�h�A�E�g
			BGM->fadeOut(100);
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, false) == true)
			{
				movingstage = true;
				gluLookAt(
					-cameraPosX, cameraPosY, 0.0f,
					-cameraPosX, cameraPosY, -10.0f,
					0.0f, 1.0f, 0.0f
				);
				cameraPosX = 0.0f;
			}
		}
		//�t�F�[�h�C���I��
		if (movingstage == true)
		{
			stageSelectinterval = 0;
			m_stageEnd = false;
			//�^�C�g���V�[���𐶐�
			MS::CMS::getInstance()->setScene(new CTitle());		//�X�e�[�W�Z���N�g��ʂɖ߂�
		}
	}


}

void CGameMain::openMap(std::string mapData)
{

	for (CCharacter* pChara : (*m_pCharacters))
	{
		if (pChara->m_tag != TAG_PLAYER_1)
		{
			pChara->m_activeFlag = false;
		}
	}

	m_game.allTextureDeletenotPlayer();

	m_stage = m_stage->changeStage();
	m_stage->init();

}

void CGameMain::qauarterUpdate()
{
	//player�̃J�E���^�[
	pPlayerChara->musicNotesCounter = m_quarterNotes * 0.5f;
	pPlayerChara->DPHeal(1.0f);
}