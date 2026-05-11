#include "Engine.h"
#include <Windows.h>
#include <stdint.h>
#include <iostream>
#include <cassert>

// Ctrl + K + O
namespace Craft
{
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{
		assert(!instance);
		instance = this;
	}
	Engine::~Engine()
	{
		instance = nullptr;
	}
	void Engine::Run()
	{
		// 윈도우즈가 제공하는 고해상도 타이머(하드웨어 타이머)
		
		// QueryPerformanceFrequency : 타이머의 해상도,
		// ex : ms(1/1000)해상도 = 1000
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		
		// 현재 시간 확인
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		
		// 프레임 시간 계산을 위한 변수
		int64_t currentTime = counter.QuadPart;
		int64_t previousTime = currentTime;
		
		// 프레임 고정.
		float oneFrameCount = 1.0f / setting.framerate;

		while (!isQuit)
		{
			// 입력 처리.
			ProcessInput();

			QueryPerformanceCounter(&counter);

			currentTime = counter.QuadPart;
			// 프레임 시간 계산.
			float deltaTime = static_cast<float>(currentTime - previousTime)
				/ static_cast<float>(frequency.QuadPart);

			if (deltaTime >= oneFrameCount)
			{
				// 레벨 초기화 이벤트 함수
				OnInitialized();

				// 레벨의 액터 초기화 이벤트 함수
				BeginPlay();

				// 레벨의 액터 업데이트 함수.
				Tick(deltaTime);
				// 업데이트된 결과를 화면에 그리는 함수.
				Draw();

				// 처리된 입력을 이전 프레임 입력으로 저장.
				SavePreviousInputStates();

				// 이전 프레임 시간 기록
				previousTime = currentTime;
			}
		}

		Shutdown();
	}

	void Engine::Quit()
	{
		isQuit = true;
	}

	Engine& Engine::Get()
	{
		assert(instance);

		return *instance;
	}

	void Engine::ProcessInput()
	{
	}

	void Engine::OnInitialized()
	{
	}

	void Engine::BeginPlay()
	{
	}

	void Engine::Tick(float deltaTime)
	{
		std::cout << "DeltaTime : " << deltaTime << " | FPS : " << (1.0f / deltaTime) << "\n";
	}

	void Engine::Draw()
	{

	}

	void Engine::SavePreviousInputStates()
	{
	}

	void Engine::Shutdown()
	{
	}
}