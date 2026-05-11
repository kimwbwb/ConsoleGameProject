#include "TestLevel.h"
#include "Actor/TestActor.h"

void TestLevel::OnInitialized()
{
	Level::OnInitialized();

	// TestActor 레벨에 추가
	SpawnActor<TestActor>();
}
