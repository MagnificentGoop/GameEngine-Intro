#pragma once
#include <cstdlib>
namespace bad {
	/// <summary>
	/// Gets a random integer value.
	/// </summary>
	/// <returns>Random int value</returns>
	inline int RandomInt() {
		return rand();
	}
	/// <summary>
	/// Gets a random integer value, maximum is exclusive
	/// </summary>
	/// <param name="maxValue">The exclusive max value wanted</param>
	/// <returns>Random int between 0 and maxValue</returns>
	inline int RandomInt(int maxValue) {
		return rand() % maxValue;
	}
	/// <summary>
	/// Gets a random integer value between minValue and exclusive maxValue
	/// </summary>
	/// <param name="minValue">The inclusive minimum value wanted</param>
	/// <param name="maxValue">The exclusive maximum value wanted</param>
	/// <returns>Random int value between minValue inclusive and maxValue exclusive</returns>
	inline int RandomInt(int minValue, int maxValue) {
		return minValue + RandomInt(maxValue - minValue);
	}
	/// <summary>
	/// gets a random float between 0 to 1
	/// </summary>
	/// <returns>Random float value between 0 and 1</returns>
	inline float RandomFloat() {
		return rand() / (float)RAND_MAX;
	}
	/// <summary>
	/// Gets a random float value between 0 and maxValue
	/// </summary>
	/// <param name="maxValue">The inclusive maximum value wanted</param>
	/// <returns>Random float value between 0 and maxValue</returns>
	inline float RandomFloat(float maxValue) {
		return RandomFloat() * maxValue;
	}
	/// <summary>
	/// Gets a random float value between minValue and maxValue
	/// </summary>
	/// <param name="minValue">The inclusive minimum value wanted</param>
	/// <param name="maxValue">The inclusive maximum value wanted</param>
	/// <returns>Random float value between minValue and MaxValue inclusive</returns>
	inline float RandomFloat(float minValue, float maxValue) {
		return minValue + RandomFloat() * (maxValue - minValue);
	}
}