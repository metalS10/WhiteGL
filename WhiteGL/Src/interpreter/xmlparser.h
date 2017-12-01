#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../Constants.h"

//==========================================
//
//	XMLノード
//
//==========================================
enum class XmlNode : int
{
	None		= -1,
	Eof			= 0,		//ファイルの終了
	StartElement= 1,		//開始要素
	EndElement	= 2,		//終了要素
	Text		= 3,		//開始ノードと終了ノードの間にあるテキスト
	
	Error		= 0,		//エラー
};

//==========================================
//
//	抽象的な式
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
//	XMLリーダー
//
//==========================================
class XmlReader
{
private:
	//コンテキスト
	std::string m_context = "";
	
	//現在参照中のノード
	XmlNode m_node = XmlNode::None;
	
	//要素名
	std::string m_name;
	
	//テキスト
	std::string m_text;
	
public:
	XmlReader();
	~XmlReader();
	
	/**
	*XMLコンテキストの作成
	*@param	filePath	ファイルパス
	*@param	true...成功	false...失敗
	*/
	bool create( const std::string& filePath );
	
	/**
	*読み込み
	*@return	true...読み込み継続	false...読み込み終了(errorの場合も終了)
	*/
	int read();
	
	//ノードの取得と設定
	XmlNode getNode()
	{
		return this -> m_node;
	}
	void setNode( XmlNode node )
	{
		this -> m_node = node;
	}
	
	//要素名の取得と設定
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
	
	//テキストの取得と設定
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
	//	属性
	//=================================
	class Attribute
	{
	private:
		std::string m_key = "";		//属性の名前
		std::string m_value = "";	//属性の値
		
	public:
		Attribute(){}
		Attribute( std::string& key,std::string& value )
			:m_key( key ),m_value( value ){}
		//属性名の取得と設定
		std::string getKey()
		{
			return this -> m_key;
		}
		void setKey( std::string& key )
		{
			this -> m_key = key;
		}
		
		//属性値の取得と設定
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
	//属性群
	std::vector< Attribute > m_attrs;
	
public:
	//属性群の取得
	std::vector< Attribute >& getAttributes()
	{
		return this -> m_attrs;
	}
	
	//属性の追加
	void addAttribute( std::string& key,std::string& value )
	{
		this -> m_attrs.push_back({key,value});
	}
};