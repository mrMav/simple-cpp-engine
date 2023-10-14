/*

	This include file should contain all includes from the Engine framework

*/
#pragma once

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"
#include "OpenGL/GLUtils.h"
#include "OpenGL/ShaderAttributes.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/FrameBufferAttachment.h"

#include "Render/Viewport.h"
#include "Render/Camera2D.h"
#include "Render/Spritebatch.h"

#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/GamePadButtonCodes.h"

#include "Utils/Utils.h"
#include "Utils/Rectangle.h"

#include "Systems/StateManager.h"
#include "Systems/FrameAnimation.h"
#include "Systems/TileSet.h"

#include "Game.h"
#include "Timer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
