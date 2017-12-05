#pragma once
#include "xmlparser.h"
#include "Element.h"
#include "../Constants.h"

class LoadXml
{
private:
	//�v�f��
	std::string element;
	//������
	std::string elementName;
	//�����l
	int elementValue;

	//�ǂݍ��݃��C���[��
	int m_layerNumber = 0;

public:

	//�v�f�f�[�^
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
		//XML���[�_�[�̐���
		XmlReader* pReader = new XmlReader();

		//�t�@�C����ǂݍ��݃R���e�L�X�g���쐬
		if (pReader->create(fileName) == false)
		{
			std::cout << "xml create is false !!!" << std::endl;
		}

		//���̃m�[�h�܂ł�ǂݍ���
		while (pReader->read())
		{
			//�m�[�h�̎�ނ��擾
			switch (pReader->getNode())
			{
				//�J�n�v�f
			case XmlNode::StartElement:
			{
				//�v�f�̖��O���擾
				std::string name = pReader->getName();

				//std::cout << "�v�f�� = " << name << std::endl;

				//���������݂����ꍇ�͑������擾
				for (auto attr : pReader->getAttributes())
				{
					//�����̖��O���擾
					std::string attrKey = attr.getKey();

					//�����̒l���擾
					std::string attrValue = attr.getValue();
					if (std::atoi(attrValue.c_str()) || attrValue == "0")
					{
						int valuenumber = std::stoi(attrValue);
						//std::cout << "������ = " << attrKey << std::endl;
						//std::cout << "�����l = " << valuenumber << std::endl;
						elementData.push_back(CElement(attrKey, valuenumber));
					}
					else
					{
						//std::cout << "������ = " << attrKey << std::endl;
						//std::cout << "�����l = " << attrValue << std::endl;
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
					//���C���[�̃Z�b�g
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

			//�I���v�f
			case XmlNode::EndElement:
				break;

				//�e�L�X�g
			case XmlNode::Text:
			{
				std::string text = pReader->getText();

				//std::cout << "�e�L�X�g = " << text << std::endl;
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