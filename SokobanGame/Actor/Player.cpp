#include "Player.h"
#include "Player.h"
#include "Player.h"
#include "Core/Input.h"
#include "Game/Game.h"
#include "Interface/ICanPlayerMove.h"
#include "Level/Level.h"
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
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ToggleMenu();
	}

	// 인터페이스에 접근
	std::shared_ptr<ICanPlayerMove> canPlayerMove
		= std::dynamic_pointer_cast<ICanPlayerMove>(GetOwner());

	if (!canPlayerMove)
		return;

	// 방향키 이동
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		Vector2 newPosition = position;
		newPosition.x -= 1;

		if (canPlayerMove->CanMove(position, newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		Vector2 newPosition = position;
		newPosition.x += 1;
		if (canPlayerMove->CanMove(position, newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKeyDown(VK_UP))
	{
		Vector2 newPosition = position;
		newPosition.y -= 1;
		if (canPlayerMove->CanMove(position, newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		Vector2 newPosition = position;
		newPosition.y += 1;
		if (canPlayerMove->CanMove(position, newPosition))
		{
			SetPosition(newPosition);
		}
	}
}
