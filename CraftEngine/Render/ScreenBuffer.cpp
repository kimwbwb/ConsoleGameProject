#include "ScreenBuffer.h"
#include <cassert>

namespace Craft
{
	ScreenBuffer::ScreenBuffer(const Vector2& screenSize)
		:screenSize(screenSize)
	{
		// 콘솔 버퍼 생성
		screenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			nullptr,
			CONSOLE_TEXTMODE_BUFFER,
			nullptr
		);

		// 제대로 생성됐는지 확인
		assert(screenBuffer != INVALID_HANDLE_VALUE);

		// 화면 창 크기 설정
		SMALL_RECT rect = {};
		rect.Top = 0;
		rect.Left = 0;
		rect.Right = static_cast<short>(screenSize.x - 1);
		rect.Bottom = static_cast<short>(screenSize.y - 1);
		BOOL result = SetConsoleWindowInfo(screenBuffer, TRUE, &rect);

		// 창 크기 설정 확인
		assert(result);

		// 화면 버퍼 크기 설정 및 예외처리
		COORD coord = {};
		coord.X = static_cast<short>(screenSize.x);
		coord.Y = static_cast<short>(screenSize.y);
		result = SetConsoleScreenBufferSize(screenBuffer, coord);

		assert(result);

		// 커서 끄기(커서 깜빡임 방지).
		CONSOLE_CURSOR_INFO info;
		GetConsoleCursorInfo(screenBuffer, &info);

		info.bVisible = FALSE;
		SetConsoleCursorInfo(screenBuffer, &info);
	}

	ScreenBuffer::~ScreenBuffer()
	{
		// 버퍼 해제
		if (screenBuffer)
		{
			CloseHandle(screenBuffer);
		}
	}

	void ScreenBuffer::Clear() const
	{
	}

	void ScreenBuffer::Draw(const CHAR_INFO* const charInfo) const
	{
	}
}