#pragma once
/**
*Render.h
*
*	2017/10/10	Mat
*		�e�N�X�`���̓ǂݍ��݁A�`��
*/

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../Vec2.h"
#include "../Vec4.h"
#include "../Constants.h"
#include "../Data/Animation/Animation.h"
#include <vector>


namespace render
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
		//�e�N�X�`�����
		std::vector<GLuint*>	_texID = {};		//�e�N�X�`����ID
		std::vector<CVec4*>		_texRectPos = {};	//�e�N�X�`���̐؂����`
		std::vector<CVec4*>		_texRect = {};		//�e�N�X�`���̋�`
		std::vector<TEX_TYPE*>	_texType = {};		//�e�N�X�`���̃^�C�v
		std::vector<CVec4*>		_texColorRGBA = {};	//�e�N�X�`���̐F���


		//�̎O�p�|���S���p
		std::vector<CVec4*> _bgPolyVert = {};		//�w�i�p�O�p�|���S���̒��_���W���
		std::vector<CVec4*> _bgPolyColor = {};		//�w�i�p�O�p�|���S���̐F���
		std::vector<float*> _bgPolyAngle = {};		//�w�i�p�O�p�|���S���̉�]���


		//�̃|���S���p
		std::vector<CVec4*> _polyVert = {};		//�|���S���̒��_���W���
		std::vector<CVec4*> _polyColor = {};		//�|���S���̐F���
		std::vector<float*> _polyAngle = {};		//�|���S���̉�]���

		

		//���C���ݒ�p
		std::vector<LAYER*> m_texLayer = {};		//�e�N�X�`���̃��C�����
		std::vector<LAYER*> m_bgPolyLayer = {};	//�w�i�p�O�p�|���S���̃��C�����
		std::vector<LAYER*> m_polyLayer = {};		//�|���S���̃��C�����


		CRenderer()
		{
			//init();
		}

		~CRenderer()
		{
			for (int i = 0; i < _texID.size(); i++)
			{
				SAFE_DELETE(_texID[i]);
				SAFE_DELETE(_texRectPos[i]);
				SAFE_DELETE(_texRect[i]);
				SAFE_DELETE(_texType[i]);
				SAFE_DELETE(_texColorRGBA[i]);
				SAFE_DELETE(m_texLayer[i]);
			}
			for (int i = 0; i < _polyVert.size(); i++)
			{
				SAFE_DELETE(_polyVert[i]);
				SAFE_DELETE(_polyColor[i]);
				SAFE_DELETE(_polyAngle[i]);
				SAFE_DELETE(m_polyLayer[i]);
			}
			for (int i = 0; i < _bgPolyVert.size(); i++)
			{
				SAFE_DELETE(_bgPolyVert[i]);
				SAFE_DELETE(_bgPolyColor[i]);
				SAFE_DELETE(_bgPolyAngle[i]);
				SAFE_DELETE(m_bgPolyLayer[i]);
			}
		}

	public:

		//������
		void init();
		void changeStageInit();

		//�e�N�X�`�����o�^
		void pushTexture(GLuint* texID, CVec4* texRectPos, CVec4* texRect, int* texType, CVec4* texColor,int* layer);
		//�|���S�����o�^
		void pushPoly(CVec4* vertex, CVec4* color, float* angle,int* layer);
		//�w�i�p�O�p�|���S�����o�^
		void pushTriPoly(CVec4* vertex, CVec4* color, float* angle, int* layer);



		//�o�^���S�Ă̕`��X�V����
		void render();











		
	};
}