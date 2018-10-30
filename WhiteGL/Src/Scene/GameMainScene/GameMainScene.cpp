#include "GameMainScene.h"
#include "../TitleScene/TitleScene.h"

CGameMain::CGameMain()
{

	this->init();
}

CGameMain::~CGameMain()
{


	SAFE_DELETE(notes);
	SAFE_DELETE(m_pCharacters);
	SAFE_DELETE(m_stage);
	CMapManager::removeInstance();
	SAFE_DELETE(m_backGround1);
	SAFE_DELETE(m_backGround2);
	SAFE_DELETE(m_UIBack);
	SAFE_DELETE(m_HPwaku);	//HPUI�g
	SAFE_DELETE(m_BPwaku);	//BPUI�g
	SAFE_DELETE(m_HP);	//BPUI
	SAFE_DELETE(m_BP);	//BPUI
	SAFE_DELETE(m_EnemyStatsUI);	//EnemyUI
	SAFE_DELETE(m_EnemyHPwaku);	//EnemyHPUI�g
	SAFE_DELETE(m_EnemyHP);	//EnemyHPUI
	SAFE_DELETE(m_GameEndUI);	//EnemyHPUI
	SAFE_DELETE(m_cirUI[0]);
	SAFE_DELETE(m_cirUI[1]);
	SAFE_DELETE(m_cirUI[2]);
	SAFE_DELETE(m_cirUI[3]);

	SAFE_DELETE(pPlayerChara);
	SAFE_DELETE(m_blackBoad);


}

bool CGameMain::init()
{
	

	//�`����̏�����
	m_game.renderInit();

	//�X�e�[�W1���J��
	m_stage = new CStage1_1();
	BGM = m_stage->getBGM();

	//�u���b�N�{�[�h
	m_blackBoad = new rendInfo::CTexRendInfo();
	m_blackBoad->setImage("", rendInfo::TEX_TYPE::QUAD, TAG_BLACKBORD, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 100.0f), rendInfo::LAYER::BB);

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

	//��x�폜���Ă��Ȃ��ƃX�e�[�W���x�V�񂾎��Ƀo�O���o��
	CLaunchScheduler::getInstance()->removeInstance();

	//�o���X�P�W���[�����o���X�P�W���[���[�Ɏ��t����
	CLaunchScheduler::getInstance()->createLauncher(m_pLaunchSchedule);

	//�L�����N�^�[�̏W�܂�̐���
	SAFE_DELETE(m_pCharacters);
	m_pCharacters = new std::vector<CCharacter*>();
	CCharacterAggregate::removeInstance();
	CCharacterAggregate::getInstance()->set(m_pCharacters);

	m_backGround1 = new rendInfo::CTexRendInfo();
	m_backGround2 = new rendInfo::CTexRendInfo();
	//�w�i
	m_backGround1->setImage(MAIN_BG, rendInfo::TEX_TYPE::PNG, TAG_BG, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, WINDOW_RIGHT, WINDOW_TOP), rendInfo::LAYER::BG);
	m_backGround2->setImage(MAIN_MOVEBG, rendInfo::TEX_TYPE::PNG, TAG_SCROLLBG, CVec2(WINDOW_RIGHT * 3, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 6400.0f, 720.0f), rendInfo::LAYER::BG);
	
	//��ʑS��UI
	m_cirUI[0] = new rendInfo::CPolygonRendInfo();
	m_cirUI[1] = new rendInfo::CPolygonRendInfo();
	m_cirUI[2] = new rendInfo::CPolygonRendInfo();
	m_cirUI[3] = new rendInfo::CPolygonRendInfo();
	m_cirUI[0]->setupPoly(CVec4(WINDOW_RIGHT * 0.01f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01f, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f),rendInfo::LAYER::UI);
	m_cirUI[1]->setupPoly(CVec4(WINDOW_RIGHT * 0.99f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01f, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[2]->setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.01f, WINDOW_RIGHT * 0.985f, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[3]->setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.99f, WINDOW_RIGHT * 0.985f, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	

	pPlayerChara = (CPlayerCharacter*)CPlayerFactoryManager::getInstance()->create(320.0f, 200.0f);


	//�v���C���[1�̃^�O��ݒ�
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregate�Ƀv���C���[��ǉ�
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	notes = new CNotesUI();


	
	
	m_UIBack = new rendInfo::CTexRendInfo();
	m_HPwaku = new rendInfo::CTexRendInfo();
	m_BPwaku = new rendInfo::CTexRendInfo();
	m_HP = new rendInfo::CTexRendInfo();
	m_BP = new rendInfo::CTexRendInfo();
	m_EnemyStatsUI = new rendInfo::CTexRendInfo();
	m_EnemyHPwaku = new rendInfo::CTexRendInfo();
	m_EnemyHP = new rendInfo::CTexRendInfo();

	//UI�̔w�i
	m_UIBack->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_UI_BACK, CVec2(WINDOW_RIGHT*0.120f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);

	//HP�̘g
	m_HPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLINE_HP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);
	//DP�̘g
	m_BPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLINE_DP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);

	//HP
	m_HP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_HP , CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);
	//DP
	m_BP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_DP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 10.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);
	//EnemyStats
	m_EnemyStatsUI->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_ENEMY_STATS, CVec2(WINDOW_RIGHT*0.355f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);
	//EnemyHPwaku
	m_EnemyHPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLLINE_ENEMYHP, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);
	//EnemyHP
	m_EnemyHP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_ENEMYHP, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);




	pPlayerChara->input = input;
	//�t�F�[�h�A�E�g
	m_blackBoad->setActionFade(true, 10.0f);


	return true;
}
bool CGameMain::stageChangeInit()
{
	//������
	pPlayerChara->m_beatInterval = 0;
	pPlayerChara->m_beatCounter = 0;

	cameraMoveX = 0.0f;
	cameraMoveY = 0.0f;
	return true;
}

//�`��pUpdate
void CGameMain::rendUpdate()
{

	CScene::rendUpdate();
		
	//�J�����Ǐ]UI�n
	m_UIBack->setTexPosition(CVec2(WINDOW_RIGHT*0.120f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY));
	m_HPwaku->setTexPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY));
	m_BPwaku->setTexPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));
	m_EnemyStatsUI->setTexPosition(CVec2(WINDOW_RIGHT*0.355f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY));
	m_EnemyHP->setTexPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));
	m_EnemyHPwaku->setTexPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));
	m_backGround1->setTexPosition(CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f + cameraPosY));
	notes->setTexPosition(CVec2(WINDOW_RIGHT-50.0f + cameraPosX, WINDOW_BOTTOM+50.0f + cameraPosY));
	m_cirUI[0]->setPolyPosX(WINDOW_RIGHT * 0.01f +cameraPosX);
	m_cirUI[1]->setPolyPosX(WINDOW_RIGHT * 0.99f +cameraPosX);
	m_cirUI[2]->setPolyPosX(WINDOW_RIGHT * 0.5f	+cameraPosX);
	m_cirUI[3]->setPolyPosX(WINDOW_RIGHT * 0.5f	+cameraPosX);
	
	//HP��HPCar�ɔ��f
	m_HP->SetProgressBarWH(CVec4(0.0f, 0.0f, pPlayerChara->m_hitPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY));
	//DP�����l
	m_BP->SetProgressBarWH(CVec4(0.0f, 10.0f, pPlayerChara->m_denkiPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

	if (!m_stageEnd)
	{

		CCharacter* pPlayerChara = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);

		if (pPlayerChara != NULL)
		{

			//�v���C���[�ɓG���Z�b�g����Ă����
			if (pPlayerChara->m_pNowEnemy != NULL)
			{
				//ENEMYHPBar�ɂ̓Z�b�g�����G��HP��ݒ�
				float EnemyHP = 100.0f * pPlayerChara->m_pNowEnemy->m_hitPoint / pPlayerChara->m_pNowEnemy->m_maxHitPoint;
				m_EnemyHP->SetProgressBarWH(CVec4(0.0f, 0.0f, EnemyHP, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

				//�G�̖��O�����x���ɃZ�b�g
				//text->setString(pPlayerChara->m_pNowEnemy->m_name);

				//�G�̖��O�������C���^�[�o��������������
				m_EnemyNameInterval = 0;
			}
			//�G���Z�b�g����Ă��Ȃ����
			else
			{
				//��ɂ���
				m_EnemyHP->SetProgressBarWH(CVec4(0.0f, 0.0f, 0.0f, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));


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
		m_EnemyHP->SetProgressBarWH(CVec4(0.0f, 0.0f, 0.0f, 10.0f), CVec2(WINDOW_RIGHT*0.272f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

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

	//�V�[���̐e�X�V
	CScene::update();
	//�J�����̐ݒ�
	cameraPosX += cameraMoveX;
	cameraPosY += cameraMoveY;

	gluLookAt(
		cameraMoveX, cameraMoveY, 0.0f,
		cameraMoveX, cameraMoveY, -10.0f,
		0.0f, 1.0f, 0.0f
	);

	scroll();
	this->cameraShake();
	notes->update();
	//�w�i�p
	m_stage->update();

	//��ʑS��UI�A�N�V�����X�V
	m_cirUI[0]->polygonBeatsAction();
	m_cirUI[1]->polygonBeatsAction();
	m_cirUI[2]->polygonBeatsAction();
	m_cirUI[3]->polygonBeatsAction();

	
}

//�q�b�g�X�g�b�v�����݂���̂Œ���
void CGameMain::update()
{
	m_blackBoad->textureActionFade();

	//�Q�[���G���h�{�^������������
	if (input->getOnKey(Input::Key::GameEnd) == true)
	{
		gluLookAt(
			-cameraPosX, 0.0f, 0.0f,
			-cameraPosX, 0.0f, -10.0f,
			0.0f, 1.0f, 0.0f
		);
		cameraPosX = 0.0f;
		stageSelectinterval = 0;
		m_stageEnd = false;
		//�^�C�g���V�[���𐶐�
		MS::CMS::getInstance()->setScene(new CTitle());		//�X�e�[�W�Z���N�g��ʂɖ߂�
	}
	//printf("%d\n",pPlayerChara->musicNotesCounter );
	//�Q�[���S�̂𐧌䂷��ꏊ
	gameMain();

	CLaunchScheduler::getInstance()->launchCharacters();
	
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
	m_blackBoad->setTexPosition(CVec2(WINDOW_RIGHT * 0.5f + cameraPosX, WINDOW_TOP * 0.5f + cameraPosY));

}

//�Q�[���S�̂̓���(�X�e�[�W�ړ�)
void CGameMain::gameMain()
{
	//���̃X�e�[�W��
	if (pPlayerChara->m_nextStage)
	{

		if (!movingstage)
		{
			//�t�F�[�h�A�E�g
			if (ActionStage(m_blackBoad, 1.0f, false) == true)
			{
				//�t�F�[�h�A�E�g���I������
				movingstage = true;
				//���̃X�e�[�W�ւ̊֐�
				openMap();
				gluLookAt(
					-cameraPosX, 0.0f, 0.0f,
					-cameraPosX, 0.0f, -10.0f,
					0.0f, 1.0f, 0.0f
				);
				cameraPosX = 0.0f;

				pPlayerChara->setPosition(CVec2(320.0f, 200.0f));
			}
		}
		//�t�F�[�h�A�E�g���I��������
		if (movingstage == true)
		{
			//�t�F�[�h�C���J�n
			if (ActionStage(m_blackBoad, 1.0f, true))
			{
				//�t�F�[�h�C�����I��
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

		m_stage->scrollBackGroundTrianglesRight(cameraPosX);

	}
	//�v���C���[�̈ʒu�����̒l��������
	else if (pt.x < WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x)
	{
		//���_�ʒu�𒴂������ɐݒ肷��
		pt.x = WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x;

		//����������ݒ肷��
		map->setp(pt);

		cameraMoveX = pPlayerChara->m_pMove->m_vel.x;

		m_stage->scrollBackGroundTrianglesLeft(cameraPosX + WINDOW_RIGHT);


	}
	else
	{
		cameraMoveX = 0.0f;

	}
	
}



//���݂̃Q�[���I������A�Z���N�g��ʂֈڍs
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
			m_GameEndUI = new rendInfo::CTexRendInfo();
			m_GameEndUI->setImage(IMAGE_STAGEEND, rendInfo::TEX_TYPE::PNG, 9995, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 1280.0f, 200.0f));


		}
		else
		{
			//Stagefailed��\��
			//this->m_StageFaildSprite->runAction(Show::create());
			m_GameEndUI = new rendInfo::CTexRendInfo();
			m_GameEndUI->setImage(IMAGE_STAGEEND, rendInfo::TEX_TYPE::PNG, 9995, CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f), CVec4(0.0f, 200.0f, 1280.0f, 200.0f));

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
			BGM->fadeOut(300);
			if (ActionStage(m_blackBoad,1.0f, false) == true)
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

void CGameMain::openMap()
{

	for (CCharacter* pChara : (*m_pCharacters))
	{
		if (pChara->m_tag != TAG_PLAYER_1)
		{
			pChara->m_activeFlag = false;
		}
	}
	m_game.changeStageInit();

	//------------------------------------
	//�摜�̍Đ���
	//------------------------------------
	//�u���b�N�{�[�h
	m_blackBoad = new rendInfo::CTexRendInfo();
	m_blackBoad->setImage("", rendInfo::TEX_TYPE::QUAD, TAG_BLACKBORD, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT), CVec4(0.0f, 0.0f, 0.0f, 100.0f), rendInfo::LAYER::BB);


	//BGM�̃t�F�[�h�A�E�g
	BGM->fadeOut(300);

	m_stage = m_stage->changeStage();
	BGM = m_stage->getBGM();

	m_backGround1 = new rendInfo::CTexRendInfo();
	m_backGround2 = new rendInfo::CTexRendInfo();
	//�w�i
	m_backGround1->setImage(MAIN_BG, rendInfo::TEX_TYPE::PNG, TAG_BG, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, WINDOW_RIGHT, WINDOW_TOP), rendInfo::LAYER::BG);
	m_backGround2->setImage(MAIN_MOVEBG, rendInfo::TEX_TYPE::PNG, TAG_SCROLLBG, CVec2(WINDOW_RIGHT * 3, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 6400.0f, 720.0f), rendInfo::LAYER::BG);

	//��ʑS��UI
	m_cirUI[0] = new rendInfo::CPolygonRendInfo();
	m_cirUI[1] = new rendInfo::CPolygonRendInfo();
	m_cirUI[2] = new rendInfo::CPolygonRendInfo();
	m_cirUI[3] = new rendInfo::CPolygonRendInfo();
	m_cirUI[0]->setupPoly(CVec4(WINDOW_RIGHT * 0.01f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01f, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[1]->setupPoly(CVec4(WINDOW_RIGHT * 0.99f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01f, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[2]->setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.01f, WINDOW_RIGHT * 0.985f, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);
	m_cirUI[3]->setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.99f, WINDOW_RIGHT * 0.985f, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::UI);

	m_UIBack = new rendInfo::CTexRendInfo();
	m_HPwaku = new rendInfo::CTexRendInfo();
	m_BPwaku = new rendInfo::CTexRendInfo();
	m_HP = new rendInfo::CTexRendInfo();
	m_BP = new rendInfo::CTexRendInfo();
	m_EnemyStatsUI = new rendInfo::CTexRendInfo();
	m_EnemyHPwaku = new rendInfo::CTexRendInfo();
	m_EnemyHP = new rendInfo::CTexRendInfo();

	//UI�̔w�i
	m_UIBack->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_UI_BACK, CVec2(WINDOW_RIGHT*0.120f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);

	//HP�̘g
	m_HPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLINE_HP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);
	//DP�̘g
	m_BPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLINE_DP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);

	//HP
	m_HP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_HP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);
	//DP
	m_BP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_DP, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 10.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);
	//EnemyStats
	m_EnemyStatsUI->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_ENEMY_STATS, CVec2(WINDOW_RIGHT*0.355f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), rendInfo::LAYER::UI);
	//EnemyHPwaku
	m_EnemyHPwaku->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_OUTLLINE_ENEMYHP, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), rendInfo::LAYER::UI);
	//EnemyHP
	m_EnemyHP->setImage(IMAGE_GAMEUI, rendInfo::TEX_TYPE::PNG, TAG_BAR_ENEMYHP, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), rendInfo::LAYER::UI);


	if (CScene::init() == false)
	{
		printf("�X�e�[�W�J�ڂɎ��s");
	}

	m_stage->init();
	if (this->stageChangeInit() == false)
		printf("�X�e�[�W�J�ڗp�������Ɏ��s");
}






void CGameMain::halfUpdate()
{
	m_stage->actionBackground(m_stage->backgroundType);
}

void CGameMain::qauarterUpdate()
{
	(*pPlayerChara->m_pSounds)[(int)SOUND::PLAYER_BEATS]->Play();
	pPlayerChara->polygonBeatsActionInit(0);
	m_cirUI[0]->polygonBeatsActionInit(1);
	m_cirUI[1]->polygonBeatsActionInit(1);
	m_cirUI[2]->polygonBeatsActionInit(1);
	m_cirUI[3]->polygonBeatsActionInit(1);
	//���q�Ԋu�̍X�V����
	for (CCharacter* pChara : (*m_pCharacters))
	{
		pChara->quarterUpdate();
	}
	if(notes != NULL)
		notes->quarter();

	pPlayerChara->playerRolling = true;
}

void CGameMain::eighthUpdate()
{

}

