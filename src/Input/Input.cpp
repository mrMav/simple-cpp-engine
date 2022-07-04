#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

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

	static InputData m_InputData;

	/* glfw callbacks */

	void GLFWKeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		_ENGINE_PASS_OR_RETURN(key != GLFW_KEY_UNKNOWN);

		if (action > GLFW_RELEASE)
			m_InputData.KeyMap.set(key);
		else
			m_InputData.KeyMap.reset(key);
	}

	void GLFWJoystickCallback(int id, int event)
	{
		if (event == GLFW_CONNECTED)
		{
			if (!glfwJoystickIsGamepad(id))
			{
				_ENGINE_LOG("INPUT", "Joystick not supported! (not gamepad mapping support)")
					return;
			}

			m_InputData.Joysticks.push_back(id);

			_ENGINE_LOG("INPUT", "Joystick connected!")

		}
		else if (event == GLFW_DISCONNECTED)
		{
			// https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
			m_InputData.Joysticks.erase(std::remove(m_InputData.Joysticks.begin(), m_InputData.Joysticks.end(), id), m_InputData.Joysticks.end());

			_ENGINE_LOG("INPUT", "Joystick disconnected!")
		}

		if (!glfwGetWindowAttrib(m_InputData.Window, GLFW_FOCUSED))
			glfwRequestWindowAttention(m_InputData.Window);
	}

	void GLFWCursorCallback(GLFWwindow* window, double xpos, double ypos)
	{
		m_InputData.CursorPosition.x = static_cast<uint32_t>(xpos);
		m_InputData.CursorPosition.y = static_cast<uint32_t>(ypos);

		//std::cout << m_InputData.CursorPosition.ToString() << std::endl;
	}

	void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		_ENGINE_PASS_OR_RETURN(button <= GLFW_MOUSE_BUTTON_3);

		m_InputData.MouseButtonStates[button] = action;
		
	}


	/* Input */

	void Input::Init(GLFWwindow* window)
	{	
		m_InputData.Window = window;

		/* wiring glfw callbacks */
		glfwSetKeyCallback(window, GLFWKeyInputCallback);
		glfwSetJoystickCallback(GLFWJoystickCallback);
		glfwSetCursorPosCallback(window, GLFWCursorCallback);
		glfwSetMouseButtonCallback(window, GLFWMouseButtonCallback);

		DetectConnectedJoysticks();

	}

	void Input::PreUpdate()
	{
		int i = 0;
		for (const auto& jid : m_InputData.Joysticks)
		{			
			glfwGetGamepadState(jid, &(m_InputData.GamePadStates[i++]));			
		}
	}

	void Input::PostUpdate()
	{	
		// bitsets copy faster than vectors
		m_InputData.LastFrameKeyMap = std::bitset(m_InputData.KeyMap);

		m_InputData.LastGamePadStates = std::vector(m_InputData.GamePadStates);
		m_InputData.LastMouseButtonStates = std::vector(m_InputData.MouseButtonStates);
	}

	/* Keyboard */

	bool Input::IsKeyPressed(KeyCode key)
	{
		return m_InputData.KeyMap.test(key);
	}

	bool Input::IsKeyUp(KeyCode key)
	{
		return !m_InputData.KeyMap.test(key);
	}

	bool Input::IsKeyJustDown(KeyCode key)
	{
		return !(m_InputData.LastFrameKeyMap.test(key)) && m_InputData.KeyMap.test(key);
	}

	/* Joystick */

	/// <summary>
	/// Sets the thumbsticks dead zone
	/// </summary>
	/// <param name="jid">the controller id</param>
	/// <param name="zone">a number between 0 and 1 (inclusive)</param>
	void Input::SetDeadZone(int jid, float zone)
	{
		m_InputData.DeadZone     = zone;
		m_InputData.HalfDeadZone = zone / 2.0f;
	}

	bool Input::IsButtonPressed(uint8_t jid, GamePadButtonCode btn)
	{
		return m_InputData.GamePadStates[jid].buttons[btn] == GLFW_PRESS;
	}

	bool Input::IsButtonUp(uint8_t jid, GamePadButtonCode btn)
	{
		return m_InputData.GamePadStates[jid].buttons[btn] == GLFW_RELEASE;
	}

	bool Input::IsButtonJustDown(uint8_t jid, GamePadButtonCode btn)
	{
		return  m_InputData.LastGamePadStates[jid].buttons[btn] == GLFW_RELEASE &&
				m_InputData.GamePadStates[jid].buttons[btn]	    == GLFW_PRESS;
	}

	float Input::GetAxisStrength(uint8_t jid, GamePadAxisCode axis)
	{
		if (axis < GamePadAxis::GamePadAxisLeftTrigger)
		{
			return ApplyGamePadDeadZone(m_InputData.GamePadStates[jid].axes[axis]);
		}

		return m_InputData.GamePadStates[jid].axes[axis];
	}

	float Input::ApplyGamePadDeadZone(float v)
	{
		if (v > -m_InputData.HalfDeadZone && v < m_InputData.HalfDeadZone) return 0.0f;
		else return v;
	}

	void Input::DetectConnectedJoysticks()
	{
		for (uint8_t i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST + 1; i++)
		{
			if(glfwJoystickPresent(i))
				m_InputData.Joysticks.push_back(i);
		}
	}

	void Input::PrintJoysticksList()
	{
		std::string str;

		for (const auto& j : m_InputData.Joysticks)
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
		return m_InputData.CursorPosition;
	}

	bool Input::IsMouseButtonPressed(MouseCode btn)
	{
		return m_InputData.MouseButtonStates[btn] == GLFW_PRESS;
	}
		 
	bool Input::IsMouseButtonJustDown(MouseCode btn)
	{
		return  m_InputData.LastMouseButtonStates[btn] == GLFW_RELEASE &&
				m_InputData.MouseButtonStates[btn] == GLFW_PRESS;
	}

	bool Input::IsMouseButtonUp(MouseCode btn)
	{
		return m_InputData.MouseButtonStates[btn] == GLFW_RELEASE;
	}



}