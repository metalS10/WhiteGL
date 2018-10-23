#pragma once
#include "../Vec2.h"
#include "../Vec4.h"
#include "../Image/image.h"
#include "../RendTexture/Render.h"

namespace rendInfo
{
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

	//==========================================
	//�e�N�X�`��
	//==========================================
	class CTexRendInfo
	{
	private:
		GLuint	_texID = 0;			//�e�N�X�`����ID���
		CImage* _texImage = {};		//�e�N�X�`���̉摜���
		CVec4	_texRectPos = {};	//�e�N�X�`���̐؂����`
		CVec2	_texPosition = {};	//�e�N�X�`���̃|�W�V����
		int		_texTag = {};		//�e�N�X�`���̃^�O
		CVec2	_texWH = {};		//�e�N�X�`���̏c��
		CVec2	_texScale = {};		//�e�N�X�`���̃X�P�[��
		CVec4	_texRect = {};		//�e�N�X�`���̋�`
		float	_texDefaultScale = {};	//�e�N�X�`���̏����X�P�[��
		TEX_TYPE _texType = {};		//�e�N�X�`���̃^�C�v
		CVec4	_texColorRGBA = {};	//�e�N�X�`���̐F���
		render::CRenderer* m_renderer = {};	//�`���
		LAYER _texLayer = {};		//�e�N�X�`���̃��C���ݒ�

		int _texActionFadeCounter = 0;	//�t�F�[�h�C���E�A�E�g�̑��x
		bool _texFadeOut = false;		//�t�F�[�h�A�E�g���ۂ�(true�Ȃ�t�F�[�h�C��)
		bool _texActionFade = false;	//�t�F�[�h�C���E�A�E�g�����ǂ���
		bool _texActionBeats = false;	//�e�N�X�`���𔏎q�ɍ��킹�邩�ۂ�

	public:
		//�R���X�g���N�^
		CTexRendInfo();
		//�f�X�g���N�^
		~CTexRendInfo();
		//�������p
		void init();

	private:
		//�`��ݒ�p
		/**
		*�e�N�X�`�����o�^
		*@param	file	�t�@�C���p�X
		*@param	tex_type	�e�N�X�`���̊g���q
		*param	texPos	�e�N�X�`���̈ʒu
		*@param	texRect	�e�N�X�`���̋�`
		*@param	color	�e�N�X�`���F
		*@param	layer	���C���ݒ�
		*/
		void setupTexture(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color,LAYER layer);
	public:
		//�e�N�X�`�����̐ݒ�
		void setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color,LAYER layer);
		void setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color);
		void setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect,LAYER layer);
		void setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect);
		//�e�N�X�`���̍��W�ݒ�(������)
		void setupTextureTransform(const CVec2 texPos, const CVec4 texRect);
		//�e�N�X�`���̐F�ݒ�(������)
		void setupTextureColor(const CVec4 color);
		//�e�N�X�`���̃X�P�[���ݒ�
		void setTextureScale(const CVec2 Size);
		//�e�N�X�`���̍��W�ݒ�
		void setTexPosition(const CVec2 position);
		//�e�N�X�`���̋�`�ݒ�
		void setTextureRect(const CVec4 Rect);
		//HP��BP�̃o�[�̂��߂̋�`�ݒ�
		void SetProgressBarWH(const CVec4 Rect, const CVec2 position);
		//Map�p
		void setMapPosition(const CVec2 position, const int tag);


		//�e�N�X�`���̃t�F�[�h�A�N�V����
		void setActionFade(const bool out, const float fadeInterval);
		//�t�F�[�h�C���E�A�E�g���̃e�N�X�`���̐F�ύX����
		void textureActionFade();
		//�e�N�X�`���t�F�[�h�I�����Ă��邩�ǂ�����Ԃ�
		bool endTextureFade();
		//�e�N�X�`���𔏎q�ɍ��킹�邩�ۂ��̃Z�b�g
		void setTexActionBeats(bool action);
		//�e�N�X�`���̔��q�ɍ��킹��A�N�V�����̍X�V����
		void textureNotesAction();

		//�e�N�X�`���̍폜
		void deleteTexture();
	};

	//===================================================
	//�|���S��
	//===================================================
	class CPolygonRendInfo
	{
	private:
		//�̃|���S���p
		CVec4 _polyVert = {};			//���_���W
		CVec4 _polyColor = {};			//�|���S���F���
		CVec2 _polyDefaultVert = {};	//�������_���W
		float _polyAngle = {};			//��]�p�x
		LAYER m_polyLayer;				//���C�����
		bool _polyActionBeats = false;	//�e�N�X�`���𔏎q�ɍ��킹�邩�ۂ�
		render::CRenderer* m_renderer = {};	//�`���

	public:
		//�R���X�g���N�^
		CPolygonRendInfo();
		//�f�X�g���N�^
		~CPolygonRendInfo();
		//�������p
		void init();

		//�|���S���ݒ�
		/**
		*�|���S�����o�^
		*@param	vertex	���_���W
		*@param	color	�|���S���F
		*@param	layer	���C���ݒ�
		*/
		void setupPoly(const CVec4 vertex, const CVec4 color, LAYER layer);
		void setPolyPos(const CVec2 vertex);	//�|���S���̍��W�Đݒ�
		void setPolyScale(const CVec2 scale);	//�|���S���̃X�P�[���Đݒ�
		void setPolyPosX(const float vertex);	//�|���S���̍��W�Đݒ�
		void setPolyAngle(const float angle);	//�|���S���̉�]�ݒ�
		void setPolyColor(const CVec4 color);	//�|���S���̐F�ݒ�
		void addPolyAngle(const float angle);	//�|���S���̉�]��
		float getPolyAngle();					//�|���S���̉�]�擾
		CVec2 getPolyScale();					//�|���S���̃X�P�[���擾
		CVec4 getPolyColor();					//�|���S���̐F�擾
		void deletePoly();		//�|���S���̍폜


		void polygonBeatsAction();		//beats�ɍ��킹��A�N�V�����̍X�V����
		void polygonBeatsActionInit(const int mode);		//beats�ɍ��킹��A�N�V����(mode(0:�T�C�Y,1�F))


	};

	//===================================================
	//�w�i�p�O�p�|���S��
	//===================================================
	class CTriPolygonRendInfo
	{
	private:
		//�̎O�p�|���S���p
		CVec4 _bgPolyVert = {};			//���_���W
		CVec4 _bgPolyColor = {};		//�F
		int _bgPolyLine = {};		//��
		int _bgPolyMaxLine = 0;		//�ő��
		int _bgPolyDefaultVert = 0;	//�������_���W
		LAYER m_bgPolyLayer = {};		//���C��
		float _bgPolyAngle = 0;			//��]�p�x

		//�|���S���B�̃A�j���[�V�����p
		int upfadeCount = 0;
		int _beatUpSize = BEAT_BIGSIZE;

		render::CRenderer* m_renderer = {};	//�`���

	public:
		//�R���X�g���N�^
		CTriPolygonRendInfo();
		//�f�X�g���N�^
		~CTriPolygonRendInfo();
		//�������p
		void init();


		//�O�p�|���S���ݒ�
		void setupTrianglesPoly(CVec4 vertex, CVec4 color, int line, LAYER layer);
		//�w�i�|���S����X���W�ύX
		void setTrianglesPolyPos(float vertexX, CVec4 color);
		//�O�p�|���S���̉�]��
		void addTrianglesPolyAngle(float angle);

		void notesFadeBackground();	//�w�i�p�̍X�V����

		void notesRandomFadeInit();		//�w�i�p�̃����_��������
		void notesUpFadeInit(int mode);			//�w�i�p�̏�ɏオ���Ă���������(mode)

	};

}