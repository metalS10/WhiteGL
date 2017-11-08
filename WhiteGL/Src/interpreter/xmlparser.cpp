#include "xmlparser.h"

/**
*�����񒆂̂��ׂĂ̕�������w��̕�����ɒu������
*@param	original	�I���W�i���̕�����
*@param	target		�u���������镶����
*@param	replacement	�u�������镶����
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
//	�`�F�b�N�̎�(���ۓI�Ȏ�)
//
//=======================================
class Checker : public Expression
{
protected:
	//�`�F�b�N��������
	int m_state;

public:
	virtual ~Checker() {}

	/**
	*�`�F�b�N�̎�
	*@param context�����s�����߂̕�
	*@return	���ŕԂ��l�͑S�ĂȂ�̎������s���Ă��邩��
	*			�`�F�b�N���邽�߂̗񋓂ƂȂ�
	*/
	virtual int interpret(std::string& context, int state) = 0;
	virtual int interpret(std::string&& context, int state)
	{
		return this->interpret(context, state);
	}
};

//=======================================
//
//	�擾�̎�(���ۓI�Ȏ�)
//
//=======================================
class Extraction : public Expression
{
protected:
	//���o�����f�[�^��ۑ�����ꏊ
	XmlReader* m_pReader = NULL;

public:
	Extraction(XmlReader* pReader)
		:m_pReader(pReader) {}

	virtual ~Extraction() {}

};

//=======================================
//
//	����L���̎�(�I�[�̎�)
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
//	��r�̎�
//		2�̋L���̃R���e�L�X�g���̊J�n�ʒu����̈ʒu���r
//=======================================
class Comparison : public Expression
{
public:
	//��r����
	enum class Result : int
	{
		Right = 0,	//�E�̕������l��������(�J�n�ʒu�ɋ߂�)
		Left = 1,	//���̕������l��������
		Equals = 2,	//���E������
		None = 3,	//���E���݂��Ȃ�
	};

private:
	Delim m_lDelim;	//���̋L��
	Delim m_rDelim;	//�E�̋L��

public:
	Comparison(std::string& lDelim, std::string& rDelim)
		:m_lDelim(lDelim), m_rDelim(rDelim) {}
	Comparison(std::string&& lDelim, std::string&& rDelim)
		:m_lDelim(lDelim), m_rDelim(rDelim) {}

	virtual ~Comparison() {}

	/**
	*@return	��r����(Comparison::Result)
	*/
	int interpret(std::string& context)override
	{
		int left = this->m_lDelim.interpret(context);
		int right = this->m_rDelim.interpret(context);

		//���݂��Ȃ�
		if (left == std::string::npos && right == std::string::npos)
			return (int)Result::None;

		//�������݂��Ȃ��̂ŉE�̕���������
		if (left == std::string::npos)
			return (int)Result::Right;

		//�E�����݂��Ȃ��̂ō��̕���������
		if (right == std::string::npos)
			return (int)Result::Left;

		//���E������
		if (left == right)
			return (int)Result::Equals;

		if (left < right)
			return (int)Result::Left;
		return (int)Result::Right;
	}
};

//========================================
//
//�`�F�b�N�m�[�h�̎�
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
	*@return	���o����f�[�^��XmlNode��Ԃ�
	*/
	int interpret(std::string& context) override
	{
		using Result = Comparison::Result;

		XmlNode node = (XmlNode)this->m_state;

		switch (node)
		{
		case XmlNode::None:
		{
			//�J�n�v�f�̒��o�J�n
			node = XmlNode::StartElement;
		}
		break;

		//<tag�̗v�f>
		case XmlNode::StartElement:
		{
			//�v�f�̊J�n���e�L�X�g���E�E�E

			//<or </�𒲂ׂ�
			Comparison comp("<", "</");

			Result result = (Result)comp.interpret(context);

			switch (result)
			{
			case Result::Left:
				//�v�f�̊J�n
				node = XmlNode::StartElement;
				break;

			case Result::Equals:
				//�e�L�X�g
				node = XmlNode::Text;
				break;

			default:
				//�J�n�v�f�̌�� < �� </�@�����݂��Ȃ��̂�error
				node = XmlNode::Error;
				break;
			}
		}
		break;

		//</tag>�̌�
		case XmlNode::EndElement:
		{
			//�v�f�̊J�n
			//< or </�@�𒲂ׂ�
			Comparison comp("<", "</");

			Result result = (Result)comp.interpret(context);

			switch (result)
			{
			case Result::None:
				//�J�n�v�f�̌�� < �� </�@�����݂��Ȃ���΃t�@�C���̏I��
				node = XmlNode::Eof;
				break;


			case Result::Left:
				//�v�f�̊J�n
				node = XmlNode::StartElement;
				break;

			case Result::Equals:
				//�e�L�X�g
				node = XmlNode::EndElement;
				break;

			default:
				break;
			}
		}
		break;

		//�e�L�X�g�̌�
		case XmlNode::Text:
		{
			//�v�f�̏I��
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
//	�����̏��
//
//=============================================
enum class AttributeState : int
{
	None = -1,	//�J�n
	Finish = 0,	//�I��
	HasAttr = 1,	//��������
	Attr = 2,	//������͒�

	Error = 0,	//�G���[
};

//==============================================
//
//	���������̃`�F�b�N
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
	*@return	1...�J�n�^�O�̒��o�𑱂���(��������)
	*			0...�J�n�^�O�̒��o���I������(�����I��)
	*/
	int interpret(std::string& tag)override
	{
		AttributeState state = (AttributeState)this->m_state;

		switch (state)
		{
			//�����̃`�F�b�N�̏���
		case AttributeState::None:
		{
			//�X�y�[�X�����݂��邩�ǂ������`�F�b�N
			Delim space(" ");
			int spPos = space.interpret(tag);

			if (spPos == std::string::npos)
			{
				//�X�y�[�X�����݂���ꍇ�͑������Ȃ��ꍇ�͏I��
				state = AttributeState::Finish;
			}
			else
			{
				//�X�y�[�X���݂���ꍇ�͑�������
				state = AttributeState::HasAttr;
			}
		}
		break;

		//�J�n�^�O����J�n�v�f�������o�����瑮�������o���Ă���
		case AttributeState::HasAttr:
			state = AttributeState::Attr;
			break;

			//�����̑��݂��`�F�b�N
		case AttributeState::Attr:
		{
			Comparison comp("=", "\"");
			if (Comparison::Result::None == (Comparison::Result) comp.interpret(tag))
			{
				//������1���o�������_��=��"�����݂��Ă��Ȃ���ΏI��
				state = AttributeState::Finish;
			}
			else
			{
				//���݂��Ă�����܂���������
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
//	���������̊J�n�v�f���̒��o
//
//==================================================
class StartElementAttributeExtraction : public Extraction
{
public:
	StartElementAttributeExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*�J�n�v�f���̎擾
	*@param	tag�J�n�v�f�^�O����
	*@return ���o�����J�n�v�f��
	*/
	std::string startElementNameExtraction(std::string& tag)
	{
		Delim space(" ");

		//�������݂��Ă���ꍇ�܂��̓X�y�[�X�܂ł𕪗�(�v�f�����擾)
		//�{���̗v�f�����擾
		int spPos = space.interpret(tag);
		std::string name = tag.substr(0, spPos);

		//tag����name�𕪗�
		tag.replace(tag.find(name, tag.find(name)), name.length(), "");

		return name;
	}

	int interpret(std::string& tag)override
	{
		//�J�n�v�f���̒��o
		std::string name = this->startElementNameExtraction(tag);

		//���o�����J�n�v�f����ݒ�
		this->m_pReader->setName(name);

		return true;
	}
};


//=================================================
//
//	���������̃L�[�ƒl�𒊏o
//		�L�[�ƒl�𕪗�����Ɛݒ�ŏ����������Ă��܂��̂�
//		�N���X�Ƃ��Ă�1�ɂ��Ă���
//		�N���X�����ŕ������Ă���
//
//=================================================
class KeyAndValueAttributeExtraction : public Extraction
{
public:
	KeyAndValueAttributeExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*�L�[�̒��o
	*@param	tag�J�n�v�f�^�O����
	*@return ���o�����L�[
	*/
	std::string keyExtraction(std::string& tag)
	{
		Delim equal("=");

		//�C�R�[���̈ʒu���Čv�Z
		int eqPos = equal.interpret(tag);

		//���̑������𒲂ׂ�(=(�C�R�[��)�܂ł̃X�y�[�X����菜��)
		std::string key = tag.substr(0, eqPos);

		//�����L�[�Ɋ܂܂��X�y�[�X�����ׂĎ�菜��
		key = replace(key, " ", "");

		//�����L�[�܂ł𕪗�
		tag.replace(0, eqPos + 1, "");

		return key;
	}

	/**
	*�l�̒��o
	*@param	tag �J�n�v�f�^�O����
	*@return ���o�����l
	*/
	std::string	valueExtraction(std::string& tag)
	{
		Delim dq("\"");

		//"(�_�u���N�H�[�e�[�V����)�̈ʒu���擾
		int dqPos = dq.interpret(tag);

		//�_�u���N�H�[�e�[�V�����܂ł��폜
		tag.replace(0, dqPos + 1, "");

		//"(�_�u���N�H�[�e�[�V����)�̈ʒu���Čv�Z
		dqPos = dq.interpret(tag);

		//�_�u���N�H�[�e�[�V�����܂ł𒊏o( �����l�̎擾 )
		std::string value = tag.substr(0, dqPos);

		//�_�u���N�H�[�e�[�V�����܂ł��폜
		tag.replace(0, dqPos + 1, "");

		return value;
	}

	int interpret(std::string& tag)override
	{
		//�L�[�̒��o
		std::string key = this->keyExtraction(tag);

		//�l�̒��o
		std::string value = this->valueExtraction(tag);

		//���o�����L�[�ƒl��ݒ�
		this->m_pReader->addAttribute(key, value);


		return true;
	}
};

//=======================================
//
//	���������̒��o
//
//=======================================
class AttributeExtrantion : public Extraction
{
private:
	//�J�n�^�O�����̉�͂̑����̏��
	AttributeState m_state = AttributeState::None;

public:
	AttributeExtrantion(XmlReader* pReader, AttributeState state)
		:Extraction(pReader), m_state(state) {}

	/**
	*��͑�����ԕʂ�Extraction���擾
	*@param	state ��͑������
	*@return Extraction
	*/
	Extraction* getExtraction(AttributeState state)
	{
		Extraction* pExt = NULL;

		switch (state)
		{
			//���������݂���ꍇ�̓X�y�[�X�܂ł̊J�n�]�i�a�����擾���ݒ�
		case AttributeState::HasAttr:
		{
			pExt = new StartElementAttributeExtraction(this->m_pReader);
		}
		break;

		//���̌�A�����̃L�[�ƒl���擾���Ă���
		case AttributeState::Attr:
		{
			pExt = new KeyAndValueAttributeExtraction(this->m_pReader);
		}
		break;

		default:
			//���������݂��Ȃ��ꍇ�͉������Ȃ�
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
//	�J�n�v�f���o
//
//===========================================
class StartElementExtraction : public Extraction
{
public:
	StartElementExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*�J�n�v�f���̎擾
	*@param	context	�R���e�L�X�g
	*@return ���o�����J�n�v�f��
	*/
	std::string startElementNameExtraction(std::string& context)
	{
		// <�̈ʒu���v�Z
		Delim start("<");
		int pos = start.interpret(context);

		// <�܂ł��폜
		context.replace(0, pos + 1, "");

		//>�̈ʒu���v�Z
		Delim end(">");
		pos = end.interpret(context);

		//>��1�O�܂ł𒊏o
		std::string name = context.substr(0, pos);

		//>�܂ł��폜
		context.replace(0, pos + 1, "");

		return name;
	}

	int interpret(std::string& context)override
	{
		//�J�n�v�f���̎擾
		std::string name = this->startElementNameExtraction(context);

		//���o�����J�n�v�f����ݒ�
		this->m_pReader->setName(name);

		//=========================================
		//	���������݂��邩�ǂ����𒲂ׂ�
		//	���݂����ꍇ�͑����̒��o�Ɉڍs
		//=========================================
		//�J�n�v�f�����J�n�^�O�Ƃ��Ď擾���Ȃ���
		std::string tag = this->m_pReader->getName();

		//���݂��鑮���̐������J��Ԃ�
		AttributeState type = AttributeState::None;
		do
		{
			//���������̃`�F�b�N
			CheckAttributeExpression attrExp;
			type = (AttributeState)attrExp.interpret(tag, (int)type);

			//���������̒��o
			AttributeExtrantion attrExt(this->m_pReader, type);
			attrExt.interpret(tag);
		} while ((bool)type == true);

		return true;
	}
};

//=========================================
//
//	�I���v�f���o
//
//=========================================
class EndElementExtraction : public Extraction
{
public:
	EndElementExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	int interpret(std::string& context) override
	{
		// <�̈ʒu���v�Z
		Delim start("</");
		int pos = start.interpret(context);

		// <�܂ł��폜
		context.replace(0, pos + 1, "");

		//>�̈ʒu���v�Z
		Delim end(">");
		pos = end.interpret(context);

		//>��1�O�܂ł𒊏o
		//���󒊏o����tag�͎g�p���Ȃ�
		std::string tag = context.substr(0, pos);

		//Debug
		//std;;cout << "end element : " << tag << std::endl;

		//>�܂ł��폜
		context.replace(0, pos + 1, "");

		return true;
	}
};


//=========================================
//
//	�e�L�X�g���o
//
//=========================================
class TextExtraction : public Extraction
{
public:
	TextExtraction(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*�e�L�X�g�̎擾
	*@param	context �R���e�L�X�g
	*@return ���o�����e�L�X�g
	*/
	std::string textExtraction(std::string& context)
	{
		// <�̈ʒu���v�Z
		Delim start("<");
		int pos = start.interpret(context);



		//>��1�O�܂ł𒊏o
		//���󒊏o����tag�͎g�p���Ȃ�
		std::string text = context.substr(0, pos);

		//>��1�O�܂ł��폜
		context.replace(0, pos, "");

		return text;
	}

	int interpret(std::string& context)override
	{
		//�e�L�X�g�̒��o
		std::string text = this->textExtraction(context);

		//���o�����e�L�X�g��ݒ�
		this->m_pReader->setText(text);

		return true;
	}
};

//========================================
//
//	�l�̒��o�̎�
//
//========================================
class DataExtractionExpression : public Extraction
{
public:
	DataExtractionExpression(XmlReader* pReader)
		:Extraction(pReader) {}

	/**
	*�m�[�h�^�C�v�ʂ�Extraction���擾
	*@param	node �m�[�h�^�C�v
	*@return Extraction
	*/
	Extraction* getExtraction(XmlNode node)
	{
		Extraction* pExt = NULL;

		switch (node)
		{
		case XmlNode::StartElement:
		{
			//�J�n�^�O�̒��o
			pExt = new StartElementExtraction(this->m_pReader);
		}
		break;

		case XmlNode::EndElement:
		{
			//�I���^�O�̒��o
			pExt = new EndElementExtraction(this->m_pReader);
		}
		break;

		case XmlNode::Text:
		{
			//�e�L�X�g�̒��o
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
//	XML���[�_�[
//
//======================================
XmlReader::XmlReader()
{

}

XmlReader::~XmlReader()
{

}

/**
*XML�R���e�L�X�g�̍쐬
*@param filePath �t�@�C���p�X
*@return true...���� false...���s
*/
bool XmlReader::create(const std::string& filePath)
{
	//�t�@�C���I�[�v��
	std::ifstream ifs(filePath);
	if (ifs.fail())
	{
		std::cout << "file stream is failed !!!" << std::endl;
		return false;
	}

	//�ǂݍ���
	std::string str;
	while (getline(ifs, str))
		this->m_context += str;

	return true;
}

/**
*�ǂݍ���
*@return true...�ǂݍ��݌p�� false...�ǂݍ��ݏI��(error�̏ꍇ���I��)
*/
int XmlReader::read()
{
	//�����Q�̏�����
	this->m_attrs.clear();

	//�m�[�h�̃`�F�b�N
	CheckNodeExpression checkExp;
	XmlNode node = (XmlNode)checkExp.interpret(this->m_context, (int)this->getNode());

	//���ݎQ�ƒ��̃m�[�h��ݒ�
	this->setNode(node);

	//�f�[�^�̎擾
	DataExtractionExpression extExp(this);
	if (extExp.interpret(this->m_context) == false)
		return false;

	return (int)this->m_node;
}