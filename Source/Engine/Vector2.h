#pragma once
#include <cmath>
#include <type_traits>
#include <cassert>

namespace bad {
	template<typename T>

	struct Vector2 {
		static_assert(std::is_arithmetic_v<T>,
			"Vector2<T> requires T to be a numeric type.");


		T x, y;

		Vector2<T>(T x = 0, T y = 0) : x{ x }, y{ y } {};
		Vector2<T>(const Vector2<T>* v) : x{ v->x }, y{ v->y } {};

		T operator[] (unsigned int i) const { assert(i < 2); return (&x)[i]; };
		T& operator[] (unsigned int i) { assert(i < 2); return (&x)[i]; };

		Vector2 operator + (const Vector2<T>& v) const {return Vector2<T>(this->x + v.x, this->y + v.y);}
		Vector2 operator - (const Vector2<T>& v) const {return Vector2<T>(this->x - v.x, this->y - v.y);}
		Vector2 operator * (const Vector2<T>& v) const {return Vector2<T>(this->x * v.x, this->y * v.y);}
		Vector2 operator / (const Vector2<T>& v) const {return Vector2<T>(this->x / v.x, this->y / v.y);}

		Vector2 operator + (const T& i) const { return Vector2<T>(this->x + i, this->y + i); }
		Vector2 operator - (const T& i) const { return Vector2<T>(this->x - i, this->y - i); }
		Vector2 operator * (const T& i) const { return Vector2<T>(this->x * i, this->y * i); }
		Vector2 operator / (const T& i) const { return Vector2<T>(this->x / i, this->y / i); }

		Vector2& operator += (const Vector2<T>& v) {this->x += v.x; this->y += v.y; return *this;}
		Vector2& operator -= (const Vector2<T>& v) {this->x -= v.x; this->y -= v.y; return *this;}
		Vector2& operator *= (const Vector2<T>& v) {this->x *= v.x; this->y *= v.y; return *this;}
		Vector2& operator /= (const Vector2<T>& v) {this->x /= v.x; this->y /= v.y; return *this;}
				  
		Vector2& operator += (const T& i) { this->x += i; this->y += i; return *this; }
		Vector2& operator -= (const T& i) { this->x -= i; this->y -= i; return *this; }
		Vector2& operator *= (const T& i) { this->x *= i; this->y *= i; return *this; }
		Vector2& operator /= (const T& i) { this->x /= i; this->y /= i; return *this; }

		bool operator==(const Vector2<T>& v) const { return (this->x == v.x && this->y == v.y); }
		bool operator!=(const Vector2<T>& v) const {return(this->x != v.x || this->y != v.y);}
		bool operator>(const Vector2<T>& v) const { return (this->x > v.x && this->y > v.y); }
		bool operator<(const Vector2<T>& v) const { return (this->x < v.x && this->y < v.y); }

		template<typename U>
		explicit operator Vector2<U>() const {return Vector2<U>(static_cast<U>(x), static_cast<U>(y)); }

		T LengthBtwnSqr(const Vector2<T>& v) const { return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y); }
		T LengthBtwn(const Vector2<T>& v) const { return std::sqrt(LengthBtwnSqr(v)); }

		T LengthSqr() const { return (x * x) + (y * y); }
		T Length() const { return std::sqrt(LengthSqr()); }

		Vector2 Normalized() const { return (Length() == 0) ? Vector2<T>{0,0} : *this / Length(); }
		T Dot(const Vector2<T>& v) const { return ((x * v.x) + (y * v.y)); }
		T Angle() const{ return std::atan2(y,x); }
		T AngleBetween(const Vector2<T>& v) const { return std::acos(Dot(v)); }

		Vector2 Rotate(float radians) const {
			Vector2 v;

			v.x = x * std::cos(radians) - y * std::sin(radians);
			v.y = x * std::sin(radians) + y * std::cos(radians);

			return v;
		}
	};
}