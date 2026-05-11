#include "TestActor.h"
#include "Core/Input.h"
#include <iostream>
#include <Windows.h>

using namespace Craft;

void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	// ESCÁ¾·á
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}

	if (Input::Get().GetKeyDown('A'))
	{
		std::cout << "A Key is Down\n";
	}

	if (Input::Get().GetKey('A'))
	{
		std::cout << "A Key is Holding\n";
	}

	if (Input::Get().GetKeyUp('A'))
	{
		std::cout << "A Key is Up\n";
	}

	//std::cout <<
	//	"TestActor::Tick() - deltaTime : " << deltaTime << " | FPS : " << (1.0f / deltaTime) << "\n";
}
