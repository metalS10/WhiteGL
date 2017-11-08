#pragma once
#include "xmlparser.h"
#include "../Constants.h"

class LoadXml
{
public:
	int loadFile( /*int argc, const char* argv[]*/)
	{
		//XML���[�_�[�̐���
		XmlReader* pReader = new XmlReader();

		//�t�@�C����ǂݍ��݃R���e�L�X�g���쐬
		if (pReader->create(MAP_DATA_1) == false)
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

				std::cout << "�v�f�� = " << name << std::endl;

				//���������݂����ꍇ�͑������擾
				for (auto attr : pReader->getAttributes())
				{
					//�����̖��O���擾
					std::string attrKey = attr.getKey();

					//�����̒l���擾
					std::string attrValue = attr.getValue();

					std::cout << "������ = " << attrKey << std::endl;
					std::cout << "�����l = " << attrValue << std::endl;
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

				std::cout << "�e�L�X�g = " << text << std::endl;
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