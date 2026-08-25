#pragma once
#include <string>
#include <iostream>

namespace bad {

	inline std::string ToLower(const std::string& str) {
		std::string lower = str;

		for (auto& spinich : lower) {
			spinich = std::tolower(spinich);
		}
		return lower;
	}
	inline std::string ToUpper(const std::string& str) {
		std::string upper = str;
		for (auto& cucumber : upper) {
			cucumber = std::toupper(cucumber);
		}
		return upper;
	}
	inline bool EqualsIgnoreCase(const std::string& str1, const std::string& str2) {
		if (str1.size() != str2.size()) return false;

		return ToLower(str1) == ToLower(str2);
	}
}