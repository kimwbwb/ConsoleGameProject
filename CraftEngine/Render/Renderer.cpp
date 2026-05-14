#include "Renderer.h"
#include <cassert>
#include <Windows.h>
#include <iostream>

namespace Craft
{
	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer()
	{
		assert(!instance);
		instance = this;

		// 콘솔 커서 안보이게 설정
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 1;
		info.bVisible = false;
		SetConsoleCursorInfo((GetStdHandle(STD_OUTPUT_HANDLE)), &info);

	}

	Renderer::~Renderer()
	{
		instance = nullptr;

		// 콘솔 커서 안보이게 설정
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 1;
		info.bVisible = true;
		SetConsoleCursorInfo((GetStdHandle(STD_OUTPUT_HANDLE)), &info);
	}

	void Renderer::Submit(const std::string& image, Vector2 position, Color color, int sortOrder)
	{
		// 그릴 명령 객체 생성
		RenderCommand command;
		command.image = image;
		command.position = position;
		command.color = color;
		command.sortOrder = sortOrder;

		// 렌더 큐에 명령 추가
		renderQueue.emplace_back(command);
	}

	void Renderer::Draw()
	{
		// 화면 지우기
		Clear();
		// 프레임 그리기
		DrawRenderQueue();
		// 버퍼 교환(이중버퍼)
		Present();
	}

	Renderer& Renderer::Get()
	{
		assert(instance);
		return *instance;
	}

	void Renderer::Clear()
	{
		// 화면 지우는 콘솔 명령어 실행
		system("cls");
	}

	void Renderer::DrawRenderQueue()
	{
		// 렌더 큐 순회
		for (const RenderCommand& command : renderQueue)
		{
			// Todo : 이중 버퍼 구현 시 그리기 순서를 비교해 그릴 지 여부 판단

			// 콘솔 좌표 이동
			COORD coord;
			coord.X = static_cast<short>(command.position.x);
			coord.Y = static_cast<short>(command.position.y);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

			// 색상 지정
			SetConsoleTextAttribute(
				GetStdHandle(STD_OUTPUT_HANDLE),
				static_cast<WORD>(command.color)
			);
			// 그리기 (글자 값)
			std::cout << command.image;
			// 콘솔 색상 되돌리기
			SetConsoleTextAttribute(
				GetStdHandle(STD_OUTPUT_HANDLE),
				static_cast<WORD>(Color::White)
			);

		}

		// 렌더 큐 비우기
		renderQueue.clear();
	}

	void Renderer::Present()
	{
		// Todo : 이중 버퍼 구현 시 사용
	}
}