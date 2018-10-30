#pragma once
#include "../Sound/Sound.h"
#include "../../Constants.h"
#include "../Map/Map.h"

//�X�e�[�W���̓����𓮂���

//�e�X�e�[�W�̂��ƂƂȂ�N���X
class CStage
{
protected:
	bool Boss = false;

	CSound* bgm;

	std::vector<rendInfo::CTriPolygonRendInfo*> m_bgPoly;
public:
	CStage(){}
	~CStage()
	{
		for (rendInfo::CTriPolygonRendInfo* triPoly : m_bgPoly)
		{
			SAFE_DELETE(triPoly);
		}
	}
	//����������(�w��̃}�b�v���J��)
	virtual void init() {}
	//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
	virtual CStage* changeStage() { return NULL; }
	//�X�e�[�W�w���BGM��Ԃ��B
	virtual CSound* getBGM() { return NULL; }
	//�X�e�[�W�̎w��̐F��Ԃ�(�X�N���[����)
	virtual CVec4 getChangePositionColor(bool Top) { return NULL; }
	//�X�e�[�W�̍X�V
	virtual	void update() {};

	//�w�i�|���S��Culling
	void scrollBackGroundTrianglesLeft(float posX);
	void scrollBackGroundTrianglesRight(float posX);

	//�w�i�|���S���̃A�N�V����
	void actionBackground(int mode);



protected:
	//�w�i�|���S���R
	std::vector<float> m_trianglesLeft = {};
	std::vector<float> m_trianglesRight ={};

	float m_polyRange = 0.0f;

	CVec4 backgroundVertex[2] = {};
	CVec4 backgroundColor[2] = {};
public:

	int backgroundType = 0;
};

//�X�e�[�W1-1
class CStage1_1 : public CStage
{
public:
	CStage1_1() {}
	~CStage1_1() {}
	//����������(�w��̃}�b�v���J��)
	virtual void init() override;
	//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
	virtual CStage* changeStage() override;
	//�X�e�[�W�w���BGM��Ԃ��B
	virtual CSound* getBGM() override;
	//�X�e�[�W�̎w��̐F��Ԃ�(�X�N���[����)
	virtual CVec4 getChangePositionColor(bool Top) override;
	//�X�e�[�W�̍X�V
	virtual	void update() override;
};
//�X�e�[�W1-2
class CStage1_2 : public CStage
{
public:
	CStage1_2() {}
	~CStage1_2() {}
	//����������(�w��̃}�b�v���J��
	virtual void init() override;
	//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
	virtual CStage* changeStage() override;
	//�X�e�[�W�w���BGM��Ԃ�
	virtual CSound* getBGM() override;
	//�X�e�[�W�̎w��̐F��Ԃ�(�X�N���[����)
	virtual CVec4 getChangePositionColor(bool Top) override;
	//�X�e�[�W�̍X�V
	virtual	void update() override;
};