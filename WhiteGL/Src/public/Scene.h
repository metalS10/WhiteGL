#pragma once
//�V�[���̐e�ƂȂ�N���X
class CScene
{
protected:

	float cameraMoveX = 0.0f;
	float cameraPosX = 0.0f;
public:
	CScene() { init(); };
	

	//�f�X�g���N�^
	virtual ~CScene() {};
	//����������
	virtual bool init() {return true; };
	//�X�V����
	virtual void update() {};
};
