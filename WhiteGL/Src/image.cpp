#include "image.h"
#pragma warning(disable:4996)

bool CBmpImage::load(const std::string&fileName)
{
	FILE *file = NULL;
	unsigned long size;			//イメージのバイトサイズ
	unsigned short int planes;	//面数
	unsigned short int bpp;		//ピクセル数
	unsigned long w = 0;		//幅
	unsigned long h = 0;		//高さ
	unsigned char* pData = NULL;//取得するピクセルデータ

	
	//ファイルを開く
	if ((file = fopen(fileName.c_str(), "rb")) == NULL)
	{
		printf("ファイルが見つからない\n");
		return false;
	}
	
	//ビットマップの幅データ部分へ移動
	fseek(file, 18, SEEK_CUR);

	//横幅を読み込む
	if (fread(&w, 4, 1, file) != 1)
	{
		printf("横幅の読み込みに失敗\n");
		return false;
	}
	//縦幅を読み込む
	if (fread(&h, 4, 1, file) != 1)
	{
		printf("縦幅の読み込みに失敗\n");
		return false;
	}

	//画像サイズの計算(幅*高さ*RGB)
	size = w * h * 3;

	//プレーン数を読み込む
	//bmpは「1」になる
	if (fread(&planes, 2, 1, file) != 1)
	{
		printf("プレーン数の読み込みに失敗\n");
		return false;
	}
	//まずは基本的な256色BMPの取り扱い
	if (planes != 1)
	{
		printf("256色以上です。\n");
		return false;
	}

	//ピクセル値を読み込む
	if (fread(&bpp, 2, 1, file) != 1)
	{
		printf("ピクセル値の取得に失敗\n");
		return false;
	}

	//24ビット(RGB)
	if (bpp != 24)
	{
		printf("RGBではありません\n");
		return false;
	}

	//24ビット分飛ばして、色データ(RGB)部分へ移動
	fseek(file, 24, SEEK_CUR);

	//データ読み込み
	pData = new unsigned char[size];
	if (pData == NULL)
	{
		printf("ピクセルデータの生成に失敗\n");
		return false;
	}

	//色データを取得していく
	if (fread(pData, size, 1, file) != 1)
	{
		printf("ピクセルデータの取得に失敗\n");
		return false;
	}

	//BGRからRGBに変換
	char temp;
	for (int i = 0;i < size;i += 3)
	{
		temp = pData[i];
		pData[i] = pData[i + 2];
		pData[i + 2] = temp;
	}

	//値を反映
	this->m_width = w;
	this->m_height = h;
	this->m_bits = pData;

	this->m_bpp = bpp;
	this->m_format = GL_RGB;
	this->m_internalFormat = GL_RGB;

	return true;
}

/**
*@desc	TGAファイルの読み込み
*@param	fileNameファイル名
*@return true...成功
*/
bool CTgaImage::load(const std::string& fileName)
{
	FILE *fp = NULL;				//ファイルポインタ
	unsigned long size;				//イメージのバイトサイズ
	GLubyte header[18];				//ヘッダ情報
	int bpp;						//ピクセル数
	GLubyte bytePerPixel;			//1ピクセル当たりのバイト数を決定
	unsigned long w = 0;			//幅
	unsigned long h = 0;			//高さ
	unsigned char* pData = NULL;	//取得するデータ

	/*
	//ファイルを開く
	if ((fp = fopen(fileName.c_str(), "rb")) == NULL)
	{
		printf("ファイルを開けませんでした\n");
		return false;
	}
	*/

	//ヘッダー情報の読み込み
	fread(header, 1, sizeof(header), fp);

	//幅と高さを計算
	w = header[13] * 256 + header[12];
	h = header[15] * 256 + header[14];

	//ビットの深さ
	bpp = header[16];
	//1ピクセル当たりのバイト数を決定
	bytePerPixel = bpp / 8;

	//データサイズの決定
	size = w * h * bytePerPixel;

	//メモリを確保
	pData = new GLubyte[size];

	//色データを取得していく
	if ((fread(pData, size, 1, fp)) != 1)
	{
		printf("データの取り出しに失敗\n");
		return false;
	}
	//BGRからRGBに変換
	for (int i=0;i < (int)size;i += bytePerPixel)
	{
		GLuint temp = pData[i];
		pData[i + 0] = pData[i + 2];
		pData[i + 2] = temp;
	}

	//ファイルを閉じる
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

	

	//PNGファイルを開く
	fopen_s(&fp, fileName, "rb");
	if (!fp) {
		fprintf(stderr, "createTextureFromPNGFile: Failed to fopen.");
		return false;
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
		return false;
	}
	
	//インターレースは非対応
	if (interlaceType != PNG_INTERLACE_NONE) {
		fprintf(stderr, "createTextureFromPNGFile: Interlace image is not supprted.");
		return false;
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

	

	this->m_width = width;
	this->m_height = height;
	this->m_bits = data;

	this->m_bpp = depth;
	this->m_format = GL_RGBA;
	this->m_internalFormat = GL_RGBA;

	//後片付け
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
	unsigned char *data; // 生データを保持する
	FILE       *fp = NULL;

	unsigned int width, height;
	int depth, colortype, interlacetype;
	std::string filename = fileName;

	// png画像ファイルのロード
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
	// メモリ領域確保
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
	// テクスチャへの登録
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	*/

	//値を反映
	this->m_width = width;
	this->m_height = height;
	this->m_bits = data;

	this->m_bpp = depth;
	this->m_format = GL_RGBA;
	this->m_internalFormat = GL_RGBA;
	
	
	return true;
}