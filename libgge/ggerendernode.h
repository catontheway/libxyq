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
\brief 渲染节点
*/

#pragma once
#include "ggerefcounter.h"
#include "ggemath.h"
#include "ggematrix.h"

namespace gge
{
	class ggeRenderNode : public ggeRefCounter
	{
	public:
		ggeRenderNode() : m_nodeID(-1), m_zOrder(0), m_localOrder(0), m_childOrder(1), m_bValid(true), m_bVisible(true), m_bNeedSort(false), 
			m_parent(0), m_userData(0), m_bUpdateLocalTransform(true), m_bUpdateWorldTransform(true), m_scale(1.0f, 1.0f, 1.0f)
		{
			_CreateNodeData();
		}

		~ggeRenderNode()
		{
			RemoveAllChild();
			if (GetParent()) 
				GetParent()->_RemoveFromChildList(this);

			_DeleteNodeData();
		}

		/// 返回父节点
		ggeRenderNode* GetParent() const { return m_parent; }

		/// 返回根节点
		GGE_EXPORT ggeRenderNode* GetRoot() const;

		/// 添加子节点
		GGE_EXPORT void AddChild(ggeRenderNode *node);

		/// 移除子节点
		GGE_EXPORT void RemoveChild(ggeRenderNode *node);

		/// 移除所有子节点
		GGE_EXPORT void RemoveAllChild();

		/// 从父节点中移除
		GGE_EXPORT void RemoveFromParent();

		/// 返回子节点数量
		GGE_EXPORT guint32 GetChildCount() const;

		/// 返回子节点
		GGE_EXPORT ggeRenderNode* GetChild(guint32 pos) const;

		/// 查找子节点
		GGE_EXPORT ggeRenderNode* FindChild(int id) const;
		
	public:
		/// 刷新，bUpdateTransform表示是否要刷新当前节点和子节点的变换矩阵
		virtual	void Update(float dt, bool bUpdateTransform = false)				
		{ 
			_Update(dt, bUpdateTransform);
		}

		/// 渲染
		virtual	void Render()						
		{ 
			if (IsVisible())
			{
				if (GetChildCount() > 0)
				{
					_Render();
				}
				else
				{
					OnRender(m_parentTransform);
				}
			}
		}

		/// 刷新时调用，parentTransform是父节点的变换矩阵，bTransformChanged表示当前节点的变换矩阵已改变
		virtual void OnUpdate(float dt, const ggeMatrix4 &parentTransform, bool bTransformChanged) 
		{
		}

		/// 渲染时调用，transform是当前节点的变换矩阵
		virtual void OnRender(const ggeMatrix4 &transform)
		{
			//Graph_PushTransformMatrix(transform);
			//Render something...
			//Graph_PopTransformMatrix();
		}

	public:
		/// 设置ID
		void			SetID(int id)		{ m_nodeID = id; }
		/// 返回ID
		int				GetID()	const		{ return m_nodeID; }

		/// 设置是否可见
		virtual void	SetVisible(bool b)	{ m_bVisible = b; }
		/// 返回是否可见
		virtual bool	IsVisible() const	{ return m_bVisible; }

		/// 设置ZOrder，默认为0，数值越大越晚渲染，如果<0则表示在父节点之前渲染
		virtual void	SetZOrder(int z)	{ _SetZOrder(z); }
		/// 返回ZOrder
		virtual int		GetZOrder() const	{ return m_zOrder; }

		/// 是否有效，下次刷新时父节点会移除掉所有无效的节点
		virtual bool	IsValid() const		{ return m_bValid; }
		/// 设置为无效状态
		virtual void	Kill()				{ m_bValid = false; }

		/// 设置用户数据
		void			SetUserData(void *v){ m_userData = v; }
		/// 返回用户数据
		void*			GetUserData() const { return m_userData; }

	public:
		/** @name 设置坐标
		*  @{
		*/
		void	SetPosition(float x, float y)				{ m_position.x = x; m_position.y = y; TransformDirty(); }
		void	SetPosition(const ggeVector &v)				{ m_position.x = v.x; m_position.y = v.y; TransformDirty(); }
		void	SetPosition3D(float x, float y, float z)	{ m_position.x = x; m_position.y = y; m_position.z = z; TransformDirty(); }
		void	SetPosition3D(const ggeVector3 &v)			{ m_position = v; TransformDirty(); }

		void	SetPositionX(float x)						{ m_position.x = x; TransformDirty(); }
		void	SetPositionY(float y)						{ m_position.y = y; TransformDirty(); }
		void	SetPositionZ(float z)						{ m_position.z = z; TransformDirty(); }
		/** 
		@} 
		*/

		/** @name 返回坐标
		*  @{
		*/
		float	GetPositionX() const						{ return m_position.x; }
		float	GetPositionY() const						{ return m_position.y; }
		float	GetPositionZ() const						{ return m_position.z; }
		const	ggeVector3& GetPosition3D() const			{ return m_position; }
		/** 
		@} 
		*/

		/** @name 设置缩放
		*  @{
		*/
		void	SetScale(float x, float y)					{ m_scale.x = x;m_scale.y = y; TransformDirty(); }
		void	SetScale(const ggeVector &v)				{ m_scale.x = v.x;m_scale.y = v.y; TransformDirty(); }
		void	SetScale3D(float x, float y, float z)		{ m_scale.x = x;m_scale.y = y;m_scale.z = z; TransformDirty(); }
		void	SetScale3D(const ggeVector3 &v)				{ m_scale = v; TransformDirty(); }

		void	SetScaleX(float x)							{ m_scale.x = x; TransformDirty(); }
		void	SetScaleY(float y)							{ m_scale.y = y; TransformDirty(); }
		void	SetScaleZ(float z)							{ m_scale.z = z; TransformDirty(); }
		/** 
		@} 
		*/

		/** @name 返回缩放
		*  @{
		*/
		const	ggeVector3& GetScale3D() const				{ return m_scale; }
		float	GetScaleX()	const							{ return m_scale.x; }
		float	GetScaleY()	const							{ return m_scale.y; }
		float	GetScaleZ()	const							{ return m_scale.z; }
		/** 
		@} 
		*/

		/** @name 设置旋转
		*  @{
		*/
		void	SetRotation(float v)						{ m_rotation.z = v; TransformDirty(); }
		void	SetRotation3D(float x, float y, float z)	{ m_rotation.x = x; m_rotation.y = y; m_rotation.z = z; TransformDirty(); }
		void	SetRotation3D(const ggeVector3 &v)			{ m_rotation = v; TransformDirty(); }

		void	SetRotationX(float x)						{ m_rotation.x = x; TransformDirty(); }
		void	SetRotationY(float y)						{ m_rotation.y = y; TransformDirty(); }
		void	SetRotationZ(float z)						{ m_rotation.z = z; TransformDirty(); }
		/** 
		@} 
		*/

		/** @name 返回旋转
		*  @{
		*/
		float	GetRotation() const							{ return m_rotation.z; }
		float	GetRotationX() const						{ return m_rotation.x; }
		float	GetRotationY() const						{ return m_rotation.y; }
		float	GetRotationZ() const						{ return m_rotation.z; }
		const	ggeVector3& GetRotation3D() const			{ return m_rotation; }
		/** 
		@} 
		*/
		
		/// 设置本地变换矩阵
		GGE_EXPORT void		SetLocalTransform(const ggeMatrix4 &mat);
		/// 返回本地变换矩阵
		GGE_EXPORT const	ggeMatrix4& GetLocalTransform() const;
		/// 返回世界变换矩阵
		GGE_EXPORT const	ggeMatrix4&	GetWorldTransform() const;
		/// 返回世界到本地的变换矩阵
		GGE_EXPORT const	ggeMatrix4& GetWorldToLocalTransform(ggeMatrix4 &mat) const;

		/// 返回世界坐标
		ggeVector3	GetWorldPosition() const						{ return GetWorldTransform().GetTranslation(); }
		/// 转换矢量到世界坐标
		void		ConvertToWorldPosition(ggeVector &v) const		{ GetWorldTransform().TransformVector(v); }
		/// 转换矢量到世界坐标
		void		ConvertToWorldPosition3D(ggeVector3 &v) const	{ GetWorldTransform().TransformVector3(v); }
		/// 转换矢量到本地坐标
		void		ConvertToNodePosition(ggeVector &v) const		{ ggeMatrix4 mat; GetWorldToLocalTransform(mat).TransformVector(v); }
		/// 转换矢量到本地坐标
		void		ConvertToNodePosition3D(ggeVector3 &v) const	{ ggeMatrix4 mat; GetWorldToLocalTransform(mat).TransformVector3(v); }

	protected:
		GGE_EXPORT	void	Sort();
		void				TransformDirty()	{ m_bUpdateLocalTransform = true; m_bUpdateWorldTransform = true; }
		void				ZOrderDirty()		{ m_bNeedSort = true; }

	protected:
		int		m_nodeID;
		int		m_zOrder;
		int		m_childOrder;
		int		m_localOrder;
		bool	m_bValid;
		bool	m_bVisible;
		bool	m_bNeedSort;
		mutable bool m_bUpdateLocalTransform;
		mutable bool m_bUpdateWorldTransform;
		
		ggeVector3	m_position;
		ggeVector3	m_scale;
		ggeVector3	m_rotation;

		mutable ggeMatrix4 m_localTransform;
		mutable ggeMatrix4 m_worldTransform;
		ggeMatrix4	m_parentTransform;

		ggeRenderNode	*m_parent;
		void			*m_userData;
		void			*m_nodeData;

	protected:
		GGE_EXPORT	void	_Update(float dt, bool bUpdateTransform);
		GGE_EXPORT	void	_Render();

	private:
		friend		bool	_RenderNodeComparison(const ggeRenderNode *node1, const ggeRenderNode *node2);
		GGE_EXPORT	void	_CreateNodeData();
		GGE_EXPORT	void	_DeleteNodeData();

		GGE_EXPORT	void	_SetZOrder(int z);
		GGE_EXPORT	int		_GetLocalOrder();
		GGE_EXPORT	bool	_RemoveFromChildList(const ggeRenderNode *node);
	};
};