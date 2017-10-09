#include "Sprite.h"

/**
*@desc	����������
*@param	fileName	�t�@�C����
*@return true...����
*/
bool CSprite::init(const std::string&fileName)
{
	this->m_pTexture = CTextureManager::getInstance()->get(fileName);
	if (this->m_pTexture == NULL)
	{
		printf("�e�N�X�`���̐����Ɏ��s\n");
		return false;
	}
	return true;
}

/**
*@desc	�`��
*/
void CSprite::draw()
{
	float width = this->m_pTexture->m_pImage->m_width;
	float height = this->m_pTexture->m_pImage->m_height;

	float left = 0;
	float top = 0;
	float right = width;
	float bottom = height;

	float half_width = this->m_pTexture->m_pImage->m_width * 0.5f;
	float half_height = this->m_pTexture->m_pImage->m_height * 0.5f;

	if (this->m_pTextureRect)
	{
		//�摜��Ԃ̍��̓_
		left = this->m_pTextureRect->m_origin.x;
		//�摜��Ԃ̏�̓_
		top = this->m_pTextureRect->m_origin.y;
		//�摜��Ԃ̉E�̓_
		right = this->m_pTextureRect->m_origin.x + this->m_pTextureRect->m_size.width;
		//�摜��Ԃ̉��̓_
		bottom = this->m_pTextureRect->m_origin.y + this->m_pTextureRect->m_size.height;

		half_width = this->m_pTextureRect->m_size.width * 0.5f;
		half_height = this->m_pTextureRect->m_size.height * 0.5f;
	}


	//���_���W�f�[�^
	GLfloat vertecies[] = {
		-half_width,-half_height,0.0f,	//����
		half_width,half_height,0.0f,	//�E��
		-half_width,half_height,0.0f,	//����
		half_width,-half_height,0.0f,	//�E��
	};

	//�F�f�[�^
	GLfloat color[] = {
		//R,G,B,A
		1.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
	};

	//�e�N�X�`�����W
	GLfloat texcoords[] = {
		left/width,(height-bottom)/height,	//�e�N�X�`����Ԃ̍����̓_���摜��Ԃ̍���̓_��
		right/width,(height-top)/height,	//�e�N�X�`����Ԃ̉E��̓_���摜��Ԃ̉E���̓_��
		left/width,(height-top)/height,		//�e�N�X�`����Ԃ̍���̓_���摜��Ԃ̍����̓_��
		right/width,(height-bottom)/height,	//�e�N�X�`����Ԃ̉E���̓_���摜��Ԃ̉E��̓_��
	};

	//�Y���f�[�^
	GLubyte indeices[] = {
		0,1,2,
		0,3,1
	};

	//�o�^���Ă���e�N�X�`����L����
	glBindTexture(GL_TEXTURE_2D, this->m_pTexture->m_texName);

	//���_���W�f�[�^���������ɓo�^���邽�߂̋��𓾂�
	glEnableClientState(GL_VERTEX_ARRAY);
	//���_���W�f�[�^���������ɓo�^����(���_�f�[�^�̎���,���_�f�[�^�̌^,�I�t�Z�b�g,���_�f�[�^)
	glVertexPointer(3, GL_FLOAT, 0, vertecies);

	//�F�f�[�^���������ɓo�^���邽�߂̋��𓾂�
	glEnableClientState(GL_COLOR_ARRAY);
	//�F�f�[�^���������ɓo�^����(�F�f�[�^�̐F���A�F�f�[�^�̌^,�I�t�Z�b�g,�F�f�[�^)
	glColorPointer(4, GL_FLOAT, 0, color);

	//�e�N�X�`�����W�f�[�^���������ɓo�^���邽�߂̋��𓾂�
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//�e�N�X�`�����W�f�[�^���������ɓo�^����
	//(�e�N�X�`�����W�f�[�^�̎������A�e�N�X�`�����W�f�[�^�̌^�A�I�t�Z�b�g�A�e�N�X�`�����W�f�[�^)
	
	
	
	
	(2, GL_FLOAT, 0, texcoords);

	//�|���S����`��(�`��,�Y���f�[�^�̐�,�Y���f�[�^�̌^,�Y���f�[�^)
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indeices);

	//�`�悷��e�N�X�`������������
	glBindTexture(GL_TEXTURE_2D, 0);

}