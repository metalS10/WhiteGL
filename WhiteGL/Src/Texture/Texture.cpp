#include "Texture.h"
#include <vector>

/**
* @desc	�e�N�X�`���̐���
* @param	fileName �t�@�C����
* @return	true...����
*/
bool CTexture2D::create(const std::string & fileName)
{
	//������̕���(�������镶����A���������؂蕶��)
	auto split = [](const std::string& str, const std::string& delim) -> std::vector<std::string>
	{
		std::vector<std::string>result;
		std::string::size_type pos = 0;
		while (pos != std::string::npos)
		{
			std::string::size_type p = str.find(delim, pos);
			if (p == std::string::npos)
			{
				result.push_back(str.substr(pos));
				break;
			}
			else
			{
				result.push_back(str.substr(pos, p - pos));
			}
			pos = p + delim.size();
		}
		return result;
	};

	//���ʎq���擾
	std::vector<std::string>result = split(fileName, ".");
	std::string end = result[result.size() - 1];

	//BMP�̐���
	if (end == "bmp" || end == "BMP")
	{
		this->m_pImage = new CBmpImage();
	}
	//TGA�̐���
	else if (end == "tga" || end == "TGA")
	{
		this->m_pImage = new CTgaImage();
	}
	else
	{
		//�Ή����Ă��Ȃ�
		printf("��͂ł��Ȃ��^�C�v�̉摜�t�@�C���ł��B\n");
		return false;
	}

	//�摜�t�@�C���̓ǂݍ���
	if (this->m_pImage->load(fileName) == false)
	{
		printf("�t�@�C���̓ǂݍ��݂Ɏ��s\n");
		SAFE_DELETE(this->m_pImage);
		return false;
	}

	//�e�N�X�`��2D�̎g�p����
	glEnable(GL_TEXTURE_2D);
	//�e�N�X�`�����𐶐����擾
	glGenTextures(1, &this->m_texName);
	//�擾�����e�N�X�`�������X�^�b�N�ɓo�^
	glBindTexture(GL_TEXTURE_2D, this->m_texName);

	//�e�N�X�`���摜���������ɂǂ̂悤�Ɋi�[����Ă��邩��PC�ɐݒ肷��
	if (this->m_pImage->m_bpp == 24)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	}
	else if (this->m_pImage->m_bpp == 32)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}

	//�s�N�Z�������X�^�b�N�̈�ԏ�ɂ���e�N�X�`�����ɑ΂��ăe�N�X�`���Ƃ��ēo�^
	glTexImage2D(
		GL_TEXTURE_2D, 0, this->m_pImage->m_internalFormat, this->m_pImage->m_width, this->m_pImage->m_height,
		0, this->m_pImage->m_format, GL_UNSIGNED_BYTE, m_pImage->m_bits
	);

	//�e�N�X�`���̊g��E�k�����@�̐ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//�e�N�X�`���̌J��Ԃ��̎w��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/*�e�N�X�`���̋��E�F*/
	//static const GLfloat border[] = { 1.0,1.0,1.0,1.0 };

	/*�e�N�X�`���̋��E�F*/
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	
	//�ݒ肷��e�N�X�`������������
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

/**
* @desc	�e�N�X�`���̔j��
*/
void CTexture2D::remove()
{
	//�摜�f�[�^�̊J��
	SAFE_DELETE(this->m_pImage);

	//�e�N�X�`�����̓o�^����
	glDeleteTextures(1, &this->m_texName);
}

//============================================================
//
//�����̃e�N�X�`�����Ǘ�����N���X
//
//============================================================
//�R���X�g���N�^
CTextureManager::CTextureManager()
{}

//get instance
CTextureManager* CTextureManager::getInstance()
{
	static CTextureManager instance;
	return &instance;
}

//�f�X�g���N�^
CTextureManager::~CTextureManager()
{
	this->clear();
}

/**
*@desc	�e�N�X�`���̎擾
*@param fileName�t�@�C����
*@return �e�N�X�`��
*@tips	���݂��Ă��Ȃ���ΐ������ĕԂ�
*/
CTexture2D* CTextureManager::get(const std::string & fileName)
{
	CTexture2D* pTex = NULL;

	//���ɐ�������Ă��邩�ǂ����𒲂ׂ�
	std::map<std::string, CTexture2D*>::iterator itr = this->m_textures.find(fileName);
	if (itr == this -> m_textures.end())
	{
		//���݂��Ă��Ȃ���΃e�N�X�`���𐶐�
		pTex = new CTexture2D();

		if (pTex->create(fileName) == false)
		{
			printf("�e�N�X�`���̐����Ɏ��s\n");
			return NULL;
		}
		//�e�N�X�`���Q�Ɏ��t����
		this->m_textures[fileName] = pTex;
	}
	else
	{
		//���݂��Ă��Ȃ���Α��݂��Ă���e�N�X�`����n��
		pTex = itr->second;	//second�͓������̂�Ԃ�
	}
	return pTex;
}

/**
*@desc	�e�N�X�`���̍폜
*@param	fileName�t�@�C����
*/
void CTextureManager::remove(const std::string&fileName)
{
	std::map<std::string, CTexture2D*>::iterator itr = this->m_textures.find(fileName);

	if (itr != this->m_textures.end())
	{
		//�e�N�X�`�����J��
		SAFE_DELETE(itr->second);

		//�C�e���[�^���폜
		this->m_textures.erase(fileName);
	}
}

/**
*@desc	�S�Ẵe�N�X�`���̍폜
*/
void CTextureManager::clear()
{
	//�S�Ẵe�N�X�`�������
	std::map<std::string, CTexture2D*>::iterator itr = this->m_textures.begin();

	while (itr != this->m_textures.end())
	{
		SAFE_DELETE(itr->second);
	}

	//�S�ẴC�e���[�^���폜
	this->m_textures.clear();

	//�L���p�V�e�B���N���A
	std::map < std::string, CTexture2D*>().swap(this->m_textures);
}