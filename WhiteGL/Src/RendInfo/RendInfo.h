#pragma once
#include "../Vec2.h"
#include "../Vec4.h"

//�e�N�X�`���̃^�C�v
enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
	QUAD = 3,
};
//���C���[�̃^�C�v
enum class LAYER : int
{
	BG = 0,
	MAIN = 1,
	UI = 2,
	BB = 3,
	MAX = BB,
};

class CRendInfo
{
protected:
	CVec4	_texRectPos = {};	//�e�N�X�`���̐؂����`
	CVec2	_texPosition = {};	//�e�N�X�`���̃|�W�V����
	int _texTag = {};	//�e�N�X�`���̃^�O
	CVec4	_texRect = {};	//�e�N�X�`���̋�`
	CVec2	_texWH = {};	//�e�N�X�`���̏c��
	CVec2	_texScale = {};	//�e�N�X�`���̃X�P�[��
	float	_texDefaultScale = {};	//�e�N�X�`���̏����X�P�[��
	TEX_TYPE _texType = {};	//�e�N�X�`���̃^�C�v
	CVec4	_texColorRGBA = {};	//�e�N�X�`���̐F���
};