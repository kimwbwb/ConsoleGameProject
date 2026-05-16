#include "Engine.h"
#include "Level/Level.h"
#include "Core/Input.h"
#include "Render/Renderer.h"
#include <Windows.h>
#include <stdint.h>
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

// Ctrl + K + O
namespace Craft
{
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{
		assert(!instance);
		instance = this;

		// 엔진 설정 로드
		LoadEngineSetting();

		// 입력 객체 생성
		input = std::make_unique<Input>();

		// 렌더러 객체 생성
		renderer = std::make_unique<Renderer>(Vector2(setting.width, setting.height));
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
	void Engine::LoadEngineSetting()
	{
		// 엔진 설정 파일 열기
		std::ifstream file("../Config/Setting.txt");

		// 정상적으로 열렸는지 확인
		assert(file.is_open());

		// 라인(Line) 별로 읽기
		std::string line;
		while (std::getline(file, line))
		{
			// 빈 줄 및 주석 건너뛰기
			if (line.empty() || line[0] == '#')
				continue;

			// key = value 포맷 파싱
			const size_t equalPosition = line.find('=');

			// 라인 문자열에 = 문자가 있는지 확인
			assert(equalPosition != std::string::npos);

			// 좌/우 공백 제거용 람다.
			auto trim = [](std::string& s)
				{
					// 공백 문자 집합 (\r\n -> CRLF) \n(LF)
					// ' ' : 스페이스
					// \t : 탭
					// \r : 윈도우 개행문자 일자
					// \n : 개행 문자
					const char* whiteSpace = " \t\r\n";

					// 문자열의 앞에서부터 공백이 아닌 첫 문자 위치 검색
					const size_t begin = s.find_first_not_of(whiteSpace);

					// 공백이 아닌 문자를 못찾은 경우에는 빈 문자열로 설정 후 반환
					if (begin == std::string::npos)
					{
						s.clear();
						return;
					}

					// 문자열의 뒤에서부터 공백이 아닌 마지막 문자 위치 검색
					const size_t end = s.find_last_not_of(whiteSpace);
					
					s = s.substr(begin, end - begin + 1);
				};

			// key 파싱
			std::string key = line.substr(0, equalPosition);
			
			// value 파싱
			std::string value = line.substr(equalPosition+1);

			// key/value에서 공백 제거
			trim(key);
			trim(value);

			// key와 vlaue가 제대로 설정됐는지 확인
			assert(!key.empty() && !value.empty());

			// 속성 읽기

			// framerate
			if (key == "framerate")
			{
				setting.framerate = static_cast<float>(atof(value.c_str()));
				assert(setting.framerate > 0.0f);
				continue;
			}

			// width
			if (key == "width")
			{
				setting.width = static_cast<int>(atoi(value.c_str()));
				assert(setting.width > 0);
				continue;
			}

			// height
			if (key == "height")
			{
				setting.height = static_cast<int>(atoi(value.c_str()));
				assert(setting.height > 0);
			}
		}

		// 처리가 완료되면 파일 닫기
		file.close();
	}
}