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
\brief 基础数据类型
*/

#pragma once

/// Galaxy2D Game Engine 名字空间
namespace gge
{
	#ifdef GALAXY2D_DLL
	#define GGE_EXPORT __declspec(dllexport)
	#else
	#define GGE_EXPORT __declspec(dllimport)
	#endif

	/// 安全删除指针
	#define GGE_DELETE(p)		{ if(p) { delete (p);     (p)=0; } }

	/// 安全删除数组
	#define GGE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=0; } }

	/// 安全释放指针
	#define GGE_RELEASE(p)		{ if(p) { (p)->Release(); (p)=0; } }

	typedef char				gint8;		///< gint8
	typedef short				gint16;		///< gint16
	typedef int					gint32;		///< gint32
	typedef long long			gint64;		///< gint64
	typedef unsigned char		guint8;		///< guint8
	typedef unsigned short		guint16;	///< guint16
	typedef unsigned int		guint32;	///< guint32
	typedef unsigned long long	guint64;	///< guint64
}
