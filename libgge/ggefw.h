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
\brief 应用程序框架基类\n
	要建立一个简单的游戏应用程序只需继承ggeApplication并提供一个实例即可。

	示例：
	@code
	class CGameMain : public ggeApplication
	{
	public:
		void OnUpdate(float dt)
		{
		}

		void OnRender()
		{
			Graph_BeginScene();
			Graph_Clear();
			//Draw Something...
			Graph_EndScene();
		}
	};

	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
	{
		CGameMain GameMain;
		GameMain.Start();

		return 0;
	}
	@endcode
*/

#pragma once
#include "ggetypes.h"

namespace gge
{
	/// 应用程序框架
	class ggeApplication
	{
	public:
		ggeApplication()						{ m_bExit = false;  _Init(); }
		virtual ~ggeApplication()				{}

	public:
		/// 游戏启动前该函数被调用，如果返回false游戏退出
		virtual bool OnConfig()					{ return true; }

		/// 游戏启动后该函数被调用，如果返回false游戏退出
		virtual bool OnInitiate()				{ return true; }

		/// 游戏退出时前该函数被调用
		virtual void OnRelease()				{}

		/// 刷新
		virtual void OnUpdate(float dt) = 0;

		/// 渲染
		virtual void OnRender() = 0;

		/// 产生Dump时调用，dir为Dump保存目录，可以此处写入一些调试信息到log里，弹出提示窗口等
		virtual void OnMiniDump(const char *dir){}

	public:
		/// 开始运行
		GGE_EXPORT void Start();

		/// 退出游戏
		void Exit()								{ m_bExit = true; }

		/// 是否正在退出游戏
		bool IsExiting()						{ return m_bExit; }

		/// 开启MiniDump，如果开启MiniDump必须保证程序目录或系统目录下存在"dbghelp.dll"
		GGE_EXPORT void EnableMiniDump();

	private:
		bool m_bExit;

	private:
		GGE_EXPORT void _Init();
		GGE_EXPORT bool _Update(float dt);
		friend class ggeAppInstance;
	};
}