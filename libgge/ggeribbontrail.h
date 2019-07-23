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
\brief 轨迹带模块
*/

#pragma once
#include "ggecommon.h"
#include "ggerefcounter.h"

namespace gge
{
	/// 轨迹带模块
	class ggeRibbonTrail : public ggeRefCounter
	{
	public:
		/**
		@brief 复制轨迹带
		@param trail 源轨迹带
		*/
		virtual void				Copy(ggeRibbonTrail *trail) = 0;
		/**
		@brief 返回当前轨迹带的一个副本
		@return 当前轨迹带副本
		*/
		virtual ggeRibbonTrail*		Clone() = 0;

		/**
		@brief 刷新轨迹带
		@param dt 上一帧所用时间，可用Timer_GetDelta()获得
		*/
		virtual void				Update(float dt) = 0;
		/**
		@brief 渲染轨迹带
		*/
		virtual void				Render() = 0;
		/**
		@brief 停止渲染轨迹带
		*/
		virtual void				Stop() = 0;
		/**
		@brief 移动轨迹带到指定位置
		@param x x坐标
		@param y y坐标
		@param bMoveNodes 如果为true，所有活动节点将被移动，否则只移动头节点
		*/
		virtual void				MoveTo(float x, float y, bool bMoveNodes = false) = 0;
		/**
		@brief 获得轨迹带坐标
		@param x x坐标
		@param y y坐标
		*/
		virtual void				GetPosition(float *x, float *y) = 0;
		/**
		@brief 设置轨迹带移动位移
		@param x x坐标
		@param y y坐标
		*/
		virtual void				Transpose(float x, float y) = 0;
		/**
		@brief 获得轨迹带位移量
		@param x x坐标
		@param y y坐标
		*/
		virtual void				GetTransposition(float *x, float *y) = 0;
		/**
		@brief 是否开启轨迹带范围跟踪
		@param bTrack 是否开启轨迹带范围跟踪
		*/
		virtual void				TrackBoundingBox(bool bTrack) = 0;

		/**
		@brief 设置轨迹带最大节点数
		@param num 最大节点数
		*/
		virtual void				SetMaxNodeNum(guint32 num) = 0;
		/**
		@brief 获得轨迹带最大节点数
		@return 轨迹带最大节点数
		*/
		virtual guint32				GetMaxNodeNum() = 0;
		/**
		@brief 设置轨迹带生命期
		@param time 轨迹带生命期(单位：秒)
		*/
		virtual void				SetLifeTime(float time) = 0	;	
		/**
		@brief 获得轨迹带生命期
		@return 轨迹带生命期
		*/
		virtual float				GetLifeTime() = 0;
		/**
		@brief 设置轨迹带起始颜色
		@param color 轨迹带起始颜色
		*/
		virtual void				SetStartColor(guint32 color) = 0;
		/**
		@brief 获得轨迹带起始颜色
		@return 轨迹带起始颜色
		*/
		virtual guint32				GetStartColor() = 0;
		/**
		@brief 设置轨迹带结束颜色
		@param color 轨迹带结束颜色
		*/
		virtual void				SetEndColor(guint32 color) = 0;
		/**
		@brief 获得轨迹带结束颜色
		@return 轨迹带结束颜色
		*/
		virtual guint32				GetEndColor() = 0;
		/**
		@brief 设置轨迹带最大宽度
		@param width 轨迹带最大宽度
		*/
		virtual void				SetMaxWidth(float width) = 0;
		/**
		@brief 获得轨迹带最大宽度
		@return 轨迹带最大宽度
		*/
		virtual float				GetMaxWidth() = 0;
		/**
		@brief 设置轨迹带最小宽度
		@param width 轨迹带最小宽度
		*/
		virtual void				SetMinWidth(float width) = 0;
		/**
		@brief 获得轨迹带最小宽度
		@return 轨迹带最小宽度
		*/
		virtual float				GetMinWidth() = 0;
		/**
		@brief 设置轨迹带节点长度
		@param len 轨迹带节点长度
		*/
		virtual void				SetNodeLength(guint32 len) = 0;
		/**
		@brief 获得轨迹带节点长度
		@return 轨迹带节点长度
		*/
		virtual guint32				GetNodeLength() = 0;
		/**
		@brief 跟踪移动方向自动设置轨迹带朝向
		@param b true为开启，false为关闭，默认开启
		*/
		virtual void				TrackMovingDirection(bool b) = 0;
		/**
		@brief 获得是否跟踪移动方向
		@return 是否跟踪移动方向
		*/
		virtual bool				IsTrackMovingDirection() = 0;
		/**
		@brief 设置轨迹带朝向，关闭跟踪移动方向功能时有效
		@param angle 轨迹带朝向(单位：弧度)
		*/
		virtual void				SetDirection(float angle) = 0;
		/**
		@brief 获得轨迹带朝向
		@return 轨迹带朝向
		*/
		virtual float				GetDirection() = 0;

		/**
		@brief 设置渲染纹理，纹理区域自动设为整个纹理
		@param texture 渲染纹理
		*/
		virtual void				SetTexture(ggeTexture *texture) = 0;
		/**
		@brief 获得用于渲染的纹理指针
		@return 用于渲染的纹理指针
		*/
		virtual ggeTexture*			GetTexture() = 0;
		/**
		@brief 设置渲染纹理区域
		@param x x坐标
		@param y y坐标
		@param width 宽度
		@param height 高度
		*/
		virtual void				SetTextureRect(float x, float y, float width, float height) = 0;
		/**
		@brief 获得用于渲染的纹理区域
		@param x x坐标
		@param y y坐标
		@param width 宽度
		@param height 高度
		*/
		virtual void				GetTextureRect(float *x, float *y, float *width, float *height) = 0;
		/**
		@brief 设置Z轴
		@param z 0.0f～1.0f，0表示最上层，1表示最下层
		*/
		virtual void				SetZ(float z) = 0;
		/**
		@brief 获得Z轴
		@return Z轴
		*/
		virtual float				GetZ() = 0;
		/**
		@brief 设置混合模式
		@param blend 混合模式，可用"|"结合，默认为 BLEND_COLORMUL|BLEND_ALPHAADD|BLEND_NOZWRITE
		@see BLEND_MODE
		*/
		virtual void				SetBlendMode(int blend) = 0;
		/**
		@brief 获得混合模式
		@return 混合模式
		*/
		virtual int					GetBlendMode() = 0;

		/**
		@brief 获得轨迹带包围盒
		@param rect 轨迹带包围盒
		*/
		virtual ggeRect*			GetBoundingBox(ggeRect *rect) = 0;
	};

	/**
	@brief 创建轨迹带
	@param startCol 轨迹带起始颜色
	@param endColor 轨迹带结束颜色
	@param maxW 轨迹带最大宽度
	@param minW 轨迹带最小宽度
	@param time 轨迹带生命期
	@param maxNodes 轨迹带最大节点数
	@param nodeLen 轨迹带节点长度(单位：像素)
	@return 成功返回ggeRibbonTrail指针，否则返回0
	*/
	GGE_EXPORT ggeRibbonTrail*  RibbonTrail_Create(guint32 startCol = 0xFFFFFFFF, guint32 endColor = 0x00FFFFFF, float maxW = 16.0f, float minW = 0.0f, float time = 1.0f, guint32 maxNodes = 64, guint32 nodeLen = 4);
}