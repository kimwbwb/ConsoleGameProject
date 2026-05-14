#pragma once

#include "Core/Core.h"
#include <Windows.h>

namespace Craft
{
	// 글자 색상을 나타내는 열거형
	enum class CRAFT_API Color : WORD
	{
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,
		Yellow = Red | Green,
		Cyan = Green | Blue,
		White = Red | Green | Blue,
		BrightWhite = White | FOREGROUND_INTENSITY,

	};
}