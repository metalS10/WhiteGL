#include <stdio.h>
#include <stdlib.h>
#include "GL/glut.h"
#include "png/png.h"
#include "Constants.h"

#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "libpng.lib")

GLuint texture;

GLuint createTextureFromPNGFile(const char *filename) {
	//長いので省略
	//「libpngでPNGファイルを読み込む」のソース見てね

	FILE *fp;
	png_structp pPng = NULL;
	png_infop pInfo = NULL;
	int depth, colorType, interlaceType;
	unsigned int width, height;
	int rowSize, imgSize;
	unsigned int i;
	unsigned char *data;
	GLuint texture;

	//PNGファイルを開く
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		fprintf(stderr, "createTextureFromPNGFile: Failed to fopen.");
		return 0;
	}

	//PNGファイルを読み込むための構造体を作成
	pPng = png_create_read_struct(
		PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL
	);
	pInfo = png_create_info_struct(pPng);

	//初期化
	png_init_io(pPng, fp);

	//画像情報を読み込み
	//画像の幅、高さ、ビット深度、色の表現方法、インターレースの情報を取得する
	png_read_info(pPng, pInfo);
	png_get_IHDR(pPng, pInfo,
		&width, &height,
		&depth, &colorType,
		&interlaceType, NULL, NULL
	);

	//RGBとRGBAのみに対応
	if (colorType != PNG_COLOR_TYPE_RGB && colorType != PNG_COLOR_TYPE_RGBA) {
		fprintf(stderr, "createTextureFromPNGFile: Supprted color type are RGB and RGBA.");
		return 0;
	}

	//インターレースは非対応
	if (interlaceType != PNG_INTERLACE_NONE) {
		fprintf(stderr, "createTextureFromPNGFile: Interlace image is not supprted.");
		return 0;
	}

	//1行のデータサイズと画像の高さから必要なメモリ量を計算して、メモリ確保
	rowSize = png_get_rowbytes(pPng, pInfo);
	imgSize = rowSize * height;
	data = (unsigned char*)malloc(imgSize);

	//ピクセルの読み込み
	for (i = 0; i < height; i++) {
		png_read_row(pPng, &data[i * rowSize], NULL);
	}

	png_read_end(pPng, pInfo);

	//OpenGLテクスチャの作成
	glGenTextures(1, &texture);

	//テクスチャを選択
	glBindTexture(GL_TEXTURE_2D, texture);

	//テクスチャにPNGファイルから読み込んだピクセルを書き込む
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data
	);

	//後片付け
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

	//テクスチャサンプリング設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//透過設定
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();

	return 0;

}