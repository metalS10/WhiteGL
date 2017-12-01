#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../Constants.h"

//==========================================
//
//	XML�m�[�h
//
//==========================================
enum class XmlNode : int
{
	None		= -1,
	Eof			= 0,		//�t�@�C���̏I��
	StartElement= 1,		//�J�n�v�f
	EndElement	= 2,		//�I���v�f
	Text		= 3,		//�J�n�m�[�h�ƏI���m�[�h�̊Ԃɂ���e�L�X�g
	
	Error		= 0,		//�G���[
};

//==========================================
//
//	���ۓI�Ȏ�
//
//==========================================
class Expression
{
public:
	virtual ~Expression(){}
	virtual int interpret( std::string& context ) = 0;
	virtual int interpret( std::string&& context )
	{
		return this -> interpret( context );
	}
};

//==========================================
//
//	XML���[�_�[
//
//==========================================
class XmlReader
{
private:
	//�R���e�L�X�g
	std::string m_context = "";
	
	//���ݎQ�ƒ��̃m�[�h
	XmlNode m_node = XmlNode::None;
	
	//�v�f��
	std::string m_name;
	
	//�e�L�X�g
	std::string m_text;
	
public:
	XmlReader();
	~XmlReader();
	
	/**
	*XML�R���e�L�X�g�̍쐬
	*@param	filePath	�t�@�C���p�X
	*@param	true...����	false...���s
	*/
	bool create( const std::string& filePath );
	
	/**
	*�ǂݍ���
	*@return	true...�ǂݍ��݌p��	false...�ǂݍ��ݏI��(error�̏ꍇ���I��)
	*/
	int read();
	
	//�m�[�h�̎擾�Ɛݒ�
	XmlNode getNode()
	{
		return this -> m_node;
	}
	void setNode( XmlNode node )
	{
		this -> m_node = node;
	}
	
	//�v�f���̎擾�Ɛݒ�
	std::string getName()
	{
		return this -> m_name;
	}
	void setName( std::string& name )
	{
		this -> m_name = name;
	}
	void setName( std::string&& name )
	{
		this -> m_name = name;
	}
	
	//�e�L�X�g�̎擾�Ɛݒ�
	std::string getText()
	{
		return this -> m_text;
	}
	void setText( std::string& text )
	{
		this -> m_text = text;
	}
	void setText( std::string&& text )
	{
		this -> m_text = text;
	}
	
public:
	//=================================
	//	����
	//=================================
	class Attribute
	{
	private:
		std::string m_key = "";		//�����̖��O
		std::string m_value = "";	//�����̒l
		
	public:
		Attribute(){}
		Attribute( std::string& key,std::string& value )
			:m_key( key ),m_value( value ){}
		//�������̎擾�Ɛݒ�
		std::string getKey()
		{
			return this -> m_key;
		}
		void setKey( std::string& key )
		{
			this -> m_key = key;
		}
		
		//�����l�̎擾�Ɛݒ�
		std::string getValue()
		{
			return this -> m_value;
		}
		void setValue( std::string& value )
		{
			this -> m_value = value;
		}
	};
	
private:
	//�����Q
	std::vector< Attribute > m_attrs;
	
public:
	//�����Q�̎擾
	std::vector< Attribute >& getAttributes()
	{
		return this -> m_attrs;
	}
	
	//�����̒ǉ�
	void addAttribute( std::string& key,std::string& value )
	{
		this -> m_attrs.push_back({key,value});
	}
};