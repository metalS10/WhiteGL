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


enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
	QUAD = 3,
};
enum class LAYER : GLuint
{
	BG = 0,
	MAIN = 1,
	UI = 2,
	MAX = 2,
};

class CRenderer
{
public:
	CVec4 _rectPos[MAX_TEXTURE_NUMBER] = {};	//�e�N�X�`���̐؂����`
	CVec2 _position[MAX_TEXTURE_NUMBER] = {};	//�e�N�X�`���̃|�W�V����
	GLuint _texTag[MAX_TEXTURE_NUMBER] = {};

	CVec4 rect[MAX_TEXTURE_NUMBER] = {};
	CVec2 texWH[MAX_TEXTURE_NUMBER] = {};
	CVec2 texScale[MAX_TEXTURE_NUMBER] = {};
	float texDefaultScale[MAX_TEXTURE_NUMBER] = {};

	TEX_TYPE texType[MAX_TEXTURE_NUMBER] = {};
	CVec4 colorRGBA[MAX_TEXTURE_NUMBER] = {};
	//�e�N�X�`�����
	GLuint g_texID[MAX_TEXTURE_NUMBER] = {};
	CImage* tex[MAX_TEXTURE_NUMBER] = {};
	bool actionFade[MAX_TEXTURE_NUMBER] = {};
	float actionFadeInterval[MAX_TEXTURE_NUMBER] = {};
	bool fadeOut[MAX_TEXTURE_NUMBER] = {};

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
			SAFE_DELETE(tex[i]);
		}
	}

public:

	void update(std::vector<CAnimation*>* anim);

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

	void setupTextureSize(const CVec2 texPos, const CVec4 texRect,const GLuint texID);
	void setupTextureSizeAtTag(const CVec2 texPos, const CVec4 texRect,const GLuint tag);

	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

	void setupTextureColor(const CVec4 cloar,const GLuint texID);
	void setupTextureColorAtTag(const CVec4 cloar,const GLuint tag);

	void TextureFade(const GLuint texID,const bool out,const float fadeInterval);

	void deleteTexture(const GLuint texID);
	void deletePoly(const GLuint tag);

	void setTextureScale(const CVec2 Size, const GLuint texID);
	void setTextureScaleAtTag(const CVec2 Size, const GLuint texID);

	void setPosition(const CVec2 position, const GLuint texID);
	void setPositionAtTag(const CVec2 position, const GLuint tag);

	void setMapPosition(const CVec2 position, const GLuint texID);

	void setTextureRect(const CVec4 Rect, const GLuint texID);

	void fadeSearch();

	void allTextureDelete();			//�Q�[���̒��̃e�N�X�`�������ׂč폜
	void allTextureDeletenotPlayer();	//�Q�[���ɕK�v�s���ȃe�N�X�`���ȊO�̃e�N�X�`�����폜(�X�e�[�W�ړ�)

	void SetProgressBarWH(const GLuint texID, const CVec4 Rect,const CVec2 position);

	void notesFadeBackground();	//�w�i�p�̍X�V����
	void polygonNotesAction();		//beats�ɍ��킹��A�N�V�����̍X�V����
	void textureNotesAction();		//�e�N�X�`����beats�ɍ��킹��A�N�V�����̍X�V����

	void notesRandomFadeInit();		//�w�i�p�̃����_��������
	void notesUpFadeInit(const GLuint mode);			//�w�i�p�̏�ɏオ���Ă���������(mode)
	void polygonNotesActionInit(const GLuint tag,const GLuint mode );		//beats�ɍ��킹��A�N�V����(mode(0:�T�C�Y,1�F))
};