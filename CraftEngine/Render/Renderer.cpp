#include "Renderer.h"
#include "ScreenBuffer.h"
#include <cassert>
#include <Windows.h>
#include <iostream>

namespace Craft
{
	Renderer::Frame::Frame(int bufferCount)
	{
		// 2차원 글자 배열 및 그리기 순서 배열 객체 생성
		charInfoArray = std::make_unique<CHAR_INFO[]>(bufferCount);
		sortingOrderArray = std::make_unique<int[]>(bufferCount);
	}

	Renderer::Frame::~Frame()
	{
	}
	void Renderer::Frame::Clear(const Vector2& screenSize)
	{
		// 이중 루프를 순회하면서 값 정리
		const int width = screenSize.x;
		const int height = screenSize.y;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				// 2차원 배열 인덱스(x,y)를 1차원 인덱스로 변환
				const int index = (y * width) + x;

				// 글자 값 초기화
				CHAR_INFO& info = charInfoArray[index];
				info.Char.AsciiChar = ' ';
				info.Attributes = 0;

				// 그리기 순서 값 초기화
				sortingOrderArray[index] = -1;
			}
		}

	}

	// ---------------------------Frame-------------------------- //
	
	
	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer(const Vector2& screenSize)
		: screenSize(screenSize)
	{
		assert(!instance);
		instance = this;

		// 이중 버퍼에 사용할 버퍼 생성
		screenBufferArray[0] = std::make_unique<ScreenBuffer>(screenSize);
		screenBufferArray[0]->Clear();
		
		screenBufferArray[1] = std::make_unique<ScreenBuffer>(screenSize);
		screenBufferArray[1]->Clear();

		// 0번 콘솔 버퍼를 창에 설정
		SetConsoleActiveScreenBuffer(screenBufferArray[0]->GetScreenBuffer());

		// 프레임 생성
		const int bufferCount = screenSize.x * screenSize.y;
		frame = std::make_unique<Frame>(bufferCount);
		frame->Clear(screenSize);
	}

	Renderer::~Renderer()
	{
		instance = nullptr;

		// 콘솔창 원래대로 복구
		SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
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