#include <stdio.h>
#include <stdlib.h>
#include "GL/glut.h"
#include "png/png.h"
#include "Constants.h"

#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "libpng.lib")

GLuint texture;

GLuint createTextureFromPNGFile(const char *filename) {
	//�����̂ŏȗ�
	//�ulibpng��PNG�t�@�C����ǂݍ��ށv�̃\�[�X���Ă�

	FILE *fp;
	png_structp pPng = NULL;
	png_infop pInfo = NULL;
	int depth, colorType, interlaceType;
	unsigned int width, height;
	int rowSize, imgSize;
	unsigned int i;
	unsigned char *data;
	GLuint texture;

	//PNG�t�@�C�����J��
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		fprintf(stderr, "createTextureFromPNGFile: Failed to fopen.");
		return 0;
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
		return 0;
	}

	//�C���^�[���[�X�͔�Ή�
	if (interlaceType != PNG_INTERLACE_NONE) {
		fprintf(stderr, "createTextureFromPNGFile: Interlace image is not supprted.");
		return 0;
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

	//OpenGL�e�N�X�`���̍쐬
	glGenTextures(1, &texture);

	//�e�N�X�`����I��
	glBindTexture(GL_TEXTURE_2D, texture);

	//�e�N�X�`����PNG�t�@�C������ǂݍ��񂾃s�N�Z������������
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data
	);

	//��Еt��
	free(data);
	png_destroy_info_struct(pPng, &pInfo);
	png_destroy_read_struct(&pPng, NULL, NULL);
	fclose(fp);

	return texture;

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-0.2f, 0.2f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(0.2f, 0.2f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-0.2f, -0.2f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.2f, -0.2f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glFlush();

}

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);

	texture = createTextureFromPNGFile(PASS"Attackw.png");
	if (!texture) {
		fprintf(stderr, "Failed to createTextureFromPNGFile\n");
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`���T���v�����O�ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//���ߐݒ�
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();

	return 0;

}