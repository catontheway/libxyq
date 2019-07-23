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
\brief RichText控件
*/

#pragma once
#include "ggeguiwindow.h"

namespace gge
{
	/// RichText 控件
	class ggeGuiRichText : public ggeGuiWindow
	{
	public:
		ggeGuiRichText(int id = -1, const ggeRect &rect = ggeRect(0, 0, 32.0f, 32.0f)) : ggeGuiWindow(id, rect), m_bUpdateData(false), m_bMouseOver(false)
		{
			_CreateRichTextData();
			SetStatic(true);
		}
		virtual ~ggeGuiRichText()
		{
			_DeleteRichTextData();
		}

		/**
		@brief 设置文本
		@note 命令列表：\n
		\##: "#"符号\n
		\#c: 设置文字颜色，如："#cFF0000FF蓝色的字"\n
		\#d: 设置阴影颜色\n
		\#b: 设置边框颜色\n
		\#u: 切换文字是否加下划线\n
		\#p: 对齐方式( 0:左对齐 / 1:居中对齐 / 2:右对齐 )\n
		\#s: 插入Sprite，如："在中间显示#s1图标"\n
		\#a: 插入Animation，如："在中间显示#a1图标"\n
		\#f: 插入特殊文字字体( 0:恢复默认字体 / >0:设置特殊字体 )，如："普通文字#f1大号文字#f0普通文字"\n
		\#h: 插入超链接，格式为："#h超链接ID,超链接高亮颜色,超链接内容#h"，如"#h100,FFFF0000,超链接#h"，点击超链接时会发送CMT_RICH_TEXT_HYPER_LINK消息到父窗口，可用GetHyperLinkID()函数获取当前点击的超链接ID\n
		*/
		virtual void		SetText(const char *text)	{ ggeGuiWindow::SetText(text); m_bUpdateData = true; }
		/// 设置最大文字宽度，超过该宽度自动换行，设为0则不自动换行，默认为0
		GGE_EXPORT void		SetMaxTextWidth(guint16 width);
		/// 返回最大文字宽度
		GGE_EXPORT guint16	GetMaxTextWidth();
		/// 返回文本宽度
		GGE_EXPORT guint16	GetCurTextWidth();
		/// 返回文本高度
		GGE_EXPORT guint16	GetCurTextHeigth();

		/// 插入Sprite
		GGE_EXPORT void		InsertSprite(guint16 id, ggeSprite *spr);
		/// 移除Sprite
		GGE_EXPORT void		RemoveSprite(guint16 id);
		/// 插入Animation
		GGE_EXPORT void		InsertAnimation(guint16 id, ggeAnimation *ani);
		/// 移除Animation
		GGE_EXPORT void		RemoveAnimation(guint16 id);
		/// 插入Font
		GGE_EXPORT void		InsertFont(guint16 id, ggeFont *fnt);
		/// 移除Font
		GGE_EXPORT void		RemoveFont(guint16 id);
		/// 返回超链接ID
		GGE_EXPORT guint16	GetHyperLinkID();

		virtual	void		SetPos(float x, float y, bool bMoveChild = true) { ggeGuiWindow::SetPos(x, y, bMoveChild); m_bUpdateData = true; }
		virtual void		SetWidth(float width)	{ ggeGuiWindow::SetWidth(width); m_bUpdateData = true; }
		virtual void		SetHeight(float height)	{ ggeGuiWindow::SetHeight(height); m_bUpdateData = true; }
		virtual void		SetRect(const ggeRect &rt, bool bMoveChild = true) { ggeGuiWindow::SetRect(rt, bMoveChild); m_bUpdateData = true; }
		virtual void		SetLineSpace(int v)		{ ggeGuiWindow::SetLineSpace(v); m_bUpdateData = true;; }
		virtual void		SetCharSpace(int v)		{ ggeGuiWindow::SetCharSpace(v); m_bUpdateData = true; }
		virtual void		SetFontState(const ggeGuiFontState &fontRS) { ggeGuiWindow::SetFontState(fontRS); m_bUpdateData = true; }
		virtual void		SetFont(ggeFont *font)	{ ggeGuiWindow::SetFont(font); m_bUpdateData = true; }

		virtual void		OnMouseOver(bool bOver)			{ m_bMouseOver = bOver; }
		virtual void		OnMouseMove(float x, float y)	{ m_mouseX = x; m_mouseY = y; }
		virtual void		OnUpdate(float dt)				{ _OnUpdate(dt); }
		virtual void		OnRender()						{ _OnRender(); }
		virtual int			GetType()						{ return GGT_RichText; }

	private:
		GGE_EXPORT	void	_CreateRichTextData();
		GGE_EXPORT	void	_DeleteRichTextData();
		GGE_EXPORT	void	_OnUpdate(float dt);
		GGE_EXPORT	void	_OnRender();
		GGE_EXPORT	void	_UpdateData();

		class				ggeGuiRichTextData;
		ggeGuiRichTextData	*m_rcTextData;
		bool				m_bUpdateData;
		bool				m_bMouseOver;
		float				m_mouseX;
		float				m_mouseY;
	};
}