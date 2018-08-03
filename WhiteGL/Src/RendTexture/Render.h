#pragma once
/**
*Render.h
*
*	2017/10/10	Mat
*		�e�N�X�`���̓ǂݍ��݁A�`��
*/

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../Image/image.h"
#include "../Vec2.h"
#include "../Vec3.h"
#include "../Vec4.h"
#include "../Constants.h"
#include "../Data/Animation/Animation.h"
#include <vector>

#pragma warning(disable:4996)

//�e�N�X�`���̃^�C�v
enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
	QUAD = 3,
};
//���C���[�̃^�C�v
enum class LAYER : GLuint
{
	BG = 0,
	MAIN = 1,
	UI = 2,
	MAX = 2,
};

//�S�Ă̕`���S���N���X
class CRenderer
{
public:
	CVec4 _texRectPos[MAX_TEXTURE_NUMBER] = {};	//�e�N�X�`���̐؂����`
	CVec2 _texPosition[MAX_TEXTURE_NUMBER] = {};	//�e�N�X�`���̃|�W�V����
	GLuint _texTag[MAX_TEXTURE_NUMBER] = {};		//�e�N�X�`���̃^�O
	CVec4 _texRect[MAX_TEXTURE_NUMBER] = {};		//�e�N�X�`���̋�`
	CVec2 _texWH[MAX_TEXTURE_NUMBER] = {};			//�e�N�X�`���̏c��
	CVec2 _texScale[MAX_TEXTURE_NUMBER] = {};		//�e�N�X�`���̃X�P�[��
	float _texDefaultScale[MAX_TEXTURE_NUMBER] = {};	//�e�N�X�`���̏����X�P�[��
	TEX_TYPE _texType[MAX_TEXTURE_NUMBER] = {};		//�e�N�X�`���̃^�C�v
	CVec4 _texColorRGBA[MAX_TEXTURE_NUMBER] = {};	//�e�N�X�`���̐F���

	//�e�N�X�`�����
	GLuint _texID[MAX_TEXTURE_NUMBER] = {};
	CImage* _texImage[MAX_TEXTURE_NUMBER] = {};
	bool _texActionFade[MAX_TEXTURE_NUMBER] = {};
	float _texActionFadeInterval[MAX_TEXTURE_NUMBER] = {};
	bool _texFadeOut[MAX_TEXTURE_NUMBER] = {};

	//�̎O�p�|���S���p
	CVec4 _bgPolyVert[MAX_BACKGROUND_NUMBER] = {};
	CVec4 _bgPolyColor[MAX_BACKGROUND_NUMBER] = {};
	GLuint _bgPolyLine[MAX_BACKGROUND_NUMBER] = {};
	GLuint _bgPolyMaxLine = 0;
	GLuint _bgPolyDefaultVert = 0;

	//�̃|���S���p
	CVec4 _polyVert[MAX_POLYGON_NUMBER] = {};
	CVec4 _polyColor[MAX_POLYGON_NUMBER] = {};
	CVec2 _polyDefaultVert[MAX_POLYGON_NUMBER] = {};
	float _polyAngle[MAX_POLYGON_NUMBER] = {};
	GLuint _polyTag[MAX_POLYGON_NUMBER] = {};

	//�|���S���B�̃A�j���[�V�����p
	GLuint upfadeCount = 0;
	GLuint _beatUpSize = BEAT_BIGSIZE;
	 
	//���C���ݒ�p
	LAYER m_texLayer[MAX_TEXTURE_NUMBER] = {};
	LAYER m_bgPolyLayer[MAX_BACKGROUND_NUMBER] = {};
	LAYER m_polyLayer[MAX_POLYGON_NUMBER] = {};



	CRenderer()
	{

	}

	~CRenderer()
	{
		for (int i = 0;i < MAX_TEXTURE_NUMBER;i++)
		{
			deleteTexture(i);
			SAFE_DELETE(_texImage[i]);
		}
	}

public:

	//�A�j���[�V�����X�V
	void update(std::vector<CAnimation*>* anim);

	//�S�Ă̕`��X�V����
	void render();

	/**
	*�e�N�X�`���̓ǂݍ��݁AID�̐ݒ�A�摜�͈�
	*
	*@param	texID	ID
	*@param	file	�t�@�C���p�X
	*@param	posLeft		�摜�̍��̈ʒu
	*@param	posRight	�摜�̉E�̈ʒu
	*@param	posBottom	�摜�̉��̈ʒu
	*@param	posTop		�摜�̏�̈ʒu
	*@param	rect		��`
	*/
	void setupTexture(const char *file, const TEX_TYPE tex_type, GLuint texID,const LAYER layer,const GLuint tag);

	//�O�p�|���S���ݒ�
	void setupTrianglesPoly(const CVec4 vertex, const CVec4 color, const GLuint line,const LAYER layer);
	void setTrianglesPolyPos(const float vertexX, const CVec4 color, const GLuint number);

	//�|���S���ݒ�
	void setupPoly(const CVec4 vertex, const CVec4 color, const LAYER layer, const GLuint tag);
	void setPolyPos(const CVec2 vertex, const GLuint tag);	//�|���S���̍��W�Đݒ�
	void setPolyScale(const CVec2 scale, const GLuint tag);	//�|���S���̃X�P�[���Đݒ�
	void setPolyPosX(const float vertex, const GLuint tag);	//�|���S���̍��W�Đݒ�
	void setPolyAngle(const float angle,const GLuint tag);	//�|���S���̉�]�ݒ�
	void setPolyColor(const CVec4 color, const GLuint tag);	//�|���S���̐F�ݒ�
	void addPolyAngle(const float angle,const GLuint tag);	//�|���S���̉�]��
	float getPolyAngle(const GLuint tag);	//�|���S���̉�]�擾
	CVec2 getPolyScale(const GLuint tag);	//�|���S���̃X�P�[���擾
	CVec4 getPolyColor(const GLuint tag);	//�|���S���̐F�擾

	//�e�N�X�`���̃T�C�Y�ݒ�
	void setupTextureSize(const CVec2 texPos, const CVec4 texRect,const GLuint texID);
	void setupTextureSizeAtTag(const CVec2 texPos, const CVec4 texRect,const GLuint tag);

	//PngImage�̃��[�h�֐�(���ꂾ���߂��Ⴍ���ᒷ���̂ŕ����܂���)
	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

	//�e�N�X�`���̐F�ݒ�
	void setupTextureColor(const CVec4 cloar,const GLuint texID);
	void setupTextureColorAtTag(const CVec4 cloar,const GLuint tag);
	
	//�e�N�X�`���̃t�F�[�h�ݒ�
	void TextureFade(const GLuint texID,const bool out,const float fadeInterval);

	//�e�N�X�`���̍폜
	void deleteTexture(const GLuint texID);
	//�|���S���̍폜
	void deletePoly(const GLuint tag);

	//�e�N�X�`���̃X�P�[���ݒ�
	void setTextureScale(const CVec2 Size, const GLuint texID);
	void setTextureScaleAtTag(const CVec2 Size, const GLuint texID);

	//�e�N�X�`���̍��W�ݒ�
	void setTexPosition(const CVec2 position, const GLuint texID);
	void setTexPositionAtTag(const CVec2 position, const GLuint tag);

	//�}�b�v�f�[�^�̍��W�ݒ�
	void setMapPosition(const CVec2 position, const GLuint texID);

	//�e�N�X�`���̋�`�ݒ�
	void setTextureRect(const CVec4 Rect, const GLuint texID);

	//�t�F�[�h�C���E�A�E�g���̃e�N�X�`���̐F�ύX����
	void fadeSearch();

	void allTextureDelete();			//�Q�[���̒��̃e�N�X�`�������ׂč폜
	void allTextureDeletenotPlayer();	//�Q�[���ɕK�v�s���ȃe�N�X�`���ȊO�̃e�N�X�`�����폜(�X�e�[�W�ړ�)

	//HP��BP�̃o�[�̂��߂̋�`�ݒ�
	void SetProgressBarWH(const GLuint texID, const CVec4 Rect,const CVec2 position);

	void notesFadeBackground();	//�w�i�p�̍X�V����
	void polygonNotesAction();		//beats�ɍ��킹��A�N�V�����̍X�V����
	void textureNotesAction();		//�e�N�X�`����beats�ɍ��킹��A�N�V�����̍X�V����

	void notesRandomFadeInit();		//�w�i�p�̃����_��������
	void notesUpFadeInit(const GLuint mode);			//�w�i�p�̏�ɏオ���Ă���������(mode)
	void polygonNotesActionInit(const GLuint tag,const GLuint mode );		//beats�ɍ��킹��A�N�V����(mode(0:�T�C�Y,1�F))
};