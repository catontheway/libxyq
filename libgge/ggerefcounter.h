/*
**  =======================================================
**                Galaxy2D Game Engine       
**                                
**       版权所有(c) 2005 沈明. 保留所有权利.
**    主页地址: http://www.cnblogs.com/jianguhan/
**			 电子邮箱: jianguhan@126.com
**  =======================================================
*/

/** \file
\brief 引用计数模块
*/

#pragma once

namespace gge
{
	class ggeRefCounter;

	/// 自定义资源释放句柄,主要用于资源管理,例如回收某些资源到内存池等
	class ggeResReleaseHandler
	{
	public:
		/// 析构函数
		virtual ~ggeResReleaseHandler() {}

		/// 自定义资源释放函数
		virtual void OnRelease(ggeRefCounter *p) = 0;
	};

	/// 引用计数模块
	class ggeRefCounter
	{
	public:
		/// 构造函数
		ggeRefCounter() : m_refCount(1), m_releaseHandler(0) {}
		/// 析构函数
		virtual ~ggeRefCounter() {}

		/**
		@brief 加引用
		@note 如果外部需要长期引用该资源,则需要手动调用该函数,并在资源不再使用时调用 Release() 函数.
		*/
		void AddRef()	{ m_refCount++; }

		/**
		@brief 减引用并释放资源
		@note 一般来说只有Create*接口创建出来的资源需要调用该函数,Get*接口返回的资源不需要调用该函数并且返回的资源只能在局部域里使用,如果需要长期引用该资源需要手动调用 AddRef() 函数
		*/
		void Release()	
		{
			m_refCount--;

			if (m_releaseHandler) 
			{
				m_releaseHandler->OnRelease(this);
			}
			else if (m_refCount == 0)
			{
				delete this;
			}
		}

		/// 返回引用数
		int GetRefCount() const
		{
			return m_refCount;
		}

		/// 自定义资源释放句柄
		void SetReleaseHandler(ggeResReleaseHandler *handler)
		{
			m_releaseHandler = handler;
		}

	private:
		ggeResReleaseHandler	*m_releaseHandler;
		mutable int				m_refCount;
	};
}

