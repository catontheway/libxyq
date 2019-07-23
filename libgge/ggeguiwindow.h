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
\brief GUI模块
*/

#pragma once
#include <string>
#include "ggemath.h"
#include "ggerefcounter.h"
#include "ggevariant.h"
#include "ggetexture.h"
#include "ggefont.h"
#include "ggesprite.h"

namespace gge
{
	/// GUI类型
	enum GGE_GUI_TYPE
	{
		GGT_Window,		///< Window
		GGT_Button,		///< Button
		GGT_CheckButton,///< CheckButton
		GGT_Slider,		///< Slider
		GGT_ListBox,	///< ListBox
		GGT_EditBox,	///< EditBox
		GGT_RichText,	///< RichText
		GGT_Last,
		GGT_FORCE32BIT = 0x7FFFFFFF,
	};

	/// 子控件消息类型
	enum CHILD_MESSAGE_TYPE
	{
		CMT_MOUSE_ENTER,			///< 鼠标移到控件上
		CMT_MOUSE_LEAVE,			///< 鼠标从控件上移走
		CMT_MOUSE_MOVE,				///< 鼠标移动
		CMT_MOUSE_LBUTTON_DOWN,		///< 鼠标左键按下
		CMT_MOUSE_LBUTTON_UP,		///< 鼠标左键抬起
		CMT_MOUSE_RBUTTON_DOWN,		///< 鼠标右键按下
		CMT_MOUSE_RBUTTON_UP,		///< 鼠标右键抬起
		CMT_MOUSE_WHEEL,			///< 鼠标滚轮移动
		CMT_KEY_CLICK,				///< 键盘按下

		CMT_GAIN_FOCUSE,			///< 获得焦点
		CMT_LOST_FOCUSE,			///< 失去焦点
		CMT_BUTTON_CLICKED,			///< 点击Button
		CMT_CHECKBUTTON_TOGGLED,	///< CheckButton状态改变
		CMT_EDIT_TEXT_CHANGED,		///< EditBox内容改变
		CMT_SLIDER_VALUE_CHANGED,	///< Slider数值变化
		CMT_SLIDER_BAR_MOVED,		///< Slider滑块移动
		CMT_LIST_ITEM_CLICKED,		///< ListBox点击项
		CMT_LIST_ITEM_CHANGED,		///< ListBox选中项改变
		CMT_LIST_TOP_ITEM_CHANGED,	///< ListBox顶部项目改变
		CMT_LIST_ITEM_ROLL,			///< ListBox项目滚动
		CMT_RICH_TEXT_HYPER_LINK,	///< RichText点击超链接
		CMT_LAST,
		CMT_FORCE32BIT = 0x7FFFFFFF,
	};

	/// GUI渲染状态
	enum GUI_RENDER_STATE_TYPE
	{
		GRST_NORMAL,				///< 普通状态
		GRST_PRESS,					///< 按下状态
		GRST_MOUSEOVER,				///< 鼠标经过状态
		GRST_DISABLE,				///< 无效状态
		GRST_CHECKED_NORMAL,		///< 选中普通状态
		GRST_CHECKED_PRESS,			///< 选中按下状态
		GRST_CHECKED_MOUSEOVER,		///< 选中鼠标经过状态
		GRST_CHECKED_DISABLE,		///< 选中无效状态
		GRST_LAST,
		GRST_FORCE32BIT = 0x7FFFFFFF,
	};

	/// GUI纹理渲染方式
	enum GUI_TEXTURE_RENDER_TYPE
	{
		GTRT_NORMAL,		///< 正常
		GTRT_STRETCH,		///< 拉伸
		GTRT_STRETCH_H,		///< 水平拉伸，可设置左、右非拉伸区域
		GTRT_STRETCH_V,		///< 垂直拉伸，可设置上、下非拉伸区域
		GTRT_STRETCH_RECT,	///< 矩形拉伸，可设置上、下、左、右非拉伸区域
		GTRT_TILE,			///< 平铺
		GTRT_LAST,
		GTRT_FORCE32BIT = 0x7FFFFFFF,
	};

	/// GUI创建信息
	class ggeGuiCreateInfo : public ggeRefCounter
	{
	public:
		/// 返回ID
		virtual int GetID() = 0;
		/// 返回控件尺寸
		virtual const ggeRect& GetRect() = 0;
		/// 返回控件类型 @see GGE_GUI_TYPE
		virtual int GetType() = 0;
		/// 返回名字
		virtual const char* GetName() = 0;
		/// 返回自定义属性对应的值，如果没则有返回0
		virtual ggeVariant* GetValue(const char *key) = 0;
		/// 返回自定义控件类名
		virtual const char* GetClassName() = 0;
	};

	/// GUI渲染状态
	class ggeGuiRenderState
	{
	public:
		/// 构造函数
		ggeGuiRenderState() : m_texRT(GTRT_NORMAL), m_texture(0), m_texRect(0, 0, 0, 0), 
			m_texColor(0xFFFFFFFF), m_topTexSize(0), m_bottomTexSize(0), m_leftTexSize(0), m_rightTexSize(0), 
			m_fontColor(0xFFFFFFFF), m_fontBColor(0xFF000000), m_fontSColor(0), m_fontOffsetX(0), m_fontOffsetY(0){}
		/// 构造函数
		ggeGuiRenderState(const ggeGuiRenderState &val) :
		m_texRT(val.m_texRT), m_texture(val.m_texture), m_texRect(val.m_texRect), 
			m_texColor(val.m_texColor), m_topTexSize(val.m_topTexSize), m_bottomTexSize(val.m_bottomTexSize), 
			m_leftTexSize(val.m_leftTexSize), m_rightTexSize(val.m_rightTexSize), m_fontColor(val.m_fontColor), 
			m_fontBColor(val.m_fontBColor), m_fontSColor(val.m_fontSColor), m_fontOffsetX(val.m_fontOffsetX), 
			m_fontOffsetY(val.m_fontOffsetY) { if (m_texture) m_texture->AddRef(); }
		/// 赋值函数
		ggeGuiRenderState& operator = (const ggeGuiRenderState &val)
		{
			if (this == &val) return *this;
			GGE_RELEASE(m_texture);

			m_texRT = val.m_texRT;
			m_texture = val.m_texture;
			m_texRect = val.m_texRect; 
			m_texColor = val.m_texColor;
			m_topTexSize = val.m_topTexSize;
			m_bottomTexSize = val.m_bottomTexSize;
			m_leftTexSize = val.m_leftTexSize;
			m_rightTexSize = val.m_rightTexSize;
			m_fontColor = val.m_fontColor;
			m_fontBColor = val.m_fontBColor;
			m_fontSColor = val.m_fontSColor;
			m_fontOffsetX = val.m_fontOffsetX;
			m_fontOffsetY = val.m_fontOffsetY;
			if (m_texture) m_texture->AddRef();

			return *this;
		}

		~ggeGuiRenderState()
		{
			GGE_RELEASE(m_texture);
		}

		/// 设置纹理渲染方式
		void SetTexRenderType(GUI_TEXTURE_RENDER_TYPE rt)	{ m_texRT = rt; }
		/// 返回纹理渲染方式
		GUI_TEXTURE_RENDER_TYPE GetTexRenderType() const	{ return m_texRT; }

		/// 设置纹理
		void SetTexture(ggeTexture *tex)	{ GGE_RELEASE(m_texture); if (tex) tex->AddRef(); m_texture = tex; }
		/// 返回纹理
		ggeTexture* GetTexture() const		{ return m_texture; }
		/// 设置纹理区域
		void SetTexRect(const ggeRect &rt)	{ m_texRect = rt; }
		/// 返回纹理区域
		const ggeRect& GetTexRect() const	{ return m_texRect; }
		/// 设置纹理颜色
		void SetTexColor(guint32 color)		{ m_texColor = color; }
		/// 返回纹理颜色
		guint32 GetTexColor() const			{ return m_texColor; }

		/// 设置非拉伸或平铺区域
		void SetTopTexSize(float v)			{ m_topTexSize = v; }
		/// 返回非拉伸或平铺区域
		float GetTopTexSize() const			{ return m_topTexSize; }
		/// 设置非拉伸或平铺区域
		void SetBottomTexSize(float v)		{ m_bottomTexSize = v; }
		/// 返回非拉伸或平铺区域
		float GetBottomTexSize() const		{ return m_bottomTexSize; }
		/// 设置非拉伸或平铺区域
		void SetLeftTexSize(float v)		{ m_leftTexSize = v; }
		/// 返回非拉伸或平铺区域
		float GetLeftTexSize() const		{ return m_leftTexSize; }
		/// 设置非拉伸或平铺区域
		void SetRightTexSize(float v)		{ m_rightTexSize = v; }
		/// 返回非拉伸或平铺区域
		float GetRightTexSize() const		{ return m_rightTexSize; }

		/// 设置字体颜色
		void SetFontColor(guint32 color)	{ m_fontColor = color; }
		/// 返回字体颜色
		guint32 GetFontColor() const		{ return m_fontColor; }
		/// 设置字体边框颜色
		void SetFontBColor(guint32 color)	{ m_fontBColor = color; }
		/// 返回字体边框颜色
		guint32 GetFontBColor() const		{ return m_fontBColor; }
		/// 设置字体阴影颜色
		void SetFontSColor(guint32 color)	{ m_fontSColor = color; }
		/// 返回字体阴影颜色
		guint32 GetFontSColor() const		{ return m_fontSColor; }
		///< 字体显示时相对控件左上角偏移量
		void SetFontOffsetX(float v)		{ m_fontOffsetX = v; }
		///< 字体显示时相对控件左上角偏移量
		float GetFontOffsetX() const		{ return m_fontOffsetX; }
		///< 字体显示时相对控件左上角偏移量
		void SetFontOffsetY(float v)		{ m_fontOffsetY = v; }
		///< 字体显示时相对控件左上角偏移量
		float GetFontOffsetY() const		{ return m_fontOffsetY; }

	private:
		GUI_TEXTURE_RENDER_TYPE	m_texRT;

		ggeTexture	*m_texture;
		ggeRect		m_texRect;
		guint32		m_texColor;

		float		m_topTexSize;
		float		m_bottomTexSize;
		float		m_leftTexSize;
		float		m_rightTexSize;

		guint32		m_fontColor;
		guint32		m_fontBColor;
		guint32		m_fontSColor;
		float		m_fontOffsetX;
		float		m_fontOffsetY;
	};

	/// GUI字体状态
	struct ggeGuiFontState
	{
		/// 构造函数
		ggeGuiFontState() : alignMode(TEXT_LEFT), bTextWarp(false), lineSpace(0), charSpace(0) {}
		/// 构造函数
		ggeGuiFontState(int _alignMode, bool _bTextWarp, int _lineSpace, int _charSpace) :
			alignMode(_alignMode), bTextWarp(_bTextWarp), lineSpace(_lineSpace), charSpace(_charSpace) {}

		int alignMode;	///< 对齐模式
		bool bTextWarp;	///< 自动换行
		int lineSpace;	///< 行间距
		int charSpace;	///< 字间距
	};

	/// Window 控件
	class ggeGuiWindow : public ggeRefCounter
	{
	public:
		/**
		@brief 构造函数
		@param id 控件ID
		@param rect 控件尺寸：ggeRect(X坐标, Y坐标, 宽度, 高度)
		*/
		ggeGuiWindow(int id = -1, const ggeRect &rect = ggeRect(0, 0, 32.0f, 32.0f)) : 
		  m_id(id), m_rect(rect), m_next(0), m_prev(0), m_parent(0),m_bStatic(false), m_bVisible(true), 
			  m_bEnabled(true), m_firstChild(0), m_lastChild(0), m_bNotifyParent(false), m_bClipping(false),
			  m_font(0), m_tooltipWidth(0), m_createInfo(0)
		  {
			  _CreateWindowData();
			  m_spr = Sprite_Create(0);
			  SetWidth(m_rect.x2);
			  SetHeight(m_rect.y2);
		  }

		/// 析构函数
		virtual ~ggeGuiWindow()
		{
			RemoveAllCtrl();
			GGE_RELEASE(m_font);
			GGE_RELEASE(m_spr);
			GGE_RELEASE(m_createInfo);
			_DestroyWnd();
			_DeleteWindowData();
		}
		
		/// 设置控件ID
		virtual void	SetID(int id)					{ m_id = id; }
		/// 返回控件ID
		int				GetID()							{ return m_id; }
		/// 设置控件名字
		virtual void	SetName(const char *name)		{ _SetName(name); }
		/// 返回控件名字
		const char*		GetName()						{ return _GetName(); }
		/// 设置控件ToolTip
		virtual void	SetToolTip(const char *str)		{ _SetToolTip(str); }
		/// 返回控件ToolTip
		const char*		GetToolTip()					{ return _GetToolTip(); }
		/// 设置ToolTip宽度，默认为0，为0时自适应设置的ToolTip字符宽度
		void			SetToolTipWidth(guint16 w)		{ m_tooltipWidth = w; }
		/// 返回ToolTip宽度
		guint16			GetToolTipWidth()				{ return m_tooltipWidth; }

		/// 设置坐标
		virtual	void	SetPos(float x, float y, bool bMoveChild = true) { _SetPos(x, y, bMoveChild); }
		/// 返回x坐标
		float			GetPosX()				{ return m_rect.x1; }
		/// 返回y坐标
		float			GetPosY()				{ return m_rect.y1; }
		/// 设置宽度
		virtual void	SetWidth(float width)	{ m_rect.SetWidth(width); }
		/// 返回宽度
		float			GetWidth()				{ return m_rect.GetWidth(); }
		/// 设置高度
		virtual void	SetHeight(float height)	{ m_rect.SetHeight(height); }
		/// 返回高度
		float			GetHeight()				{ return m_rect.GetHeight(); }
		/// 设置控件矩形坐标
		virtual void	SetRect(const ggeRect &rt, bool bMoveChild = true) { _SetRect(rt, bMoveChild); }
		/// 返回控件矩形坐标
		ggeRect&		GetRect()				{ return m_rect; }
		/// 设置收到键盘鼠标消息时是否先通知父控件，如果父控件未接收才发送到本控件处理，默认为false
		void			SetNotifyParent(bool b)	{ m_bNotifyParent = b; }
		/// 返回收到键盘鼠标消息时是否先通知父控件
		bool			IsNotifyParent()		{ return m_bNotifyParent; }
		/// 设置剪裁
		void			SetClipping(bool b)		{ m_bClipping = b; }
		/// 返回是否剪裁
		bool			IsClipping()			{ return m_bClipping; }

		/// 设为静态控件，静态控件不会接收键盘鼠标消息，不能设置焦点，默认为false
		void	SetStatic(bool b)	{ m_bStatic = b; }
		/// 是否是静态控件
		bool	IsStatic()			
		{ 
			if (GetParent() && GetParent()->IsStatic()) return true;
			return m_bStatic; 
		}
		/// 设置是否可见，如果控件不可见，不会接收键盘鼠标消息，不能设置焦点，也不会渲染，默认为true
		void	SetVisible(bool b)	{ m_bVisible = b; }
		/// 是否可见
		bool	IsVisible()	
		{ 
			if (GetParent() && !GetParent()->IsVisible()) return false;
			return m_bVisible; 
		}
		/// 设置是否有效，如果控件无效不会接收键盘鼠标消息，不能设置焦点，也不会刷新，默认为true
		void	SetEnabled(bool b)	{ m_bEnabled = b;  }
		/// 是否有效
		bool	IsEnabled()
		{ 
			if (GetParent() && !GetParent()->IsEnabled()) return false;
			return m_bEnabled; 
		}
		/// 设置文本
		virtual void		SetText(const char *text)	{ _SetText(text); }
		/// 返回文本
		virtual const char*	GetText()			{ return _GetText(); }
		/// 设置对齐模式，默认为 TEXT_LEFT @see FONT_ALIGN
		virtual void		SetAlignMode(int v)	{ m_fontState.alignMode = v; }
		/// 返回对齐模式
		int					GetAlignMode()		{ return m_fontState.alignMode; }
		/// 设置是否自动换行，默认为false
		virtual void		SetTextWarp(bool b)	{ m_fontState.bTextWarp = b; }
		/// 返回是否自动换行
		bool				IsTextWarp()		{ return m_fontState.bTextWarp; }
		/// 设置行间距
		virtual void		SetLineSpace(int v) { m_fontState.lineSpace = v; }
		/// 返回行间距
		int					GetLineSpace()		{ return m_fontState.lineSpace; }
		/// 设置字间距
		virtual void		SetCharSpace(int v) { m_fontState.charSpace = v; }
		/// 返回字间距
		int					GetCharSpace()		{ return m_fontState.charSpace; }
		/// 设置字体状态
		virtual void		SetFontState(const ggeGuiFontState &fontRS) { m_fontState = fontRS; }
		/// 返回字体状态
		const ggeGuiFontState& GetFontState()	{ return  m_fontState; }
		
		/// 获得第一个子控件
		ggeGuiWindow*	GetFirstChildCtrl()	{ return m_firstChild; }
		/// 获得最后一个子控件
		ggeGuiWindow*	GetLastChildCtrl()	{ return m_lastChild; }
		/// 返回前一个控件
		ggeGuiWindow*	GetPrevCtrl()		{ return m_prev; }
		/// 返回后一个控件
		ggeGuiWindow*	GetNextCtrl()		{ return m_next; }
		/// 返回父控件 
		ggeGuiWindow*	GetParent()			{ return m_parent; }
		/// 设置为顶层控件
		virtual void	SetTop()			{ _SetTop(); }
		/// 设置为焦点控件
		virtual void	SetFocus()			{ _SetFocus(); }

		/**
		@brief 添加一个控件，添加失败返回false
		@param ctrl 要添加的控件
		@param bAdjustPos 调整到相对于父控件的坐标
		@return 成功返回true，失败返回false
		*/
		GGE_EXPORT	bool			AddCtrl(ggeGuiWindow *ctrl, bool bAdjustPos = false);
		/// 移除控件
		GGE_EXPORT	void			RemoveCtrl(ggeGuiWindow *ctrl);
		/// 移除所有控件
		GGE_EXPORT	void			RemoveAllCtrl();
		/// 查找第一个指定ID的控件，bTraversal指定是否遍历所有子控件
		GGE_EXPORT	ggeGuiWindow*	FindCtrl(int id, bool bTraversal = false);
		/// 查找第一个指定名字的控件，bTraversal指定是否遍历所有子控件
		GGE_EXPORT	ggeGuiWindow*	FindCtrl(const char *name, bool bTraversal = false);
		/// 查找指定位置第一个可见控件
		virtual		ggeGuiWindow*	FindCtrlFromPoint(float x, float y)	{ return _FindCtrlFromPoint(GetLastChildCtrl(), x, y); }
		/// 控件是否是该窗口的子控件，bTraversal指定是否遍历所有子控件
		GGE_EXPORT	bool			IsChild(ggeGuiWindow *ctrl, bool bTraversal = false);
		/// 该窗口是否是控件的子控件
		GGE_EXPORT	bool			IsParent(ggeGuiWindow *ctrl);
		/**
		@brief 发送消息给子控件
		@param msgType 消息类型
		@param msgData 消息数据
		@param bTraversal 如果为false，只发送消息给第一层子控件，如果为true，则发送消息给所有子控件
		*/
		bool						SendChildMsg(int msgType, void *msgData = 0, bool bTraversal = false) { return _SendChildMsg(this, m_lastChild, msgType, msgData, bTraversal); }
		/**
		@brief 发送消息给父控件
		@param msgType 消息类型
		@param msgData 消息数据
		*/
		GGE_EXPORT	bool			SendParentMsg(int msgType, void *msgData = 0);
		/**
		@brief 通知父控件
		@param msgType 消息类型 @see CHILD_MESSAGE_TYPE
		*/
		virtual bool				NotifyParent(int msgType)	{ if (GetParent()) return GetParent()->OnChildMsg(msgType, this); return false; }

		/// 设置字体
		virtual void				SetFont(ggeFont *font)		{ GGE_RELEASE(m_font); if (font) font->AddRef(); m_font = font; }
		/// 返回字体
		virtual ggeFont*			GetFont()					{ return m_font; }
		/// 设置渲染状态
		virtual void				SetRenderState(GUI_RENDER_STATE_TYPE rt, const ggeGuiRenderState &rs)
		{
			switch (rt)
			{
			case GRST_NORMAL:
				m_normalRS = rs;
				break;

			case GRST_DISABLE:
				m_disableRS = rs;
				break;
			}
		}
		/// 返回渲染状态
		virtual ggeGuiRenderState*	GetRenderState(GUI_RENDER_STATE_TYPE rt)
		{
			switch (rt)
			{
			case GRST_NORMAL:
				return &m_normalRS;

			case GRST_DISABLE:
				return &m_disableRS;
			}

			return 0;
		}
		/// 返回当前渲染状态
		virtual ggeGuiRenderState*	GetCurRenderState()
		{
			if (IsEnabled())
				return GetRenderState(GRST_NORMAL); 

			return GetRenderState(GRST_DISABLE);
		}
		/// 绘制纹理
		GGE_EXPORT void	RenderTexture(const ggeGuiRenderState &rs, const ggeRect &rt);
		/// 绘制字体
		GGE_EXPORT void	RenderFont(const ggeGuiRenderState &rs, ggeFont *font, const char *str, float x, float y, float lineWidth, const ggeGuiFontState &fontRS);
		/// 绘制控件纹理
		virtual void	RenderCtrlTexture(const ggeGuiRenderState &rs)	{ RenderTexture(rs, GetRect()); }
		/// 绘制控件字体
		virtual void	RenderCtrlFont(const ggeGuiRenderState &rs)		{ RenderFont(rs, GetFont(), GetText(), GetPosX(), GetPosY(), GetWidth(), GetFontState()); }
		/// 刷新
		virtual void	Update(float dt)								{ _Update(dt); }
		/// 渲染
		virtual void	Render()										{ _Render(); }

	public:
		/// 渲染控件
		virtual void	OnRender() { ggeGuiRenderState *rs = GetCurRenderState(); if (rs) { RenderCtrlTexture(*rs); RenderCtrlFont(*rs); } }
		/// 刷新控件
		virtual void	OnUpdate(float dt) {}

		/**
		@brief 在控件得到或失去焦点时调用
		@param bFocused 为true时得到焦点，为false时失去焦点
		*/
		virtual void	OnFocus(bool bFocused) {}
		/**
		@brief 鼠标进入或离开控件区域时调用
		@param bOver 为true时进入控件，为false时离开控件
		*/
		virtual void	OnMouseOver(bool bOver) {}
		/**
		@brief 鼠标在控件上移动时调用
		@param x 鼠标X坐标
		@param y 鼠标Y坐标
		*/
		virtual void	OnMouseMove(float x, float y) {}
		/**
		@brief 鼠标左键状态改变时调用
		@param bDown 鼠标按键是否按下
		@param x 鼠标X坐标
		@param y 鼠标Y坐标
		*/
		virtual void	OnMouseLButton(bool bDown, float x, float y) {}
		/**
		@brief 鼠标右键状态改变时调用
		@param bDown 鼠标按键是否按下
		@param x 鼠标X坐标
		@param y 鼠标Y坐标
		*/
		virtual void	OnMouseRButton(bool bDown, float x, float y) {}
		/**
		@brief 鼠标滚轮值改变时调用
		@param notches 滚轮值，向前滚动为正，向后滚动为负
		*/
		virtual void	OnMouseWheel(int notches)	{}
		/**
		@brief 键盘按下时调用
		@param key 键值
		@param str 字符串
		*/
		virtual void	OnKeyClick(int key, const char* str) {}
		/**
		@brief 收到消息时调用
		@param ctrl 发出消息的控件
		@param msgType 消息类型
		@param msgData 消息数据
		@return 如果接收该消息返回true，否则返回false
		*/
		virtual bool	OnMessage(ggeGuiWindow *ctrl, int msgType, void *msgData = 0) { return false; }
		/**
		@brief 收到子控件消息时调用
		@param msgType 消息类型 @see CHILD_MESSAGE_TYPE
		@param ctrl 发出消息的控件
		@return 如果接收该消息返回true，否则返回false
		*/
		virtual bool	OnChildMsg(int msgType, ggeGuiWindow *ctrl) { if (GetParent()) return GetParent()->OnChildMsg(msgType, ctrl); return false; }
		/// 返回控件类型 @see GGE_GUI_TYPE
		virtual int		GetType() { return GGT_Window; }
		
		/// 返回创建信息
		ggeGuiCreateInfo* GetCreateInfo() { return m_createInfo; }

	private:
		int				m_id;
		ggeRect			m_rect;
		bool			m_bStatic;
		bool			m_bVisible;
		bool			m_bEnabled;
		bool			m_bNotifyParent;
		bool			m_bClipping;
		guint16			m_tooltipWidth;
		ggeGuiFontState	m_fontState;

		ggeGuiWindow	*m_next;
		ggeGuiWindow	*m_prev;
		ggeGuiWindow	*m_parent;
		ggeGuiWindow	*m_firstChild;
		ggeGuiWindow	*m_lastChild;
		ggeFont			*m_font;
		ggeSprite		*m_spr;

		ggeGuiRenderState	m_normalRS;
		ggeGuiRenderState	m_disableRS;
		ggeGuiCreateInfo	*m_createInfo;

		struct				ggeGuiWindowData;
		ggeGuiWindowData	*m_wndData;

	private:
		GGE_EXPORT	void			_CreateWindowData();
		GGE_EXPORT	void			_DeleteWindowData();
		GGE_EXPORT	void			_DestroyWnd();
		GGE_EXPORT	void			_SetName(const char *name);
		GGE_EXPORT	const char*		_GetName();
		GGE_EXPORT	void			_SetToolTip(const char *str);
		GGE_EXPORT	const char*		_GetToolTip();
		GGE_EXPORT	void			_SetText(const char *text);
		GGE_EXPORT	const char*		_GetText();
		GGE_EXPORT	void			_SetPos(float x, float y, bool bMoveChild);
		GGE_EXPORT	void			_SetRect(const ggeRect &rt, bool bMoveChild);
		GGE_EXPORT	void			_SetTop();
		GGE_EXPORT	void			_SetFocus();
		GGE_EXPORT	void			_RemoveCtrl(ggeGuiWindow *ctrl);
		GGE_EXPORT	ggeGuiWindow*	_FindCtrlFromPoint(ggeGuiWindow* ctrl, float x, float y);
		GGE_EXPORT	bool			_SendChildMsg(ggeGuiWindow *sendctrl, ggeGuiWindow *ctrl, int msgType, void *msgData, bool bTraversal);
		GGE_EXPORT	void			_Update(float dt);
		GGE_EXPORT	void			_Render();

	private:
		ggeGuiWindow(const ggeGuiWindow &val);
		ggeGuiWindow& operator = (const ggeGuiWindow &val);
		friend class ggeGUILoaderImp;
	};


}