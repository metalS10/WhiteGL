#pragma once
#include "public/Scene.h"
#include "PlayerFactory.h"
#include "LaunchTrigger.h"
#include "TitleScene.h"

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
	
	
public:
	CGameMain();
	~CGameMain();
	bool init()override;
	void update()override;
	void rendUpdate()override;
	void sceneUpdate()override;


	void gameMain();
	void scroll();

	void StageEnd(bool clear);
	void openMap(std::string mapData);


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