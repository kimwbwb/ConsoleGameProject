#include "Engine/Engine.h"
#include "Level/TestLevel.h"

using namespace Craft;

int main()
{
	Engine engine;
	engine.AddNewLevel<TestLevel>();
	engine.Run();
}