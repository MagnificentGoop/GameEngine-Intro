#pragma once
#include "Vector2.h"
namespace bad {
	template<typename T>
	struct Vector3 {
		static_assert(std::is_arithmetic_v<T>,
			"Vector3<T> requires T to be a numeric type.");

		union {
			struct { T x; T y; T z; }; //position
			struct { T posX; T posY; T s; }; //position and size
		};

		Vector3<T>(T x = 0, T y = 0, T z = 0) : x{ x }, y{ y }, z { z } {};
		Vector3<T>(const Vector2<T>* v, T z = 0) : Vector3(v->x,v->y,z) {};
		Vector3<T>(const Vector3<T>* v) : x{ v->x }, y{ v->y }, z{ v->z } {};

		T operator[] (unsigned int i) const { assert(i < 3); return (&x)[i]; };
		T& operator[] (unsigned int i) { assert(i < 3); return (&x)[i]; };

		Vector3 operator + (const Vector3<T>& v) const { return Vector3<T>(this->x + v.x, this->y + v.y, this->z + v.z); }
		Vector3 operator - (const Vector3<T>& v) const { return Vector3<T>(this->x - v.x, this->y - v.y, this->z - v.z); }
		Vector3 operator * (const Vector3<T>& v) const { return Vector3<T>(this->x * v.x, this->y * v.y, this->z * v.z); }
		Vector3 operator / (const Vector3<T>& v) const { return Vector3<T>(this->x / v.x, this->y / v.y, this->z / v.z); }

		Vector3 operator + (const T& i) const { return Vector3<T>(this->x + i, this->y + i, this->z + i); }
		Vector3 operator - (const T& i) const { return Vector3<T>(this->x - i, this->y - i, this->z - i); }
		Vector3 operator * (const T& i) const { return Vector3<T>(this->x * i, this->y * i, this->z * i); }
		Vector3 operator / (const T& i) const { return Vector3<T>(this->x / i, this->y / i, this->z / i); }

		Vector3& operator += (const Vector3<T>& v) { this->x += v.x; this->y += v.y; this->z += v.z; return *this; }
		Vector3& operator -= (const Vector3<T>& v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; return *this; }
		Vector3& operator *= (const Vector3<T>& v) { this->x *= v.x; this->y *= v.y; this->z *= v.z; return *this; }
		Vector3& operator /= (const Vector3<T>& v) { this->x /= v.x; this->y /= v.y; this->z /= v.z; return *this;}

		Vector3& operator += (const T i) { this->x += i; this->y += i; this->z += i; return *this;}
		Vector3& operator -= (const T i) { this->x -= i; this->y -= i; this->z -= i; return *this;}
		Vector3& operator *= (const T i) { this->x *= i; this->y *= i; this->z *= i; return *this;}
		Vector3& operator /= (const T i) { this->x /= i; this->y /= i; this->z /= i; return *this;}

		bool operator==(const Vector3<T>& v) const { return (this->x == v.x && this->y == v.y && this->z == v.z); }
		bool operator!=(const Vector3<T>& v) const { return (this->x == v.x && this->y != v.y || this->z != v.z); }
		bool operator>(const Vector3<T>& v) const { return (this->x > v.x && this->y > v.y && this->z > v.z); }
		bool operator<(const Vector3<T>& v) const { return (this->x < v.x && this->y < v.y && this->z < v.z); }

		template<typename U>
		explicit operator Vector3<U>() const { return Vector3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z)); }

		T LengthSqr() const { return (x * x) + (y * y) + (z * z); }
		T Length() const { return std::sqrt(LengthSqr()); }

		Vector3 Normalized() const { return *this / Length(); }
		T Dot(const Vector3<T>& v) const { return ((x * v.x) + (y * v.y) + (z * v.z)); }
	};
}