#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "Internal.h"
#include "Input.h"
#include "Utils/Utils.h"

namespace Engine
{
	
	struct InputData
	{
		InputData() :
			GamePadStates(GLFW_JOYSTICK_LAST + 1), LastGamePadStates(GLFW_JOYSTICK_LAST + 1), CursorPosition({ 0, 0 }),
			MouseButtonStates(GLFW_MOUSE_BUTTON_3 + 1), LastMouseButtonStates(GLFW_MOUSE_BUTTON_3 + 1)
		{

		}

		GLFWwindow* Window = nullptr;

		/* Keyboard */
		std::bitset<GLFW_KEY_LAST + 1> LastFrameKeyMap;
		std::bitset<GLFW_KEY_LAST + 1> KeyMap;

		/* Joysticks */
		std::vector<uint8_t> Joysticks;
		std::vector<GLFWgamepadstate> LastGamePadStates;
		std::vector<GLFWgamepadstate> GamePadStates;

		/* Mouse */
		Cursor CursorPosition;
		std::vector<MouseCode> LastMouseButtonStates;
		std::vector<MouseCode> MouseButtonStates;

		float DeadZone = 0;
		float HalfDeadZone = 0;
	};

	static InputData s_InputData;

	/* glfw callbacks */

	void GLFWKeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		_ENGINE_PASS_OR_RETURN(key != GLFW_KEY_UNKNOWN);

		if (action > GLFW_RELEASE)
			s_InputData.KeyMap.set(key);
		else
			s_InputData.KeyMap.reset(key);
	}

	void GLFWJoystickCallback(int id, int event)
	{
		if (event == GLFW_CONNECTED)
		{
			if (!glfwJoystickIsGamepad(id))
			{
				_ENGINE_LOG("INPUT", "Joystick not supported! (no gamepad mapping support)") 
				return;
			}

			s_InputData.Joysticks.push_back(id);

			_ENGINE_LOG("INPUT", "Joystick connected!")

		}
		else if (event == GLFW_DISCONNECTED)
		{
			// https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
			s_InputData.Joysticks.erase(std::remove(s_InputData.Joysticks.begin(), s_InputData.Joysticks.end(), id), s_InputData.Joysticks.end());

			_ENGINE_LOG("INPUT", "Joystick disconnected!")
		}

		if (!glfwGetWindowAttrib(s_InputData.Window, GLFW_FOCUSED))
			glfwRequestWindowAttention(s_InputData.Window);
	}

	void GLFWCursorCallback(GLFWwindow* window, double xpos, double ypos)
	{
		s_InputData.CursorPosition.x = static_cast<uint32_t>(xpos);
		s_InputData.CursorPosition.y = static_cast<uint32_t>(ypos);

		//std::cout << m_InputData.CursorPosition.ToString() << std::endl;
	}

	void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		_ENGINE_PASS_OR_RETURN(button <= GLFW_MOUSE_BUTTON_3);

		s_InputData.MouseButtonStates[button] = action;
		
	}


	/* Input */

	void Input::Init(GLFWwindow* window)
	{	
		s_InputData.Window = window;

		/* wiring glfw callbacks */
		glfwSetKeyCallback(window, GLFWKeyInputCallback);
		glfwSetJoystickCallback(GLFWJoystickCallback);
		glfwSetCursorPosCallback(window, GLFWCursorCallback);
		glfwSetMouseButtonCallback(window, GLFWMouseButtonCallback);

		// Loading custom gamepad mappings
		std::ifstream file("gamepad_mappings.txt");
		if(file.good())
		{

			std::stringstream buffer;
			buffer << file.rdbuf();
			
			int success = glfwUpdateGamepadMappings(buffer.str().c_str());
			if(success == GLFW_FALSE)
			{
				_ENGINE_LOG("INPUT", "Could not set custom gamepad mappings.")
			} else
			{
				_ENGINE_LOG("INPUT", "Updated custom gamepad mappings!")
			}
			
		}

		DetectConnectedJoysticks();

	}

	void Input::PreUpdate()
	{
		int i = 0;
		for (const auto& jid : s_InputData.Joysticks)
		{			
			glfwGetGamepadState(jid, &(s_InputData.GamePadStates[i++]));			
		}
	}

	void Input::PostUpdate()
	{	
		// bitsets copy faster than vectors
		s_InputData.LastFrameKeyMap = std::bitset(s_InputData.KeyMap);

		s_InputData.LastGamePadStates = std::vector(s_InputData.GamePadStates);
		s_InputData.LastMouseButtonStates = std::vector(s_InputData.MouseButtonStates);
	}

	/* Keyboard */

	bool Input::IsKeyPressed(KeyCode key)
	{
		return s_InputData.KeyMap.test(key);
	}

	bool Input::IsKeyUp(KeyCode key)
	{
		return !s_InputData.KeyMap.test(key);
	}

	bool Input::IsKeyJustDown(KeyCode key)
	{
		return !(s_InputData.LastFrameKeyMap.test(key)) && s_InputData.KeyMap.test(key);
	}

	/* Joystick */

	/// <summary>
	/// Sets the thumbsticks dead zone
	/// </summary>
	/// <param name="jid">the controller id</param>
	/// <param name="zone">a number between 0 and 1 (inclusive)</param>
	void Input::SetDeadZone(int jid, float zone)
	{
		s_InputData.DeadZone     = zone;
		s_InputData.HalfDeadZone = zone / 2.0f;
	}

	bool Input::IsButtonPressed(uint8_t jid, GamePadButtonCode btn)
	{
		return s_InputData.GamePadStates[jid].buttons[btn] == GLFW_PRESS;
	}

	bool Input::IsButtonUp(uint8_t jid, GamePadButtonCode btn)
	{
		return s_InputData.GamePadStates[jid].buttons[btn] == GLFW_RELEASE;
	}

	bool Input::IsButtonJustDown(uint8_t jid, GamePadButtonCode btn)
	{
		return  s_InputData.LastGamePadStates[jid].buttons[btn] == GLFW_RELEASE &&
				s_InputData.GamePadStates[jid].buttons[btn]	    == GLFW_PRESS;
	}

	float Input::GetAxisStrength(uint8_t jid, GamePadAxisCode axis)
	{
		if (axis < GamePadAxis::GamePadAxisLeftTrigger)
		{
			return ApplyGamePadDeadZone(s_InputData.GamePadStates[jid].axes[axis]);
		}

		return s_InputData.GamePadStates[jid].axes[axis];
	}

	float Input::ApplyGamePadDeadZone(float v)
	{
		if (v > -s_InputData.HalfDeadZone && v < s_InputData.HalfDeadZone) return 0.0f;
		else return v;
	}

	void Input::DetectConnectedJoysticks()
	{
		for (uint8_t i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST + 1; i++)
		{
			if(glfwJoystickPresent(i))
				s_InputData.Joysticks.push_back(i);
		}
	}

	void Input::PrintJoysticksList()
	{
		std::string str;

		for (const auto& j : s_InputData.Joysticks)
		{
			str.append("id: " + std::to_string(j));
			str.append(" Name: ");
			str.append(glfwGetJoystickName(j));
			str.append("\n");
		}

		_ENGINE_LOG("INPUT", str)
	}

	/* Mouse */

	Cursor Input::GetCursorPosition()
	{
		return s_InputData.CursorPosition;
	}

	bool Input::IsMouseButtonPressed(MouseCode btn)
	{
		return s_InputData.MouseButtonStates[btn] == GLFW_PRESS;
	}
		 
	bool Input::IsMouseButtonJustDown(MouseCode btn)
	{
		return  s_InputData.LastMouseButtonStates[btn] == GLFW_RELEASE &&
				s_InputData.MouseButtonStates[btn] == GLFW_PRESS;
	}

	bool Input::IsMouseButtonUp(MouseCode btn)
	{
		return s_InputData.MouseButtonStates[btn] == GLFW_RELEASE;
	}



}