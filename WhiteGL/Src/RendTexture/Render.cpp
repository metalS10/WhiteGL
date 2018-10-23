#include "Render.h"
#include "../Search/BinarySearch.h"
#include <algorithm>

using namespace render;

//������
void CRenderer::init()
{
	//==================================
	//�e�N�X�`��
	//==================================
	//�܂��S�폜
	_texRectPos.clear();
	_texRect.clear();
	_texType.clear();
	_texColorRGBA.clear();
	_texID.clear();
	m_texLayer.clear();	

	//vector�^�̏�����
	_texRectPos			= std::vector<CVec4*>();
	_texRect			= std::vector<CVec4*>();
	_texType			= std::vector<TEX_TYPE*>();
	_texColorRGBA		= std::vector<CVec4*>();
	_texID				= std::vector<GLuint*>();
	m_texLayer			= std::vector<LAYER*>();

	//==================================
	//�|���S��
	//==================================
	_polyVert.clear();
	_polyColor.clear();
	_polyAngle.clear();
	m_polyLayer.clear();

	//������
	_polyVert		= std::vector<CVec4*>();
	_polyColor		= std::vector<CVec4*>();
	_polyAngle		= std::vector<float*>();
	m_polyLayer		= std::vector<LAYER*>();


	//==================================
	//�w�i�|���S��
	//==================================
	_bgPolyVert.clear();
	_bgPolyColor.clear();
	_bgPolyAngle.clear();
	m_bgPolyLayer.clear();

	_bgPolyVert		= std::vector<CVec4*>();
	_bgPolyColor	= std::vector<CVec4*>();
	_bgPolyAngle	= std::vector<float*>();
	 m_bgPolyLayer	= std::vector<LAYER*>();	//�w�i�p�O�p�|���S���̃��C�����

}
//�X�e�[�W�ړ��̏�����
void CRenderer::changeStageInit()
{
	//==================================
	//�e�N�X�`��
	//==================================
	//�܂��S�폜
	_texRectPos.clear();
	_texRect.clear();
	_texType.clear();
	_texColorRGBA.clear();
	_texID.clear();
	m_texLayer.clear();

	//vector�^�̏�����
	_texRectPos = std::vector<CVec4*>();
	_texRect = std::vector<CVec4*>();
	_texType = std::vector<TEX_TYPE*>();
	_texColorRGBA = std::vector<CVec4*>();
	_texID = std::vector<GLuint*>();
	m_texLayer = std::vector<LAYER*>();

	//==================================
	//�w�i�|���S��
	//==================================
	_bgPolyVert.clear();
	_bgPolyColor.clear();
	_bgPolyAngle.clear();
	m_bgPolyLayer.clear();

	_bgPolyVert = std::vector<CVec4*>();
	_bgPolyColor = std::vector<CVec4*>();
	_bgPolyAngle = std::vector<float*>();
	m_bgPolyLayer = std::vector<LAYER*>();	//�w�i�p�O�p�|���S���̃��C�����
}




//�S�Ă̕`��X�V����
void CRenderer::render()
{
	// The following two lines enable semi transparent
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_ARRAY);
	//�F�f�[�^���������ɓo�^���邽�߂̋���
	glEnableClientState(GL_COLOR_ARRAY);
	//�e�N�X�`���������l
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//���C���[���Find�ł�������
	for (GLuint i = 0; i <= (GLuint)LAYER::MAX; i++)
	{
		//�w�i�p�|���S���`��
		for (int j = 0; j < _bgPolyVert.size(); j++)
		{
			if (_bgPolyVert.size() != 0)		//���g�����邩�m�F
			{
				if ((GLuint)*(m_bgPolyLayer)[j] == i)
				{

					//��ł���Δ�΂�
					if (!_bgPolyVert[j]->x && !_bgPolyVert[j]->y && !_bgPolyVert[j]->z)
						continue;

					glPushMatrix();
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					glEnableClientState(GL_VERTEX_ARRAY);


					//�ꏊ�w��
					const GLfloat vtx2[] = {	//x�����ƂȂ�_�̈ʒu,��ӂƂȂ�_�̈ʒuy,z��̓_�̈ʒu,w�O�p�`�̑傫��
						_bgPolyVert[j]->x - _bgPolyVert[j]->z * 0.5f 		,	_bgPolyVert[j]->y - _bgPolyVert[j]->w * 0.5f,1.0f,	//��
						_bgPolyVert[j]->x + _bgPolyVert[j]->z * 0.5f		,	_bgPolyVert[j]->y - _bgPolyVert[j]->w * 0.5f,1.0f,	//�E
						_bgPolyVert[j]->x									,	_bgPolyVert[j]->y + _bgPolyVert[j]->w * 0.5f,1.0f,	//��
					};
					//3����
					glVertexPointer(3, GL_FLOAT, 0, vtx2);

					//�F�ݒ�
					const GLfloat color[] = {
						_bgPolyColor[j]->x*0.01f,_bgPolyColor[j]->y*0.01f,_bgPolyColor[j]->z*0.01f,_bgPolyColor[j]->w*0.01f,
						_bgPolyColor[j]->x*0.01f,_bgPolyColor[j]->y*0.01f,_bgPolyColor[j]->z*0.01f,_bgPolyColor[j]->w*0.01f,
						_bgPolyColor[j]->x*0.01f,_bgPolyColor[j]->y*0.01f,_bgPolyColor[j]->z*0.01f,_bgPolyColor[j]->w*0.01f,
						_bgPolyColor[j]->x*0.01f,_bgPolyColor[j]->y*0.01f,_bgPolyColor[j]->z*0.01f,_bgPolyColor[j]->w*0.01f,
					};
					//�F���f
					glColorPointer(4, GL_FLOAT, 0, color);
					//�e�N�X�`���̗̈�w��
					const GLfloat texuv[] = {
						0.0f, 0.0f,
						0.0f, 0.0f,
						0.0f, 0.0f,
						0.0f, 0.0f,
					};
					//���_�̐ݒ�
					glTexCoordPointer(2, GL_FLOAT, 0, texuv);
					//�|���S���\��
					glDrawArrays(GL_TRIANGLES, 0, 4);

					//�F�ݒ�
					const GLfloat colorLine[] = {
						0,0,0,100,
						0,0,0,100,
						0,0,0,100,
						0,0,0,100,
					};


					glColorPointer(4, GL_FLOAT, 0, colorLine);
					//3����
					glVertexPointer(3, GL_FLOAT, 0, vtx2);
					glDrawArrays(GL_LINE_LOOP, 0, 3);

					glDisableClientState(GL_VERTEX_ARRAY);

					glPopMatrix();
				}
			}
		}
		//�|���S���`��
		for (int j = 0; j < _polyVert.size(); j++)
		{
			if (_polyVert.size() != 0)		//���g�����邩�m�F
			{
				if ((GLuint)*(m_polyLayer)[j] == i)
				{
					//��ł���Δ�΂�
					if (_polyVert[j]->x && !_polyVert[j]->y && !_polyVert[j]->z && !_polyVert[j]->w)
						continue;

					glPushMatrix();
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					glEnableClientState(GL_VERTEX_ARRAY);

					//�ꏊ�w��
					const GLfloat vtx2[] = {	//x:X���W����,y:Y���W����,z:X���WScale,w:y���WScale
						_polyVert[j]->x + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->x - _polyVert[j]->z * 0.5f) - _polyVert[j]->x) - sin(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y - _polyVert[j]->w * 0.5f) - _polyVert[j]->y) 	, _polyVert[j]->y + sin(*_polyAngle[j] / 180.0f) * ((_polyVert[j]->x - _polyVert[j]->z * 0.5f) - _polyVert[j]->x) + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y - _polyVert[j]->w * 0.5f) - _polyVert[j]->y) ,1.0f,	//����
						_polyVert[j]->x + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->x + _polyVert[j]->z * 0.5f) - _polyVert[j]->x) - sin(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y - _polyVert[j]->w * 0.5f) - _polyVert[j]->y) 	, _polyVert[j]->y + sin(*_polyAngle[j] / 180.0f) * ((_polyVert[j]->x + _polyVert[j]->z * 0.5f) - _polyVert[j]->x) + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y - _polyVert[j]->w * 0.5f) - _polyVert[j]->y) ,1.0f,	//�E��
						_polyVert[j]->x + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->x + _polyVert[j]->z * 0.5f) - _polyVert[j]->x) - sin(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y + _polyVert[j]->w * 0.5f) - _polyVert[j]->y) 	, _polyVert[j]->y + sin(*_polyAngle[j] / 180.0f) * ((_polyVert[j]->x + _polyVert[j]->z * 0.5f) - _polyVert[j]->x) + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y + _polyVert[j]->w * 0.5f) - _polyVert[j]->y) ,1.0f,	//�E��
						_polyVert[j]->x + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->x - _polyVert[j]->z * 0.5f) - _polyVert[j]->x) - sin(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y + _polyVert[j]->w * 0.5f) - _polyVert[j]->y) 	, _polyVert[j]->y + sin(*_polyAngle[j] / 180.0f) * ((_polyVert[j]->x - _polyVert[j]->z * 0.5f) - _polyVert[j]->x) + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y + _polyVert[j]->w * 0.5f) - _polyVert[j]->y) ,1.0f,	//����
					};
					//3����
					glVertexPointer(3, GL_FLOAT, 0, vtx2);

					//�F�ݒ�
					const GLfloat color[] = {
						_polyColor[j]->x*0.01f,_polyColor[j]->y*0.01f,_polyColor[j]->z*0.01f,_polyColor[j]->w*0.01f,
						_polyColor[j]->x*0.01f,_polyColor[j]->y*0.01f,_polyColor[j]->z*0.01f,_polyColor[j]->w*0.01f,
						_polyColor[j]->x*0.01f,_polyColor[j]->y*0.01f,_polyColor[j]->z*0.01f,_polyColor[j]->w*0.01f,
						_polyColor[j]->x*0.01f,_polyColor[j]->y*0.01f,_polyColor[j]->z*0.01f,_polyColor[j]->w*0.01f,
					};
					//�F���f
					glColorPointer(4, GL_FLOAT, 0, color);

					//�|���S���\��
					glDrawArrays(GL_QUADS, 0, 4);

					//�F�ݒ�
					const GLfloat colorLine[] = {
						0,0,0,_polyColor[j]->w*0.01f,
						0,0,0,_polyColor[j]->w*0.01f,
						0,0,0,_polyColor[j]->w*0.01f,
						0,0,0,_polyColor[j]->w*0.01f,
					};


					glColorPointer(4, GL_FLOAT, 0, colorLine);
					//3����
					glVertexPointer(3, GL_FLOAT, 0, vtx2);
					glDrawArrays(GL_LINE_LOOP, 0, 4);

					glDisableClientState(GL_VERTEX_ARRAY);

					glPopMatrix();
				}
			}
		}
		for (int j = 0; j < _texID.size(); j++)
		{
			if (_texID.size() != 0)		//���g�����邩�m�F
			{
				if ((GLuint)*m_texLayer[j] == i)
				{
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					//�g�p����
					glEnable(GL_TEXTURE_2D);

					if (*_texType[j] == TEX_TYPE::BMP)
					{
						//�ꏊ�w��
						const GLfloat vtx2[] = {
							_texRectPos[j]->x,_texRectPos[j]->z,0,
							_texRectPos[j]->y,_texRectPos[j]->z,0,
							_texRectPos[j]->y,_texRectPos[j]->w,0,
							_texRectPos[j]->x,_texRectPos[j]->w,0,
						};
						glVertexPointer(3, GL_FLOAT, 0, vtx2);

						const GLfloat color[] = {
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
						};
						glColorPointer(4, GL_FLOAT, 0, color);

						//�e�N�X�`���̗̈�w��
						const GLfloat texuv[] = {
							_texRect[j]->x, _texRect[j]->z,
							_texRect[j]->y, _texRect[j]->z,
							_texRect[j]->y, _texRect[j]->w,
							_texRect[j]->x, _texRect[j]->w,
						};
						//���_�̐ݒ�
						glTexCoordPointer(2, GL_FLOAT, 0, texuv);

					}
					else if (*_texType[j] == TEX_TYPE::PNG)
					{
						//�ꏊ�w��
						const GLfloat vtx2[] = {
							_texRectPos[j]->x, _texRectPos[j]->z,0,
							_texRectPos[j]->y, _texRectPos[j]->z,0,
							_texRectPos[j]->y, _texRectPos[j]->w,0,
							_texRectPos[j]->x, _texRectPos[j]->w,0,
						};
						glVertexPointer(3, GL_FLOAT, 0, vtx2);

						const GLfloat color[] = {
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,

						};
						glColorPointer(4, GL_FLOAT, 0, color);

						//�e�N�X�`���̗̈�w��
						const GLfloat texuv[] = {
							_texRect[j]->x, _texRect[j]->w,
							_texRect[j]->y, _texRect[j]->w,
							_texRect[j]->y, _texRect[j]->z,
							_texRect[j]->x, _texRect[j]->z,
						};
						//���_�̐ݒ�
						glTexCoordPointer(2, GL_FLOAT, 0, texuv);

					}
					else if (*_texType[j] == TEX_TYPE::QUAD)
					{
						//�ꏊ�w��
						const GLfloat vtx2[] = {
							_texRectPos[j]->x, _texRectPos[j]->z,0,
							_texRectPos[j]->y, _texRectPos[j]->z,0,
							_texRectPos[j]->y, _texRectPos[j]->w,0,
							_texRectPos[j]->x, _texRectPos[j]->w,0,
						};
						glVertexPointer(3, GL_FLOAT, 0, vtx2);

						const GLfloat color[] = {
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
						};
						glColorPointer(4, GL_FLOAT, 0, color);

						//�e�N�X�`���̗̈�w��
						const GLfloat texuv[] = {
							_texRect[j]->x, _texRect[j]->w,
							_texRect[j]->y, _texRect[j]->w,
							_texRect[j]->y, _texRect[j]->z,
							_texRect[j]->x, _texRect[j]->z,
						};
						//���_�̐ݒ�
						glTexCoordPointer(2, GL_FLOAT, 0, texuv);
					}

					glEnableClientState(GL_VERTEX_ARRAY);
					//�e�N�X�`���̉摜�w��
					glBindTexture(GL_TEXTURE_2D, *(_texID)[j]);
					//�|���S���\��
					glDrawArrays(GL_QUADS, 0, 4);

					glDisableClientState(GL_VERTEX_ARRAY);

					//�g�p����
					glDisable(GL_TEXTURE_2D);

				}
			}
		}
	}

	//�����O��
	glDisable(GL_BLEND);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//�e�N�X�`�����o�^�֐�
void CRenderer::pushTexture(GLuint* texID, CVec4* texRectPos, CVec4* texRect, int* texType, CVec4* texColor,int* layer)
{
	_texID			.push_back(texID);
	_texRectPos		.push_back(texRectPos);
	_texRect		.push_back(texRect);
	_texType		.push_back((TEX_TYPE*)texType);
	_texColorRGBA	.push_back(texColor);
	m_texLayer		.push_back((LAYER*)layer);
}
//�|���S�����o�^�֐�
void CRenderer::pushPoly(CVec4* vertex, CVec4* color, float* angle, int* layer)
{
	_polyVert	.push_back(vertex);
	_polyColor	.push_back(color);
	_polyAngle	.push_back(angle);
	m_polyLayer	.push_back((LAYER*)layer);
}
//�|���S�����o�^�֐�
void CRenderer::pushTriPoly(CVec4* vertex, CVec4* color, float* angle, int* layer)
{
	_bgPolyVert		.push_back(vertex);
	_bgPolyColor	.push_back(color);
	_bgPolyAngle	.push_back(angle);
	m_bgPolyLayer	.push_back((LAYER*)layer);
}




















