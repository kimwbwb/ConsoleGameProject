#include "Game.h"
#include "Level/GameLevel.h"
#include "Level/MenuLevel.h"

using namespace Craft;

Game::Game()
{
	// 두 레벨 생성 및 배열에 추가
	levelList.emplace_back(std::make_shared<GameLevel>());
	levelList.emplace_back(std::make_shared<MenuLevel>());

	// 시작 상태(레벨) 설정
	state = State::Menu;

	// 메인 레벨 설정
	mainLevel = levelList[static_cast<int>(state)];
}

void Game::ToggleMenu()
{
	// 다음 레벨 인덱스
	int stateIndex = static_cast<int>(state);
	int nextState = 1 - stateIndex;
	
	// 메인 레벨 설정
	mainLevel = levelList[nextState];
	
	// 상태 설정
	state = static_cast<State>(nextState);
}
