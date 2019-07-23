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
\brief Json模块
*/

#pragma once
#include "ggetypes.h"
#include "ggerefcounter.h"

namespace gge
{
	/// Json值
	class ggeJsonValue
	{
	public:
		/// 值类型
		enum ValType
		{
			VAL_NULL,		///< Null
			VAL_BOOL,		///< Bool
			VAL_INT,		///< Int
			VAL_FLOAT,		///< Float
			VAL_STRING,		///< String
			VAL_OBJECT,		///< Object
			VAL_ARRAY,		///< Array
		};

		/// 对象迭代器
		class Iterator
		{
		public:
			Iterator() : m_Index(0), m_JsonValue(0), m_JsonDocument(0) {}

			/// 返回名字
			GGE_EXPORT const char*	GetName();
			/// 返回值
			GGE_EXPORT ggeJsonValue	GetValue();
			/// 迭代器是否有效
			GGE_EXPORT bool			IsValid();
			/// 获取下一个值
			GGE_EXPORT void			NextValue();

		private:
			friend class ggeJsonValue;
			guint32	m_Index;
			void	*m_JsonValue;
			void	*m_JsonDocument;
		};

		/// 构造函数
		ggeJsonValue() : m_JsonValue(0), m_JsonDocument(0) {}

		/// 返回值类型
		GGE_EXPORT ValType		GetType() const;
		/// 是否有效
		GGE_EXPORT bool			IsValid() const;

		/** @name 设置值
		*  @{
		*/
		GGE_EXPORT void			SetInt(int val);
		GGE_EXPORT void			SetUInt(guint32 val);
		GGE_EXPORT void			SetLongLong(gint64 val);
		GGE_EXPORT void			SetULongLong(guint64 val);
		GGE_EXPORT void			SetBool(bool val);
		GGE_EXPORT void			SetFloat(float val);
		GGE_EXPORT void			SetDouble(double val);
		GGE_EXPORT void			SetString(const char *val);
		/** 
		@} 
		*/

		/// 设置为数组
		GGE_EXPORT ggeJsonValue& SetArray();
		/// 设置为对象
		GGE_EXPORT ggeJsonValue& SetObject();
		
		/** @name 返回指定类型的值
		*  @{
		*/
		GGE_EXPORT int			GetInt() const;
		GGE_EXPORT guint32		GetUInt() const;
		GGE_EXPORT gint64		GetLongLong() const;
		GGE_EXPORT guint64		GetULongLong() const;
		GGE_EXPORT bool			GetBool() const;
		GGE_EXPORT float		GetFloat() const;
		GGE_EXPORT double		GetDouble() const;
		GGE_EXPORT const char*	GetString() const;
		/** 
		@} 
		*/

		/**
		@brief 添加值
		@param name 如果当前值是对象，该参数用于设置名字
		@return 新添加的值
		*/
		GGE_EXPORT ggeJsonValue	AddValue(const char *name = 0);

		/**
		@brief 获取数组值
		@param index 数组索引
		@return 返回指定索引的值
		*/
		GGE_EXPORT ggeJsonValue	GetValue(guint32 index);
		/**
		@brief 获取对象值
		@param name 对象名
		@return 返回指定名字的值
		*/
		GGE_EXPORT ggeJsonValue	GetValue(const char *name);

		/**
		@brief 删除数组值
		@param index 数组索引
		*/
		GGE_EXPORT void			DelValue(guint32 index);
		/**
		@brief 删除对象值
		@param name 对象名
		@param bKeepOrder 是否保持顺序，不保持可以提高删除效率
		*/
		GGE_EXPORT void			DelValue(const char *name, bool bKeepOrder = false);

		/// 返回数组或对象内值的数量
		GGE_EXPORT guint32		GetValueCount();
		/// 返回对象迭代器
		GGE_EXPORT Iterator		GetObjectIterator();

	private:
		friend class ggeJsonValueHelper;
		void *m_JsonValue;
		void *m_JsonDocument;
	};

	/// Json文档
	class ggeJsonDocument : public ggeRefCounter
	{
	public:
		/**
		@brief 载入Json文件，调用该函数后，之前返回的ggeJsonValue将失效
		@param filename 文件名
		@return 成功返回true，否则返回false
		*/
		virtual bool			LoadFile(const char *filename) = 0;
		/**
		@brief 保存Json文件
		@param filename 文件名
		@param bFomart 是否格式化输出文件，格式化后的文件内容更易读，但会使文件更大
		@return 成功返回true，否则返回false
		@note 注意，根节点必须是数组或对象
		*/
		virtual bool			SaveFile(const char *filename, bool bFomart = false) = 0;
		/**
		@brief 解析Json字符串，调用该函数后，之前返回的ggeJsonValue将失效
		@param str 要解析的字符串，如：{ aaa: "test", bbb: 123 }
		@return 成功返回true，否则返回false
		*/
		virtual bool			Parse(const char* str) = 0;
		/**
		@brief 返回根节点
		*/
		virtual ggeJsonValue	GetRootValue() = 0;
	};

	/**
	@brief 创建Json文档
	@return 成功返回ggeJsonDocument指针，否则返回0
	@note
	\code
		示例程序：

		//创建Json文档
		ggeJsonDocument *doc = Json_Create();
		//获取根节点，并设置为对象
		ggeJsonValue root = doc->GetRootValue().SetObject();

		//添加数值
		root.AddValue("val1").SetDouble(3.14);

		//添加字符串
		root.AddValue("val2").SetString("This is a test!");

		//添加名字为Val1的值，并设置为数组
		ggeJsonValue val = root.AddValue("val3").SetArray();

		//添加数值
		for (int i = 0; i < 4; i++)
		{
			val.AddValue().SetInt(i * 10);
		}

		//保存xml文件
		doc->SaveFile("myjson.json");

		//打开xml文件
		doc->LoadFile("myjson.json");

		//获取根节点
		root = doc->GetRootValue();

		//遍历对象值
		for (ggeJsonValue::Iterator it = root.GetObjectIterator(); it.IsValid(); it.NextValue())
		{
			val = it.GetValue();
			switch (val.GetType())
			{
			case ggeJsonValue::VAL_FLOAT:
				cout<<it.GetName()<<"  "<<val.GetDouble()<<endl;
				break;

			case ggeJsonValue::VAL_INT:
				cout<<it.GetName()<<"  "<<val.GetInt()<<endl;
				break;

			case ggeJsonValue::VAL_STRING:
				cout << it.GetName() << "  " << val.GetString() << endl;
				break;

			case ggeJsonValue::VAL_ARRAY:
				cout<<it.GetName()<<endl;
				//遍历数组值
				for (guint32 i = 0; i < val.GetValueCount(); i++)
				{
					ggeJsonValue arrval = val.GetValue(i);
					cout<<"    "<<arrval.GetInt()<<endl;
				}
				break;
			}
		}

		//释放Doc
		GGE_RELEASE(doc);
	\endcode
	*/
	GGE_EXPORT ggeJsonDocument* Json_Create();
}