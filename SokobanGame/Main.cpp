#include "Game/Game.h"
#include <Windows.h>

using namespace Craft;

int main()
{
	// RTTI : RunTime Type Information(실시간 타입 정보)
	// dynamic_cast

	//Engine engine;
	//engine.AddNewLevel<GameLevel>();
	//engine.Run();

	// 창 제목 설정
	SetConsoleTitleA("Sokoban Game");

	Game game;
	game.Run();
	
}