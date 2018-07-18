#include "GameMainScene.h"

CGameMain::CGameMain()
{

	this->init();
}

CGameMain::~CGameMain()
{
	SAFE_DELETE(m_pCharacters);
}

bool CGameMain::init()
{
	
	//�S�e�N�X�`���폜
	m_game.allTextureDelete();
	//�X�e�[�W1���J��
	m_stage = new CStage1_1();
	BGM = m_stage->getBGM();
	if (CScene::init() == false)
	{
		printf("�V�[���������Ɏ��s");
		return false;
	}	
	

	m_game.allTextureDelete();

	//�}�b�v���J��(������)
	m_stage->init(m_game);
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


	//�w�i
	m_game.setupTexture(MAIN_BG, TEX_TYPE::PNG, BG_ID, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, WINDOW_RIGHT, WINDOW_TOP),LAYER::BG);
	m_game.setupTexture(MAIN_MOVEBG, TEX_TYPE::PNG, SCROLLBG_ID, CVec2(WINDOW_RIGHT * 3, WINDOW_TOP*0.5f), CVec4(0.0f, 0.0f, 6400.0f, 720.0f),LAYER::BG);
	
	//��ʑS��UI
	m_game.setupPoly(CVec4(WINDOW_RIGHT * 0.01f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), NULL, POLY_TYPE::QUAD, LAYER::UI, TAG_BEATSACTION1);
	m_game.setupPoly(CVec4(WINDOW_RIGHT * 0.99f, WINDOW_TOP * 0.5f, WINDOW_TOP * 0.01, WINDOW_TOP * 0.99f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), NULL, POLY_TYPE::QUAD, LAYER::UI, TAG_BEATSACTION2);
	m_game.setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.01f, WINDOW_RIGHT * 0.985, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), NULL, POLY_TYPE::QUAD, LAYER::UI, TAG_BEATSACTION3);
	m_game.setupPoly(CVec4(WINDOW_RIGHT * 0.5f, WINDOW_TOP * 0.99f, WINDOW_RIGHT * 0.985, WINDOW_TOP * 0.01f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), NULL, POLY_TYPE::QUAD, LAYER::UI, TAG_BEATSACTION4);


	pPlayerChara = (CPlayerCharacter*)CPlayerFactoryManager::getInstance()->create(320.0f, 200.0f);


	//�v���C���[1�̃^�O��ݒ�
	pPlayerChara->m_tag = TAG_PLAYER_1;

	//CCharacterAggregate�Ƀv���C���[��ǉ�
	CCharacterAggregate::getInstance()->add(pPlayerChara);

	SAFE_DELETE(notes);
	notes = new CNotesUI();


	//PlayerEffect
	m_game.setupPoly(CVec4(pPlayerChara->m_pMove->m_pos.x, pPlayerChara->m_pMove->m_pos.y, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 40.0f), 0, POLY_TYPE::QUAD, TAG_PLAYER_EFFECT_3);
	m_game.setupPoly(CVec4(pPlayerChara->m_pMove->m_pos.x, pPlayerChara->m_pMove->m_pos.y, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 60.0f), 0, POLY_TYPE::QUAD, TAG_PLAYER_EFFECT_2);
	m_game.setupPoly(CVec4(pPlayerChara->m_pMove->m_pos.x, pPlayerChara->m_pMove->m_pos.y, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 80.0f), 0, POLY_TYPE::QUAD, TAG_PLAYER_EFFECT_1);
	//Player
	//m_game.setupTexture(pPlayerChara->texPass, TEX_TYPE::PNG, pPlayerChara->m_texID, pPlayerChara->m_pMove->m_pos, (*pPlayerChara->m_pAnimations)[0]->getCurrentChip());
	m_game.setupPoly(CVec4(pPlayerChara->m_pMove->m_pos.x, pPlayerChara->m_pMove->m_pos.y, 64.0f,64.0f),CVec4(100.0f,100.0f,100.0f,100.0f),0,POLY_TYPE::QUAD, TAG_PLAYER_1);
	//�����킹UI
	m_game.setupTexture(notes->texPas, TEX_TYPE::PNG, NOTES_ID, CVec2(WINDOW_RIGHT - (*notes->m_pAnimations)[0]->getCurrentChip().z * 0.5f,WINDOW_BOTTOM + (*notes->m_pAnimations)[0]->getCurrentChip().w * 0.5), (*notes->m_pAnimations)[0]->getCurrentChip(), LAYER::UI);


	//UI�̃o�b�N
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, UI_BACK_ID, CVec2(WINDOW_RIGHT*0.120f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), LAYER::UI);

	//HP�̘g
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, OUTLINE_HP_ID, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), LAYER::UI);
	//DP�̘g
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, OUTLINE_DP_ID, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), LAYER::UI);

	//HP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, BAR_HP_ID , CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.962f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), LAYER::UI);
	//DP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, BAR_DP_ID, CVec2(WINDOW_RIGHT*0.12f, WINDOW_TOP*0.92f), CVec4(0.0f, 10.0f, 200.0f, 10.0f), LAYER::UI);
	//EnemyStats
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, ENEMY_STATS_ID, CVec2(WINDOW_RIGHT*0.355f, WINDOW_TOP*0.94f), CVec4(0.0f, 34.0f, 300.0f, 80.0f), LAYER::UI);
	//EnemyHPwaku
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, OUTLLINE_ENEMYHP_ID, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 20.0f, 210.0f, 14.0f), LAYER::UI);
	//EnemyHP
	m_game.setupTexture(IMAGE_GAMEUI, TEX_TYPE::PNG, BAR_ENEMYHP_ID, CVec2(WINDOW_RIGHT*0.35f, WINDOW_TOP*0.92f), CVec4(0.0f, 0.0f, 200.0f, 10.0f), LAYER::UI);




	pPlayerChara->input = input;




	return true;
}
bool CGameMain::stageChangeInit()
{
	//�w�i�|���S���R�̏�����
	m_trianglesLeft = m_stage->m_trianglesLeft;
	m_trianglesRight = m_stage->m_trianglesRight;

	m_polyRange = m_stage->m_polyRange;
	//������
	pPlayerChara->m_beatInterval = 0;
	pPlayerChara->m_beatCounter = 0;

	return true;
}

//�`��pUpdate
void CGameMain::rendUpdate()
{

	CScene::rendUpdate();

	//�X�e�[�W�I�����Ă��Ȃ����
	if (!m_stageEnd)
	{
		for (CCharacter* pChara : (*m_pCharacters))
		{
			if (pChara != pPlayerChara)
			{
				m_game.setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip(), pChara->m_texID);
				m_game.setTexScale(pChara->m_scale, pChara->m_texID);
				m_game.setPosition(pChara->m_pMove->m_pos, pChara->m_texID);
			}
		}
		m_game.setTextureRect((*notes->m_pAnimations)[notes->m_state]->getCurrentChip(), NOTES_ID);
		//m_game.setPosition(pPlayerChara->m_pMove->m_pos, pPlayerChara->m_texID);
		m_game.setPolyPos(CVec2(pPlayerChara->m_pMove->m_pos.x, pPlayerChara->m_pMove->m_pos.y), TAG_PLAYER_1);
	}
		
		
		
		
		
	//�J�����Ǐ]UI�n
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.120f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY), UI_BACK_ID);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY), OUTLINE_HP_ID);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.12f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY), OUTLINE_DP_ID);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.355f + cameraPosX, WINDOW_TOP*0.94f + cameraPosY), ENEMY_STATS_ID);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY), OUTLLINE_ENEMYHP_ID);
	//m_game.setPosition(CVec2(WINDOW_RIGHT*0.35f + cameraPosX, WINDOW_TOP*0.92f), 11);
	m_game.setPosition(CVec2(WINDOW_RIGHT*0.5f + cameraPosX, WINDOW_TOP*0.5f + cameraPosY), BG_ID);
	m_game.setPosition(CVec2( (WINDOW_RIGHT - (*notes->m_pAnimations)[0]->getCurrentChip().z * 0.5f) + cameraPosX , (WINDOW_BOTTOM + (*notes->m_pAnimations)[0]->getCurrentChip().w * 0.5 ) + cameraPosY) , NOTES_ID);
	m_game.setPolyPosX(WINDOW_RIGHT * 0.01f +cameraPosX, TAG_BEATSACTION1);
	m_game.setPolyPosX(WINDOW_RIGHT * 0.99f +cameraPosX, TAG_BEATSACTION2);
	m_game.setPolyPosX(WINDOW_RIGHT * 0.5f	+cameraPosX, TAG_BEATSACTION3);
	m_game.setPolyPosX(WINDOW_RIGHT * 0.5f	+cameraPosX, TAG_BEATSACTION4);
	
	//HP��HPCar�ɔ��f
	m_game.SetProgressBarWH(BAR_HP_ID, CVec4(0.0f, 0.0f, pPlayerChara->m_hitPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.962f + cameraPosY));
	//DP�����l
	m_game.SetProgressBarWH(BAR_DP_ID, CVec4(0.0f, 10.0f, pPlayerChara->m_denkiPoint, 10.0f), CVec2(WINDOW_RIGHT*0.042f + cameraPosX, WINDOW_TOP*0.92f + cameraPosY));

	if (!m_stageEnd)
	{

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

	
}

//�q�b�g�X�g�b�v�����݂���̂Œ���
void CGameMain::update()
{
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

	CLaunchScheduler::getInstance()->launchCharacters(m_game);
	this->playerAction();
	
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

//�Q�[���S�̂̓���(�X�e�[�W�ړ�)
void CGameMain::gameMain()
{

	//���̃X�e�[�W��
	if (pPlayerChara->m_nextStage)
	{

		if (!movingstage)
		{
			//�t�F�[�h�A�E�g
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, false) == true)
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
			if (m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true))
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

		scrollBackGroundTrianglesRight(cameraPosX);

	}
	//�v���C���[�̈ʒu�����̒l��������
	else if (pt.x < WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x)
	{
		//���_�ʒu�𒴂������ɐݒ肷��
		pt.x = WINDOW_RIGHT*0.2f - pPlayerChara->m_pMove->m_pos.x;

		//����������ݒ肷��
		map->setp(pt);

		cameraMoveX = pPlayerChara->m_pMove->m_vel.x;

		scrollBackGroundTrianglesLeft(cameraPosX + WINDOW_RIGHT);


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
			BGM->fadeOut(300);
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

void CGameMain::openMap()
{

	for (CCharacter* pChara : (*m_pCharacters))
	{
		if (pChara->m_tag != TAG_PLAYER_1)
		{
			pChara->m_activeFlag = false;
		}
	}

	//BGM�̃t�F�[�h�A�E�g
	BGM->fadeOut(300);

	m_game.allTextureDeletenotPlayer();

	m_stage = m_stage->changeStage();
	BGM = m_stage->getBGM();

	if (CScene::init() == false)
	{
		printf("�X�e�[�W�J�ڂɎ��s");
	}

	m_stage->init(m_game);
	if (this->stageChangeInit() == false)
		printf("�X�e�[�W�J�ڗp�������Ɏ��s");
}

//�w�i�X�N���[���p�̊֐�
//���փX�N���[����
void CGameMain::scrollBackGroundTrianglesLeft(float posX)
{
	for (int i = 0; i < m_trianglesLeft.size();i++)
	{
		//�|���S���̍�����ʉE�[�ɗ�����
		if (m_trianglesLeft[i] >= posX)
		{
			float pos = m_trianglesLeft[i];

			//������ʍ��[+�|���S���Ԋu�ɍĐݒu
			m_trianglesLeft[i] = pos - WINDOW_RIGHT - m_polyRange;
			//�E����ʍ��[��
			m_trianglesRight[i] = pos - WINDOW_RIGHT;
			//�F���Đݒ�
			int r = rand() % 100;
			int l = i;
			while (l >= 0)
			{
				l -= 2;
				if (l <= -1)
				{
					m_game.setTrianglesPolyPos(m_trianglesLeft[i], m_stage->getChangePositionColor(false), i);	//�w�i�ɔ��f
					break;
				}
				else if(l <= 0)
				{
					m_game.setTrianglesPolyPos(m_trianglesLeft[i], m_stage->getChangePositionColor(true), i);	//�w�i�ɔ��f
					break;
				}
			}
		}
	}
}
//�E�փX�N���[����
void CGameMain::scrollBackGroundTrianglesRight(float posX)
{
	for (int i = 0; i < m_trianglesRight.size(); i++)
	{
		float pos = m_trianglesRight[i];

		//�|���S���̉E����ʍ��[�ɗ�����
		if (m_trianglesRight[i] <= posX)
		{
			//������ʉE�[��
			m_trianglesLeft[i] = pos + WINDOW_RIGHT ;
			//�E����ʉE�[+�|���S���Ԋu��
			m_trianglesRight[i] = pos + WINDOW_RIGHT + m_polyRange;
			//�F���Đݒ�
			int r = rand() % 100;
			int l = i;
			while (l >= 0)
			{
				l -= 2;
				if (l <= -1)
				{
					m_game.setTrianglesPolyPos(m_trianglesLeft[i], m_stage->getChangePositionColor(false), i);	//�w�i�ɔ��f
					break;
				}
				else if (l <= 0)
				{
					m_game.setTrianglesPolyPos(m_trianglesLeft[i], m_stage->getChangePositionColor(true), i);	//�w�i�ɔ��f
					break;
				}
			}
		}
	}
}

void CGameMain::playerAction()
{
	//�_���[�W���ɐF��ς���
	if (pPlayerChara->m_isDamage)
	{
		m_game.setPolyColor(CVec4(100.0f, 0.0f, 0.0f, 100.0f),TAG_PLAYER_1);
	}
	else if (pPlayerChara->musicNotesMiss > 0)
	{
		//beats�̃~�X�̓s���N
		m_game.setPolyColor(CVec4(100.0f, 50.0f, 50.0f, 100.0f), TAG_PLAYER_1);
	}
	else if (pPlayerChara->m_isAvoidance)
	{
		//��𐬌����̉���s���͉��F
		m_game.setPolyColor(CVec4(100.0f, 100.0f, 0.0f, 100.0f), TAG_PLAYER_1);
	}
	else
	{
		//�����Ȃ���Ζ߂�
		m_game.setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 100.0f), TAG_PLAYER_1);
	}
	//��]���
	if (playerRolling)
	{
		playerAngle -= pPlayerChara->m_CharaLaunchVector.x*50.0f;
		if (playerAngle >= 600 || playerAngle <= -600)
		{
			playerAngle = 0;
			playerRolling = false;
		}
		m_game.setPolyAngle(playerAngle, TAG_PLAYER_1);
	}
	//Player�̃G�t�F�N�g����
	this->playerEffect();
}

void CGameMain::playerEffect()
{
	//�����Ă���G�t�F�N�g�\��
	if (pPlayerChara->m_pMove->m_vel.x != 0 || pPlayerChara->m_pMove->m_vel.y != 0)
	{
		playerEffectCount[0]++;
		playerEffectCount[1]++;
		playerEffectCount[2]++;
		if (playerEffectCount[0] >= 2)
		{
			playerEffectCount[0] = 0;
			m_game.setPolyPos(CVec2(pPlayerChara->m_pMove->m_pos.x, pPlayerChara->m_pMove->m_pos.y), TAG_PLAYER_EFFECT_1);
			m_game.setPolyScale(m_game.getPolyScale(TAG_PLAYER_1), TAG_PLAYER_EFFECT_1);
			m_game.setPolyAngle(m_game.getPolyAngle(TAG_PLAYER_1), TAG_PLAYER_EFFECT_1);
			CVec4 playerColor = m_game.getPolyColor(TAG_PLAYER_1);
			playerColor.w = 80.0f;
			m_game.setPolyColor(playerColor, TAG_PLAYER_EFFECT_1);
		}
		if (playerEffectCount[1] >= 4)
		{
			playerEffectCount[1] = 0;
			m_game.setPolyPos(CVec2(pPlayerChara->m_pMove->m_pos.x, pPlayerChara->m_pMove->m_pos.y), TAG_PLAYER_EFFECT_2);
			m_game.setPolyScale(m_game.getPolyScale(TAG_PLAYER_1), TAG_PLAYER_EFFECT_2);
			m_game.setPolyAngle(m_game.getPolyAngle(TAG_PLAYER_1), TAG_PLAYER_EFFECT_2);
			CVec4 playerColor = m_game.getPolyColor(TAG_PLAYER_1);
			playerColor.w = 60.0f;
			m_game.setPolyColor(playerColor, TAG_PLAYER_EFFECT_2);
		}
		if (playerEffectCount[2] >= 6)
		{
			playerEffectCount[2] = 0;
			m_game.setPolyPos(CVec2(pPlayerChara->m_pMove->m_pos.x, pPlayerChara->m_pMove->m_pos.y), TAG_PLAYER_EFFECT_3);
			m_game.setPolyScale(m_game.getPolyScale(TAG_PLAYER_1), TAG_PLAYER_EFFECT_3);
			m_game.setPolyAngle(m_game.getPolyAngle(TAG_PLAYER_1), TAG_PLAYER_EFFECT_3);
			CVec4 playerColor = m_game.getPolyColor(TAG_PLAYER_1);
			playerColor.w = 40.0f;
			m_game.setPolyColor(playerColor, TAG_PLAYER_EFFECT_3);
		}
		moving = true;
	}
	//�����Ă��Ȃ���΃G�t�F�N�g��\��
	else
	{
		//�O��̏������u�����Ă����ԁv�Ȃ�
		if (moving == true)
		{
			moving = false;
			m_game.setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 0.0f), TAG_PLAYER_EFFECT_1); 
			m_game.setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 0.0f), TAG_PLAYER_EFFECT_2);
			m_game.setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 0.0f), TAG_PLAYER_EFFECT_3);
		}
	}

}

void CGameMain::halfUpdate()
{
	m_game.notesAction(m_stage->backgroundType);
}

void CGameMain::qauarterUpdate()
{
	(*pPlayerChara->m_pSounds)[(int)SOUND::PLAYER_BEATS]->Play();
	m_game.polygonAction(TAG_PLAYER_1,0);
	m_game.polygonAction(TAG_BEATSACTION1,1);
	m_game.polygonAction(TAG_BEATSACTION2,1);
	m_game.polygonAction(TAG_BEATSACTION3,1);
	m_game.polygonAction(TAG_BEATSACTION4,1);
	//���q�Ԋu�̍X�V����
	for (CCharacter* pChara : (*m_pCharacters))
	{
		pChara->quarterUpdate();
	}
	if(notes != NULL)
		notes->quarter();

	playerRolling = true;
}

void CGameMain::eighthUpdate()
{

}