#include "Player.h"
#include "Core/Input.h"
#include <iostream>
#include <Windows.h>

using namespace Craft;

Player::Player(const Craft::Vector2& position)
	: Actor("P", position, Color::Green)
{
	sortingOrder = 5;
}

void Player::Tick(float deltaTime)
{
	//Actor::Tick(deltaTime);
	super::Tick(deltaTime);

	// ESC종료
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}

	// 방향키 이동
	if (Input::Get().GetKey(VK_LEFT) && position.x > 0)
	{
		position.x -= 1;
	}

	if (Input::Get().GetKey(VK_RIGHT) && position.x < 39)
	{
		position.x += 1;
	}

	if (Input::Get().GetKey(VK_UP) && position.y > 0)
	{
		position.y -= 1;
	}

	if (Input::Get().GetKey(VK_DOWN) && position.y < 24)
	{
		position.y += 1;
	}
}
