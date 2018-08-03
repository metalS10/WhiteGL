#include "Render.h"


//�A�j���[�V�����X�V����
void CRenderer::update(std::vector<CAnimation*>* anim)
{
	for (int i = 1 ; i <= anim->size();i++)
	{
		GLuint texID = i - 1;
		(*anim)[texID]->update();
		CVec4 texRect = (*anim)[texID]->getCurrentChip();



		glBindTexture(GL_TEXTURE_2D, _texID[texID]);


		//�摜�̋�`�͈͂�ݒ�
		CVec4 changerect4 = CVec4(texRect.x / _texImage[texID]->m_width, (texRect.x + texRect.z) / _texImage[texID]->m_width, texRect.y / _texImage[texID]->m_height, (texRect.y + texRect.w) / _texImage[texID]->m_height);
		_texRect[texID] = CVec4(changerect4);
	}
	this->fadeSearch();
}

//�t�F�[�h�C���E�A�E�g���̃e�N�X�`���̓���(�F���)
void CRenderer::fadeSearch()
{
	for (int i = 0;i <= MAX_TEXTURE_NUMBER;i++)
	{
		//�t�F�[�h�C���A�E�g
		if (_texActionFade[i])
		{
			//�t�F�[�h�A�E�g
			if (_texFadeOut[i])
			{
				_texColorRGBA[i].w -= _texActionFadeInterval[i];
				if (_texColorRGBA[i].w <= 0.0f)
				{
					_texColorRGBA[i].w = 0.0f;
					_texActionFade[i] = false;
				}
			}
			//�t�F�[�h�C��
			else
			{
				_texColorRGBA[i].w += _texActionFadeInterval[i];
				if (_texColorRGBA[i].w >= 100.0f)
				{
					_texColorRGBA[i].w = 100.0f;
					_texActionFade[i] = false;
				}
			}

			glBindTexture(GL_TEXTURE_2D, _texID[i]);
		}
	}
}

//�S�Ă̕`��X�V����
void CRenderer::render()
{
	// The following two lines enable semi transparent
	glEnable(GL_BLEND);
	//�F�f�[�^���������ɓo�^���邽�߂̋���
	glEnableClientState(GL_COLOR_ARRAY);
	//�e�N�X�`���������l
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//���C���[���Find�ł�������
	for (GLuint i = 0; i <= (GLuint)LAYER::MAX; i++)
	{
		//�w�i�p�|���S���`��
		for (int j = 0; j < MAX_BACKGROUND_NUMBER; j++)
		{
			if ((GLuint)m_bgPolyLayer[j] == i)
			{



				//��ł���Δ�΂�
				if (!_bgPolyVert[j].x && !_bgPolyVert[j].y && !_bgPolyVert[j].z)
					continue;

				glPushMatrix();
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glEnableClientState(GL_VERTEX_ARRAY);
				
				//�ꏊ�w��
				const GLfloat vtx2[] = {	//x�����ƂȂ�_�̈ʒu,��ӂƂȂ�_�̈ʒuy,z��̓_�̈ʒu,w�O�p�`�̑傫��
					_bgPolyVert[j].x  - _bgPolyVert[j].z * 0.5f 	,	_bgPolyVert[j].y - _bgPolyVert[j].w * 0.5f,1.0f,	//��
					_bgPolyVert[j].x  + _bgPolyVert[j].z * 0.5f		,	_bgPolyVert[j].y - _bgPolyVert[j].w * 0.5f,1.0f,	//�E
					_bgPolyVert[j].x								,	_bgPolyVert[j].y + _bgPolyVert[j].w * 0.5f,1.0f,	//��
				};
				//3����
				glVertexPointer(3, GL_FLOAT, 0, vtx2);

				//�F�ݒ�
				const GLfloat color[] = {
					_bgPolyColor[j].x*0.01f,_bgPolyColor[j].y*0.01f,_bgPolyColor[j].z*0.01f,_bgPolyColor[j].w*0.01f,
					_bgPolyColor[j].x*0.01f,_bgPolyColor[j].y*0.01f,_bgPolyColor[j].z*0.01f,_bgPolyColor[j].w*0.01f,
					_bgPolyColor[j].x*0.01f,_bgPolyColor[j].y*0.01f,_bgPolyColor[j].z*0.01f,_bgPolyColor[j].w*0.01f,
					_bgPolyColor[j].x*0.01f,_bgPolyColor[j].y*0.01f,_bgPolyColor[j].z*0.01f,_bgPolyColor[j].w*0.01f,
				};
				//�F���f
				glColorPointer(4, GL_FLOAT, 0, color);

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
		//�|���S���`��
		for (int j = 0; j < MAX_POLYGON_NUMBER; j++)
		{
			if ((GLuint)m_polyLayer[j] == i)
			{
				//��ł���Δ�΂�
				if (!_polyVert[j].x && !_polyVert[j].y && !_polyVert[j].z && !_polyVert[j].w)
					continue;

				glPushMatrix();
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glEnableClientState(GL_VERTEX_ARRAY);

				//�ꏊ�w��
				const GLfloat vtx2[] = {	//x:X���W����,y:Y���W����,z:X���WScale,w:y���WScale
					_polyVert[j].x + cos(_polyAngle[j] / 180.0f)*((_polyVert[j].x - _polyVert[j].z * 0.5f) - _polyVert[j].x) - sin(_polyAngle[j] / 180.0f)*((_polyVert[j].y - _polyVert[j].w * 0.5f) - _polyVert[j].y) 	, _polyVert[j].y + sin(_polyAngle[j] / 180.0f) * ((_polyVert[j].x - _polyVert[j].z * 0.5f) - _polyVert[j].x) + cos(_polyAngle[j] / 180.0f)*((_polyVert[j].y - _polyVert[j].w * 0.5f) - _polyVert[j].y) ,1.0f,	//����
					_polyVert[j].x + cos(_polyAngle[j] / 180.0f)*((_polyVert[j].x + _polyVert[j].z * 0.5f) - _polyVert[j].x) - sin(_polyAngle[j] / 180.0f)*((_polyVert[j].y - _polyVert[j].w * 0.5f) - _polyVert[j].y) 	, _polyVert[j].y + sin(_polyAngle[j] / 180.0f) * ((_polyVert[j].x + _polyVert[j].z * 0.5f) - _polyVert[j].x) + cos(_polyAngle[j] / 180.0f)*((_polyVert[j].y - _polyVert[j].w * 0.5f) - _polyVert[j].y) ,1.0f,	//�E��
					_polyVert[j].x + cos(_polyAngle[j] / 180.0f)*((_polyVert[j].x + _polyVert[j].z * 0.5f) - _polyVert[j].x) - sin(_polyAngle[j] / 180.0f)*((_polyVert[j].y + _polyVert[j].w * 0.5f) - _polyVert[j].y) 	, _polyVert[j].y + sin(_polyAngle[j] / 180.0f) * ((_polyVert[j].x + _polyVert[j].z * 0.5f) - _polyVert[j].x) + cos(_polyAngle[j] / 180.0f)*((_polyVert[j].y + _polyVert[j].w * 0.5f) - _polyVert[j].y) ,1.0f,	//�E��
					_polyVert[j].x + cos(_polyAngle[j] / 180.0f)*((_polyVert[j].x - _polyVert[j].z * 0.5f) - _polyVert[j].x) - sin(_polyAngle[j] / 180.0f)*((_polyVert[j].y + _polyVert[j].w * 0.5f) - _polyVert[j].y) 	, _polyVert[j].y + sin(_polyAngle[j] / 180.0f) * ((_polyVert[j].x - _polyVert[j].z * 0.5f) - _polyVert[j].x) + cos(_polyAngle[j] / 180.0f)*((_polyVert[j].y + _polyVert[j].w * 0.5f) - _polyVert[j].y) ,1.0f,	//����
				};
				//3����
				glVertexPointer(3, GL_FLOAT, 0, vtx2);

				//�F�ݒ�
				const GLfloat color[] = {
					_polyColor[j].x*0.01f,_polyColor[j].y*0.01f,_polyColor[j].z*0.01f,_polyColor[j].w*0.01f,
					_polyColor[j].x*0.01f,_polyColor[j].y*0.01f,_polyColor[j].z*0.01f,_polyColor[j].w*0.01f,
					_polyColor[j].x*0.01f,_polyColor[j].y*0.01f,_polyColor[j].z*0.01f,_polyColor[j].w*0.01f,
					_polyColor[j].x*0.01f,_polyColor[j].y*0.01f,_polyColor[j].z*0.01f,_polyColor[j].w*0.01f,
				};
				//�F���f
				glColorPointer(4, GL_FLOAT, 0, color);

				//�|���S���\��
				glDrawArrays(GL_QUADS, 0, 4);

				//�F�ݒ�
				const GLfloat colorLine[] = {
					0,0,0,_polyColor[j].w*0.01f,
					0,0,0,_polyColor[j].w*0.01f,
					0,0,0,_polyColor[j].w*0.01f,
					0,0,0,_polyColor[j].w*0.01f,
				};


				glColorPointer(4, GL_FLOAT, 0, colorLine);
				//3����
				glVertexPointer(3, GL_FLOAT, 0, vtx2);
				glDrawArrays(GL_LINE_LOOP, 0, 4);

				glDisableClientState(GL_VERTEX_ARRAY);

				glPopMatrix();
			}
		}
		for (int texID = 0; texID < MAX_TEXTURE_NUMBER; texID++)
		{
			if (_texID[texID] != 0)
			{

				if ((GLuint)m_texLayer[texID] == i)
				{
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					//�g�p����
					glEnable(GL_TEXTURE_2D);

					if (_texType[texID] == TEX_TYPE::BMP)
					{
						//�ꏊ�w��
						const GLfloat vtx2[] = {
							_texRectPos[texID].x,_texRectPos[texID].z,0,
							_texRectPos[texID].y,_texRectPos[texID].z,0,
							_texRectPos[texID].y,_texRectPos[texID].w,0,
							_texRectPos[texID].x,_texRectPos[texID].w,0,
						};
						glVertexPointer(3, GL_FLOAT, 0, vtx2);

						const GLfloat color[] = {
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
						};
						glColorPointer(4, GL_FLOAT, 0, color);

						//�e�N�X�`���̗̈�w��
						const GLfloat texuv[] = {
							_texRect[texID].x, _texRect[texID].z,
							_texRect[texID].y, _texRect[texID].z,
							_texRect[texID].y, _texRect[texID].w,
							_texRect[texID].x, _texRect[texID].w,
						};
						//���_�̐ݒ�
						glTexCoordPointer(2, GL_FLOAT, 0, texuv);

					}
					else if (_texType[texID] == TEX_TYPE::PNG)
					{
						//�ꏊ�w��
						const GLfloat vtx2[] = {
							_texRectPos[texID].x, _texRectPos[texID].z,0,
							_texRectPos[texID].y, _texRectPos[texID].z,0,
							_texRectPos[texID].y, _texRectPos[texID].w,0,
							_texRectPos[texID].x, _texRectPos[texID].w,0,
						};
						glVertexPointer(3, GL_FLOAT, 0, vtx2);

						const GLfloat color[] = {
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,

						};
						glColorPointer(4, GL_FLOAT, 0, color);

						//�e�N�X�`���̗̈�w��
						const GLfloat texuv[] = {
							_texRect[texID].x, _texRect[texID].w,
							_texRect[texID].y, _texRect[texID].w,
							_texRect[texID].y, _texRect[texID].z,
							_texRect[texID].x, _texRect[texID].z,
						};
						//���_�̐ݒ�
						glTexCoordPointer(2, GL_FLOAT, 0, texuv);

					}
					else if (_texType[texID] == TEX_TYPE::QUAD)
					{
						//�ꏊ�w��
						const GLfloat vtx2[] = {
							_texRectPos[texID].x, _texRectPos[texID].z,0,
							_texRectPos[texID].y, _texRectPos[texID].z,0,
							_texRectPos[texID].y, _texRectPos[texID].w,0,
							_texRectPos[texID].x, _texRectPos[texID].w,0,
						};
						glVertexPointer(3, GL_FLOAT, 0, vtx2);

						const GLfloat color[] = {
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
							_texColorRGBA[texID].x*0.01f,_texColorRGBA[texID].y*0.01f,_texColorRGBA[texID].z*0.01f,_texColorRGBA[texID].w*0.01f,
						};
						glColorPointer(4, GL_FLOAT, 0, color);

						//�e�N�X�`���̗̈�w��
						const GLfloat texuv[] = {
							_texRect[texID].x, _texRect[texID].w,
							_texRect[texID].y, _texRect[texID].w,
							_texRect[texID].y, _texRect[texID].z,
							_texRect[texID].x, _texRect[texID].z,
						};
						//���_�̐ݒ�
						glTexCoordPointer(2, GL_FLOAT, 0, texuv);
					}

					glEnableClientState(GL_VERTEX_ARRAY);
					//�e�N�X�`���̉摜�w��
					glBindTexture(GL_TEXTURE_2D, _texID[texID]);
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

void CRenderer::setupTexture(const char *file, const TEX_TYPE tex_type, GLuint texID, const LAYER layer ,const GLuint tag)
{
	//�g�p����
	glEnable(GL_TEXTURE_2D);
	//texID���󂢂Ă���Ƃ����
	glGenTextures(1, &_texID[texID]);

	//�摜�f�[�^�ƃe�N�X�`��iD�����т���
	glBindTexture(GL_TEXTURE_2D, _texID[texID]);

	_texScale[texID] = CVec2(1, 1);
	_texDefaultScale[texID] = 1.0f;

	switch (tex_type)
	{
	case TEX_TYPE::BMP:
		_texImage[texID] = new CBmpImage();
		if (_texImage[texID]->load(file) == false)
		{
			std::cerr << "ERROR : �摜�̓ǂݍ��݂Ɏ��s" << std::endl;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _texImage[texID]->m_width, _texImage[texID]->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _texImage[texID]->m_bits);

		//�e�N�X�`���̊g��E�k�����@�̐ݒ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//�e�N�X�`���̌J��Ԃ��̎w��
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		break;

	case TEX_TYPE::PNG:
		_texImage[texID] = new CPngImage();
		if (_texImage[texID]->load(file) == false)
		{
			std::cerr << "ERROR : �摜�̓ǂݍ��݂Ɏ��s" << std::endl;
		}

		if (_texImage[texID]->m_format == PNG_COLOR_TYPE_RGBA)
		{
			//�e�N�X�`����PNG�t�@�C������ǂݍ��񂾃s�N�Z������������
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _texImage[texID]->m_width, _texImage[texID]->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _texImage[texID]->m_bits);

			//�e�N�X�`���̊g��E�k�����@�̐ݒ�
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			//�e�N�X�`���̌J��Ԃ��̎w��
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		}
		else if (_texImage[texID]->m_format == PNG_COLOR_TYPE_RGB)
		{
			//�e�N�X�`����PNG�t�@�C������ǂݍ��񂾃s�N�Z������������
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _texImage[texID]->m_width, _texImage[texID]->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _texImage[texID]->m_bits);

			//�e�N�X�`���̊g��E�k�����@�̐ݒ�
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			//�e�N�X�`���̌J��Ԃ��̎w��
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		}
		else if (_texImage[texID]->m_format == PNG_COLOR_TYPE_PALETTE)
		{
			GLubyte* textureImage;		

			int width, height;
			bool hasAlpha = true;	//�Ƃ肠����Png��Alpha����ł���
			const char* filename = file;
			bool success = loadPngImage(filename, width, height, hasAlpha, &textureImage);
			if (!success) {
				//std::cout << "Unable to load png file" << std::endl;
				return;
			}
			//std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
				height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
				textureImage);

			//�e�N�X�`���̊g��E�k�����@�̐ݒ�
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			//�e�N�X�`���̌J��Ԃ��̎w��
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			SAFE_DELETE(textureImage);
		}
		else if (_texImage[texID]->m_format == PNG_COLOR_TYPE_GRAY)
		{
			//�e�N�X�`����PNG�t�@�C������ǂݍ��񂾃s�N�Z������������
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _texImage[texID]->m_width, _texImage[texID]->m_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, _texImage[texID]->m_bits);
			//gray���Ăǂ��`�悷��񂾂낤
			std::cout << "PNG_COLOR_TYPE_GRAY�p�`��V�X�e��������" << std::endl;
		}

		break;

	case TEX_TYPE::QUAD:
		_texImage[texID] = new CPngImage();

		_texImage[texID]->m_width = 1;_texImage[texID]->m_height = 1;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ONE, 1, 1, 0, GL_ONE, GL_UNSIGNED_BYTE, 0);

		//�e�N�X�`���̊g��E�k�����@�̐ݒ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//�e�N�X�`���̌J��Ԃ��̎w��
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		break;


	default:
		break;
	}
	_texTag[texID] = tag;

	//������
	glBindTexture(GL_TEXTURE_2D, 0);

	m_texLayer[texID] = layer;

	//�g�p����
	glDisable(GL_TEXTURE_2D);
	_texColorRGBA[texID] = (CVec4(100.0f, 100.0f, 100.0f, 100.0f));
	_texType[texID] = (tex_type);
}
//�O�p�|���S���̃Z�b�g�A�b�v
void CRenderer::setupTrianglesPoly(const CVec4 vertex,const CVec4 color,const GLuint line,const LAYER layer)
{
	for (int i = 0; i < MAX_BACKGROUND_NUMBER; i++)
	{
		if (!_bgPolyVert[i].x && !_bgPolyVert[i].y && !_bgPolyVert[i].z && !_bgPolyVert[i].w)
		{
			//�|���S���ݒ��ǉ�
			_bgPolyVert[i] = vertex;
			_bgPolyColor[i] = color;
			_bgPolyLine[i] = line;
			_bgPolyMaxLine = line;
			_bgPolyDefaultVert = vertex.z;
			m_bgPolyLayer[i] = layer;
			break;
		}
	}
}
void CRenderer::setTrianglesPolyPos(const float vertexX, const CVec4 color, const GLuint number)
{
	_bgPolyVert[number].x = vertexX;
	_bgPolyColor[number] = color;
}

//�|���S���̃Z�b�g�A�b�v
void CRenderer::setupPoly(const CVec4 vertex, const CVec4 color,const LAYER layer, const GLuint tag)
{
	for (int i = 0; i < MAX_BACKGROUND_NUMBER; i++)
	{
		if (!_polyVert[i].x && !_polyVert[i].y && !_polyVert[i].z && !_polyVert[i].w)
		{
			//�|���S���ݒ��ǉ�
			_polyVert[i] = vertex;
			_polyColor[i] = color;
			_polyDefaultVert[i] = CVec2(vertex.z,vertex.w);
			m_polyLayer[i] = layer;
			_polyTag[i] = tag;
			break;
		}
	}
}
void CRenderer::setPolyPos(const CVec2 vertex, const GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
		{
			_polyVert[i].x = vertex.x;
			_polyVert[i].y = vertex.y;
		}
	}
}
void CRenderer::setPolyScale(const CVec2 scale, const GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
		{
			_polyVert[i].z = scale.x;
			_polyVert[i].w = scale.y;
		}
	}
}

void CRenderer::setPolyPosX(const float vertex, const GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
		{
			_polyVert[i].x = vertex;
		}
	}
}
void CRenderer::setPolyAngle(const float angle, GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
			_polyAngle[i] = angle;
	}
}
void CRenderer::setPolyColor(const CVec4 color, const GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
			_polyColor[i] = color;
	}
}
void CRenderer::addPolyAngle(const float angle, GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
			_polyAngle[i] += angle;
	}
}
float CRenderer::getPolyAngle(const GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
			return _polyAngle[i];
	}
}
CVec2 CRenderer::getPolyScale(const GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
			return CVec2(_polyVert[i].z,_polyVert[i].w);
	}
}
CVec4 CRenderer::getPolyColor(const GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
			return _polyColor[i];
	}
}

//�|���S���̍폜
void CRenderer::deletePoly(const GLuint tag)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		if (_polyTag[i] == tag)
			setPolyPos(CVec2(0.0f,0.0f), tag);
			setPolyScale(CVec2(0.0f,0.0f), tag);
			setPolyAngle(0.0f, tag);
	}
}


//�e�N�X�`���̃T�C�Y�ݒ�
void CRenderer::setupTextureSize(const CVec2 texPos, const CVec4 texRect, const GLuint texID)
{

	//�����c�����Z�b�g
	_texWH[texID] = CVec2(((texRect.x + texRect.z) - texRect.x) * 0.5f, ((texRect.y + texRect.w) - texRect.y) * 0.5f);
	_texRectPos[texID] = CVec4(texPos.x - _texWH[texID].x, texPos.x + _texWH[texID].x, texPos.y - _texWH[texID].y, texPos.y + _texWH[texID].y);
	_texPosition[texID] = texPos;

	//�摜�̋�`�͈͂�ݒ�
	CVec4 changerect4 = CVec4(texRect.x / _texImage[texID]->m_width, (texRect.x + texRect.z) / _texImage[texID]->m_width, texRect.y / _texImage[texID]->m_height, (texRect.y + texRect.w) / _texImage[texID]->m_height);
	_texRect[texID] = CVec4(changerect4);




	if (_texImage[texID] == NULL)
	{
		std::cerr << "BMP,PNG,JPEG�Ȃ�ł��Ȃ��ł�" << std::endl;
	}
}
void CRenderer::setupTextureSizeAtTag(const CVec2 texPos,const CVec4 texRect,const GLuint tag)
{
	for (int i = 0; i < MAX_TEXTURE_NUMBER; i++)
	{
		if (_texTag[i] == tag)
		{
			//�����c�����Z�b�g
			_texWH[i] = CVec2(((texRect.x + texRect.z) - texRect.x) * 0.5f, ((texRect.y + texRect.w) - texRect.y) * 0.5f);
			_texRectPos[i] = CVec4(texPos.x - _texWH[i].x, texPos.x + _texWH[i].x, texPos.y - _texWH[i].y, texPos.y + _texWH[i].y);
			_texPosition[i] = texPos;

			//�摜�̋�`�͈͂�ݒ�
			CVec4 changerect4 = CVec4(texRect.x / _texImage[i]->m_width, (texRect.x + texRect.z) / _texImage[i]->m_width, texRect.y / _texImage[i]->m_height, (texRect.y + texRect.w) / _texImage[i]->m_height);
			_texRect[i] = CVec4(changerect4);




			if (_texImage[i] == NULL)
			{
				std::cerr << "BMP,PNG,JPEG�Ȃ�ł��Ȃ��ł�" << std::endl;
			}
			return;
		}
	}
}

//�e�N�X�`���̍폜
void CRenderer::deleteTexture(const GLuint texID)
{
	//�g�p����
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &_texID[texID]);
	_texID[texID] = 0;
	_texRect[texID] = {};
	_texRectPos[texID] = {};

	//�g�p����
	glDisable(GL_TEXTURE_2D);
}

//PngImage�̃��[�h�֐�(���ꂾ���߂��Ⴍ���ᒷ���̂ŕ����܂���)
bool CRenderer::loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	FILE *fp;

	if ((fp = fopen(name, "rb")) == NULL)
		return false;

	/* Create and initialize the png_struct
	* with the desired error handler
	* functions.  If you want to use the
	* default stderr and longjump method,
	* you can supply NULL for the last
	* three parameters.  We also supply the
	* the compiler header file version, so
	* that we know if the application
	* was compiled with a compatible version
	* of the library.  REQUIRED
	*/
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL);

	if (png_ptr == NULL) {
		fclose(fp);
		return false;
	}

	/* Allocate/initialize the memory
	* for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	/* Set error handling if you are
	* using the setjmp/longjmp method
	* (this is the normal method of
	* doing things with libpng).
	* REQUIRED unless you  set up
	* your own error handlers in
	* the png_create_read_struct()
	* earlier.
	*/
	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated
		* with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		/* If we get here, we had a
		* problem reading the file */
		return false;
	}

	/* Set up the output control if
	* you are using standard C streams */
	png_init_io(png_ptr, fp);

	/* If we have already
	* read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);

	/*
	* If you have enough memory to read
	* in the entire image at once, and
	* you need to specify only
	* transforms that can be controlled
	* with one of the PNG_TRANSFORM_*
	* bits (this presently excludes
	* dithering, filling, setting
	* background, and doing gamma
	* adjustment), then you can read the
	* entire image (including pixels)
	* into the info structure with this
	* call
	*
	* PNG_TRANSFORM_STRIP_16 |
	* PNG_TRANSFORM_PACKING  forces 8 bit
	* PNG_TRANSFORM_EXPAND forces to
	*  expand a palette into RGB
	*/
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 width, height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
		&interlace_type, NULL, NULL);
	outWidth = width;
	outHeight = height;

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*outData = (unsigned char*)malloc(row_bytes * outHeight);

	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < outHeight; i++) {
		// note that png is ordered top to
		// bottom, but OpenGL expect it bottom to top
		// so the order or swapped
		memcpy(*outData + (row_bytes * i), row_pointers[i], row_bytes);
	}

	/* Clean up after the read,
	* and free any memory allocated */
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	/* Close the file */
	fclose(fp);
	/* That's it */
	return true;
}

//�e�N�X�`���̐F�ݒ�
void CRenderer::setupTextureColor(const CVec4 color, const GLuint texID)
{
	_texColorRGBA[texID] = color;
}
void CRenderer::setupTextureColorAtTag(const CVec4 color, const GLuint tag)
{
	for (int i = 0; i < MAX_TEXTURE_NUMBER; i++)
	{
		if (_texTag[i] == tag)
		{
			_texColorRGBA[i] = color;
			return;
		}
	}
}

//�e�N�X�`���̃t�F�[�h�ݒ�
void CRenderer::TextureFade(const GLuint texID, const bool out,const float fadeInterval)
{
	_texActionFade[texID] = true;
	_texActionFadeInterval[texID] = fadeInterval;
	_texFadeOut[texID] = out;
	this->fadeSearch();

}

//�e�N�X�`���̃X�P�[���ݒ�
void CRenderer::setTextureScale(const CVec2 Size, const GLuint texID)
{
	_texScale[texID] = Size;
	_texRectPos[texID] = CVec4(_texPosition[texID].x - _texWH[texID].x * Size.x, _texPosition[texID].x + _texWH[texID].x * Size.x, _texPosition[texID].y - _texWH[texID].y * Size.y, _texPosition[texID].y + _texWH[texID].y * Size.y);
}
void CRenderer::setTextureScaleAtTag(const CVec2 Size, const GLuint tag)
{
	for (int i = 0; i < MAX_TEXTURE_NUMBER; i++)
	{

		if (_texTag[i] == tag)
		{
			_texScale[i] = Size;
			_texRectPos[i] = CVec4(_texPosition[i].x - _texWH[i].x * Size.x, _texPosition[i].x + _texWH[i].x * Size.x, _texPosition[i].y - _texWH[i].y * Size.y, _texPosition[i].y + _texWH[i].y * Size.y);
			return;
		}
	}
}

//�e�N�X�`���̍��W�ݒ�
void CRenderer::setTexPosition(const CVec2 position, const GLuint texID)
{
	_texPosition[texID] = position;
	_texRectPos[texID] = CVec4(
		_texPosition[texID].x - _texWH[texID].x * _texScale[texID].x,
		_texPosition[texID].x + _texWH[texID].x * _texScale[texID].x,
		_texPosition[texID].y - _texWH[texID].y * _texScale[texID].y,
		_texPosition[texID].y + _texWH[texID].y * _texScale[texID].y);
}
void CRenderer::setTexPositionAtTag(const CVec2 position, const GLuint tag)
{
	for (int i = 0; i < MAX_TEXTURE_NUMBER; i++)
	{
		if (_texTag[i] == tag)
		{
			_texPosition[i] = position;
			_texRectPos[i] = CVec4(
				_texPosition[i].x - _texWH[i].x * _texScale[i].x,
				_texPosition[i].x + _texWH[i].x * _texScale[i].x,
				_texPosition[i].y - _texWH[i].y * _texScale[i].y,
				_texPosition[i].y + _texWH[i].y * _texScale[i].y);
			return;
		}
	}
}

//�}�b�v�f�[�^�̍��W�ݒ�
void CRenderer::setMapPosition(const CVec2 position, const GLuint texID)
{
	_texPosition[texID] = position;
	CVec4 defrect = _texRectPos[texID];
	_texRectPos[texID] = CVec4(_texPosition[texID].x + defrect.x, _texPosition[texID].x + defrect.y, _texPosition[texID].y + defrect.z, _texPosition[texID].y + defrect.w);
}


//�e�N�X�`���̋�`�ݒ�
void CRenderer::setTextureRect(const CVec4 rect,const GLuint texID)
{
	//�g�p����
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texID[texID]);


	//�摜�̋�`�͈͂�ݒ�
	CVec4 changerect4 = CVec4(rect.x / _texImage[texID]->m_width, (rect.x + rect.z) / _texImage[texID]->m_width, rect.y / _texImage[texID]->m_height, (rect.y + rect.w) / _texImage[texID]->m_height);

	_texRect[texID] = CVec4(changerect4);

	//�g�p����
	glDisable(GL_TEXTURE_2D);
}

//HP��BP�̃o�[�̂��߂̋�`�ݒ�
void CRenderer::SetProgressBarWH(const GLuint texID,const CVec4 _texRect, const CVec2 position)
{
	//�g�p����
	glEnable(GL_TEXTURE_2D);
	CVec2 vec2;
	glBindTexture(GL_TEXTURE_2D, _texID[texID]);
	if (_texRect.z >= 0)
	{
		_texWH[texID] = CVec2(_texRect.z, 5.0f);
		vec2 = CVec2(position.x + _texRect.z, position.y);
	}
	else
	{
		_texWH[texID] = CVec2(0.0f, 5.0f);
		vec2 = CVec2(position.x + 0.0f, position.y);
	}
	_texPosition[texID] = vec2;
	_texRectPos[texID] = CVec4(
		_texPosition[texID].x - _texWH[texID].x * _texScale[texID].x,
		_texPosition[texID].x + _texWH[texID].x * _texScale[texID].x,
		_texPosition[texID].y - _texWH[texID].y * _texScale[texID].y,
		_texPosition[texID].y + _texWH[texID].y * _texScale[texID].y);

	//�g�p����
	glDisable(GL_TEXTURE_2D);

}
//�Q�[���̒��̃e�N�X�`�������ׂč폜
void CRenderer::allTextureDelete()
{
	for (int i = 0;i < MAX_TEXTURE_NUMBER;i++)
	{
		if (i != MAX_TEXTURE_NUMBER - 1)
		{
			deleteTexture(i);
			SAFE_DELETE(_texImage[i]);
		}
	}
	for (int i = 0; i < MAX_BACKGROUND_NUMBER; i++)
	{
		_bgPolyVert[i] = {};
		_bgPolyColor[i] = {};
		_bgPolyLine[i] = {};
		_bgPolyMaxLine = {};
	}
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		_polyVert[i] = {};
		_polyColor[i] = {};
		_polyTag[i] = {};
	}
}

//�Q�[���ɕK�v�s���ȃe�N�X�`���ȊO�̃e�N�X�`�����폜(�X�e�[�W�ړ�)
void CRenderer::allTextureDeletenotPlayer()
{
	for (int i = 0;i < MAX_TEXTURE_NUMBER;i++)
	{
		//BB��UI�ȉ��ȊO�̃e�N�X�`�����폜
		if (i != BLACKBORD_ID && i != NOTES_ID && i > BAR_ENEMYHP_ID)
		{
			deleteTexture(i);
			SAFE_DELETE(_texImage[i]);
		}
	}
	for (int i = 0; i < MAX_BACKGROUND_NUMBER; i++)
	{
		_bgPolyVert[i] = {};
		_bgPolyColor[i] = {};
		_bgPolyLine[i] = {};
		_bgPolyMaxLine = {};
	}
}
//�w�i�p�̍X�V����
void CRenderer::notesFadeBackground()
{
	for (int i = 0; i < MAX_BACKGROUND_NUMBER; i++)
	{
		if (_bgPolyColor[i].w > 10.0f)
			_bgPolyColor[i].w -= 5.0f;

		if (_bgPolyVert[i].z > _bgPolyDefaultVert)
		{
			_bgPolyVert[i].z -= _beatUpSize * 0.1f;
			//�������O�p
			if(_bgPolyVert[i].w < 0)
				_bgPolyVert[i].w += _beatUpSize * 0.1f;
			else
				_bgPolyVert[i].w -= _beatUpSize * 0.1f;
		}
	}
}
//beats�ɍ��킹��A�N�V�����̍X�V����
void CRenderer::polygonNotesAction()
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
		//������菬�������
		if (_polyVert[i].z < _polyDefaultVert[i].x)
		{
			//Scale�����X�ɖ߂�
			_polyVert[i].z += _polyDefaultVert[i].x*0.02f;
			_polyVert[i].w += _polyDefaultVert[i].y*0.02f;
		}
		if (_polyColor[i].w > 10.0f)
		{
			if(_polyTag[i] == TAG_BEATSACTION1 || _polyTag[i] == TAG_BEATSACTION2 || _polyTag[i] == TAG_BEATSACTION3 || _polyTag[i] == TAG_BEATSACTION4)
				_polyColor[i].w -= 10.0f;
		}
		if (_polyTag[i] == TAG_PLAYER_1)
		{
			if (_polyColor[i].z < 100.0f)
				_polyColor[i].z += 10.0f;
		}
	}
}

//�e�N�X�`����beats�ɍ��킹��A�N�V�����̍X�V����
void CRenderer::textureNotesAction()
{
	for (int i = 0; i < MAX_TEXTURE_NUMBER; i++)
	{
		if (_texScale[i].x < _texDefaultScale[i])
		{
			if (_texTag[i] == TAG_TITLE_TEXT1 || _texTag[i] == TAG_TITLE_TEXT2 || _texTag[i] == TAG_TITLE_TEXT3)
				setTextureScaleAtTag(CVec2(_texScale[i].x + 0.011f, _texScale[i].y + 0.01f), _texTag[i]);
		}
	}
}

//�w�i�p�̃����_��������
void CRenderer::notesRandomFadeInit()
{
	for (int i = 0; i < MAX_BACKGROUND_NUMBER; i++)
	{
		if (rand() % 3 == 1)
		{
			_bgPolyColor[i].w = 100.0f;
			_bgPolyVert[i].z += _beatUpSize;
			//�������O�p
			if (_bgPolyVert[i].w < 0)
				_bgPolyVert[i].w -= _beatUpSize;
			else
				_bgPolyVert[i].w += _beatUpSize;
		}

	}
}

//�w�i�p�̏�ɏオ���Ă���������(mode)
void CRenderer::notesUpFadeInit(GLuint mode)
{
	switch (mode)
	{
	case 0:
		for (int i = 0; i < MAX_BACKGROUND_NUMBER; i++)
		{
			if (_bgPolyLine[i] == upfadeCount)
			{
				_bgPolyColor[i].w = 100.0f;
				_bgPolyVert[i].z += _beatUpSize;
				//�������O�p
				if (_bgPolyVert[i].w < 0)
					_bgPolyVert[i].w -= _beatUpSize;
				else
					_bgPolyVert[i].w += _beatUpSize;
			}
		}
		upfadeCount++;
		if (upfadeCount > _bgPolyMaxLine)
		{
			upfadeCount = 0;
		}
		break;
	case 1:
		for (int i = 0; i < MAX_BACKGROUND_NUMBER; i++)
		{
			if (_bgPolyLine[i] == upfadeCount || _bgPolyLine[i] == upfadeCount + 1)
			{
				_bgPolyColor[i].w = 100.0f;
				_bgPolyVert[i].z += _beatUpSize;
				//�������O�p
				if (_bgPolyVert[i].w < 0)
					_bgPolyVert[i].w -= _beatUpSize;
				else
					_bgPolyVert[i].w += _beatUpSize;
			}
		}
		upfadeCount += 2;
		if (upfadeCount > _bgPolyMaxLine)
		{
			upfadeCount = 0;
		}
		break;
	default:
		break;
	}
	
}

//beats�ɍ��킹��A�N�V����(mode(0:�T�C�Y,1�F))
void CRenderer::polygonNotesActionInit(const GLuint tag,const GLuint mode)
{
	for (int i = 0; i < MAX_POLYGON_NUMBER; i++)
	{
	
		if (_polyTag[i] == tag)
		{
			switch (mode)
			{
			case 0:
				_polyVert[i].z = _polyDefaultVert[i].x * 0.6f;
				_polyVert[i].w = _polyDefaultVert[i].y * 0.6f;
				break;
			case 1:
				_polyColor[i].w = 100.0f;
				break;
			default:
				break;
			}
		}

	
	
	}
}