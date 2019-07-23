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
\brief 游戏状态管理器
*/

#pragma once
#include "ggetypes.h"
#include "ggerefcounter.h"

namespace gge
{
	class ggeGameStateManager;

	/// 状态基类
	class ggeGameState : public ggeRefCounter
	{
	public:
		ggeGameState()					{ m_manager = 0; }
		virtual ~ggeGameState()			{}

		/// 进入该状态时调用
		virtual void OnEnter()			{}

		/// 离开该状态时调用
		virtual void OnLeave()			{}

		/// 刷新
		virtual void OnUpdate(float dt)	{}

		/// 渲染
		virtual void OnRender()			{}

		/** @brief 收到消息时调用，返回true则表示消息已处理，不再传给别的状态
		    @param msgType 消息类型
			@param msgData 消息数据
		*/
		virtual bool OnMessage(int msgType, void *msgData = 0) { return false; }

		/// 返回该状态的管理器
		ggeGameStateManager* GetManager()		{ return m_manager; }

	private:
		ggeGameStateManager	*m_manager;
		friend class	ggeGameStateManagerImp;
	};

	/// 状态管理器
	class ggeGameStateManager : public ggeRefCounter
	{
	public:
		/// 增加状态
		virtual bool AddState(const char *stateName, ggeGameState *state) = 0;

		/// 返回状态
		virtual ggeGameState* GetState(const char *stateName) = 0;

		/// 移除状态
		virtual void RemoveState(const char *stateName) = 0;

		/// 移除状态
		virtual void RemoveState(ggeGameState *state) = 0;

		/// 移除所有状态
		virtual void RemoveAllState() = 0;

		/// 改变当前状态
		virtual bool ChangeState(const char *stateName) = 0;

		/// 返回当前状态
		virtual ggeGameState* GetCurrentState() = 0;

		/// 刷新
		virtual void Update(float dt) = 0;

		/// 渲染
		virtual void Render() = 0;

		/** @brief 发送消息
			@param stateName 接收消息的状态名，如果为0则发送给所有状态
		    @param msgType 消息类型
			@param msgData 消息数据
		*/
		virtual bool SendMsg(const char *stateName = 0, int msgType = 0, void *msgData = 0) = 0;
	};

	/// 返回状态管理器
	GGE_EXPORT ggeGameStateManager*  GameState_CreateManager();
}