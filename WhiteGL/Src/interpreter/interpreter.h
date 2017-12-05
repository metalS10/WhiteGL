#pragma once
#include "xmlparser.h"
#include "Element.h"
#include "../Constants.h"

class LoadXml
{
private:
	//要素名
	std::string element;
	//属性名
	std::string elementName;
	//属性値
	int elementValue;

	//読み込みレイヤー数
	int m_layerNumber = 0;

public:

	//要素データ
	std::vector<CElement> elementData;
	std::vector<char> m_elementName;
	float m_width = 0.0f;
	float m_height = 0.0f;
	CLayerData m_layerData[MAX_LAYER_NUMBER] = {};

	LoadXml(const char* fileName)
	{
		loadFile(fileName);
	}

	void loadFile(const char* fileName)
	{
		//XMLリーダーの生成
		XmlReader* pReader = new XmlReader();

		//ファイルを読み込みコンテキストを作成
		if (pReader->create(fileName) == false)
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

				//std::cout << "要素名 = " << name << std::endl;

				//属性が存在した場合は属性を取得
				for (auto attr : pReader->getAttributes())
				{
					//属性の名前を取得
					std::string attrKey = attr.getKey();

					//属性の値を取得
					std::string attrValue = attr.getValue();
					if (std::atoi(attrValue.c_str()) || attrValue == "0")
					{
						int valuenumber = std::stoi(attrValue);
						//std::cout << "属性名 = " << attrKey << std::endl;
						//std::cout << "属性値 = " << valuenumber << std::endl;
						elementData.push_back(CElement(attrKey, valuenumber));
					}
					else
					{
						//std::cout << "属性名 = " << attrKey << std::endl;
						//std::cout << "属性値 = " << attrValue << std::endl;
					}

					if (name == "tile")
					{
						if (attrKey == "gid")
							for (CLayerData& layer : m_layerData)
								if (!layer.m_gidcomp)
								{
									layer.addgid(m_width, m_height, std::stoi(attrValue));
									break;
								}
					}
					//レイヤーのセット
					if (name == "tileset" || name == "image")
					{
						this->setLayerData(attrKey, attrValue);
					}

					if (name == "map")
					{
						if (attrKey == "width")
						{
							m_width = std::stof(attrValue);
						}
						else if (attrKey == "height")
						{
							m_height = std::stof(attrValue);
						}
					}
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

				//std::cout << "テキスト = " << text << std::endl;
			}
			break;

			default:
				break;
			}
		}
		SAFE_DELETE(pReader);

	}

	void setLayerData(std::string attrKey,std::string attrValue)
	{
		if (attrKey == "firstgid")
		{
			for (CLayerData& layer : m_layerData)
			{
				if (!layer.m_datacomp)
				{
					layer.m_firstgid = std::stoi(attrValue);
					break;
				}
			}
		}
		else if (attrKey == "name")
		{
			for (CLayerData& layer : m_layerData)
			{
				if (!layer.m_datacomp)
				{
					layer.m_mapChip = attrValue;
					break;
				}
			}
		}
		else if (attrKey == "tilewidth")
		{
			for (CLayerData& layer : m_layerData)
			{
				if (!layer.m_datacomp)
				{
					layer.m_tileWidth = std::stof(attrValue);
					break;
				}
			}
		}
		else if (attrKey == "tileheight")
		{
			for (CLayerData& layer : m_layerData)
			{
				if (!layer.m_datacomp)
				{
					layer.m_tileHeight = std::stof(attrValue);
					break;
				}
			}
		}
		else if (attrKey == "tilecount")
		{
			for (CLayerData& layer : m_layerData)
			{
				if (!layer.m_datacomp)
				{
					layer.m_tilecount = std::stoi(attrValue);
					break;
				}
			}
		}
		else if (attrKey == "columns")
		{
			for (CLayerData& layer : m_layerData)
			{
				if (!layer.m_datacomp)
				{
					layer.m_columns = std::stoi(attrValue);
					break;
				}
			}
		}
		else if (attrKey == "source")
		{
			for (CLayerData& layer : m_layerData)
			{
				if (!layer.m_datacomp)
				{
					layer.m_imageSource = MAP_PASS + attrValue;
					break;
				}
			}
		}
		else if (attrKey == "width")
		{
			for (CLayerData& layer : m_layerData)
			{
				if (!layer.m_datacomp)
				{
					layer.m_imagewidth = std::stoi(attrValue);
					break;
				}
			}
		}
		else if (attrKey == "height")
		{
			for (CLayerData& layer : m_layerData)
			{
				if (!layer.m_datacomp)
				{
					layer.m_imageheight = std::stoi(attrValue);
					layer.m_datacomp = true;
					break;
				}
			}
		}
	}
	/*
	inline const Size& getTileSize() const 
	{
		return Size(this->m_layerData[0].m_tileWidth, this->m_layerData[0].m_tileHeight);
	}

	inline const Size& getMapSize() const
	{
		return Size(this->m_width, this->m_height);
	}

	inline const CVec2& getPosition() const
	{
		return CVec2(0.0f, 0.0f);
	}
	*/
};