#include "Stage.h"

//����������
void CStage1_1::init()
{
	//�X�e�[�W�ɒ�߂�ꂽ�}�b�v���J��
	CMapManager::getInstance()->setMap(MAP_DATA_1);
}
//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
CStage* CStage1_1::changeStage()
{
	//���̃X�e�[�W��Ԃ�
	return new CStage1_2;
}

//�X�e�[�W�w���BGM��Ԃ��B
CSound* CStage1_1::getBGM(CSound* bgm)
{
	//��x������폜
	SAFE_DELETE(bgm);
	//���̃X�e�[�W��BGM��ݒ�
	bgm = new CSound(SOUND_BGM, 139, true);
	//�ݒ肵�����̂�n��
	return bgm;
}

//����������
void CStage1_2::init()
{
	//�X�e�[�W�ɒ�߂�ꂽ�}�b�v���J��
	CMapManager::getInstance()->setMap(MAP_DATA_2);
}
//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
CStage* CStage1_2::changeStage()
{
	//���̃X�e�[�W��Ԃ�
	return NULL;
}

//�X�e�[�W�w���BGM��Ԃ��B
CSound* CStage1_2::getBGM(CSound* bgm)
{
	//��x������폜
	SAFE_DELETE(bgm);
	//���̃X�e�[�W��BGM��ݒ�
	bgm = new CSound(SOUND_BGM, 139, true);
	//�ݒ肵�����̂�n��
	return bgm;
}