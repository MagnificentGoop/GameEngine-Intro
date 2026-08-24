#pragma once
#include "Vector3.h"
namespace bad {
	template<typename T>
	struct Vector4 {
		static_assert(std::is_arithmetic_v<T>,
			"Vector4<T> requires T to be a numeric type.");

		union {
			struct { T x; T y; T z; T w; }; //"position" in a loose sense
			struct { T r; T g; T b; T a; }; //color
		};

		Vector4<T>(T x = 0, T y = 0, T z = 0, T w = 0) : x{ x }, y{ y }, z{ z }, w{ w } {};
		Vector4<T>(const Vector2<T>* v, T z = 0, T w = 0) : Vector4(v->x, v->y, z, w) {};
		Vector4<T>(const Vector3<T>* v, T w = 0) : Vector4(v->x, v->y, v->z, w) {};
		Vector4<T>(const Vector4<T>* v) : x{ v->x }, y{ v->y }, z{ v->z }, w{ v->w } {};

		T operator[] (unsigned int i) const { assert(i < 4); return (&x)[i]; };
		T& operator[] (unsigned int i) { assert(i < 4); return (&x)[i]; };

		Vector4 operator + (const Vector4<T>& v) const { return Vector4<T>(this->r + v.r, this->g + v.g, this->z + v.z, this->w + v.w); }
		Vector4 operator - (const Vector4<T>& v) const { return Vector4<T>(this->r - v.r, this->g - v.g, this->z - v.z, this->w - v.w); }
		Vector4 operator * (const Vector4<T>& v) const { return Vector4<T>(this->r * v.r, this->g * v.g, this->z * v.z, this->w * v.w); }
		Vector4 operator / (const Vector4<T>& v) const { return Vector4<T>(this->r / v.r, this->g / v.g, this->z / v.z, this->w / v.w); }

		Vector4 operator + (const T& i) const { return Vector4(this->r + i, this->g + i, this->z + i, this->w + i); }
		Vector4 operator - (const T& i) const { return Vector4(this->r - i, this->g - i, this->z - i, this->w - i); }
		Vector4 operator * (const T& i) const { return Vector4(this->r * i, this->g * i, this->z * i, this->w * i); }
		Vector4 operator / (const T& i) const { return Vector4(this->r / i, this->g / i, this->z / i, this->w / i); }

		Vector4& operator += (const Vector4<T>& v) { this->x += v.x; this->y += v.y; this->z += v.z; this->w += v.w; return *this; }
		Vector4& operator -= (const Vector4<T>& v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; this->w -= v.w; return *this; }
		Vector4& operator *= (const Vector4<T>& v) { this->x *= v.x; this->y *= v.y; this->z *= v.z; this->w *= v.w; return *this; }
		Vector4& operator /= (const Vector4<T>& v) { this->x /= v.x; this->y /= v.y; this->z /= v.z; this->w /= v.w; return *this; }

		Vector4& operator += (const T& i) { this->x += i; this->y += i; this->z += i; this->w += i; return *this; }
		Vector4& operator -= (const T& i) { this->x -= i; this->y -= i; this->z -= i; this->w -= i; return *this; }
		Vector4& operator *= (const T& i) { this->x *= i; this->y *= i; this->z *= i; this->w *= i; return *this; }
		Vector4& operator /= (const T& i) { this->x /= i; this->y /= i; this->z /= i; this->w /= i; return *this; }

		bool operator==(const Vector4<T>& v) const { return (this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w); }
		bool operator!=(const Vector4<T>& v) const { return (this->x != v.x && this->y == v.y && this->z != v.z || this->w == v.w); }
		bool operator>(const Vector4<T>& v) const { return (this->x > v.x && this->y > v.y && this->z > v.z && this->w > v.w); }
		bool operator<(const Vector4<T>& v) const { return (this->x < v.x && this->y < v.y && this->z < v.z && this->w < v.w); }

		template<typename U>
		explicit operator Vector4<U>() const { return Vector4<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z), static_cast<U>(w)); }

		T LengthSqr() const { return (x * x) + (y * y) + (z * z) + (w * w); }
		T Length() const { return std::sqrt(LengthSqr()); }

		Vector4 Normalized() const { return *this / Length(); }
		T Dot(const Vector4<T>& v) const { return ((x * v.x) + (y * v.y) + (z * v.z) + (w * v.w)); }
	};
}