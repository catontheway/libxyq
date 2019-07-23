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
\brief ListBox控件
*/

#pragma once
#include "ggeguiwindow.h"

namespace gge
{
	/// ListBox 控件
	class ggeGuiListBox : public ggeGuiWindow
	{
	public:
		ggeGuiListBox(int id = -1, const ggeRect &rect = ggeRect(0, 0, 32.0f, 32.0f)) : ggeGuiWindow(id, rect)
		{
			_CreateListBoxData();
			m_selectedItem = -1;
			m_topItem = 0;
			m_bMouseOver = false;
		}

		virtual ~ggeGuiListBox()
		{
			_DeleteListBoxData();
		}

		/// 添加一个项目并返回项目索引，项目索引从0开始
		GGE_EXPORT	int		AddItem(const char *item, void *p = 0);
		/// 删除一个项目
		GGE_EXPORT	bool	DeleteItem(int n);
		/// 获得当前选中的项目的项目索引，未选中任何项返回-1
		int		GetSelectedItem()			{ return m_selectedItem; }
		/// 设置当前选中的项目的项目索引
		GGE_EXPORT	void	SetSelectedItem(int n);
		/// 得到顶部项目索引
		int		GetTopItem()				{ return m_topItem; }
		/// 设置顶部项目索引
		GGE_EXPORT	void	SetTopItem(int n);

		/// 设置项目上下文
		GGE_EXPORT	bool	SetContext(int n, void *p);
		/// 返回项目上下文
		GGE_EXPORT	void*	GetContext(int n);
		/// 设置项目文本
		GGE_EXPORT	void	SetItemText(int n, const char *text);
		/// 获得项目文本
		GGE_EXPORT	const char*	GetItemText(int n);
		/// 获得项目总数
		GGE_EXPORT	int		GetNumItems();
		/// 获得显示的项目数
		GGE_EXPORT	int		GetNumRows();
		/// 删除所有项目
		GGE_EXPORT	void	Clear();
		/// 返回项目高度
		GGE_EXPORT	int		GetItemHeight();

		virtual void SetRenderState(GUI_RENDER_STATE_TYPE rt, const ggeGuiRenderState &rs)
		{
			switch (rt)
			{
			case GRST_PRESS:
				m_pressRS = rs;
				break;

			case GRST_MOUSEOVER:
				m_mouseOverRS = rs;
				break;

			default:
				ggeGuiWindow::SetRenderState(rt, rs);
				break;
			}
		}
		virtual ggeGuiRenderState* GetRenderState(GUI_RENDER_STATE_TYPE rt)
		{
			switch (rt)
			{
			case GRST_PRESS:
				return &m_pressRS;

			case GRST_MOUSEOVER:
				return &m_mouseOverRS;
			}

			return ggeGuiWindow::GetRenderState(rt);
		}

		virtual void	OnRender()						{ _OnRender(); }
		virtual void	OnMouseLButton(bool bDown, float x, float y) { _OnMouseLButton(bDown, x, y); }
		virtual void	OnMouseOver(bool bOver)			{ m_bMouseOver = bOver; }
		virtual void	OnMouseMove(float x, float y)	{ m_mouseY = y; }
		virtual void	OnMouseWheel(int notches)		{ int topItem = m_topItem - notches; SetTopItem(topItem); NotifyParent(CMT_LIST_ITEM_ROLL); }
		virtual void	OnKeyClick(int key, const char *str) { _OnKeyClick(key, str); }
		virtual int		GetType()						{ return GGT_ListBox; }

	private:
		GGE_EXPORT	void	_CreateListBoxData();
		GGE_EXPORT	void	_DeleteListBoxData();
		GGE_EXPORT	void	_OnRender();
		GGE_EXPORT	void	_OnMouseLButton(bool bDown, float x, float y);
		GGE_EXPORT	void	_OnKeyClick(int key, const char *str);

		struct				ggeGuiListBoxData;
		ggeGuiListBoxData	*m_listBoxData;

		ggeGuiRenderState	m_pressRS;
		ggeGuiRenderState	m_mouseOverRS;

		bool	m_bMouseOver;
		float	m_mouseY;

		int		m_selectedItem;
		int		m_topItem;
	};
}