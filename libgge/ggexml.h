/*
**  =======================================================
**              Galaxy2D Game Engine       
**                                
**       版权所有(c) 2005 沈明. 保留所有权利.
**    主页地址: http://www.cnblogs.com/jianguhan/
**			 电子邮箱: jianguhan@126.com
**  =======================================================
*/

/** \file
\brief XML模块
*/

#pragma once
#include "ggetypes.h"
#include "ggerefcounter.h"

namespace gge
{
	/// XML节点
	class ggeXmlNode
	{
	public:
		/// 构造函数
		ggeXmlNode() : m_XmlNode(0) {}

		/// 设置节点名字
		GGE_EXPORT void			SetName(const char *name);
		/// 返回节点名字
		GGE_EXPORT const char*	GetName() const;
		/// 是否是有效节点
		GGE_EXPORT bool			IsValid() const;

		/**
		@brief 返回下一个节点
		@param name 如果指定了该参数，则返回下一个名字与该参数相同的节点
		@return 返回ggeXmlNode
		*/
		GGE_EXPORT ggeXmlNode	GetNextNode(const char *name = 0) const;
		/**
		@brief 返回前一个节点
		@param name 如果指定了该参数，则返回前一个名字与该参数相同的节点
		@return 返回ggeXmlNode
		*/
		GGE_EXPORT ggeXmlNode	GetPreviousNode(const char *name = 0) const;
		/**
		@brief 返回第一个子节点
		@param name 如果指定了该参数，则返回第一个名字与该参数相同的子节点
		@return 返回ggeXmlNode
		*/
		GGE_EXPORT ggeXmlNode	GetFirstChild(const char *name = 0) const;
		/**
		@brief 返回最后一个子节点
		@param name 如果指定了该参数，则返回最后一个名字与该参数相同的子节点
		@return 返回ggeXmlNode
		*/
		GGE_EXPORT ggeXmlNode	GetLastChild(const char *name = 0) const;
		
		/**
		@brief 在首部插入节点
		@param name 节点名字
		@param bText 是否是Text类型节点，如果是Text类型节点，不能设置属性和子节点
		@return 返回插入的节点
		*/
		GGE_EXPORT ggeXmlNode	InsertFirstChild(const char *name, bool bText = false);
		/**
		@brief 在指定子节点后插入节点
		@param after 插入位置
		@param name 节点名字
		@param bText 是否是Text类型节点，如果是Text类型节点，不能设置属性和子节点
		@return 返回插入的节点
		*/
		GGE_EXPORT ggeXmlNode	InsertAfterChild(ggeXmlNode after, const char *name, bool bText = false);
		/**
		@brief 在尾部插入节点
		@param name 节点名字
		@param bText 是否是Text类型节点，如果是Text类型节点，不能设置属性和子节点
		@return 返回插入的节点
		*/
		GGE_EXPORT ggeXmlNode	InsertEndChild(const char *name, bool bText = false);
		/**
		@brief 删除一个子节点
		@param remove 要删除的节点
		*/
		GGE_EXPORT void			DeleteChild(ggeXmlNode remove);
		/**
		@brief 清除所有子节点
		*/
		GGE_EXPORT void			Clear();


		/** @name 设置属性值
		*  @{
		*/
		GGE_EXPORT void			SetInt(const char *name, int val);
		GGE_EXPORT void			SetLongLong(const char *name, gint64 val);
		GGE_EXPORT void			SetUInt(const char *name, guint32 val);
		GGE_EXPORT void			SetULongLong(const char *name, guint64 val);
		GGE_EXPORT void			SetFloat(const char *name, float val);
		GGE_EXPORT void			SetDouble(const char *name, double val);
		GGE_EXPORT void			SetBool(const char *name, bool val);
		GGE_EXPORT void			SetString(const char *name, const char *val);
		/** 
		@} 
		*/

		/** @name 返回属性值，如果获取属性失败返回def
		*  @{
		*/
		GGE_EXPORT int			GetInt(const char *name, int def = 0) const;
		GGE_EXPORT gint64		GetLongLong(const char *name, gint64 def = 0) const;
		GGE_EXPORT guint32		GetUInt(const char *name, guint32 def = 0) const;
		GGE_EXPORT guint64		GetULongLong(const char *name, guint64 def = 0) const;
		GGE_EXPORT float		GetFloat(const char *name, float def = 0) const;
		GGE_EXPORT double		GetDouble(const char *name, double def = 0) const;
		GGE_EXPORT bool			GetBool(const char *name, bool def = false) const;
		GGE_EXPORT const char*	GetString(const char *name, const char* def = 0) const;
		/** 
		@} 
		*/
		
		/**
		@brief 删除属性
		@param name 属性名
		*/
		GGE_EXPORT void			DeleteAttribute(const char *name);
		/**
		@brief 设置当前节点是否是CData，当前节点是Text类型节点时有效
		@param b 为true表示当前节点是CData，否则不是
		*/
		GGE_EXPORT void			SetCData(bool b);
		/**
		@brief 返回当前节点是否是CData
		*/
		GGE_EXPORT bool			IsCData();

	private:
		friend class	ggeXmlElementHelper;
		void			*m_XmlNode;
	};

	/// XML文档
	class ggeXmlDocument : public ggeRefCounter
	{
	public:
		/**
		@brief 载入XML文件，调用该函数后，之前返回的ggeXmlNode将失效
		@param filename 文件名
		@return 成功返回true，否则返回false
		*/
		virtual bool			LoadFile(const char *filename) = 0;
		/**
		@brief 保存XML文件
		@param filename 文件名
		@return 成功返回true，否则返回false
		*/
		virtual bool			SaveFile(const char *filename) = 0;
		/**
		@brief 解析XML字符串，调用该函数后，之前返回的ggeXmlNode将失效
		@param str 要解析的字符串，如：\<node string="string">test_node\</node>
		@return 成功返回true，否则返回false
		*/
		virtual bool			Parse(const char* str) = 0;
		/**
		@brief 返回根节点
		*/
		virtual ggeXmlNode		GetRootNode() = 0;
	};

	/**
	@brief 创建XML文档
	@return 成功返回ggeXmlDocument指针，否则返回0
	@note
		\code
		XML文件内容：
		<?xml version="1.0" encoding="gb2312" ?>
		<XmlRoot>
			<Val1 Str="Test" />
			<Val2 Num="1" />
			<Val3>
				<ChildNode ID="0" />
				<ChildNode ID="1" />
				<ChildNode ID="2" />
				<ChildNode ID="3" />
			</Val3>
			<Val4>This is a text!</Val4>
		</XmlRoot>
		\endcode
		\code
		示例程序：

		//创建XML文档
		ggeXmlDocument *doc = Xml_Create();
		//获取根节点
		ggeXmlNode root = doc->GetRootNode();
		root.SetName("XmlRoot");

		//插入名字为Val1的节点
		ggeXmlNode valNode = root.InsertEndChild("Val1");
		//设置属性"Str"的值为"Test"
		valNode.SetString("Str", "Test");

		//插入名字为Val2的节点
		valNode = root.InsertEndChild("Val2");
		//设置属性"Num"的值为1
		valNode.SetInt("Num", 1);

		//创建名字为Val3的节点，
		valNode = root.InsertEndChild("Val3");
		for (int i = 0; i < 4; i++)
		{
		//在Val3节点下创建子节点
		ggeXmlNode childNode = valNode.InsertEndChild("ChildNode");
		//设置属性"ID"值
		childNode.SetInt("ID", i);
		}

		//创建名字为Val4的节点
		valNode = root.InsertEndChild("Val4");
		//插入一个字符串子节点
		valNode = valNode.InsertEndChild("This is a test!", true);

		//保存xml文件
		doc->SaveFile("myxml.xml");

		//打开xml文件
		doc->LoadFile("myxml.xml");

		//获取根节点
		root = doc->GetRootNode();

		//输出Root名
		cout<<root.GetName()<<endl;
		//输出Val1
		cout<<"Val1:"<<root.GetFirstChild("Val1").GetString("Str")<<endl;
		//输出Val2
		cout<<"Val2:"<<root.GetFirstChild("Val2").GetInt("Num")<<endl;
		//输出Val3
		valNode = root.GetFirstChild("Val3").GetFirstChild("ChildNode");
		while (valNode.IsValid())
		{
		cout<<"Val3:"<<valNode.GetString("ID")<<endl;
		valNode = valNode.GetNextNode();
		}
		//输出Val4
		cout<<"Val4:"<<root.GetFirstChild("Val4").GetFirstChild().GetName()<<endl;

		//释放Doc
		GGE_RELEASE(doc);
	\endcode
	*/
	GGE_EXPORT ggeXmlDocument*  Xml_Create();
}