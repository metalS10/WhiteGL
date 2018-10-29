#include "RendInfo.h"
#include "../AllController/AllController.h"
#include "../Image/LoadImage/LoadImage.h"

using namespace rendInfo;

//===============================================================
//	�e�N�X�`��
//===============================================================

//�R���X�g���N�^
CTexRendInfo::CTexRendInfo()
{
	init();
}
//�f�X�g���N�^
CTexRendInfo::~CTexRendInfo()
{
	deleteTexture();
	SAFE_DELETE(_texImage);
}
//������
void CTexRendInfo::init()
{
	//�S�̕`���m_renderer���Q�b�g
	m_renderer = MS::CMS::getInstance()->getRenderer();

	//renderer�Ɏ����̕`��p�̑S�Ă�ݒ肷��
	m_renderer->pushTexture(&_texID, &_texRectPos, &_texRect, (int*)&_texType, &_texColorRGBA, (int*)&_texLayer);
}


//==============================================================
//���ݒ�n
//==============================================================

//�e�N�X�`���̏��ݒ�(������)
/**
*�e�N�X�`�����o�^
*@param	file	�t�@�C���p�X
*@param	tex_type	�e�N�X�`���̊g���q
*param	texPos	�e�N�X�`���̈ʒu
*@param	texRect	�e�N�X�`���̋�`
*@param	color	�e�N�X�`���F
*@param	layer	���C���ݒ�
*/
void CTexRendInfo::setupTexture(const char *file, const TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color, LAYER layer)
{

	//�g�p����
	glEnable(GL_TEXTURE_2D);

	//texID���󂢂Ă���Ƃ����
	_texID = texID;
	//glGenTextures(1, &_texID);
	//������
	glBindTexture(GL_TEXTURE_2D, _texID);

	switch (tex_type)
	{
	case TEX_TYPE::BMP:
		_texImage = new CBmpImage();
		//�摜���ǂݍ���
		if (_texImage->load(file) == false)
		{
			std::cerr << "ERROR : �摜�̓ǂݍ��݂Ɏ��s" << std::endl;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _texImage->m_width, _texImage->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _texImage->m_bits);

		//�e�N�X�`���̊g��E�k�����@�̐ݒ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//�e�N�X�`���̌J��Ԃ��̎w��
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		break;

	case TEX_TYPE::PNG:
		_texImage = new CPngImage();
		if (_texImage->load(file) == false)
		{
			std::cerr << "ERROR : �摜�̓ǂݍ��݂Ɏ��s" << std::endl;
		}
		if (_texImage->m_format == PNG_COLOR_TYPE_RGBA)
		{
			//�e�N�X�`����PNG�t�@�C������ǂݍ��񂾃s�N�Z������������
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _texImage->m_width, _texImage->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _texImage->m_bits);

			//�e�N�X�`���̊g��E�k�����@�̐ݒ�
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			//�e�N�X�`���̌J��Ԃ��̎w��
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		}
		else if (_texImage->m_format == PNG_COLOR_TYPE_RGB)
		{
			//�e�N�X�`����PNG�t�@�C������ǂݍ��񂾃s�N�Z������������
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _texImage->m_width, _texImage->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _texImage->m_bits);

			//�e�N�X�`���̊g��E�k�����@�̐ݒ�
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			//�e�N�X�`���̌J��Ԃ��̎w��
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		}
		else if (_texImage->m_format == PNG_COLOR_TYPE_PALETTE)
		{
			GLubyte* textureImage;

			int width, height;
			bool hasAlpha = true;	//�Ƃ肠����Png��Alpha����ł���
			const char* filename = file;
			bool success = loadImage::CLoadImage::loadPngImage(filename, width, height, hasAlpha, &textureImage);
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
		else if (_texImage->m_format == PNG_COLOR_TYPE_GRAY)
		{
			//�e�N�X�`����PNG�t�@�C������ǂݍ��񂾃s�N�Z������������
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _texImage->m_width, _texImage->m_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, _texImage->m_bits);
			//gray���Ăǂ��`�悷��񂾂낤
			std::cout << "PNG_COLOR_TYPE_GRAY�p�`��V�X�e��������" << std::endl;
		}

		break;

	case TEX_TYPE::QUAD:
		_texImage = new CPngImage();

		_texImage->m_width = 1; _texImage->m_height = 1;
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
	
	//�X�P�[���̏�����
	_texScale = CVec2(1, 1);
	//�X�P�[���̏����l
	_texDefaultScale = 1.0f;


	//���C���ݒ�
	_texLayer = layer;
	//�e�N�X�`���F�ݒ�(������)
	setupTextureColor(color);
	//�e�N�X�`���g���q�̐ݒ�
	_texType = tex_type;

	//���W�ݒ�
	setupTextureTransform(texPos,texRect);


	//�g�p����
	glDisable(GL_TEXTURE_2D);

}
void CTexRendInfo::setImage(const char *file, TEX_TYPE tex_type,GLuint texID,CVec2 texPos, CVec4 texRect, CVec4 color, LAYER layer)
{
	setupTexture(file, tex_type, texID, texPos, texRect, color, layer);
}
void CTexRendInfo::setImage(const char *file, TEX_TYPE tex_type,GLuint texID,CVec2 texPos, CVec4 texRect, CVec4 color)
{
	setupTexture(file, tex_type, texID, texPos, texRect, color, LAYER::MAIN);
}
void CTexRendInfo::setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, LAYER layer)
{
	setupTexture(file, tex_type, texID, texPos, texRect, CVec4(100.0f,100.0f,100.0f,100.0f), layer);
}
void CTexRendInfo::setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect)
{
	setupTexture(file, tex_type, texID, texPos, texRect, CVec4(100.0f,100.0f,100.0f,100.0f), LAYER::MAIN);
}

//�e�N�X�`���̃g�����X�t�H�[���ݒ�(������)
void CTexRendInfo::setupTextureTransform(const CVec2 texPos, const CVec4 texRect)
{

	//�����c�����Z�b�g
	_texWH = CVec2(((texRect.x + texRect.z) - texRect.x) * 0.5f, ((texRect.y + texRect.w) - texRect.y) * 0.5f);
	_texRectPos = CVec4(texPos.x - _texWH.x, texPos.x + _texWH.x, texPos.y - _texWH.y, texPos.y + _texWH.y);
	_texPosition = texPos;
	//�摜�̋�`�͈͂�ݒ�
	CVec4 changerect4 = CVec4(texRect.x / _texImage->m_width, (texRect.x + texRect.z) / _texImage->m_width, texRect.y / _texImage->m_height, (texRect.y + texRect.w) / _texImage->m_height);
	_texRect = CVec4(changerect4);

	if (_texImage == NULL)
	{
		std::cerr << "BMP,PNG,JPEG�Ȃ�ł��Ȃ��ł�" << std::endl;
	}
}

//�e�N�X�`���̐F�ݒ�(������)
void CTexRendInfo::setupTextureColor(const CVec4 color)
{
	_texColorRGBA = color;
}
//�e�N�X�`���̃X�P�[���ݒ�
void CTexRendInfo::setTextureScale(const CVec2 Size)
{
	_texScale= Size;
	_texRectPos = CVec4(_texPosition.x - _texWH.x * Size.x, _texPosition.x + _texWH.x * Size.x, _texPosition.y - _texWH.y * Size.y, _texPosition.y + _texWH.y * Size.y);
}
//�e�N�X�`���̍��W�ݒ�
void CTexRendInfo::setTexPosition(const CVec2 position)
{
	_texPosition = position;
	_texRectPos = CVec4(
		_texPosition.x - _texWH.x * _texScale.x,
		_texPosition.x + _texWH.x * _texScale.x,
		_texPosition.y - _texWH.y * _texScale.y,
		_texPosition.y + _texWH.y * _texScale.y);
}
//�e�N�X�`���̋�`�ݒ�
void CTexRendInfo::setTextureRect(const CVec4 rect)
{
	//�摜�̋�`�͈͂�ݒ�
	CVec4 changerect4 = CVec4(rect.x / _texImage->m_width, (rect.x + rect.z) / _texImage->m_width, rect.y / _texImage->m_height, (rect.y + rect.w) / _texImage->m_height);

	_texRect = CVec4(changerect4);
}
//HP��BP�̃o�[�̂��߂̋�`�ݒ�
void CTexRendInfo::SetProgressBarWH(const CVec4 _texRect, const CVec2 position)
{
	CVec2 vec2;
	if (_texRect.z >= 0)
	{
		_texWH = CVec2(_texRect.z, 5.0f);
		vec2 = CVec2(position.x + _texRect.z, position.y);
	}
	else
	{
		_texWH = CVec2(0.0f, 5.0f);
		vec2 = CVec2(position.x + 0.0f, position.y);
	}
	_texPosition = vec2;
	_texRectPos = CVec4(
		_texPosition.x - _texWH.x * _texScale.x,
		_texPosition.x + _texWH.x * _texScale.x,
		_texPosition.y - _texWH.y * _texScale.y,
		_texPosition.y + _texWH.y * _texScale.y);

	return;
}


//==============================================================
//Map�p
//==============================================================
//�}�b�v�f�[�^�̍��W�ݒ�
void CTexRendInfo::setMapPosition(const CVec2 position, const int tag)
{
	_texPosition = position;
	CVec4 defrect = _texRectPos;
	_texRectPos = CVec4(_texPosition.x + defrect.x, _texPosition.x + defrect.y, _texPosition.y + defrect.z, _texPosition.y + defrect.w);
	return;
}


//==============================================================
//�A�N�V�����n
//==============================================================

//�e�N�X�`���̃t�F�[�h�A�N�V�����ݒ�
void CTexRendInfo::setActionFade(const bool out, const float fadeCounter)
{
	//�t�F�[�h�C���E�A�E�g���ł���
	_texActionFade = true;
	//�t�F�[�h�̑��x
	_texActionFadeCounter = fadeCounter;
	//�t�F�[�h�C��or�A�E�g�̃Z�b�g
	_texFadeOut = out;

	return;
}

//�t�F�[�h�C���E�A�E�g���̓���(�F���)
void CTexRendInfo::textureActionFade()
{
	//�t�F�[�h�C���A�E�g
	if (_texActionFade)
	{
		//�t�F�[�h�A�E�g
		if (_texFadeOut)
		{
			_texColorRGBA.w -= _texActionFadeCounter;
			if (_texColorRGBA.w < 0.0f)
			{
				_texColorRGBA.w = 0.0f;
				_texActionFade = false;
			}
		}
		//�t�F�[�h�C��
		else
		{
			_texColorRGBA.w += _texActionFadeCounter;
			if (_texColorRGBA.w > 100.0f)
			{
				_texColorRGBA.w = 100.0f;
				_texActionFade = false;
			}
		}

	}

}

//�e�N�X�`���t�F�[�h�I�����Ă��邩�ǂ�����Ԃ�
bool CTexRendInfo::endTextureFade()
{
	return !_texActionFade;
}
//�e�N�X�`���𔏎q�ɍ��킹�邩�ۂ��̃Z�b�g
void CTexRendInfo::setTexActionBeats(bool action)
{
	_texActionBeats = action;
}
//�e�N�X�`���̃T�C�Y���߂铮��
void CTexRendInfo::textureNotesAction()
{
	if (_texActionBeats)
	{
		if (_texScale.x < _texDefaultScale)
		{
			setTextureScale(CVec2(_texScale.x + 0.01f, _texScale.y + 0.01f));
		}
	}
}

//==============================================================
//�폜�n
//==============================================================


//�e�N�X�`���̍폜
void CTexRendInfo::deleteTexture()
{
	//�g�p����
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texID);
	glDeleteTextures(1, &_texID);
	glBindTexture(GL_TEXTURE_2D, 0);
	//_texID = 0;
	_texRect = {};
	_texRectPos = {};

	//�g�p����
	glDisable(GL_TEXTURE_2D);
}


//===============================================================
//�|���S��
//===============================================================
//�R���X�g���N�^
CPolygonRendInfo::CPolygonRendInfo()
{
	init();
}
//�f�X�g���N�^
CPolygonRendInfo::~CPolygonRendInfo()
{
	deletePoly();
}
//������
void CPolygonRendInfo::init()
{
	//�S�̕`���m_renderer���Q�b�g
	m_renderer = MS::CMS::getInstance()->getRenderer();

	//renderer�Ɏ����̕`��p�̑S�Ă�ݒ肷��
	m_renderer->pushPoly(&_polyVert, &_polyColor, &_polyAngle, (int*)&m_polyLayer);
}


//�|���S���̃Z�b�g�A�b�v
void CPolygonRendInfo::setupPoly(const CVec4 vertex, const CVec4 color, const LAYER layer)
{
	//�|���S���ݒ��ǉ�
	_polyVert = vertex;
	_polyColor = color;
	_polyDefaultVert = CVec2(vertex.z, vertex.w);
	m_polyLayer = layer;
}
void CPolygonRendInfo::setPolyPos(const CVec2 vertex)
{
	_polyVert.x = vertex.x;
	_polyVert.y = vertex.y;
}
void CPolygonRendInfo::setPolyScale(const CVec2 scale)
{
	_polyVert.z = scale.x;
	_polyVert.w = scale.y;
}

void CPolygonRendInfo::setPolyPosX(const float vertex)
{
	_polyVert.x = vertex;
}
void CPolygonRendInfo::setPolyAngle(const float angle)
{
	_polyAngle = angle;
}
void CPolygonRendInfo::setPolyColor(const CVec4 color)
{
	_polyColor = color;
}
void CPolygonRendInfo::addPolyAngle(const float angle)
{
	_polyAngle += angle;
}
float CPolygonRendInfo::getPolyAngle()
{
	return _polyAngle;
}
CVec2 CPolygonRendInfo::getPolyScale()
{
	return CVec2(_polyVert.z, _polyVert.w);
}
CVec4 CPolygonRendInfo::getPolyColor()
{
	return _polyColor;
}

//�|���S���̍폜
void CPolygonRendInfo::deletePoly()
{
	setPolyPos(CVec2(0.0f, 0.0f));
	setPolyScale(CVec2(0.0f, 0.0f));
	setPolyAngle(0.0f);
}

//=====================================================
//�A�N�V����
//=====================================================
//beats�ɍ��킹��A�N�V�����̍X�V����
void CPolygonRendInfo::polygonBeatsAction()
{
	//������菬�������
	if (_polyVert.z < _polyDefaultVert.x)
	{
		//Scale�����X�ɖ߂�
		_polyVert.z += _polyDefaultVert.x*0.02f;
		_polyVert.w += _polyDefaultVert.y*0.02f;
	}
	//10���傫�����
	if (_polyColor.w > 10.0f)
	{
		if (_polyActionBeats)
			_polyColor.w -= 10.0f;	//���������Ă���
	}
	/*
	if (_polyTag == TAG_PLAYER_1)
	{
		if (_polyColor.z < 100.0f)
			_polyColor.z += 10.0f;
	}
	*/

}

//beats�ɍ��킹��A�N�V����(mode(0:�T�C�Y,1�F))
void CPolygonRendInfo::polygonBeatsActionInit(const int mode)
{
	_polyActionBeats = true;
	switch (mode)
	{
	case 0:
		_polyVert.z = _polyDefaultVert.x * 0.6f;
		_polyVert.w = _polyDefaultVert.y * 0.6f;
		break;
	case 1:
		_polyColor.w = 100.0f;
		break;
	default:
		break;
	}
}

//===============================================================
//�w�i�p�O�p�|���S��
//===============================================================
CTriPolygonRendInfo::CTriPolygonRendInfo()
{
	init();
}

CTriPolygonRendInfo::~CTriPolygonRendInfo()
{
	
}

void CTriPolygonRendInfo::init()
{
	//�S�̕`���m_renderer���Q�b�g
	m_renderer = MS::CMS::getInstance()->getRenderer();

	//renderer�Ɏ����̕`��p�̑S�Ă�ݒ肷��
	m_renderer->pushTriPoly(&_bgPolyVert, &_bgPolyColor, &_bgPolyAngle, (int*)&m_bgPolyLayer);
}

//�O�p�|���S���̃Z�b�g�A�b�v
void CTriPolygonRendInfo::setupTrianglesPoly(CVec4 vertex, CVec4 color, int line, LAYER layer)
{
	if (!_bgPolyVert.x && !_bgPolyVert.y && !_bgPolyVert.z && !_bgPolyVert.w)
	{
		//�|���S���ݒ��ǉ�
		_bgPolyVert = vertex;
		_bgPolyColor = color;
		_bgPolyLine = line;
		_bgPolyMaxLine = line;
		_bgPolyDefaultVert = vertex.z;
		m_bgPolyLayer = layer;
	}
}


void CTriPolygonRendInfo::setTrianglesPolyPos(float vertexX, CVec4 color)
{
	_bgPolyVert.x = vertexX;
	_bgPolyColor = color;
}
void CTriPolygonRendInfo::addTrianglesPolyAngle(float angle)
{
	_bgPolyAngle += angle;
}

//===============================================================
//�A�N�V����
//===============================================================
//�w�i�p�̍X�V����
void CTriPolygonRendInfo::notesFadeBackground()
{
	if (_bgPolyColor.w > 10.0f)
		_bgPolyColor.w -= 5.0f;

	if (_bgPolyVert.z > _bgPolyDefaultVert)
	{
		_bgPolyVert.z -= _beatUpSize * 0.1f;
		//�������O�p
		if (_bgPolyVert.w < 0)
			_bgPolyVert.w += _beatUpSize * 0.1f;
		else
			_bgPolyVert.w -= _beatUpSize * 0.1f;
	}

}



//�w�i�p�̃����_��������
void CTriPolygonRendInfo::notesRandomFadeInit()
{
	if (rand() % 3 == 1)
	{
		_bgPolyColor.w = 100.0f;
		_bgPolyVert.z += _beatUpSize;
		//�������O�p
		if (_bgPolyVert.w < 0)
		{
			_bgPolyVert.w -= _beatUpSize;
		}
		else
		{
			_bgPolyVert.w += _beatUpSize;
		}
	}


}

//�w�i�p�A�N�V�����̏�����(mode)
void CTriPolygonRendInfo::notesUpFadeInit(int mode)
{
	switch (mode)
	{
	case 0:
		if (_bgPolyLine == upfadeCount)
		{
			_bgPolyColor.w = 100.0f;
			_bgPolyVert.z += _beatUpSize;
			//�������O�p
			if (_bgPolyVert.w < 0)
				_bgPolyVert.w -= _beatUpSize;
			else
				_bgPolyVert.w += _beatUpSize;
		}
		upfadeCount++;
		if (upfadeCount > _bgPolyMaxLine)
		{
			upfadeCount = 0;
		}
		break;
	case 1:
		if (_bgPolyLine == upfadeCount || _bgPolyLine == upfadeCount + 1)
		{
			_bgPolyColor.w = 100.0f;
			_bgPolyVert.z += _beatUpSize;
			//�������O�p
			if (_bgPolyVert.w < 0)
				_bgPolyVert.w -= _beatUpSize;
			else
				_bgPolyVert.w += _beatUpSize;
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