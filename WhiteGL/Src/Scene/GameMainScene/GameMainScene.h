#pragma once
#include "../Scene.h"
#include "../../Factory/PlayerFactory/PlayerFactory.h"
#include "../../Data/LaunchTrigger/LaunchTrigger.h"
#include "../TitleScene/TitleScene.h"
#include "../../Data/Stage/Stage.h"
#include "../../NotesUI/NotesUI.h"

class CGameMain : public CScene
{
private:
	bool movingstage = false;
	int stageSelectinterval = 0;
	bool m_stageEnd = false;
	bool m_stageClear = false;
	std::vector<CLaunchTrigger*>* m_pLaunchSchedule;
	std::vector<CCharacter*>* m_pCharacters;
	CPlayerCharacter* pPlayerChara;
	int m_EnemyNameInterval = 0;
	CStage* m_stage = NULL;
	CNotesUI* notes = NULL;
	//�w�i�|���S���̕~���l�ߊԊu
	float m_polyRange = 0.0f;
	//�w�i�̃|�W�V�����Q
	std::vector<float> m_trianglesLeft;
	std::vector<float> m_trianglesRight;

	int playerEffectCount[3] = {0,0,0};
	bool moving = false;
	float playerAngle = 0;
	bool playerRolling = false;


public:
	CGameMain();
	~CGameMain();
	bool init()override;		//����������
	void update()override;		//�V�т̓����X�V
	void rendUpdate()override;	//�`��X�V
	void sceneUpdate()override;	//�V�X�e���̍X�V
	void halfUpdate()override;	//2�������̍X�V
	void qauarterUpdate()override;	//4�������̍X�V
	void eighthUpdate()override;	//8�������̍X�V

	//�X�e�[�W�J�ڏ�����
	bool stageChangeInit() override;

	//�Q�[���̎�ȓ����̍X�V
	void gameMain();
	//���X�N���[��
	void scroll();
	
	//�X�e�[�W�̏I������
	void StageEnd(bool clear);
	//TiledMap�̓ǂݍ���&�J��
	void openMap();


	void scrollBackGroundTrianglesLeft(float posX);
	void scrollBackGroundTrianglesRight(float posX);

	void playerAction();
	void playerEffect();



	/**
	*	@desc	�`�F�b�N�Ǝ��O������ ( �P�� )
	*	@tips	�L���t���O�� false �̃C���X�^���X�����C���[������O��
	*/
	template <typename Ty>
	void checkAndRemove(Ty* pChara) 
	{
		if (pChara->m_activeFlag == false) 
		{
			pChara->removeFromParent();
		}
	}

	/**
	*	@desc	�`�F�b�N�Ǝ��O������ ( ���� )
	*	@tips	�L���t���O�� false �̃C���X�^���X�����C���[�� std::vector ������O��
	*/
	template <typename Ty>
	void checkAndRemove(std::vector<Ty*>* pCharas) {

		// ���[�J���ϐ��̌^�̃e���v���[�g�����̎w��Ƃ���
		// �e���v���[�g�������w�肷��ꍇ�� typename �w������Ȃ���΂Ȃ�Ȃ�
		typename std::vector<Ty*>::iterator itr = pCharas->begin();
		while (itr != pCharas->end()) {

			if ((*itr)->m_activeFlag == false)
			{
				if ((*itr)->m_charaType == CHARACTER_TYPE::ATTACK)
				{
					m_game.deletePoly(TAG_PLAYER_ATTACK);
				}
				(*itr)->removeFromParent();
				itr = pCharas->erase(itr);

			}
			else
			{
				itr++;
			}
		}
	}

	/**
	*@desc	�`�F�b�N�Ɖ��
	*@tips	�L���t���O��false�̃C���X�^���X���J����std::vector������O��
	*/
	template<typename Ty>
	void checkAndDelete(std::vector<Ty*>*pVector)
	{
		//���[�J���ϐ��̕��̃e���v���[�g�����̎w��Ƃ���
		//�e���v���[�g�������w�肷��ꍇ��typename�w������Ȃ���΂Ȃ�Ȃ�
		typename std::vector<Ty*>::iterator itr = pVector->begin();
		while (itr != pVector->end())
		{
			if ((*itr)->m_activeFlag == false)
			{
				SAFE_DELETE((*itr));
				itr = pVector->erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
};