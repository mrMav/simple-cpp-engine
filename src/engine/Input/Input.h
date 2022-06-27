#pragma once

#include <glfw/glfw3.h>

#include <iostream>
#include <bitset>

#include "KeyCodes.h"

namespace Engine
{
	// wrapper class for glfw input
	class Input
	{
	public:

		static void Init(GLFWwindow*);

		static void Update();

		static void SetMap(int key, int scancode, int action, int mods);

		static bool IsKeyPressed(KeyCode key);

		static bool IsKeyUp(KeyCode key);

		static bool IsKeyJustDown(KeyCode key);

	private:

		static std::bitset<GLFW_KEY_LAST> m_LastFrameKeyMap;
		static std::bitset<GLFW_KEY_LAST> m_KeyMap;

	};
}