#include "Texture.h"
#include <vector>

/**
* @desc	テクスチャの生成
* @param	fileName ファイル名
* @return	true...成功
*/
bool CTexture2D::create(const std::string & fileName)
{
	//文字列の分割(分割する文字列、分割する区切り文字)
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

	//識別子を取得
	std::vector<std::string>result = split(fileName, ".");
	std::string end = result[result.size() - 1];

	//BMPの生成
	if (end == "bmp" || end == "BMP")
	{
		this->m_pImage = new CBmpImage();
	}
	//TGAの生成
	else if (end == "tga" || end == "TGA")
	{
		this->m_pImage = new CTgaImage();
	}
	else
	{
		//対応していない
		printf("解析できないタイプの画像ファイルです。\n");
		return false;
	}

	//画像ファイルの読み込み
	if (this->m_pImage->load(fileName) == false)
	{
		printf("ファイルの読み込みに失敗\n");
		SAFE_DELETE(this->m_pImage);
		return false;
	}

	//テクスチャ2Dの使用許可
	glEnable(GL_TEXTURE_2D);
	//テクスチャ名を生成し取得
	glGenTextures(1, &this->m_texName);
	//取得したテクスチャ名をスタックに登録
	glBindTexture(GL_TEXTURE_2D, this->m_texName);

	//テクスチャ画像がメモリにどのように格納されているかをPCに設定する
	if (this->m_pImage->m_bpp == 24)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	}
	else if (this->m_pImage->m_bpp == 32)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}

	//ピクセル情報をスタックの一番上にあるテクスチャ名に対してテクスチャとして登録
	glTexImage2D(
		GL_TEXTURE_2D, 0, this->m_pImage->m_internalFormat, this->m_pImage->m_width, this->m_pImage->m_height,
		0, this->m_pImage->m_format, GL_UNSIGNED_BYTE, m_pImage->m_bits
	);

	//テクスチャの拡大・縮小方法の設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//テクスチャの繰り返しの指定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/*テクスチャの境界色*/
	//static const GLfloat border[] = { 1.0,1.0,1.0,1.0 };

	/*テクスチャの境界色*/
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	
	//設定するテクスチャを解除する
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

/**
* @desc	テクスチャの破棄
*/
void CTexture2D::remove()
{
	//画像データの開放
	SAFE_DELETE(this->m_pImage);

	//テクスチャ名の登録解除
	glDeleteTextures(1, &this->m_texName);
}

//============================================================
//
//複数のテクスチャを管理するクラス
//
//============================================================
//コンストラクタ
CTextureManager::CTextureManager()
{}

//get instance
CTextureManager* CTextureManager::getInstance()
{
	static CTextureManager instance;
	return &instance;
}

//デストラクタ
CTextureManager::~CTextureManager()
{
	this->clear();
}

/**
*@desc	テクスチャの取得
*@param fileNameファイル名
*@return テクスチャ
*@tips	存在していなければ生成して返す
*/
CTexture2D* CTextureManager::get(const std::string & fileName)
{
	CTexture2D* pTex = NULL;

	//既に生成されているかどうかを調べる
	std::map<std::string, CTexture2D*>::iterator itr = this->m_textures.find(fileName);
	if (itr == this -> m_textures.end())
	{
		//存在していなければテクスチャを生成
		pTex = new CTexture2D();

		if (pTex->create(fileName) == false)
		{
			printf("テクスチャの生成に失敗\n");
			return NULL;
		}
		//テクスチャ群に取り付ける
		this->m_textures[fileName] = pTex;
	}
	else
	{
		//存在していなければ存在しているテクスチャを渡す
		pTex = itr->second;	//secondは同じものを返す
	}
	return pTex;
}

/**
*@desc	テクスチャの削除
*@param	fileNameファイル名
*/
void CTextureManager::remove(const std::string&fileName)
{
	std::map<std::string, CTexture2D*>::iterator itr = this->m_textures.find(fileName);

	if (itr != this->m_textures.end())
	{
		//テクスチャを開放
		SAFE_DELETE(itr->second);

		//イテレータを削除
		this->m_textures.erase(fileName);
	}
}

/**
*@desc	全てのテクスチャの削除
*/
void CTextureManager::clear()
{
	//全てのテクスチャを解放
	std::map<std::string, CTexture2D*>::iterator itr = this->m_textures.begin();

	while (itr != this->m_textures.end())
	{
		SAFE_DELETE(itr->second);
	}

	//全てのイテレータを削除
	this->m_textures.clear();

	//キャパシティをクリア
	std::map < std::string, CTexture2D*>().swap(this->m_textures);
}