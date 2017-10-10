#include "image.h"
#pragma warning(disable:4996)

bool CBmpImage::load(const std::string&fileName)
{
	FILE *file = NULL;
	unsigned long size;			//�C���[�W�̃o�C�g�T�C�Y
	unsigned short int planes;	//�ʐ�
	unsigned short int bpp;		//�s�N�Z����
	unsigned long w = 0;		//��
	unsigned long h = 0;		//����
	unsigned char* pData = NULL;//�擾����s�N�Z���f�[�^

	
	//�t�@�C�����J��
	if ((file = fopen(fileName.c_str(), "rb")) == NULL)
	{
		printf("�t�@�C����������Ȃ�\n");
		return false;
	}
	
	//�r�b�g�}�b�v�̕��f�[�^�����ֈړ�
	fseek(file, 18, SEEK_CUR);

	//������ǂݍ���
	if (fread(&w, 4, 1, file) != 1)
	{
		printf("�����̓ǂݍ��݂Ɏ��s\n");
		return false;
	}
	//�c����ǂݍ���
	if (fread(&h, 4, 1, file) != 1)
	{
		printf("�c���̓ǂݍ��݂Ɏ��s\n");
		return false;
	}

	//�摜�T�C�Y�̌v�Z(��*����*RGB)
	size = w * h * 3;

	//�v���[������ǂݍ���
	//bmp�́u1�v�ɂȂ�
	if (fread(&planes, 2, 1, file) != 1)
	{
		printf("�v���[�����̓ǂݍ��݂Ɏ��s\n");
		return false;
	}
	//�܂��͊�{�I��256�FBMP�̎�舵��
	if (planes != 1)
	{
		printf("256�F�ȏ�ł��B\n");
		return false;
	}

	//�s�N�Z���l��ǂݍ���
	if (fread(&bpp, 2, 1, file) != 1)
	{
		printf("�s�N�Z���l�̎擾�Ɏ��s\n");
		return false;
	}

	//24�r�b�g(RGB)
	if (bpp != 24)
	{
		printf("RGB�ł͂���܂���\n");
		return false;
	}

	//24�r�b�g����΂��āA�F�f�[�^(RGB)�����ֈړ�
	fseek(file, 24, SEEK_CUR);

	//�f�[�^�ǂݍ���
	pData = new unsigned char[size];
	if (pData == NULL)
	{
		printf("�s�N�Z���f�[�^�̐����Ɏ��s\n");
		return false;
	}

	//�F�f�[�^���擾���Ă���
	if (fread(pData, size, 1, file) != 1)
	{
		printf("�s�N�Z���f�[�^�̎擾�Ɏ��s\n");
		return false;
	}

	//BGR����RGB�ɕϊ�
	char temp;
	for (int i = 0;i < size;i += 3)
	{
		temp = pData[i];
		pData[i] = pData[i + 2];
		pData[i + 2] = temp;
	}

	//�l�𔽉f
	this->m_width = w;
	this->m_height = h;
	this->m_bits = pData;

	this->m_bpp = bpp;
	this->m_format = GL_RGB;
	this->m_internalFormat = GL_RGB;

	return true;
}

/**
*@desc	TGA�t�@�C���̓ǂݍ���
*@param	fileName�t�@�C����
*@return true...����
*/
bool CTgaImage::load(const std::string& fileName)
{
	FILE *fp = NULL;				//�t�@�C���|�C���^
	unsigned long size;				//�C���[�W�̃o�C�g�T�C�Y
	GLubyte header[18];				//�w�b�_���
	int bpp;						//�s�N�Z����
	GLubyte bytePerPixel;			//1�s�N�Z��������̃o�C�g��������
	unsigned long w = 0;			//��
	unsigned long h = 0;			//����
	unsigned char* pData = NULL;	//�擾����f�[�^

	/*
	//�t�@�C�����J��
	if ((fp = fopen(fileName.c_str(), "rb")) == NULL)
	{
		printf("�t�@�C�����J���܂���ł���\n");
		return false;
	}
	*/

	//�w�b�_�[���̓ǂݍ���
	fread(header, 1, sizeof(header), fp);

	//���ƍ������v�Z
	w = header[13] * 256 + header[12];
	h = header[15] * 256 + header[14];

	//�r�b�g�̐[��
	bpp = header[16];
	//1�s�N�Z��������̃o�C�g��������
	bytePerPixel = bpp / 8;

	//�f�[�^�T�C�Y�̌���
	size = w * h * bytePerPixel;

	//���������m��
	pData = new GLubyte[size];

	//�F�f�[�^���擾���Ă���
	if ((fread(pData, size, 1, fp)) != 1)
	{
		printf("�f�[�^�̎��o���Ɏ��s\n");
		return false;
	}
	//BGR����RGB�ɕϊ�
	for (int i=0;i < (int)size;i += bytePerPixel)
	{
		GLuint temp = pData[i];
		pData[i + 0] = pData[i + 2];
		pData[i + 2] = temp;
	}

	//�t�@�C�������
	fclose(fp);

	this->m_bits = pData;
	this->m_width = w;
	this->m_height = h;

	this->m_name = fileName;
	this->m_bpp = bpp;

	//	24bit
	if (this->m_bpp == 24)
	{
		this->m_format = GL_RGB;
		this->m_internalFormat = GL_RGB;
	}

	//	32bit
	else if (bpp == 32)
	{
		this->m_format = GL_RGBA;
		this->m_internalFormat = GL_RGBA;
	}
	return true;
}

bool CPngImage::loadchara(const char* fileName)
{
	//1
	FILE *fp;
	png_structp pPng = NULL;
	png_infop pInfo = NULL;
	int depth, colorType, interlaceType;
	unsigned int width, height;
	int rowSize, imgSize;
	unsigned int i;
	unsigned char *data;

	

	//PNG�t�@�C�����J��
	fopen_s(&fp, fileName, "rb");
	if (!fp) {
		fprintf(stderr, "createTextureFromPNGFile: Failed to fopen.");
		return false;
	}

	//PNG�t�@�C����ǂݍ��ނ��߂̍\���̂��쐬
	pPng = png_create_read_struct(
		PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL
	);
	pInfo = png_create_info_struct(pPng);

	//������
	png_init_io(pPng, fp);

	//�摜����ǂݍ���
	//�摜�̕��A�����A�r�b�g�[�x�A�F�̕\�����@�A�C���^�[���[�X�̏����擾����
	png_read_info(pPng, pInfo);
	png_get_IHDR(pPng, pInfo,
		&width, &height,
		&depth, &colorType,
		&interlaceType, NULL, NULL
	);
	
	//RGB��RGBA�݂̂ɑΉ�
	if (colorType != PNG_COLOR_TYPE_RGB && colorType != PNG_COLOR_TYPE_RGBA) {
		fprintf(stderr, "createTextureFromPNGFile: Supprted color type are RGB and RGBA.");
		return false;
	}
	
	//�C���^�[���[�X�͔�Ή�
	if (interlaceType != PNG_INTERLACE_NONE) {
		fprintf(stderr, "createTextureFromPNGFile: Interlace image is not supprted.");
		return false;
	}

	//1�s�̃f�[�^�T�C�Y�Ɖ摜�̍�������K�v�ȃ������ʂ��v�Z���āA�������m��
	rowSize = png_get_rowbytes(pPng, pInfo);
	imgSize = rowSize * height;
	data = (unsigned char*)malloc(imgSize);

	//�s�N�Z���̓ǂݍ���
	for (i = 0; i < height; i++) {
		png_read_row(pPng, &data[i * rowSize], NULL);
	}

	png_read_end(pPng, pInfo);

	

	this->m_width = width;
	this->m_height = height;
	this->m_bits = data;

	this->m_bpp = depth;
	this->m_format = GL_RGBA;
	this->m_internalFormat = GL_RGBA;

	//��Еt��
	free(data);
	png_destroy_info_struct(pPng, &pInfo);
	png_destroy_read_struct(&pPng, NULL, NULL);
	fclose(fp);

	return true;
}

bool CPngImage::load(const std::string& fileName)
{
	//2
	png_structp pPng = NULL;
	png_infop pInfo = NULL;
	unsigned char *data; // ���f�[�^��ێ�����
	FILE       *fp = NULL;

	unsigned int width, height;
	int depth, colortype, interlacetype;
	std::string filename = fileName;

	// png�摜�t�@�C���̃��[�h
	png_structp sp = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop   ip = png_create_info_struct(sp);
				fp = fopen(filename.c_str(), "rb");
	if (!fp) {
		perror(filename.c_str());
	}
	png_init_io(sp, fp);
	png_read_info(sp, ip);
	png_get_IHDR(sp, ip, (png_uint_32*)&width, (png_uint_32*)&height,
		&depth, &colortype, &interlacetype, NULL, NULL);
	// �������̈�m��
	int rb = png_get_rowbytes(sp, ip);
	data = new unsigned char[height * rb];
	unsigned char **recv = new unsigned char*[height];
	for (int i = 0; i < height; i++)
		recv[i] = &data[i * rb];
	png_read_image(sp, recv);
	png_read_end(sp, ip);
	png_destroy_read_struct(&sp, &ip, NULL);
	fclose(fp);
	delete[] recv;

	/*
	// �e�N�X�`���ւ̓o�^
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	*/

	//�l�𔽉f
	this->m_width = width;
	this->m_height = height;
	this->m_bits = data;

	this->m_bpp = depth;
	this->m_format = GL_RGBA;
	this->m_internalFormat = GL_RGBA;
	
	
	return true;
}