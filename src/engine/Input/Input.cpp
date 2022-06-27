
#include <iostream>

#include "Input.h"
#include "Utils/Utils.h"


namespace Engine
{
	std::bitset<GLFW_KEY_LAST> Input::m_LastFrameKeyMap;
	std::bitset<GLFW_KEY_LAST> Input::m_KeyMap;

	void GLFWKeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Input::SetMap(key, scancode, action, mods);
	}

	void Input::Init(GLFWwindow* window)
	{		
		glfwSetKeyCallback(window, GLFWKeyInputCallback);
	}

	void Input::Update()
	{
		m_LastFrameKeyMap = std::bitset(m_KeyMap);
	}

	void Input::SetMap(int key, int scancode, int action, int mods)
	{
		if (action > GLFW_RELEASE)
			m_KeyMap.set(key);
		else
			m_KeyMap.reset(key);
	}

	bool Input::IsKeyPressed(KeyCode key)
	{
		return m_KeyMap.test(key);
	}

	bool Input::IsKeyUp(KeyCode key)
	{
		return !m_KeyMap.test(key);
	}

	bool Input::IsKeyJustDown(KeyCode key)
	{
		return !(m_LastFrameKeyMap.test(key)) && m_KeyMap.test(key);
	}

}