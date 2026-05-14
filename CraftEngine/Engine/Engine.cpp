#include "Engine.h"
#include "Level/Level.h"
#include "Core/Input.h"
#include "Render/Renderer.h"
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

		// 입력 객체 생성
		input = std::make_unique<Input>();

		// 렌더러 객체 생성
		renderer = std::make_unique<Renderer>();
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

				// 레벨 전환 처리
				if (nextLevel)
				{
					// 기존 레벨 정리.
					if (mainLevel)
					{
						mainLevel.reset();
					}

					// 이전 프레임에 전환 요청된 레벨을 메인 레벨로 설정.
					mainLevel = std::move(nextLevel);

					// 정리.
					nextLevel.reset();
				}

				// 레벨 정리
				if (mainLevel)
				{
					mainLevel->ProcessAddAndDestroyActors();
				}

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
		assert(input);

		// 입력 처리함수 호출
		input->ProcessInput();
	}


	void Engine::OnInitialized()
	{

		// 레벨에 이벤트 전달
		if (!mainLevel)
		{
			return;
		}

		// 레벨이 이미 초기화되있으면 처리 안함.
		if (mainLevel->HasInitialized())
		{
			return;
		}

		mainLevel->OnInitialized();
	}

	void Engine::BeginPlay()
	{
		// 레벨에 이벤트 전달
		if (!mainLevel)
		{
			return;
		}

		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{
		//std::cout << "DeltaTime : " << deltaTime << " | FPS : " << (1.0f / deltaTime) << "\n";
		// 레벨에 이벤트 전달
		if (!mainLevel)
		{
			return;
		}

		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		// 레벨에 이벤트 전달
		if (!mainLevel)
		{
			return;
		}

		mainLevel->Draw();

		// 렌더러에 Draw 이벤트 전달(호출)
		renderer->Draw();
	}

	void Engine::SavePreviousInputStates()
	{
		assert(input);

		input->SavePreviousStates();
	}

	void Engine::Shutdown()
	{
	}
}