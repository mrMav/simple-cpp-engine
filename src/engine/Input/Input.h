#pragma once

#include <glfw/glfw3.h>

#include <iostream>
#include <vector>
#include <bitset>

#include "KeyCodes.h"
#include "GamePadButtonCodes.h"

namespace Engine
{
	// wrapper class for glfw input
	class Input
	{
	public:

		static void Init(GLFWwindow*);

		/// <summary>
		/// To be called before any game logic is processed.
		/// </summary>
		static void PreUpdate();

		/// <summary>
		/// To be called after all game logic is processed, but before glfw event polling.
		/// </summary>
		static void PostUpdate();

		/*  Keyboard */

		static void SetMap(int key, int scancode, int action, int mods);

		static bool IsKeyPressed(KeyCode key);

		static bool IsKeyUp(KeyCode key);

		static bool IsKeyJustDown(KeyCode key);

		/* Joysticks */

		static bool IsButtonPressed(uint8_t jid, GamePadButtonCode btn);

		static bool IsButtonUp(uint8_t jid, GamePadButtonCode btn);

		static bool IsButtonJustDown(uint8_t jid, GamePadButtonCode btn);

		static void SetJoysticks(int id, int event);

		static void PrintJoysticksList();

	private:

		static void Input::DetectConnectedJoysticks();

	};
}