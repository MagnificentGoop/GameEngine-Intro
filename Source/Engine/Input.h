#pragma once
#include <vector>
#include "Vector2.h"
#include <SDL3/SDL.h>
namespace bad {
	class Input {
	public:
		enum MouseButton
		{
			LEFT = 1,
			MIDDLE = 2,
			RIGHT = 3,
			X1 = 4,
			X2 = 5
		};

	public:
		bool Initialize();
		void Shutdown();

		void Update();

		bool GetKeyPressed(int key) const { return m_keyStates[key]; }
		bool GetPrevKeyPressed(int key) const { return m_prevKeyStates[key]; }
		bool GetKeyDown(int key) const { return !m_prevKeyStates[key] && m_keyStates[key]; }
		bool GetKeyUp(int key) const { return m_prevKeyStates[key] && !m_keyStates[key]; }


		bool GetButtonPressed(MouseButton button) const { return m_buttonStates & GetButtonBit(button); }
		bool GetPrevButtonPressed(MouseButton button) const { return m_prevButtonStates & GetButtonBit(button); }
		bool GetButtonDown(MouseButton button) const { return !GetPrevButtonPressed(button) && GetButtonPressed(button); }
		bool GetButtonUp(MouseButton button) const { return GetPrevButtonPressed(button) && !GetButtonPressed(button); }

		Vector2<float> GetMousePosition() { return m_mousePosition; }
	private:
		uint32_t GetButtonBit(MouseButton button) const { return SDL_BUTTON_MASK(button); }

	private:
		std::vector<bool>m_keyStates;
		std::vector<bool>m_prevKeyStates;

		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;

		Vector2<float> m_mousePosition;
	};
}