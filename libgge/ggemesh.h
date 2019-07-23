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
\brief 网格模块
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"

namespace gge
{
	/// 位移锚点
	enum MESH_REF_POINT
	{
		MESH_NODE,		///< 原始坐标
		MESH_TOPLEFT,	///< 网格左上角
		MESH_CENTER,	///< 网格中心
		MESH_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 网格模块
	class ggeMesh : public ggeRefCounter
	{
	public:
		/**
		@brief 复制网格
		@param mesh 源网格
		*/
		virtual void		Copy(ggeMesh *mesh) = 0;
		/**
		@brief 返回当前网格的一个副本
		@return 当前网格的一个副本
		*/
		virtual ggeMesh*	Clone() = 0;

		/**
		@brief 渲染网格
		@param x x坐标
		@param y y坐标
		*/
		virtual void		Render(float x, float y) = 0;
		/**
		@brief 重置网格
		@param color 颜色
		@param z Z轴
		*/
		virtual void		Clear(guint32 color = 0xFFFFFFFF, float z = 0.5f) = 0;

		/**
		@brief 设置渲染纹理，纹理区域自动设为整个纹理
		@param texture 用于渲染的纹理
		*/
		virtual void		SetTexture(ggeTexture *texture) = 0;
		/**
		@brief 获得用于渲染的纹理指针
		@return 用于渲染的纹理指针
		*/
		virtual ggeTexture*	GetTexture() = 0;
		/**
		@brief 设置渲染纹理区域
		@param x x坐标
		@param y y坐标
		@param width 宽度
		@param height 高度
		*/
		virtual void		SetTextureRect(float x, float y, float width, float height) = 0;
		/**
		@brief 获得用于渲染的纹理区域
		@param x x坐标
		@param y y坐标
		@param width 宽度
		@param height 高度
		*/
		virtual void		GetTextureRect(float *x, float *y, float *width, float *height) = 0;
		/**
		@brief 设置混合模式
		@param blend 混合模式，可用"|"结合
		@see BLEND_MODE
		*/
		virtual void		SetBlendMode(int blend) = 0;
		/**
		@brief 获得混合模式
		@return 混合模式
		*/
		virtual int			GetBlendMode() = 0;
		/**
		@brief 设置Z轴
		@param col 列
		@param row 行
		@param z 0.0f～1.0f，0表示最上层，1表示最下层
		*/
		virtual void		SetZ(int col, int row, float z) = 0;
		/**
		@brief 获得Z轴
		@param col 列
		@param row 行
		@return Z轴
		*/
		virtual float		GetZ(int col, int row) = 0;
		/**
		@brief 设置渲染颜色
		@param col 列
		@param row 行
		@param color 渲染颜色
		*/
		virtual void		SetColor(int col, int row, guint32 color) = 0;
		/**
		@brief 获得颜色
		@param col 列
		@param row 行
		@return 顶点颜色
		*/
		virtual guint32		GetColor(int col, int row) = 0;
		/**
		@brief 设置节点位移
		@param col 要移动的列
		@param row 要移动的行
		@param dx x位移
		@param dy y位移
		@param ref 位移锚点 @see MESH_REF_POINT
		*/
		virtual void		SetDisplacement(int col, int row, float dx, float dy, int ref = MESH_NODE) = 0;
		/**
		@brief 获得顶点位移
		@param col 列
		@param row 行
		@param dx x位移
		@param dy y位移
		@param ref 位移锚点 @see MESH_REF_POINT
		*/
		virtual void		GetDisplacement(int col, int row, float *dx, float *dy, int ref = MESH_NODE) = 0;

		/**
		@brief 获得行数
		@return 行数
		*/
		virtual int			GetRows() = 0;
		/**
		@brief 获得列数
		@return 列数
		*/
		virtual int			GetCols() = 0;
		/**
		@brief 获得节点队列
		@return 节点队列
		*/
		virtual ggeVertex*	GetNodeList() = 0;
	};

	/**
	@brief 创建网格
	@param cols 列数
	@param rows 行数
	@return 成功返回ggeMesh指针，否则返回0
	*/
	GGE_EXPORT ggeMesh*  Mesh_Create(int cols, int rows);
}