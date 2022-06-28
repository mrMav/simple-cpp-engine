#pragma once

namespace Engine
{
	using GamePadButtonCode = uint16_t;

	namespace Button
	{
		enum : GamePadButtonCode
		{
			// From glfw3.h
			ButtonA         = 0,
			ButtonB         = 1,
			ButtonX         = 2,
			ButtonY         = 3,
			BumperLeft      = 4,
			BumperRight     = 5,
			Back            = 6,
			Start           = 7,
			Guide           = 8,
			ThumbLeft       = 9,
			ThumbRight      = 10,
			DPadUp          = 11,
			DPadRight       = 12,
			DPadDown        = 13,
			DPadLeft        = 14			
		};

	}
}
