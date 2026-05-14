#pragma once

#include "Core/Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <vector>
#include <string>

namespace Craft
{
	// 화면에 그리는 기능을 제공
	class CRAFT_API Renderer
	{
		// 화면에 그릴 데이터를 명령으로 모아둘 구조체
		struct RenderCommand
		{
			// 화면에 그릴 글자 값.
			std::string image;

			// 위치.
			Vector2 position;

			// 색상.
			Color color = Color::White;

			// 그리기 정렬 순서.
			int sortOrder = -1;
		};

	public:
		Renderer();
		~Renderer();

		// 장면을 구성하는 모든 객체(액터)가 화면에 그릴 데이터를 전달하는 함수.
		void Submit(const std::string& image, Vector2 position, Color color = Color::White, int sortOrder = 0);

		// Draw 이벤트 함수(Engine에서 호출).
		void Draw();

		// 전역 접근 함수
		static Renderer& Get();

	private:
		// 프레임을 시작할 떄 화면을 지우는 함수.
		void Clear();

		// 전달 받은 그리기 명령을 활용해 그리는 함수
		void DrawRenderQueue();

		// 이중 버퍼 구현 시 버퍼를 교환하는 함수.
		void Present();

	private:
		// 싱글톤 구현을 위한 전역 변수
		static Renderer* instance;

		// 이번 프레임에 화명네 그릴 데이터를 모아둔 동적 배열(큐).
		std::vector<RenderCommand> renderQueue;
	};
}
