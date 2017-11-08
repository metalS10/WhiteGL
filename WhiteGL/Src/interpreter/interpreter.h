#pragma once
#include "xmlparser.h"
#include "../Constants.h"

class LoadXml
{
public:
	int loadFile( /*int argc, const char* argv[]*/)
	{
		//XMLリーダーの生成
		XmlReader* pReader = new XmlReader();

		//ファイルを読み込みコンテキストを作成
		if (pReader->create(MAP_DATA_1) == false)
		{
			std::cout << "xml create is false !!!" << std::endl;
		}

		//次のノードまでを読み込み
		while (pReader->read())
		{
			//ノードの種類を取得
			switch (pReader->getNode())
			{
				//開始要素
			case XmlNode::StartElement:
			{
				//要素の名前を取得
				std::string name = pReader->getName();

				std::cout << "要素名 = " << name << std::endl;

				//属性が存在した場合は属性を取得
				for (auto attr : pReader->getAttributes())
				{
					//属性の名前を取得
					std::string attrKey = attr.getKey();

					//属性の値を取得
					std::string attrValue = attr.getValue();

					std::cout << "属性名 = " << attrKey << std::endl;
					std::cout << "属性値 = " << attrValue << std::endl;
				}
			}
			break;

			//終了要素
			case XmlNode::EndElement:
				break;

				//テキスト
			case XmlNode::Text:
			{
				std::string text = pReader->getText();

				std::cout << "テキスト = " << text << std::endl;
			}
			break;

			default:
				break;
			}
		}
		SAFE_DELETE(pReader);

		return 0;
	}
};