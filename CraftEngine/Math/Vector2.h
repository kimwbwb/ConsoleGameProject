#pragma once

#include "Core/Core.h"

namespace Craft
{
	// 2차원 벡터 클래스
	class CRAFT_API Vector2
	{
	public:
		Vector2(int x = 0, int y = 0);
		~Vector2();

		// 연산자 오버로딩
		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator*(const Vector2& other) const;
		Vector2 operator*(float value) const;
		Vector2 operator/(const Vector2& other) const;

		// 대입 연산자 오버로딩
		Vector2& operator=(const Vector2& other);

		// 비교 연산자 오버로딩
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;

	public:
		// x 좌표
		int x = 0;

		// y 좌표
		int y = 0;

		// 자주 사용할만한 값을 전역변수로 선언
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;
	};
}
