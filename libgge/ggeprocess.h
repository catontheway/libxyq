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
\brief Process模块，用于游戏中的并行处理。
*/

#pragma once
#include "ggetypes.h"
#include "ggerefcounter.h"

namespace gge
{
	class ggeProcessManager;

	/// 进程基类
	class ggeProcess : public ggeRefCounter
	{
	public:
		ggeProcess():m_type(-1), m_bKill(false), m_bActive(true), m_bPause(false), 
			m_bInitialize(false), m_bAttache(false), m_manager(0), m_next(0) {}

		virtual ~ggeProcess()					{ GGE_RELEASE(m_next); }

		/// 杀死当前进程
		virtual void	Kill()					{ m_bKill = true; }
		/// 进程是否已死
		virtual bool	IsDead()				{ return m_bKill; }

		/// 设置进程类型，默认为-1
		virtual void	SetType(int type)		{ m_type = type; }
		/// 得到进程类型
		virtual int		GetType()				{ return m_type; }

		/// 设置进程是否激活
		virtual void	SetActive(bool b)		{ m_bActive = b; }
		/// 进程是否激活
		virtual bool	IsActive()				{ return m_bActive; }

		/// 进程管理器加入/移除该进程时调用
		virtual void	SetAttached(bool b)		{ m_bAttache = b; }
		/// 进程是否被加到进程管理器
		virtual bool	IsAttached()			{ return m_bAttache;}

		/// 切换暂停
		virtual void	TogglePause()			{ m_bPause = !m_bPause; }
		/// 是否暂停
		virtual bool	IsPaused()				{ return m_bPause; }

		/// 进程是否已初始化
		virtual bool	IsInitialized()			{ return !m_bInitialize; }

		/// 返回下个进程
		virtual ggeProcess*	GetNext()			{ return m_next; }
		/** @brief 设置当前进程结束后下一个要执行的进程
		    @note 返回值为下个进程，示例：\n
		    npcProcess->SetNext(new WalkToDoor)->SetNext(new OpenDoor)->SetNext(new WalkToTable);
		*/
		virtual ggeProcess*	SetNext(ggeProcess *next) { if (next) next->AddRef(); m_next = next; return next; }

		/// 刷新时调用
		virtual void	OnUpdate(float dt)		{}
		/// 初始化时调用
		virtual void	OnInitialize()			{}
		/** @brief 收到消息时调用，返回true则表示消息已处理，不再传给别的进程\n
		    @param msgType 消息类型
			@param msgData 消息数据
		*/
		virtual bool	OnMessage(int msgType, void *msgData) { return false; }

		/// 返回该进程的管理器
		ggeProcessManager* GetManager()			{ return m_manager; }

	private:
		int				m_type;
		bool			m_bKill;
		bool			m_bActive;
		bool			m_bPause;
		bool			m_bInitialize;
		bool			m_bAttache;
		ggeProcess		*m_next;

	private:	
		ggeProcessManager	*m_manager;
		ggeProcess(const ggeProcess &rhs);
		ggeProcess& operator = (const ggeProcess& val);
		friend class ggeProcessManagerImp;
	};

	/// 进程管理器
	class ggeProcessManager : public ggeRefCounter
	{
	public:
		/// 附加一个进程到管理器
		virtual void	Attach(ggeProcess *process) = 0;

		/// 刷新管理器
		virtual void	Update(float dt) = 0;

		/// 清空进程表
		virtual void	ClearProcessList() = 0;

		/// 进程表中是否有进程
		virtual bool	HasProcesses() = 0;

		/// 获得某类型进程数，若type为-1返回所有进程数
		virtual int		GetProcessCount(int type = -1) = 0;

		/// 是否有指定类型的进程被激活
		virtual bool	IsProcessActive(int type) = 0;

		/// 杀死所有指定类型的进程
		virtual void	KillProcess(int type) = 0;

		/// 发送消息给指定类型的进程，若消息被处理，则返回true。type = -1则发给所有进程
		virtual bool	SendMsg(int msgType, void *msgData = 0, int type = -1) = 0;

		/// 发送消息到消息队列，所有消息在下次调用Update时发送到指定进程。type = -1则发给所有进程
		virtual void	PostMsg(int msgType, void *msgData = 0, int type = -1) = 0;

		/// 设置用户数据
		virtual void	SetUserDate(void *data) = 0;

		/// 获得用户数据
		virtual void*	GetUserData() = 0;
	};

	/// 返回状态管理器
	GGE_EXPORT ggeProcessManager*  Process_CreateManager();
}