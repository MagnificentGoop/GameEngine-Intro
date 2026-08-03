namespace bad::math {
	constexpr float PI = 3.14159265358979323846264338327950288419716939937510f;
	constexpr float TWO_PI = 6.283185307179586476925286766559f;
	constexpr float HALF_PI = 1.5707963267948966192313216916398f;
	
	template <typename T>
	T Wrap(T& value, const T maxVal, const T minVal){
		if (value > maxVal) {value = minVal + (value - maxVal);}
		if (value < minVal) {value = maxVal + (value - minVal);}
		return value;
	}
	template <typename T>
	T Clamp(T& value, const T maxVal, const T minVal) {
		if (value > maxVal) value = maxVal;
		if (value < minVal) value = minVal;
		return value;
	}

	template <typename T>
	T Min(T a, T b) {return (a < b) ? a : b;}
	template <typename T>
	T Max(T a, T b) {return (a > b) ? a : b;}
}