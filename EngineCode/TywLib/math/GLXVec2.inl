#ifndef _GLX_VEC2_MATH_INLINE_H_
#define _GLX_VEC2_MATH_INLINE_H_

/*
Sets vector to 0, 0
*/
template<class T>
inline void glx::vec2<T>::Clear()
{
	x = y = T(0);
}

template<class T>
inline glx::vec2<T>::vec2(T _x, T _y) {
	x = _x;
	y = _y;
}

template<class T>
inline glx::vec2<T>::vec2(const T* pf) {
	if (!pf)return;
	x = pf[0];
	y = pf[1];
}

// casting
template<class T>
inline glx::vec2<T>::operator float* () {

	return static_cast<float*> (&x);
}

template<class T>
inline glx::vec2<T>::operator const float* () const {
	return (const float*)&x;
}

// assignment operators
template<class T>
inline glx::vec2<T>& glx::vec2<T>::operator += (const glx::vec2<T>& v) {
	x += v.x;
	y += v.y;
	return *this;
}

template<class T>
inline glx::vec2<T>& glx::vec2<T>::operator -= (const glx::vec2<T>& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

template<class T>
inline glx::vec2<T>& glx::vec2<T>::operator *= (T s) {
	x *= s;
	y *= s;
	return *this;
}

template<class T>
inline glx::vec2<T>& glx::vec2<T>::operator /= (T s) {
	x /= s;
	y /= s;
	return *this;
}

template<class T>
inline glx::vec2<T>& glx::vec2<T>::operator  = (const vec2<T>& v)
{
	x = v.x;
	y = v.y;
	return *this;
}


// unary operators
template<class T>
inline glx::vec2<T> glx::vec2<T>::operator + () const {
	return *this;
}

template<class T>
inline glx::vec2<T> glx::vec2<T>::operator - () const {
	return glx::vec2<T>(-x, -y);
}

// binary operators
template<class T>
inline glx::vec2<T> glx::vec2<T>::operator + (const glx::vec2<T>& v) const {
	return glx::vec2<T>(x + v.x, y + v.y);
}

template<class T>
inline glx::vec2<T> glx::vec2<T>::operator - (const glx::vec2<T>& v) const {
	return glx::vec2<T>(x - v.x, y - v.y);
}

template<class T>
inline glx::vec2<T> glx::vec2<T>::operator * (T f) const {
	return glx::vec2<T>(x*f, y*f);
}

template<class T>
inline glx::vec2<T> glx::vec2<T>::operator / (T f) const {
	return glx::vec2<T>(x / f, y / f);
}

template<class T>
inline glx::vec2<T> operator * (T f, const glx::vec2<T>& v) {
	return glx::vec2<T><T>(f*v.x, f*v.y);
}

template<class T>
inline bool glx::vec2<T>::operator == (const glx::vec2<T>& v) const {
	return x == v.x && y == v.y;
}

template<class T>
inline bool glx::vec2<T>::operator != (const glx::vec2<T>& v) const {
	return x != v.x || y != v.y;
}

#endif