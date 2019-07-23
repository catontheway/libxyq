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
\brief 变量模块
*/

#pragma once
#include "ggetypes.h"

namespace gge
{
	/// 变量
	class ggeVariant
	{
	public:
		/// 值类型
		enum ValType
		{
			VAL_NONE,		///< None
			VAL_CHAR,		///< Char
			VAL_SHORT,		///< Short
			VAL_INT,		///< Int
			VAL_LONGLONG,	///< LongLong
			VAL_UCHAR,		///< UChar
			VAL_USHORT,		///< UShort
			VAL_UINT,		///< UInt
			VAL_ULONGLONG,	///< ULongLong
			VAL_FLOAT,		///< Float
			VAL_DOUBLE,		///< Double
			VAL_BOOL,		///< Bool
			VAL_STRING,		///< String
		};

		/** @name 构造函数
		*  @{
		*/
		ggeVariant() : m_Type(VAL_NONE), m_VarBuf(0)				{}
		ggeVariant(gint8 v) : m_Type(VAL_CHAR), m_VarBuf(0)			{ m_Data.IntVal = v; }
		ggeVariant(gint16 v) : m_Type(VAL_SHORT), m_VarBuf(0)		{ m_Data.IntVal = v; }
		ggeVariant(gint32 v) : m_Type(VAL_INT), m_VarBuf(0)			{ m_Data.IntVal = v; }
		ggeVariant(gint64 v) : m_Type(VAL_LONGLONG), m_VarBuf(0)	{ m_Data.IntVal = v; }
		ggeVariant(guint8 v) : m_Type(VAL_UCHAR), m_VarBuf(0)		{ m_Data.UIntVal = v; }
		ggeVariant(guint16 v) : m_Type(VAL_USHORT), m_VarBuf(0)		{ m_Data.UIntVal = v; }
		ggeVariant(guint32 v) : m_Type(VAL_UINT), m_VarBuf(0)		{ m_Data.UIntVal = v; }
		ggeVariant(guint64 v) : m_Type(VAL_ULONGLONG), m_VarBuf(0)	{ m_Data.UIntVal = v; }
		ggeVariant(float v) : m_Type(VAL_FLOAT), m_VarBuf(0)		{ m_Data.FloatVal = v; }
		ggeVariant(double v) : m_Type(VAL_DOUBLE), m_VarBuf(0)		{ m_Data.DoubleVal = v; }
		ggeVariant(bool v) : m_Type(VAL_BOOL), m_VarBuf(0)			{ m_Data.BoolVal = v; }
		GGE_EXPORT ggeVariant(const char *v);
		GGE_EXPORT ggeVariant(const ggeVariant &other);
		/** 
		@} 
		*/

		/// 析构函数
		GGE_EXPORT ~ggeVariant();
		
		/** @name 赋值函数
		*  @{
		*/
		
		ggeVariant& operator= (gint8 v)		{ m_Type = VAL_CHAR; m_Data.IntVal = v; return *this; }
		ggeVariant& operator= (gint16 v)	{ m_Type = VAL_SHORT; m_Data.IntVal = v; return *this; }
		ggeVariant& operator= (gint32 v)	{ m_Type = VAL_INT; m_Data.IntVal = v; return *this; }
		ggeVariant& operator= (gint64 v)	{ m_Type = VAL_LONGLONG; m_Data.IntVal = v; return *this; }
		ggeVariant& operator= (guint8 v)	{ m_Type = VAL_UCHAR; m_Data.UIntVal = v; return *this; }
		ggeVariant& operator= (guint16 v)	{ m_Type = VAL_USHORT; m_Data.UIntVal = v; return *this; }
		ggeVariant& operator= (guint32 v)	{ m_Type = VAL_UINT; m_Data.UIntVal = v; return *this; }
		ggeVariant& operator= (guint64 v)	{ m_Type = VAL_ULONGLONG; m_Data.UIntVal = v; return *this; }
		ggeVariant& operator= (float v)		{ m_Type = VAL_FLOAT; m_Data.FloatVal = v; return *this; }
		ggeVariant& operator= (double v)	{ m_Type = VAL_DOUBLE; m_Data.DoubleVal = v; return *this; }
		ggeVariant& operator= (bool v)		{ m_Type = VAL_BOOL; m_Data.BoolVal = v; return *this; }
		GGE_EXPORT ggeVariant& operator= (const ggeVariant &other);
		GGE_EXPORT ggeVariant& operator= (const char *v);
		/** 
		@} 
		*/

		/** @name 比较函数
		*  @{
		*/
		GGE_EXPORT bool operator!= (const ggeVariant& v) const;
		GGE_EXPORT bool operator== (const ggeVariant& v) const;
		/** 
		@} 
		*/

		/** @name 返回指定类型的值
		*  @{
		*/
		GGE_EXPORT gint8		GetChar(gint8 def = 0) const;
		GGE_EXPORT gint16		GetShort(gint16 def = 0) const;
		GGE_EXPORT gint32		GetInt(gint32 def = 0) const;
		GGE_EXPORT gint64		GetLongLong(gint64 def = 0) const;
		GGE_EXPORT guint8		GetUChar(guint8 def = 0) const;
		GGE_EXPORT guint16		GetUShort(guint16 def = 0) const;
		GGE_EXPORT guint32		GetUInt(guint32 def = 0) const;
		GGE_EXPORT guint64		GetULongLong(guint64 def = 0) const;
		GGE_EXPORT float		GetFloat(float def = 0) const;
		GGE_EXPORT double		GetDouble(double def = 0) const;
		GGE_EXPORT bool			GetBool(bool def = false) const;
		GGE_EXPORT const char*	GetString() const;
		/** 
		@} 
		*/

		/// 清除
		void	Clear()			{ m_Type = VAL_NONE; }
		/// 返回是否有效
		bool	IsValid() const { return GetType() != VAL_NONE; }
		/// 返回值类型
		ValType	GetType() const { return m_Type; }
		
	private:
		union ValueDataType
		{
			gint64	IntVal;
			guint64	UIntVal;
			float	FloatVal;
			double	DoubleVal;
			bool	BoolVal;
		};

		ValueDataType	m_Data;
		ValType			m_Type;

		struct ggeVariantBuffer;
		mutable ggeVariantBuffer *m_VarBuf;
	};

	 /**
	@brief 将多字节码转换为宽字节码
	@param str 要转换的字符串
	@return 转换成功返回转换后的宽字节码，否则返回0
	@note 该函数当次调用有效，如果外部需要保留返回值，必须自行复制
	*/
	GGE_EXPORT const wchar_t*	Variant_Asc2Unicode(const char *str);
	 /**
	@brief 将宽字节码转换为多字节码
	@param str 要转换的字符串
	@return 转换成功返回转换后的 多字节码 ，否则返回0
	@note 该函数当次调用有效，如果外部需要保留返回值，必须自行复制
	*/
	GGE_EXPORT const char*		Variant_Unicode2Asc(const wchar_t *str);
	 /**
	@brief 将宽字节码转换为UTF8编码
	@param str 要转换的字符串
	@return 转换成功返回转换后的UTF8编码，否则返回0
	@note 该函数当次调用有效，如果外部需要保留返回值，必须自行复制
	*/
	GGE_EXPORT const char*		Variant_Unicode2Utf8(const wchar_t *str);
	 /**
	@brief 将UTF8编码转换为宽字节码
	@param str 要转换的字符串
	@return 转换成功返回转换后的宽字节码，否则返回0
	@note 该函数当次调用有效，如果外部需要保留返回值，必须自行复制
	*/
	GGE_EXPORT const wchar_t*	Variant_Utf82Unicode(const char *str);
	 /**
	@brief 将多字节码转换为UTF8编码
	@param str 要转换的字符串
	@return 转换成功返回转换后的UTF8编码，否则返回0
	@note 该函数当次调用有效，如果外部需要保留返回值，必须自行复制
	*/
	GGE_EXPORT const char*		Variant_Asc2Utf8(const char *str);
	 /**
	@brief 将UTF8编码转换为多字节码
	@param str 要转换的字符串
	@return 转换成功返回转换后的多字节码，否则返回0
	@note 该函数当次调用有效，如果外部需要保留返回值，必须自行复制
	*/
	GGE_EXPORT const char*		Variant_Utf82Asc(const char *str);
}