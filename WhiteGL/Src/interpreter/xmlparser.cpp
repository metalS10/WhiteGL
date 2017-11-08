#include "xmlparser.h"

/**
*文字列中のすべての文字列を指定の文字列に置換する
*@param	original	オリジナルの文字列
*@param	target		置き換えられる文字列
*@param	replacement	置き換える文字列
*/
std::string replace(
	std::string original,
	std::string&& target,
	std::string&& replacement)
{
	std::string::size_type Pos(original.find(target));

	while (Pos != std::string::npos)
	{
		original.replace(Pos, target.length(), replacement);
		Pos = original.find(target, Pos + replacement.length());
	}
	return original;
}

//=======================================
//
//	チェックの式(抽象的な式)
//
//=======================================
class Checker : public Expression
{
protected:
	//チェックした結果
	int m_state;

public:
	virtual ~Checker() {}

	/**
	*チェックの式
	*@param context式を行うための文
	*@return	式で返す値は全てなんの式を実行しているかを
	*			チェックするための列挙となる
	*/
	virtual int interpret(std::string& context, int state) = 0;
	virtual int interpret(std::string&& context, int state)
	{
		return this->interpret(context, state);
	}
};

//=======================================
//
//	取得の式(抽象的な式)
//
//=======================================
class Extraction : public Expression
{
protected:
	//抽出したデータを保存する場所
	XmlReader* m_pReader = NULL;

public:
	Extraction(XmlReader* pReader)
		:m_pReader(pReader) {}

	virtual ~Extraction() {}

};

//=======================================
//
//	特殊記号の式(終端の式)
//
//=======================================
class Delim : public Expression
{
private:
	std::string m_delim;

public:
	Delim(std::string& delim)
		:m_delim(delim) {}
	Delim(std::string&& delim)
		:m_delim(delim) {}

	virtual ~Delim() {}
	int interpret(std::string& context) override
	{
		return (int)context.find(this->m_delim);
	}
};

//=======================================
//	比較の式
//		2つの記号のコンテキスト中の開始位置からの位置を比較
//=======================================
class Comparison : public Expression
{
public:
	//比較結果
	enum class Result : int
	{
		Right = 0,	//右の方が数値が小さい(開始位置に近い)
		Left = 1,	//左の方が数値が小さい
		Equals = 2,	//左右等しい
		None = 3,	//左右存在しない
	};

private:
	Delim m_lDelim;	//左の記号
	Delim m_rDelim;	//右の記号

public:
	Comparison(std::string& lDelim, std::string& rDelim)
		:m_lDelim(lDelim), m_rDelim(rDelim) {}
	Comparison(std::string&& lDelim, std::string&& rDelim)
		:m_lDelim(lDelim), m_rDelim(rDelim) {}

	virtual ~Comparison() {}

	/**
	*@return	比較結果(Comparison::Result)
	*/
	int interpret(std::string& context)override
	{
		int left = this->m_lDelim.interpret(context);
		int right = this->m_rDelim.interpret(context);

		//存在しない
		if (left == std::string::npos && right == std::string::npos)
			return (int)Result::None;

		//左が存在しないので右の方が小さい
		if (left == std::string::npos)
			return (int)Result::Right;

		//右が存在しないので左の方が小さい
		if (right == std::string::npos)
			return (int)Result::Left;

		//左右等しい
		if (left == right)
			return (int)Result::Equals;

		if (left < right)
			return (int)Result::Left;
		return (int)Result::Right;
	}
};

//========================================
//
//チェックノードの式
//
//========================================
class CheckNodeExpression : public Checker
{
public:
	int interpret(std::string& context, int state)override
	{
		this->m_state = state;
		return this->interpret(context);
	}

	/**
	*@return	抽出するデータのXmlNodeを返す
	*/
	int interpret(std::string& context) override
	{
		using Result = Comparison::Result;

		XmlNode node = (XmlNode)this->m_state;

		switch (node)
		{
		case XmlNode::None:
		{
			//開始要素の抽出開始
			node = XmlNode::StartElement;
		}
		break;

		//<tagの要素>
		case XmlNode::StartElement:
		{
			//要素の開始かテキストか・・・

			//<or </を調べる
			Comparison comp("<", "</");

			Result result = (Result)comp.interpret(context);

			switch (result)
			{
			case Result::Left:
				//要素の開始
				node = XmlNode::StartElement;
				break;

			case Result::Equals:
				//テキスト
				node = XmlNode::Text;
				break;

			default:
				//開始要素の後に < も </　も存在しないのはerror
				node = XmlNode::Error;
				break;
			}
		}
		break;

		//</tag>の後
		case XmlNode::EndElement:
		{
			//要素の開始
			//< or </　を調べる
			Comparison comp("<", "</");

			Result result = (Result)comp.interpret(context);

			switch (result)
			{
			case Result::None:
				//開始要素の後に < も </　も存在しなければファイルの終了
				node = XmlNode::Eof;
				break;


			case Result::Left:
				//要素の開始
				node = XmlNode::StartElement;
				break;

			case Result::Equals:
				//テキスト
				node = XmlNode::EndElement;
				break;

			default:
				break;
			}
		}
		break;

		//テキストの後
		case XmlNode::Text:
		{
			//要素の終了
			node = XmlNode::EndElement;
		}
		break;

		default:
			break;
		}
		return (int)node;
	}
};

//=============================================
//
//	属性の状態
//
//=============================================
enum class AttributeState : int
{
	None = -1,	//開始
	Finish = 0,	//終了
	HasAttr = 1,	//属性あり
	Attr = 2,	//属性解析中

	Error = 0,	//エラー
};

//==============================================
//
//	属性部分のチェック
//
//==============================================
class CheckAttributeExpression : public Checker
{
public:
	int interpret(std::string& context, int state) override
	{
		this->m_state = state;
		return this->interpret(context);
	}

	/**
	*@return	1...開始タグの抽出を続ける(属性あり)
	*			0...開始タグの抽出を終了する(属性終了)
	*/
	int interpret(std::string& tag)override
	{
		AttributeState state = (AttributeState)this->m_state;

		switch (state)
		{
			//属性のチェックの初回
		case AttributeState::None:
		{
			//スペースが存在するかどうかをチェック
			Delim space(" ");
			int spPos = space.interpret(tag);

			if (spPos == std::string::npos)
			{
				//スペースが存在する場合は属性しない場合は終了
				state = AttributeState::Finish;
			}
			else
			{
				//スペース存在する場合は属性あり
				state = AttributeState::HasAttr;
			}
		}
		break;

		//開始タグから開始要素名を取り出したら属性を取り出していく
		case AttributeState::HasAttr:
			state = AttributeState::Attr;
			break;

			//属性の存在をチェック
		case AttributeState::Attr:
		{
			Comparison comp("=", "\"");
			if (Comparison::Result::None == (Comparison::Result) comp.interpret(tag))
			{
				//属性を1つ取り出した時点で=も"も存在していなければ終了
				state = AttributeState::Finish;
			}
			else
			{
				//存在していたらまだ属性あり
				state = AttributeState::Attr;
			}
		}
		break;

		default:
			break;
		}
		return (int)state;
	}
};


//==================================================
//
//	属性部分の開始要素名の抽出
//
//==================================================
class StartElementAttributeExtraction : public Extraction
{
public:
	StartElementAttributeExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*開始要素名の取得
	*@param	tag開始要素タグ部分
	*@return 抽出した開始要素名
	*/
	std::string startElementNameExtraction(std::string& tag)
	{
		Delim space(" ");

		//両方存在している場合まずはスペースまでを分離(要素名を取得)
		//本来の要素名を取得
		int spPos = space.interpret(tag);
		std::string name = tag.substr(0, spPos);

		//tagからnameを分離
		tag.replace(tag.find(name, tag.find(name)), name.length(), "");

		return name;
	}

	int interpret(std::string& tag)override
	{
		//開始要素名の抽出
		std::string name = this->startElementNameExtraction(tag);

		//抽出した開始要素名を設定
		this->m_pReader->setName(name);

		return true;
	}
};


//=================================================
//
//	属性部分のキーと値を抽出
//		キーと値を分離すると設定で処理が増えてしまうので
//		クラスとしては1つにしておき
//		クラス内部で分離しておく
//
//=================================================
class KeyAndValueAttributeExtraction : public Extraction
{
public:
	KeyAndValueAttributeExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*キーの抽出
	*@param	tag開始要素タグ部分
	*@return 抽出したキー
	*/
	std::string keyExtraction(std::string& tag)
	{
		Delim equal("=");

		//イコールの位置を再計算
		int eqPos = equal.interpret(tag);

		//次の属性名を調べる(=(イコール)までのスペースを取り除く)
		std::string key = tag.substr(0, eqPos);

		//属性キーに含まれるスペースをすべて取り除く
		key = replace(key, " ", "");

		//属性キーまでを分離
		tag.replace(0, eqPos + 1, "");

		return key;
	}

	/**
	*値の抽出
	*@param	tag 開始要素タグ部分
	*@return 抽出した値
	*/
	std::string	valueExtraction(std::string& tag)
	{
		Delim dq("\"");

		//"(ダブルクォーテーション)の位置を取得
		int dqPos = dq.interpret(tag);

		//ダブルクォーテーションまでを削除
		tag.replace(0, dqPos + 1, "");

		//"(ダブルクォーテーション)の位置を再計算
		dqPos = dq.interpret(tag);

		//ダブルクォーテーションまでを抽出( 属性値の取得 )
		std::string value = tag.substr(0, dqPos);

		//ダブルクォーテーションまでを削除
		tag.replace(0, dqPos + 1, "");

		return value;
	}

	int interpret(std::string& tag)override
	{
		//キーの抽出
		std::string key = this->keyExtraction(tag);

		//値の抽出
		std::string value = this->valueExtraction(tag);

		//抽出したキーと値を設定
		this->m_pReader->addAttribute(key, value);


		return true;
	}
};

//=======================================
//
//	属性部分の抽出
//
//=======================================
class AttributeExtrantion : public Extraction
{
private:
	//開始タグ部分の解析の属性の状態
	AttributeState m_state = AttributeState::None;

public:
	AttributeExtrantion(XmlReader* pReader, AttributeState state)
		:Extraction(pReader), m_state(state) {}

	/**
	*解析属性状態別のExtractionを取得
	*@param	state 解析属性状態
	*@return Extraction
	*/
	Extraction* getExtraction(AttributeState state)
	{
		Extraction* pExt = NULL;

		switch (state)
		{
			//属性が存在する場合はスペースまでの開始余殃疎明を取得し設定
		case AttributeState::HasAttr:
		{
			pExt = new StartElementAttributeExtraction(this->m_pReader);
		}
		break;

		//その後、属性のキーと値を取得していく
		case AttributeState::Attr:
		{
			pExt = new KeyAndValueAttributeExtraction(this->m_pReader);
		}
		break;

		default:
			//属性が存在しない場合は何もしない
			break;
		}
		return pExt;
	}
	int interpret(std::string& tag)override
	{
		Extraction* pExt = this->getExtraction(this->m_state);
		if (pExt != NULL)
		{
			pExt->interpret(tag);
			SAFE_DELETE(pExt);
		}

		return true;
	}
};

//===========================================
//
//	開始要素抽出
//
//===========================================
class StartElementExtraction : public Extraction
{
public:
	StartElementExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*開始要素名の取得
	*@param	context	コンテキスト
	*@return 抽出した開始要素名
	*/
	std::string startElementNameExtraction(std::string& context)
	{
		// <の位置を計算
		Delim start("<");
		int pos = start.interpret(context);

		// <までを削除
		context.replace(0, pos + 1, "");

		//>の位置を計算
		Delim end(">");
		pos = end.interpret(context);

		//>の1つ前までを抽出
		std::string name = context.substr(0, pos);

		//>までを削除
		context.replace(0, pos + 1, "");

		return name;
	}

	int interpret(std::string& context)override
	{
		//開始要素名の取得
		std::string name = this->startElementNameExtraction(context);

		//抽出した開始要素名を設定
		this->m_pReader->setName(name);

		//=========================================
		//	属性が存在するかどうかを調べて
		//	存在した場合は属性の抽出に移行
		//=========================================
		//開始要素名を開始タグとして取得しなおす
		std::string tag = this->m_pReader->getName();

		//存在する属性の数だけ繰り返す
		AttributeState type = AttributeState::None;
		do
		{
			//属性部分のチェック
			CheckAttributeExpression attrExp;
			type = (AttributeState)attrExp.interpret(tag, (int)type);

			//属性部分の抽出
			AttributeExtrantion attrExt(this->m_pReader, type);
			attrExt.interpret(tag);
		} while ((bool)type == true);

		return true;
	}
};

//=========================================
//
//	終了要素抽出
//
//=========================================
class EndElementExtraction : public Extraction
{
public:
	EndElementExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	int interpret(std::string& context) override
	{
		// <の位置を計算
		Delim start("</");
		int pos = start.interpret(context);

		// <までを削除
		context.replace(0, pos + 1, "");

		//>の位置を計算
		Delim end(">");
		pos = end.interpret(context);

		//>の1つ前までを抽出
		//現状抽出したtagは使用しない
		std::string tag = context.substr(0, pos);

		//Debug
		//std;;cout << "end element : " << tag << std::endl;

		//>までを削除
		context.replace(0, pos + 1, "");

		return true;
	}
};


//=========================================
//
//	テキスト抽出
//
//=========================================
class TextExtraction : public Extraction
{
public:
	TextExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*テキストの取得
	*@param	context コンテキスト
	*@return 抽出したテキスト
	*/
	std::string textExtraction(std::string& context)
	{
		// <の位置を計算
		Delim start("<");
		int pos = start.interpret(context);



		//>の1つ前までを抽出
		//現状抽出したtagは使用しない
		std::string text = context.substr(0, pos);

		//>の1つ前までを削除
		context.replace(0, pos, "");

		return text;
	}

	int interpret(std::string& context)override
	{
		//テキストの抽出
		std::string text = this->textExtraction(context);

		//抽出したテキストを設定
		this->m_pReader->setText(text);

		return true;
	}
};

//========================================
//
//	値の抽出の式
//
//========================================
class DataExtractionExpression : public Extraction
{
public:
	DataExtractionExpression(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*ノードタイプ別のExtractionを取得
	*@param	node ノードタイプ
	*@return Extraction
	*/
	Extraction* getExtraction(XmlNode node)
	{
		Extraction* pExt = NULL;

		switch (node)
		{
		case XmlNode::StartElement:
		{
			//開始タグの抽出
			pExt = new StartElementExtraction(this->m_pReader);
		}
		break;

		case XmlNode::EndElement:
		{
			//終了タグの抽出
			pExt = new EndElementExtraction(this->m_pReader);
		}
		break;

		case XmlNode::Text:
		{
			//テキストの抽出
			pExt = new TextExtraction(this->m_pReader);
		}
		break;

		default:
			break;
		}
		return pExt;
	}
	int interpret(std::string& context)override
	{
		Extraction* pExt = this->getExtraction(this->m_pReader->getNode());
		if (pExt != NULL)
		{
			pExt->interpret(context);
			SAFE_DELETE(pExt);
		}
		return true;
	}
};

//======================================
//
//	XMLリーダー
//
//======================================
XmlReader::XmlReader()
{

}

XmlReader::~XmlReader()
{

}

/**
*XMLコンテキストの作成
*@param filePath ファイルパス
*@return true...成功 false...失敗
*/
bool XmlReader::create(const std::string& filePath)
{
	//ファイルオープン
	std::ifstream ifs(filePath);
	if (ifs.fail())
	{
		std::cout << "file stream is failed !!!" << std::endl;
		return false;
	}

	//読み込み
	std::string str;
	while (getline(ifs, str))
		this->m_context += str;

	return true;
}

/**
*読み込み
*@return true...読み込み継続 false...読み込み終了(errorの場合も終了)
*/
int XmlReader::read()
{
	//属性群の初期化
	this->m_attrs.clear();

	//ノードのチェック
	CheckNodeExpression checkExp;
	XmlNode node = (XmlNode)checkExp.interpret(this->m_context, (int)this->getNode());

	//現在参照中のノードを設定
	this->setNode(node);

	//データの取得
	DataExtractionExpression extExp(this);
	if (extExp.interpret(this->m_context) == false)
		return false;

	return (int)this->m_node;
}