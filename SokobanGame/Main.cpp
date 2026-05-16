#include "Engine/Engine.h"
#include "Level/TestLevel.h"

using namespace Craft;

int main()
{
	// RTTI : RunTime Type Information(실시간 타입 정보)
	// dynamic_cast

	Engine engine;
	engine.AddNewLevel<TestLevel>();
	engine.Run();
}