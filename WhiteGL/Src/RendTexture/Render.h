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
	BB = 3,
	MAX = BB,
};

//�S�Ă̕`���S���N���X
class CRenderer
{
public:
	std::vector<CVec4>	_texRectPos		= {};	//�e�N�X�`���̐؂����`
	std::vector<CVec2>	_texPosition	= {};	//�e�N�X�`���̃|�W�V����
	std::vector<GLuint> _texTag			= {};	//�e�N�X�`���̃^�O
	std::vector<CVec4>	_texRect		= {};	//�e�N�X�`���̋�`
	std::vector<CVec2>	_texWH			= {};	//�e�N�X�`���̏c��
	std::vector<CVec2>	_texScale		= {};	//�e�N�X�`���̃X�P�[��
	std::vector<float>	_texDefaultScale= {};	//�e�N�X�`���̏����X�P�[��
	std::vector<TEX_TYPE> _texType		= {};	//�e�N�X�`���̃^�C�v
	std::vector<CVec4>	_texColorRGBA	= {};	//�e�N�X�`���̐F���

	//�e�N�X�`�����
	std::vector<GLuint> _texID = {};
	std::vector<CImage*> _texImage = {};
	std::vector<bool> _texActionFade = {};
	std::vector<float> _texActionFadeInterval = {};
	std::vector<bool> _texFadeOut = {};

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
	std::vector<GLuint> _polyTag = {};

	//�|���S���B�̃A�j���[�V�����p
	GLuint upfadeCount = 0;
	GLuint _beatUpSize = BEAT_BIGSIZE;
	 
	//���C���ݒ�p
	std::vector<LAYER> m_texLayer = {};
	LAYER m_bgPolyLayer[MAX_BACKGROUND_NUMBER] = {};
	LAYER m_polyLayer[MAX_POLYGON_NUMBER] = {};



	CRenderer()
	{
		init();
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

	//������
	void init();

	//�A�j���[�V�����X�V
	void update(std::vector<CAnimation*>* anim);

	//�S�Ă̕`��X�V����
	void render();

	/**
	*�e�N�X�`�����o�^
	*@param	file	�t�@�C���p�X
	*@param	tex_type	�e�N�X�`���̊g���q
	*@param	tag		�e�N�X�`��ID,texTag
	*@param	layer	���C���ݒ�
	*/
	void setupTexture(const char *file, const TEX_TYPE tex_type, GLuint tag,const LAYER layer);

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

	//�e�N�X�`���̃g�����X�t�H�[���ݒ�(������)
	void setupTextureTransform(const CVec2 texPos, const CVec4 texRect);
	//�e�N�X�`���̃g�����X�t�H�[���ݒ�
	void setupTextureTransformAtTag(const CVec2 texPos, const CVec4 texRect,const GLuint tag);

	//PngImage�̃��[�h�֐�(���ꂾ���߂��Ⴍ���ᒷ���̂ŕ����܂���)
	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

	//�e�N�X�`���̐F�ݒ�(������)
	void setupTextureColor(const CVec4 cloar);
	//�e�N�X�`���F�ύX�ݒ�
	void setupTextureColorAtTag(const CVec4 cloar,const GLuint tag);
	
	//�e�N�X�`���̃t�F�[�h�ݒ�
	void TextureFade(const GLuint tag,const bool out,const float fadeInterval);
	//�e�N�X�`���t�F�[�h�I�����Ă��邩
	bool endTextureFade(GLuint tag);

	//�e�N�X�`���̍폜
	void deleteTexture(const GLuint tag);
	//�|���S���̍폜
	void deletePoly(const GLuint tag);

	//�e�N�X�`���̃X�P�[���ݒ�
	void setTextureScale(const CVec2 Size, const GLuint texID);
	void setTextureScaleAtTag(const CVec2 Size, const GLuint tag);

	//�e�N�X�`���̍��W�ݒ�
	void setTexPosition(const CVec2 position, const GLuint texID);
	void setTexPositionAtTag(const CVec2 position, const GLuint tag);

	//�}�b�v�f�[�^�̍��W�ݒ�
	void setMapPosition(const CVec2 position, const GLuint tag);

	//�e�N�X�`���̋�`�ݒ�
	void setTextureRect(const CVec4 Rect, const GLuint texID);
	void setTextureRectAtTag(const CVec4 Rect, const GLuint tag);

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