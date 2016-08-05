#ifndef _GLX_MATH_4X4_H_
#define _GLX_MATH_4X4_H_

namespace glx
{
	template<class T>
	class mat4
	{
	public:
		union {
			struct {
				T _11, _21, _31, _41;
				T _12, _22, _32, _42;
				T _13, _23, _33, _43;
				T _14, _24, _34, _44;
			};
			T m[4][4];
		};


	public:
		mat4() {}
		mat4(const T*);
		mat4(mat4<T> &);
		mat4(
			T m11, T m21, T m31, T m41,
			T m12, T m22, T m32, T m42,
			T m13, T m23, T m33, T m43,
			T m14, T m24, T m34, T m44);

		//acces grants
		T& operator () (unsigned int row, unsigned int col);
		T  operator () (unsigned int row, unsigned int col) const;

		//casting operators
		operator float* ();
		operator const float* () const;

		//assignement operators
		mat4<T>& operator *= (const  mat4<T>&);
		mat4<T>& operator += (const  mat4<T>&);
		mat4<T>& operator -= (const  mat4<T>&);
		mat4<T>& operator *= (T);
		mat4<T>& operator /= (T);
		mat4<T>& operator  = (const mat4<T>&);

		//unary operators
		mat4<T> operator + () const;
		mat4<T> operator - () const;

		//binary operators
		mat4<T> operator * (const mat4<T>&) const;
		mat4<T> operator + (const mat4<T>&) const;
		mat4<T> operator - (const mat4<T>&) const;
		mat4<T> operator * (T) const;
		mat4<T> operator / (T) const;

		friend mat4<T> operator * (T, const mat4<T>&);

		bool operator == (const mat4<T>&) const;
		bool operator != (const mat4<T>&) const;

		//Setters
		void SetPosition(const glx::vec3<T> &vec);
		void SetPosition(const glx::vec4<T> &vec);
		void SetScale(const glx::vec3<T> &vec);
		void SetRotation(const glx::mat4<T> & m);

		//Getters
		glx::vec3<T> GetPosition() const;
		glx::vec3<T> GetScale() const;
		glx::vec3<T> GetDirection() const;

		//Resets to identity matrix
		void Clear();
	};
}

#include "GLXMat4x4.inl"
#endif
