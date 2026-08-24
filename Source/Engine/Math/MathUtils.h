#pragma once
namespace bad {
	constexpr float PI = 3.14159265358979323846264338327950288419716939937510f;
	constexpr float TWO_PI = 6.283185307179586476925286766559f;
	constexpr float HALF_PI = 1.5707963267948966192313216916398f;

	constexpr float RadToDeg = 180.0f / PI;
	constexpr float DegToRad = PI / 180.0f;

	template <typename T>
	T Wrap(T& value, const T minVal, const T maxVal) {
		if (value > maxVal) { value = minVal + (value - maxVal); }
		if (value < minVal) { value = maxVal + (value - minVal); }
		return value;
	}

	template <typename T>
	T Clamp(T& value, const T minVal, const T maxVal) {
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
		return value;
	}

	template <typename T>
	T Min(T a, T b) { return (a < b) ? a : b; }
	template <typename T>
	T Max(T a, T b) { return (a > b) ? a : b; }
}