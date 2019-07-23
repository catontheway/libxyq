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
\brief 矩阵运算库
*/

#pragma once
#include "ggemath.h"

namespace gge
{
	/**	@brief Matrix
		\code
		struct 
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float m[9];
		float _m[3][3];
		\endcode
	*/
	class ggeMatrix
	{
	public:
		union
		{
			struct 
			{
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			float m[9];
			float _m[3][3];
		};

		/// 构造函数
		ggeMatrix() {}
		/// 构造函数
		ggeMatrix(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33) :
		_11(m11), _12(m12), _13(m13), _21(m21), _22(m22), _23(m23), _31(m31), _32(m32), _33(m33) {}

		/// 运算符重载
		float& operator()(const int row, const int col)				{ return _m[row][col]; }
		/// 运算符重载
		const float& operator()(const int row, const int col) const { return _m[row][col]; }
		/// 运算符重载
		float& operator[](int index)								{ return m[index]; }
		/// 运算符重载
		const float& operator[](int index) const					{ return m[index]; }

		/// 运算符重载
		bool operator==(const ggeMatrix &om) const
		{
			if (m[0] != om.m[0] || m[1] != om.m[1] || m[2] != om.m[2] || 
				m[3] != om.m[3] || m[4] != om.m[4] || m[5] != om.m[5] || 
				m[6] != om.m[6] || m[7] != om.m[7] || m[8] != om.m[8])
				return false;
			return true;
		}
		/// 运算符重载
		bool operator!=(const ggeMatrix &om) const
		{
			if (m[0] != om.m[0] || m[1] != om.m[1] || m[2] != om.m[2] || 
				m[3] != om.m[3] || m[4] != om.m[4] || m[5] != om.m[5] || 
				m[6] != om.m[6] || m[7] != om.m[7] || m[8] != om.m[8])
				return true;
			return false;
		}
		/// 运算符重载
		ggeMatrix operator+(const ggeMatrix &om) const
		{
			ggeMatrix mat;

			mat[0] = m[0] + om.m[0]; mat[1] = m[1] + om.m[1]; mat[2] = m[2] + om.m[2];  
			mat[3] = m[3] + om.m[3]; mat[4] = m[4] + om.m[4]; mat[5] = m[5] + om.m[5];  
			mat[6] = m[6] + om.m[6]; mat[7] = m[7] + om.m[7]; mat[8] = m[8] + om.m[8];

			return mat;
		}
		/// 运算符重载
		ggeMatrix& operator+=(const ggeMatrix &om)
		{
			m[0] += om.m[0]; m[1] += om.m[1]; m[2] += om.m[2];  
			m[3] += om.m[3]; m[4] += om.m[4]; m[5] += om.m[5];  
			m[6] += om.m[6]; m[7] += om.m[7]; m[8] += om.m[8];

			return *this;
		}
		/// 运算符重载
		ggeMatrix operator-(const ggeMatrix &om) const
		{
			ggeMatrix mat;

			mat[0] = m[0] - om.m[0]; mat[1] = m[1] - om.m[1]; mat[2] = m[2] - om.m[2];  
			mat[3] = m[3] - om.m[3]; mat[4] = m[4] - om.m[4]; mat[5] = m[5] - om.m[5];  
			mat[6] = m[6] - om.m[6]; mat[7] = m[7] - om.m[7]; mat[8] = m[8] - om.m[8];

			return mat;
		}
		/// 运算符重载
		ggeMatrix& operator-=(const ggeMatrix &om)
		{
			m[0] -= om.m[0]; m[1] -= om.m[1]; m[2] -= om.m[2];  
			m[3] -= om.m[3]; m[4] -= om.m[4]; m[5] -= om.m[5];  
			m[6] -= om.m[6]; m[7] -= om.m[7]; m[8] -= om.m[8];

			return *this;
		}
		/// 运算符重载
		ggeMatrix operator*(const ggeMatrix &om) const
		{
			ggeMatrix mat;

			mat[0] = m[0] * om.m[0] + m[1] * om.m[3] + m[2] * om.m[6];
			mat[1] = m[0] * om.m[1] + m[1] * om.m[4] + m[2] * om.m[7];
			mat[2] = m[0] * om.m[2] + m[1] * om.m[5] + m[2] * om.m[8];

			mat[3] = m[3] * om.m[0] + m[4] * om.m[3] + m[5] * om.m[6];
			mat[4] = m[3] * om.m[1] + m[4] * om.m[4] + m[5] * om.m[7];
			mat[5] = m[3] * om.m[2] + m[4] * om.m[5] + m[5] * om.m[8];

			mat[6] = m[6] * om.m[0] + m[7] * om.m[3] + m[8] * om.m[6];
			mat[7] = m[6] * om.m[1] + m[7] * om.m[4] + m[8] * om.m[7];
			mat[8] = m[6] * om.m[2] + m[7] * om.m[5] + m[8] * om.m[8];

			return mat;
		}
		/// 运算符重载
		ggeMatrix& operator*=(const ggeMatrix &om)
		{
			ggeMatrix mat(*this);

			m[0]  = mat[0] * om.m[0] + mat[1] * om.m[3] + mat[2] * om.m[6];
			m[1]  = mat[0] * om.m[1] + mat[1] * om.m[4] + mat[2] * om.m[7];
			m[2]  = mat[0] * om.m[2] + mat[1] * om.m[5] + mat[2] * om.m[8];

			m[3]  = mat[3] * om.m[0] + mat[4] * om.m[3] + mat[5] * om.m[6];
			m[4]  = mat[3] * om.m[1] + mat[4] * om.m[4] + mat[5] * om.m[7];
			m[5]  = mat[3] * om.m[2] + mat[4] * om.m[5] + mat[5] * om.m[8];

			m[6]  = mat[6] * om.m[0] + mat[7] * om.m[3] + mat[8] * om.m[6];
			m[7]  = mat[6] * om.m[1] + mat[7] * om.m[4] + mat[8] * om.m[7];
			m[8]  = mat[6] * om.m[2] + mat[7] * om.m[5] + mat[8] * om.m[8];

			return *this;
		}
		/// 运算符重载
		ggeMatrix operator*(const float scalar) const
		{
			ggeMatrix mat;

			mat[0] = m[0] * scalar; mat[1] = m[1] * scalar; mat[2] = m[2] * scalar; 
			mat[3] = m[3] * scalar; mat[4] = m[4] * scalar; mat[5] = m[5] * scalar; 
			mat[6] = m[6] * scalar; mat[7] = m[7] * scalar; mat[8] = m[8] * scalar;

			return mat;
		}
		/// 运算符重载
		ggeMatrix& operator*=(const float scalar)
		{
			m[0] *= scalar; m[1] *= scalar; m[2] *= scalar; 
			m[3] *= scalar; m[4] *= scalar; m[5] *= scalar; 
			m[6] *= scalar; m[7] *= scalar; m[8] *= scalar;

			return *this;
		}

		/**
		@brief 设置成单位矩阵
		*/
		GGE_EXPORT void SetIdentity();
		/**
		@brief 是否为单位矩阵
		@return 是否为单位矩阵
		*/
		GGE_EXPORT bool IsIdentity() const;
		/**
		@brief 设置位移
		@param translation 位移
		*/
		GGE_EXPORT void SetTranslation(const ggeVector &translation);
		/**
		@brief 返回位移
		@return 位移
		*/
		GGE_EXPORT ggeVector GetTranslation() const;
		/**
		@brief 设置旋转
		@param rotation 旋转弧度
		*/
		GGE_EXPORT void SetRotation(const float rotation);
		/**
		@brief 返回旋转
		@return 旋转弧度
		*/
		GGE_EXPORT float GetRotation() const;
		/**
		@brief 设置缩放
		@param scale 缩放
		*/
		GGE_EXPORT void SetScale(const ggeVector &scale);
		/**
		@brief 返回缩放
		@return 缩放
		*/
		GGE_EXPORT ggeVector GetScale() const;
		/**
		@brief 变换矢量
		@param vec 要变换的矢量
		*/
		GGE_EXPORT void TransformVector(ggeVector &vec) const;
		/**
		@brief 设置为逆矩阵
		@return 成功返回true
		*/
		GGE_EXPORT bool SetInverse();
		/**
		@brief 获取逆矩阵
		@param mat 用于保存逆矩阵
		@return 成功返回true
		*/
		GGE_EXPORT bool GetInverse(ggeMatrix &mat) const;
		/**
		@brief 设置为转置矩阵
		*/
		GGE_EXPORT void SetTranspose();
		/**
		@brief 获取转置矩阵
		@param mat 用于保存转置矩阵
		*/
		GGE_EXPORT void GetTranspose(ggeMatrix &mat) const;
	};

	/**	@brief Matrix4
		\code
		struct 
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[16];
		float _m[4][4];
		\endcode
	*/
	class ggeMatrix4
	{
	public:
		union
		{
			struct 
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[16];
			float _m[4][4];
		};

		/// 构造函数
		ggeMatrix4() {}
		/// 构造函数
		ggeMatrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44) :
			_11(m11), _12(m12), _13(m13), _14(m14), _21(m21), _22(m22), _23(m23), _24(m24), 
			_31(m31), _32(m32), _33(m33), _34(m34), _41(m41), _42(m42), _43(m43), _44(m44) {}

		/// 运算符重载
		float& operator()(const int row, const int col)				{ return _m[row][col]; }
		/// 运算符重载
		const float& operator()(const int row, const int col) const { return _m[row][col]; }
		/// 运算符重载
		float& operator[](int index)								{ return m[index]; }
		/// 运算符重载
		const float& operator[](int index) const					{ return m[index]; }

		/// 运算符重载
		bool operator==(const ggeMatrix4 &om) const
		{
			if (m[0]  != om.m[0]  || m[1]  != om.m[1]  || m[2]  != om.m[2]  || m[3]  != om.m[3]  ||
				m[4]  != om.m[4]  || m[5]  != om.m[5]  || m[6]  != om.m[6]  || m[7]  != om.m[7]  ||
				m[8]  != om.m[8]  || m[9]  != om.m[9]  || m[10] != om.m[10] || m[11] != om.m[11] ||
				m[12] != om.m[12] || m[13] != om.m[13] || m[14] != om.m[14] || m[15] != om.m[15])
				return false;
			return true;
		}
		/// 运算符重载
		bool operator!=(const ggeMatrix4 &om) const
		{
			if (m[0]  != om.m[0]  || m[1]  != om.m[1]  || m[2]  != om.m[2]  || m[3]  != om.m[3]  ||
				m[4]  != om.m[4]  || m[5]  != om.m[5]  || m[6]  != om.m[6]  || m[7]  != om.m[7]  ||
				m[8]  != om.m[8]  || m[9]  != om.m[9]  || m[10] != om.m[10] || m[11] != om.m[11] ||
				m[12] != om.m[12] || m[13] != om.m[13] || m[14] != om.m[14] || m[15] != om.m[15])
				return true;
			return false;
		}
		/// 运算符重载
		ggeMatrix4 operator+(const ggeMatrix4 &om) const
		{
			ggeMatrix4 mat;

			mat[0]  = m[0]  + om.m[0];  mat[1]  = m[1]  + om.m[1];  mat[2] =  m[2]  + om.m[2];  mat[3]  = m[3]  + om.m[3];
			mat[4]  = m[4]  + om.m[4];  mat[5]  = m[5]  + om.m[5];  mat[6] =  m[6]  + om.m[6];  mat[7]  = m[7]  + om.m[7];
			mat[8]  = m[8]  + om.m[8];  mat[9]  = m[9]  + om.m[9];  mat[10] = m[10] + om.m[10]; mat[11] = m[11] + om.m[11];
			mat[12] = m[12] + om.m[12]; mat[13] = m[13] + om.m[13]; mat[14] = m[14] + om.m[14]; mat[15] = m[15] + om.m[15];

			return mat;
		}
		/// 运算符重载
		ggeMatrix4& operator+=(const ggeMatrix4 &om)
		{
			m[0]  += om.m[0];  m[1]  += om.m[1];  m[2]  += om.m[2];  m[3]  += om.m[3]; 
			m[4]  += om.m[4];  m[5]  += om.m[5];  m[6]  += om.m[6];  m[7]  += om.m[7]; 
			m[8]  += om.m[8];  m[9]  += om.m[9];  m[10] += om.m[10]; m[11] += om.m[11]; 
			m[12] += om.m[12]; m[13] += om.m[13]; m[14] += om.m[14]; m[15] += om.m[15];

			return *this;
		}
		/// 运算符重载
		ggeMatrix4 operator-(const ggeMatrix4 &om) const
		{
			ggeMatrix4 mat;

			mat[0]  = m[0]  - om.m[0];  mat[1]  = m[1]  - om.m[1];  mat[2]  = m[2]  - om.m[2];  mat[3]  = m[3]  - om.m[3];
			mat[4]  = m[4]  - om.m[4];  mat[5]  = m[5]  - om.m[5];  mat[6]  = m[6]  - om.m[6];  mat[7]  = m[7]  - om.m[7];
			mat[8]  = m[8]  - om.m[8];  mat[9]  = m[9]  - om.m[9];  mat[10] = m[10] - om.m[10]; mat[11] = m[11] - om.m[11];
			mat[12] = m[12] - om.m[12]; mat[13] = m[13] - om.m[13]; mat[14] = m[14] - om.m[14]; mat[15] = m[15] - om.m[15];

			return mat;
		}
		/// 运算符重载
		ggeMatrix4& operator-=(const ggeMatrix4 &om)
		{
			m[0]  -= om.m[0];  m[1]  -= om.m[1];  m[2]  -= om.m[2];  m[3]  -= om.m[3];
			m[4]  -= om.m[4];  m[5]  -= om.m[5];  m[6]  -= om.m[6];  m[7]  -= om.m[7];
			m[8]  -= om.m[8];  m[9]  -= om.m[9];  m[10] -= om.m[10]; m[11] -= om.m[11];
			m[12] -= om.m[12]; m[13] -= om.m[13]; m[14] -= om.m[14]; m[15] -= om.m[15];

			return *this;
		}
		/// 运算符重载
		ggeMatrix4 operator*(const ggeMatrix4 &om) const
		{
			ggeMatrix4 mat;

			mat[0]  = m[0] * om.m[0] + m[4] * om.m[1] + m[8]  * om.m[2] + m[12] * om.m[3];
			mat[1]  = m[1] * om.m[0] + m[5] * om.m[1] + m[9]  * om.m[2] + m[13] * om.m[3];
			mat[2]  = m[2] * om.m[0] + m[6] * om.m[1] + m[10] * om.m[2] + m[14] * om.m[3];
			mat[3]  = m[3] * om.m[0] + m[7] * om.m[1] + m[11] * om.m[2] + m[15] * om.m[3];

			mat[4]  = m[0] * om.m[4] + m[4] * om.m[5] + m[8]  * om.m[6] + m[12] * om.m[7];
			mat[5]  = m[1] * om.m[4] + m[5] * om.m[5] + m[9]  * om.m[6] + m[13] * om.m[7];
			mat[6]  = m[2] * om.m[4] + m[6] * om.m[5] + m[10] * om.m[6] + m[14] * om.m[7];
			mat[7]  = m[3] * om.m[4] + m[7] * om.m[5] + m[11] * om.m[6] + m[15] * om.m[7];

			mat[8]  = m[0] * om.m[8] + m[4] * om.m[9] + m[8]  * om.m[10] + m[12] * om.m[11];
			mat[9]  = m[1] * om.m[8] + m[5] * om.m[9] + m[9]  * om.m[10] + m[13] * om.m[11];
			mat[10] = m[2] * om.m[8] + m[6] * om.m[9] + m[10] * om.m[10] + m[14] * om.m[11];
			mat[11] = m[3] * om.m[8] + m[7] * om.m[9] + m[11] * om.m[10] + m[15] * om.m[11];

			mat[12] = m[0] * om.m[12] + m[4] * om.m[13] + m[8]  * om.m[14] + m[12] * om.m[15];
			mat[13] = m[1] * om.m[12] + m[5] * om.m[13] + m[9]  * om.m[14] + m[13] * om.m[15];
			mat[14] = m[2] * om.m[12] + m[6] * om.m[13] + m[10] * om.m[14] + m[14] * om.m[15];
			mat[15] = m[3] * om.m[12] + m[7] * om.m[13] + m[11] * om.m[14] + m[15] * om.m[15];

			return mat;
		}
		/// 运算符重载
		ggeMatrix4& operator*=(const ggeMatrix4 &om)
		{
			ggeMatrix4 mat(*this);

			m[0]  = mat[0] * om.m[0] + mat[4] * om.m[1] + mat[8]  * om.m[2] + mat[12] * om.m[3];
			m[1]  = mat[1] * om.m[0] + mat[5] * om.m[1] + mat[9]  * om.m[2] + mat[13] * om.m[3];
			m[2]  = mat[2] * om.m[0] + mat[6] * om.m[1] + mat[10] * om.m[2] + mat[14] * om.m[3];
			m[3]  = mat[3] * om.m[0] + mat[7] * om.m[1] + mat[11] * om.m[2] + mat[15] * om.m[3];

			m[4]  = mat[0] * om.m[4] + mat[4] * om.m[5] + mat[8]  * om.m[6] + mat[12] * om.m[7];
			m[5]  = mat[1] * om.m[4] + mat[5] * om.m[5] + mat[9]  * om.m[6] + mat[13] * om.m[7];
			m[6]  = mat[2] * om.m[4] + mat[6] * om.m[5] + mat[10] * om.m[6] + mat[14] * om.m[7];
			m[7]  = mat[3] * om.m[4] + mat[7] * om.m[5] + mat[11] * om.m[6] + mat[15] * om.m[7];

			m[8]  = mat[0] * om.m[8] + mat[4] * om.m[9] + mat[8]  * om.m[10] + mat[12] * om.m[11];
			m[9]  = mat[1] * om.m[8] + mat[5] * om.m[9] + mat[9]  * om.m[10] + mat[13] * om.m[11];
			m[10] = mat[2] * om.m[8] + mat[6] * om.m[9] + mat[10] * om.m[10] + mat[14] * om.m[11];
			m[11] = mat[3] * om.m[8] + mat[7] * om.m[9] + mat[11] * om.m[10] + mat[15] * om.m[11];

			m[12] = mat[0] * om.m[12] + mat[4] * om.m[13] + mat[8]  * om.m[14] + mat[12] * om.m[15];
			m[13] = mat[1] * om.m[12] + mat[5] * om.m[13] + mat[9]  * om.m[14] + mat[13] * om.m[15];
			m[14] = mat[2] * om.m[12] + mat[6] * om.m[13] + mat[10] * om.m[14] + mat[14] * om.m[15];
			m[15] = mat[3] * om.m[12] + mat[7] * om.m[13] + mat[11] * om.m[14] + mat[15] * om.m[15];

			return *this;
		}
		/// 运算符重载
		ggeMatrix4 operator*(const float scalar) const
		{
			ggeMatrix4 mat;

			mat[0]  = m[0]  * scalar; mat[1]  = m[1]  * scalar; mat[2] =  m[2]  * scalar; mat[3]  = m[3]  * scalar;
			mat[4]  = m[4]  * scalar; mat[5]  = m[5]  * scalar; mat[6] =  m[6]  * scalar; mat[7]  = m[7]  * scalar;
			mat[8]  = m[8]  * scalar; mat[9]  = m[9]  * scalar; mat[10] = m[10] * scalar; mat[11] = m[11] * scalar;
			mat[12] = m[12] * scalar; mat[13] = m[13] * scalar; mat[14] = m[14] * scalar; mat[15] = m[15] * scalar;

			return mat;
		}
		/// 运算符重载
		ggeMatrix4& operator*=(const float scalar)
		{
			m[0]  *= scalar; m[1]  *= scalar; m[2]  *= scalar; m[3]  *= scalar;
			m[4]  *= scalar; m[5]  *= scalar; m[6]  *= scalar; m[7]  *= scalar;
			m[8]  *= scalar; m[9]  *= scalar; m[10] *= scalar; m[11] *= scalar;
			m[12] *= scalar; m[13] *= scalar; m[14] *= scalar; m[15] *= scalar;

			return *this;
		}

		/**
		@brief 设置成单位矩阵
		*/
		GGE_EXPORT void SetIdentity();
		/**
		@brief 是否为单位矩阵
		@return 是否为单位矩阵
		*/
		GGE_EXPORT bool IsIdentity() const;
		/**
		@brief 设置位移
		@param translation X/Y/Z轴上的位移
		*/
 		GGE_EXPORT void SetTranslation(const ggeVector3 &translation);
		/**
		@brief 返回位移
		@return X/Y/Z轴上的位移
		*/
		GGE_EXPORT ggeVector3 GetTranslation() const;
		/**
		@brief 用欧拉角设置旋转
		@param rotation 欧拉角旋转弧度
		*/
 		GGE_EXPORT void SetRotation(const ggeVector3 &rotation);
		/**
		@brief 返回旋转欧拉角
		@return 欧拉角旋转弧度
		*/
		GGE_EXPORT ggeVector3 GetRotation() const;
		/**
		@brief 设置围绕X轴的旋转
		@param angle 旋转弧度
		*/
		GGE_EXPORT void SetRotationX(float angle);
		/**
		@brief 设置围绕Y轴的旋转
		@param angle 旋转弧度
		*/
		GGE_EXPORT void SetRotationY(float angle);
		/**
		@brief 设置围绕Z轴的旋转
		@param angle 旋转弧度
		*/
		GGE_EXPORT void SetRotationZ(float angle);
		/**
		@brief 设置围绕指定轴的旋转
		@param axis 旋转轴
		@param angle 旋转弧度
		*/
	   GGE_EXPORT void SetRotationAxis(const ggeVector3 &axis, float angle);
		/**
		@brief 设置缩放
		@param scale X/Y/Z轴上的缩放
		*/
 		GGE_EXPORT void SetScale(const ggeVector3 &scale);
		/**
		@brief 返回缩放
		@return X/Y/Z轴上的缩放
		*/
		GGE_EXPORT ggeVector3 GetScale() const;
		/**
		@brief 变换矢量
		@param vec 要变换的矢量
		*/
		GGE_EXPORT void TransformVector(ggeVector &vec) const;
		/**
		@brief 变换矢量
		@param vec 要变换的矢量
		*/
		GGE_EXPORT void TransformVector3(ggeVector3 &vec) const;
		/**
		@brief 设置为逆矩阵
		@return 成功返回true
		*/
 		GGE_EXPORT bool SetInverse();
		/**
		@brief 获取逆矩阵
		@param mat 用于保存逆矩阵
		@return 成功返回true
		*/
		GGE_EXPORT bool GetInverse(ggeMatrix4 &mat) const;
		/**
		@brief 设置为转置矩阵
		*/
		GGE_EXPORT void SetTranspose();
		/**
		@brief 获取转置矩阵
		@param mat 用于保存转置矩阵
		*/
		GGE_EXPORT void GetTranspose(ggeMatrix4 &mat) const;
		/**
		@brief 生成透视投影矩阵
		@param fov y轴观察范围夹角弧度
		@param aspect 纵横比
		@param zn 近裁剪面
		@param zf 远裁剪面
		*/
		GGE_EXPORT void BuildProjectionMatrixPerspectiveFovLH(float fov, float aspect, float zn, float zf);
		/**
		@brief 生成正交投影矩阵
		@param wov 屏幕宽度
		@param hov 屏幕高度
		@param zn Z缓存最小值
		@param zf Z缓存最大值
		*/
		GGE_EXPORT void BuildProjectionMatrixOrthoLH(float wov, float hov, float zn, float zf);
		/**
		@brief 生成视图矩阵
		@param position 观察点位置
		@param target 观察目标位置
		@param up 向上方向
		*/
		GGE_EXPORT void BuildCameraLookAtMatrixLH(const ggeVector3 &position, const ggeVector3 &target, const ggeVector3 &up);
	};
}